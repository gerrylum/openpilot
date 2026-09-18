#!/usr/bin/env python3
"""
Diagnostic (not a patch): compares panda's hardcoded C slip_factor constant
against what Python's own VehicleModel computes for the current CarSpecs.

Context: after fixing rivian.h's wheelbase 3.08 -> 3.45, test_rivian.py's
test_lateral_accel_limit / test_lateral_jerk_limit went from failing "at the
boundary" (expected) to failing "just above the boundary" (unexpected) --
C is now accepting angle commands 1 CAN unit (0.1 deg) past where Python's
own reference VM says the limit should be.

Likely cause: panda's RIVIAN_ANGLE_STEERING_PARAMS.slip_factor is a single
hardcoded constant approximating the real physics-based slip factor that
Python's VehicleModel computes dynamically from CarSpecs (mass, wheelbase,
centerToFront, tire stiffness front/rear -- see calc_slip_factor() in
opendbc/car/vehicle_model.py). That constant was presumably originally
fit/computed using the OLD wheelbase (3.08) and whatever centerToFront paired
with it at the time. Wheelbase alone changing to 3.45 (correct) without also
updating slip_factor to match leaves the C-side "physics" self-inconsistent
with what Python computes for the same CarSpecs -- a small enough mismatch
(shown only at the ~0.1deg boundary) that it didn't matter when 3.08 already
had a huge margin, but does now.

This script just PRINTS the correct value -- it doesn't patch anything, since
we want to see the actual number first before deciding what to hardcode.

Run from repo root (~/openpilot), with the venv active:
    source .venv/bin/activate
    python3 check_slip_factor_mismatch.py
"""
import sys

sys.path.insert(0, "opendbc_repo")
from opendbc.car.rivian.ext_controller import get_safety_CP  # noqa: E402
from opendbc.car.vehicle_model import VehicleModel, calc_slip_factor  # noqa: E402


def main():
    CP = get_safety_CP()
    print("CarParams used to build the Python reference VM (from CarInterface.get_non_essential_params):")
    print(f"  wheelbase:          {CP.wheelbase}")
    print(f"  centerToFront:      {CP.centerToFront}")
    print(f"  mass:               {CP.mass}")
    print(f"  steerRatio:         {CP.steerRatio}")
    print(f"  steerRatioRear:     {CP.steerRatioRear}")
    print(f"  tireStiffnessFront: {CP.tireStiffnessFront}")
    print(f"  tireStiffnessRear:  {CP.tireStiffnessRear}")
    print(f"  rotationalInertia:  {CP.rotationalInertia}")
    print()

    VM = VehicleModel(CP)
    sf = calc_slip_factor(VM)

    print(f"Python-computed slip_factor for these CarSpecs: {sf!r}")
    print(f"Currently hardcoded in rivian.h (RIVIAN_ANGLE_STEERING_PARAMS.slip_factor): -0.0005445721739802007")
    print()
    if abs(sf - (-0.0005445721739802007)) < 1e-12:
        print("MATCH -- slip_factor is already correct, the boundary mismatch must be something else.")
    else:
        print("MISMATCH -- these differ. The hardcoded C constant does not match what Python's own")
        print("VM computes for the current (3.45m) CarSpecs. This is likely the real remaining bug --")
        print(f"rivian.h's slip_factor should probably be updated to {sf!r} to match.")
        print()
        print("Paste this whole output back for review before we touch rivian.h again.")


if __name__ == "__main__":
    main()
