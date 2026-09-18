#!/usr/bin/env python3
"""
Anchor-verified patch #2 for the panda Rivian wheelbase fix (see
fix_panda_rivian_wheelbase.py for the first patch and full context).

After fixing RIVIAN_ANGLE_STEERING_PARAMS.wheelbase (3.08 -> 3.45),
test_rivian.py's test_lateral_accel_limit / test_lateral_jerk_limit stopped
failing "at the boundary" but started failing "1 unit above the boundary" --
C was accepting angle commands ~0.1deg past where Python's own reference VM
says the limit should be.

Root cause: Python's reference VM doesn't use a fixed slip_factor constant --
it computes it dynamically per-CarSpecs (calc_slip_factor() in
opendbc/car/vehicle_model.py: m*(cF*aF - cR*aR) / (l**2 * cF * cR), a function
of mass, tire stiffness front/rear, wheelbase, and centerToFront). Panda's C
side hardcodes a single slip_factor constant that was only ever correct for
the OLD wheelbase (3.08) + whatever centerToFront/mass/tireStiffness were
paired with it at the time -- changing wheelbase alone left this second
constant stale too.

Confirmed via check_slip_factor_mismatch.py, run against the CURRENT
RIVIAN_R1 CarSpecs (wheelbase=3.45, centerToFront=1.725, mass=3342.0,
tireStiffnessFront=366031.28, tireStiffnessRear=578620.875), same
CarInterface.get_non_essential_params() path test_rivian.py's own test
harness uses to build self.VM:

    Python-computed slip_factor: -0.00048616876264612327
    Currently hardcoded in rivian.h:  -0.0005445721739802007   (MISMATCH)

This patches rivian.h's RIVIAN_ANGLE_STEERING_PARAMS.slip_factor to match.

Run from the repo root (~/openpilot), on the rx-wb-src branch (after
fix_panda_rivian_wheelbase.py has already been applied):
    python3 fix_panda_rivian_slip_factor.py
"""
import pathlib
import sys

ROOT = pathlib.Path(__file__).resolve().parent


def patch(path: str, anchor: str, replacement: str, already_done_marker: str):
    p = ROOT / path
    text = p.read_text()
    if already_done_marker in text:
        print(f"SKIP (already patched): {path}")
        return
    if anchor not in text:
        print(f"FAILED: anchor not found in {path} -- aborting, nothing was changed.")
        print("---- anchor expected ----")
        print(anchor)
        sys.exit(1)
    if text.count(anchor) != 1:
        print(f"FAILED: anchor appears {text.count(anchor)} times in {path} (expected exactly 1) -- aborting.")
        sys.exit(1)
    p.write_text(text.replace(anchor, replacement))
    print(f"OK: patched {path}")


patch(
    "opendbc_repo/opendbc/safety/modes/rivian.h",
    "  const AngleSteeringParams RIVIAN_ANGLE_STEERING_PARAMS = {\n"
    "    .slip_factor = -0.0005445721739802007,\n"
    "    .steer_ratio = 15.2,\n"
    "    .wheelbase = 3.45,\n"
    "  };",
    "  const AngleSteeringParams RIVIAN_ANGLE_STEERING_PARAMS = {\n"
    "    .slip_factor = -0.00048616876264612327,\n"
    "    .steer_ratio = 15.2,\n"
    "    .wheelbase = 3.45,\n"
    "  };",
    already_done_marker=".slip_factor = -0.00048616876264612327,",
)

print("\nEdit applied. Next steps:")
print("  1. git diff   # sanity check -- only slip_factor should have changed this time")
print("  2. cd opendbc_repo/opendbc/safety/tests && python3 -m unittest test_rivian -v")
print("     # expect: Ran 151 tests ... OK (with the same 19 skips as before, 0 failures)")
print("  3. cd ../../../..   # back to repo root")
print("     python3 tools/test_runner.py opendbc_repo/opendbc/car/tests/test_car_interfaces.py")
print("     # same baseline check as always: 272 passed / 1 known pre-existing failure")
print("  4. git add -A && git commit -m \"panda(rivian): fix stale safety-firmware slip_factor to match 3.45m wheelbase\"")
print("  5. git push origin rx-wb-src")
print("  6. Compiled panda firmware -- confirm it actually reflashes (pandad.py's panda.flash())")
print("     on next boot into a branch with this fix, rather than assuming it silently took effect.")
