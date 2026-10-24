import copy
import unittest

import numpy as np
from types import SimpleNamespace

from opendbc.car import Bus, structs
from opendbc.car.rivian.ext_controller import ExternalController, MIN_TORQUE_FRAMES, HANDS_OFF_EXIT_FRAMES
from opendbc.car.rivian.fingerprints import FW_VERSIONS
from opendbc.car.rivian.interface import CarInterface
from opendbc.car.rivian.values import CAR, CarControllerParams, FW_QUERY_CONFIG, WMI, ModelLine, ModelYear

GearShifter = structs.CarState.GearShifter


class TestRivian(unittest.TestCase):
  def test_custom_fuzzy_fingerprinting(self):
    for platform in CAR:
      with self.subTest(platform=platform.name):
        for wmi in WMI:
          for line in ModelLine:
            for year in ModelYear:
              for bad in (True, False):
                vin = ["0"] * 17
                vin[:3] = wmi
                vin[3] = line.value
                vin[9] = year.value
                if bad:
                  vin[3] = "Z"
                vin = "".join(vin)

                matches = FW_QUERY_CONFIG.match_fw_to_car_fuzzy({}, vin, FW_VERSIONS)
                should_match = year in platform.config.years and not bad
                assert (matches == {platform}) == should_match, "Bad match"


class TestExternalControllerForceTorque(unittest.TestCase):
  @staticmethod
  def _run(erc, frames, lat_active=True):
    actuators = SimpleNamespace(steeringAngleDeg=0.0, torque=0.3)
    states = []
    for _ in range(frames):
      # hands off, wheel settled on the commanded angle; the EPAS reports ready, then active once it is steering on angle
      out = SimpleNamespace(steeringAngleDeg=0.0, steeringRateDeg=0.0, steeringTorque=0.0, steeringPressed=False,
                            vEgo=25.0, vEgoRaw=25.0, aEgo=0.0)
      CS = SimpleNamespace(out=out, hands_on_level=0, eac_status=2 if erc.angle_active else 1, eac_error_code=0,
                           sccm_wheel_touch={"SCCM_WheelTouch_Calibration": 1000, "SCCM_WheelTouch_CapacitiveValue": 0})
      erc.update(CS, lat_active, actuators)
      states.append((erc.torque_active, erc.angle_active, erc.apply_torque_last))
    return states

  def test_default_steers_on_angle(self):
    erc = ExternalController()
    assert not erc.force_torque
    for torque_active, angle_active, apply_torque in self._run(erc, 300):
      assert not torque_active and angle_active and apply_torque == 0

  def test_force_torque_never_hands_back(self):
    erc = ExternalController()
    erc.force_torque = True
    # well past every hand-back condition: hands off, EPAS ready, wheel settled on the commanded angle
    states = self._run(erc, 4 * (MIN_TORQUE_FRAMES + HANDS_OFF_EXIT_FRAMES))
    for torque_active, angle_active, _ in states:
      assert torque_active and not angle_active
    assert states[-1][2] > 0 and erc.toi_act_cmd

    # lateral off: everything idle, same as the normal mode
    for torque_active, angle_active, apply_torque in self._run(erc, 5, lat_active=False):
      assert not torque_active and not angle_active and apply_torque == 0
    assert not erc.toi_act_cmd


class TestBlockedEngagePress(unittest.TestCase):
  """The ACC stalk is also the gear selector: only a stalk-down in Drive may be reported as a blocked ACC press."""

  @staticmethod
  def _run(seq, engageable=False):
    # seq: (gear, VDM_UserAdasRequest) per frame. Returns the frames that raised engage_request_blocked.
    CP = CarInterface.get_non_essential_params(CAR.RIVIAN_R1)
    CP.openpilotLongitudinalControl = True
    CI = CarInterface(CP, structs.CarParamsSP())
    CC, CS = CI.CC, CI.CS
    CC.openpilot_engageable = engageable
    CS.acm_lka_hba_cmd = copy.copy(CI.can_parsers[Bus.cam].vl["ACM_lkaHbaCmd"])
    CS.sccm_wheel_touch = copy.copy(CI.can_parsers[Bus.pt].vl["SCCM_WheelTouch"])
    adas_status = copy.copy(CI.can_parsers[Bus.pt].vl["VDM_AdasSts"])
    car_control = structs.CarControl().as_reader()

    raised = []
    for frame, (gear, request) in enumerate(seq):
      CS.out = structs.CarState(gearShifter=gear, vEgo=0.3, vEgoRaw=0.3)
      CS.vdm_adas_status = [dict(adas_status, VDM_UserAdasRequest=request)]
      CC.update(car_control, structs.CarControlSP(), CS, 0)
      if CC.engage_request_blocked:
        raised.append(frame)
        CC.engage_request_blocked = False
    return raised

  def test_gear_changes_are_not_engage_presses(self):
    D, R, P = GearShifter.drive, GearShifter.reverse, GearShifter.park
    self.assertEqual(self._run([(D, 0), (D, 2), (R, 2), (R, 0)]), [])  # D -> R, stalk up
    self.assertEqual(self._run([(R, 0), (R, 4), (D, 4), (D, 0)]), [])  # R -> D, stalk down
    self.assertEqual(self._run([(P, 0), (P, 3), (D, 3), (D, 4), (D, 0)]), [])  # P -> D
    self.assertEqual(self._run([(D, 0), (D, 1), (D, 0)]), [])  # cancel

  def test_acc_press_in_drive_is_reported(self):
    D = GearShifter.drive
    self.assertEqual(self._run([(D, 0), (D, 3), (D, 4), (D, 0)]), [1])
    self.assertEqual(self._run([(D, 0), (D, 4), (D, 0), (D, 4), (D, 0)]), [1, 3])
    # openpilot can engage: the press goes to the ACM, nothing to report
    self.assertEqual(self._run([(D, 0), (D, 4), (D, 0)], engageable=True), [])


