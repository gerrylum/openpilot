"""
Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.

This file is part of sunnypilot and is licensed under the MIT License.
See the LICENSE.md file in the root directory for more details.
"""
import math

from openpilot.common.params import Params

PARAMS_READ_FRAMES = 300  # ~15s at 20Hz, matches LatControlTorqueExtOverride's polling cadence


class RivianOfftrackCompensation:
  """
  Rear-axle off-tracking compensation for long-wheelbase Rivians (R1T).

  On a tight turn, the rear axle cuts inside the path the front axle takes -
  the tighter the turn and the longer the wheelbase, the bigger the gap
  (see wheelbase-offtracking-plan.md). openpilot's driving model has no
  concept of vehicle geometry, so it can command the same curvature for an
  R1T that it would for a sedan, letting the rear wheels clip a curb the
  front cleared comfortably. This widens the commanded curvature (never
  tightens it) by a wheelbase- and radius-dependent amount, scaled by a
  user-tunable gain (0 = off, 1 = full geometric compensation) that is
  adjustable from the sunnylink dashboard: RivianOfftrackCompensationEnabled
  / RivianOfftrackCompensationGain (offroad only).

  This is a geometric prior, not curb sensing: it doesn't know where the
  actual curb is, so start with a conservative gain and validate on logged
  routes before trusting it.
  """

  def __init__(self, params: Params):
    self.params = params
    self.enabled = self.params.get_bool("RivianOfftrackCompensationEnabled")
    self.gain = float(self.params.get("RivianOfftrackCompensationGain", return_default=True))
    self.frame = -1

  def _update_params(self):
    self.frame += 1
    if self.frame % PARAMS_READ_FRAMES == 0:
      self.enabled = self.params.get_bool("RivianOfftrackCompensationEnabled")
      self.gain = float(self.params.get("RivianOfftrackCompensationGain", return_default=True))

  def apply(self, curvature: float, wheelbase: float) -> float:
    self._update_params()
    if not self.enabled or self.gain <= 0. or abs(curvature) < 1e-4:
      return curvature

    radius = 1.0 / abs(curvature)
    if radius <= wheelbase:
      return curvature  # at/near the geometric turning limit; leave clip_curvature's MAX_CURVATURE to handle it

    off_track = radius - math.sqrt(radius ** 2 - wheelbase ** 2)  # rear-axle cut-in at this radius
    compensated_radius = radius + self.gain * off_track
    return math.copysign(1.0 / compensated_radius, curvature)
