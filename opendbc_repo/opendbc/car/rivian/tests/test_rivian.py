import copy
import unittest

from opendbc.car import Bus, structs
from opendbc.car.rivian.fingerprints import FW_VERSIONS
from opendbc.car.rivian.interface import CarInterface
from opendbc.car.rivian.values import CAR, FW_QUERY_CONFIG, WMI, ModelLine, ModelYear

GearShifter = structs.CarState.GearShifter
D, R, P = GearShifter.drive, GearShifter.reverse, GearShifter.park


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


class TestEngageFeedback(unittest.TestCase):
  @staticmethod
  def _run(seq, engageable=False, v_ego=0.3, cruise=False, acm_fault=0):
    # seq: (gear, VDM_UserAdasRequest) per frame. Returns (frame, engage_feedback) for each feedback raised.
    CP = CarInterface.get_non_essential_params(CAR.RIVIAN_R1)
    CP.openpilotLongitudinalControl = True
    CI = CarInterface(CP, structs.CarParamsSP())
    CC, CS = CI.CC, CI.CS
    CC.openpilot_engageable = engageable
    CS.acm_lka_hba_cmd = copy.copy(CI.can_parsers[Bus.cam].vl["ACM_lkaHbaCmd"])
    CS.sccm_wheel_touch = copy.copy(CI.can_parsers[Bus.pt].vl["SCCM_WheelTouch"])
    CS.acm_fault_supervisor_state = acm_fault
    adas_status = copy.copy(CI.can_parsers[Bus.pt].vl["VDM_AdasSts"])
    raised = []
    for frame, (gear, request) in enumerate(seq):
      CS.out = structs.CarState(gearShifter=gear, vEgo=v_ego, vEgoRaw=v_ego, cruiseState={"enabled": cruise})
      CS.vdm_adas_status = [dict(adas_status, VDM_UserAdasRequest=request)]
      CC.update(structs.CarControl().as_reader(), structs.CarControlSP(), CS, 0)
      if CC.engage_feedback:
        raised.append((frame, CC.engage_feedback))
        CC.engage_feedback = None
    return raised

  def test_gear_changes_are_not_acc_presses(self):
    assert self._run([(D, 0), (D, 2), (R, 2), (R, 0)]) == []  # D -> R, stalk up
    assert self._run([(R, 0), (R, 4), (D, 4), (D, 0)]) == []  # R -> D, stalk down
    assert self._run([(P, 0), (P, 3), (D, 3), (D, 4), (D, 0)]) == []  # P -> D
    assert self._run([(D, 0), (D, 1), (D, 0)]) == []  # cancel

  def test_blocked_press_in_drive(self):
    assert self._run([(D, 0), (D, 3), (D, 4), (D, 0)]) == [(1, 'blocked')]
    assert self._run([(D, 0), (D, 4), (D, 0), (D, 4), (D, 0)]) == [(1, 'blocked'), (3, 'blocked')]

  def test_acm_declined_press(self):
    press = [(D, 0), (D, 4)] + [(D, 0)] * 60
    assert self._run(press, engageable=True) == [(50, 'lowSpeed')]
    assert self._run(press, engageable=True, acm_fault=1) == [(50, 'notReady')]
    assert self._run(press, engageable=True, v_ego=15.) == []  # fast enough, the ACM gave no reason we know
    assert self._run(press, engageable=True, cruise=True) == []  # the ACM took it