class _FakeErc:
  """Stands in for ExternalController: angle_active follows a schedule (or lat_active)."""
  def __init__(self, schedule=None):
    self.schedule, self.frame, self.lat_seen = schedule, 0, []
    self.apply_torque_last, self.apply_angle_last, self.toi_act_cmd, self.force_torque = 0, 0.0, False, False
    self.angle_active = self.torque_active = False

  def update(self, CS, lat_active, actuators):
    self.lat_seen.append(lat_active)
    self.angle_active = self.schedule(self.frame) if self.schedule else lat_active
    self.torque_active = lat_active and not self.angle_active
    self.frame += 1


def _run_steer(frames, schedule=None):
  """Runs the CarController; returns (per-frame [(addr, dat)] for 0x100/0x110/0x120, the fake erc)."""
  CP = CarInterface.get_non_essential_params(CAR.RIVIAN_R1)
  CI = CarInterface(CP, structs.CarParamsSP())
  CC, CS = CI.CC, CI.CS
  CC.erc = _FakeErc(schedule)
  CS.acm_lka_hba_cmd = copy.copy(CI.can_parsers[Bus.cam].vl["ACM_lkaHbaCmd"])
  CS.sccm_wheel_touch = copy.copy(CI.can_parsers[Bus.pt].vl["SCCM_WheelTouch"])
  CS.vdm_adas_status = []
  car_control = structs.CarControl().as_reader()
  out = []
  for _ in range(frames):
    CS.out = structs.CarState(gearShifter=GearShifter.drive, vEgo=20.0, vEgoRaw=20.0)
    _, can_sends = CC.update(car_control, structs.CarControlSP(), CS, 0)
    out.append([(addr, dat) for addr, dat, _ in can_sends if addr in (0x100, 0x110, 0x120)])
  return out, CC.erc


def _eac_enabled(dat):
  return (dat[1] >> 4) & 0x3


class TestSteer50Hz(unittest.TestCase):
  def test_rate_and_counter(self):
    out, _ = _run_steer(40)
    sent = [(f, dict(m)[0x110][1] & 0x0F) for f, m in enumerate(out) if 0x110 in dict(m)]
    assert sent == [(f, (f // 2) % 15) for f in range(0, 40, 2)]  # 50 Hz, counter +1 per message sent
    for addr in (0x100, 0x120):  # ACM_Status and ACM_lkaHbaCmd stay at 100 Hz
      assert all(addr in dict(m) for m in out)

  def test_mode_change_on_off_frame(self):
    # route 0000014e: a takeover on an odd frame changed ACM_Status FeatureStatus while the last 0x110 still had
    # EacEnabled set -> EPAS Feature_Status_Invalid (latched). 0x110 must go out on that frame, before ACM_Status.
    for schedule, switch in ((lambda f: f < 7, 7), (lambda f: f >= 9, 9)):  # takeover, hand back
      out, _ = _run_steer(20, schedule=schedule)
      addrs = [a for a, _ in out[switch]]
      assert 0x110 in addrs and addrs.index(0x110) < addrs.index(0x100)
      assert _eac_enabled(dict(out[switch])[0x110]) == int(schedule(switch))
      counters = [dict(m)[0x110][1] & 0x0F for m in out if 0x110 in dict(m)]
      assert counters == [i % 15 for i in range(len(counters))]


class TestSteer50HzWithinPandaLimits(unittest.TestCase):
  """Every other frame of the angle controller's output, under maximum demand, stays inside the panda's per-message
  jerk limit at 50 Hz (safety/lateral.h steer_angle_cmd_checks_vm)."""

  def test_max_demand(self):
    import math
    for speed in (5.0, 10.0, 20.0, 30.0):
      erc = ExternalController()
      sent = []
      for frame in range(400):
        desired = 400.0 if (frame // 100) % 2 == 0 else -400.0
        out = SimpleNamespace(steeringAngleDeg=erc.apply_angle_last, steeringRateDeg=0.0, steeringTorque=0.0,
                              steeringPressed=False, vEgo=speed, vEgoRaw=speed, aEgo=0.0)
        CS = SimpleNamespace(out=out, hands_on_level=0, eac_status=2 if erc.angle_active else 1, eac_error_code=0,
                             sccm_wheel_touch={"SCCM_WheelTouch_Calibration": 1000, "SCCM_WheelTouch_CapacitiveValue": 0})
        erc.update(CS, True, SimpleNamespace(steeringAngleDeg=desired, torque=0.0))
        if frame % 2 == 0:
          sent.append(round(erc.apply_angle_last * 10))
      v = max(speed - 1.0, 1.0)  # panda: fudged speed, float32, int(delta * 10 + 1)
      rate = math.degrees(erc.VM_safety.get_steer_from_curvature(CarControllerParams.ANGLE_LIMITS.MAX_LATERAL_JERK / v ** 2, v, 0))
      limit = int(np.float32(rate) / np.float32(50) * 10 + 1)
      assert max(abs(b - a) for a, b in zip(sent, sent[1:], strict=False)) <= limit, speed
