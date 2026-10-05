import unittest
from types import SimpleNamespace

from opendbc.car.rivian.ext_controller import ExternalController, MIN_TORQUE_FRAMES, HANDS_OFF_EXIT_FRAMES
from opendbc.car.rivian.fingerprints import FW_VERSIONS
from opendbc.car.rivian.values import CAR, FW_QUERY_CONFIG, WMI, ModelLine, ModelYear


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
