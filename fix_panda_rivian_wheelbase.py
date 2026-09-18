#!/usr/bin/env python3
"""
Anchor-verified patch: fix panda's safety-firmware Rivian wheelbase constant.

Root cause (confirmed two ways -- by test_rivian.py's own test_lateral_accel_limit /
test_lateral_jerk_limit failures on the current rx-wb source, AND by the real
steerFaultPermanent/EPAS_EacErrorCode=7 fault seen in the field): panda's C safety
firmware (opendbc/safety/modes/rivian.h, compiled into the actual panda hardware via
panda/board/main.c -> safety.h -> rivian.h) hardcodes wheelbase = 3.08 in
RIVIAN_ANGLE_STEERING_PARAMS, used by rivian_tx_hook()'s steer_angle_cmd_checks_vm()
to decide whether to BLOCK an outgoing angle command. This was never updated when
Fix A corrected the live control stack's wheelbase to 3.45. A smaller wheelbase makes
this check MORE restrictive (smaller max angle for the same curvature), so panda can
legitimately reject angle commands the live stack (correctly, per Fix A) considers
valid -- producing exactly the counter/timing EPAS fault (Angle_Control_Cntr_Err) seen
in the field, because the message never reaches the car's bus at all.

Fix: change the constant to 3.45 uniformly for both R1S and R1T. This is NOT a new
R1S/R1T-aware toggle -- deliberately. Every other place in the codebase that encodes
this same physical constant for safety/limiting purposes (ext_controller.py's own
internal VM_safety, and the CarSpecs used to build test_rivian.py's own self.VM) is
ALREADY uniformly 3.45 for both body styles; panda's rivian.h was the only outlier.
A smaller wheelbase only makes the safety ceiling MORE restrictive, never less --
so 3.08 was never a "conservative choice for R1S," it was simply stale, and 3.45
only loosens the ceiling (EPAS/steering hardware limits remain the real backstop).
True per-variant awareness here would require opendbc/car/rivian/interface.py's
_get_params() to read live Params() and keep THREE places in sync (panda's C
constant, ext_controller.py's own Python VM, and the live control stack) -- the
same live-Params()-in-opendbc/car risk explicitly avoided for the original
R1S/R1T controls-layer toggle, for close to zero real benefit.

This is compiled panda firmware, not app-layer Python -- after this change panda
needs to be reflashed (happens automatically via pandad.py's panda.flash() on
next boot with the new code) for the fix to take effect on the actual hardware.

Run from the repo root (~/openpilot), on the rx-wb-src branch:
    python3 fix_panda_rivian_wheelbase.py
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
    "    .slip_factor = -0.0005445721739802007,\n"
    "    .steer_ratio = 15.2,\n"
    "    .wheelbase = 3.08,",
    "    .slip_factor = -0.0005445721739802007,\n"
    "    .steer_ratio = 15.2,\n"
    "    .wheelbase = 3.45,",
    already_done_marker=".wheelbase = 3.45,",
)

print("\nEdit applied. Next steps:")
print("  1. git diff   # sanity check -- should be a single-value change (3.08 -> 3.45) in rivian.h")
print("  2. cd opendbc_repo/opendbc/safety/tests && python3 -m unittest test_rivian -v")
print("     # expect: the 4 previously-failing tests (test_lateral_accel_limit /")
print("     # test_lateral_jerk_limit x2 classes) should now PASS, with no new failures")
print("  3. cd ../../../..   # back to repo root")
print("     python3 tools/test_runner.py opendbc_repo/opendbc/car/tests/test_car_interfaces.py")
print("     # same baseline check as always: 272 passed / 1 known pre-existing failure")
print("  4. git add -A && git commit -m \"panda(rivian): fix stale safety-firmware wheelbase 3.08 -> 3.45\"")
print("  5. git push origin rx-wb-src")
print("  6. This is compiled panda firmware -- after installing/switching to the rebuilt branch,")
print("     panda will get reflashed automatically (pandad.py's panda.flash()) on next boot.")
print("     Worth confirming that happens (e.g. a log line from pandad, or just that the car")
print("     drives normally) rather than assuming it silently took effect.")
