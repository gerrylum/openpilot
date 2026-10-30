import numpy as np

from openpilot.common.constants import CV
from openpilot.common.params import Params
from openpilot.common.realtime import DT_MDL

MAX_BOOST = 0.7  # m/s^2 above the model
MIN_SPEED, MIN_DEFICIT = 20 * CV.MPH_TO_MS, 2 * CV.MPH_TO_MS
MAX_LAT_ACCEL = 1.0  # m/s^2, off in turns
MODEL_SLOWING, MODEL_BRAKING = -0.1, -0.3  # m/s^2
RAMP_UP, RAMP_DOWN = 0.5, 1.5  # m/s^3


class SetSpeedAssist:
  """Raises only the model's accel toward the cruise ramp. Lead MPC and cruise stay in the planner's min(), and model braking wins."""
  def __init__(self):
    self.params, self.enabled, self.frame, self.boost = Params(), False, 0, 0.

  def update(self, sm, a_e2e: float, a_cruise: float, v_cruise: float) -> float:
    if self.frame % int(1. / DT_MDL) == 0:
      self.enabled = self.params.get_bool("SetSpeedAssist")
    self.frame += 1

    v, action = sm['carState'].vEgo, sm['modelV2'].action
    if a_e2e < MODEL_BRAKING or action.shouldStop:
      self.boost = 0.
    else:
      active = (self.enabled and sm['selfdriveState'].enabled and a_e2e >= MODEL_SLOWING and v > MIN_SPEED and v_cruise - v > MIN_DEFICIT
                and abs(action.desiredCurvature) * v ** 2 < MAX_LAT_ACCEL)
      target = float(np.clip(a_cruise - a_e2e, 0., MAX_BOOST)) if active else 0.
      self.boost = float(np.clip(target, self.boost - RAMP_DOWN * DT_MDL, self.boost + RAMP_UP * DT_MDL))
    return a_e2e + self.boost
