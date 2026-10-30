from types import SimpleNamespace

import pytest

from openpilot.common.constants import CV
from openpilot.common.params import Params
from openpilot.common.realtime import DT_MDL
from openpilot.sunnypilot.selfdrive.controls.lib.set_speed_assist import MAX_BOOST, RAMP_UP, SetSpeedAssist


def run(ssa, frames, a_e2e=0.1, a_cruise=1.2, v_mph=40., should_stop=False, curvature=0., enabled=True):
  sm = {'carState': SimpleNamespace(vEgo=v_mph * CV.MPH_TO_MS), 'selfdriveState': SimpleNamespace(enabled=enabled),
        'modelV2': SimpleNamespace(action=SimpleNamespace(shouldStop=should_stop, desiredCurvature=curvature))}
  return [ssa.update(sm, a_e2e, a_cruise, 60 * CV.MPH_TO_MS) for _ in range(frames)][-1]


@pytest.mark.parametrize("on", [True, False])
def test_ramps_to_the_cap_under_cruise(on):
  Params().put_bool("SetSpeedAssist", on)
  ssa = SetSpeedAssist()
  assert run(ssa, 1) == pytest.approx(0.1 + RAMP_UP * DT_MDL * on)
  assert run(ssa, 100) == pytest.approx(0.1 + MAX_BOOST * on)
  assert run(ssa, 100, a_cruise=0.5) == pytest.approx(0.5 if on else 0.1)  # never above the cruise ramp


@pytest.mark.parametrize("kw, at_once", [({"a_e2e": -0.5}, True), ({"a_e2e": -0.15}, True), ({"should_stop": True}, True), ({"v_mph": 15.}, False),
                                         ({"v_mph": 59.}, False), ({"curvature": 0.01}, False), ({"enabled": False}, False)])
def test_backs_off(kw, at_once):
  Params().put_bool("SetSpeedAssist", True)
  ssa = SetSpeedAssist()
  run(ssa, 100)
  a_e2e = kw.get("a_e2e", 0.1)
  assert (run(ssa, 1, **kw) == pytest.approx(a_e2e)) == at_once
  assert run(ssa, 100, **kw) == pytest.approx(a_e2e)
