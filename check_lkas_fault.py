#!/usr/bin/env python3
"""
Checks a user-submitted rlog for an LKAS/steering fault and looks for any
correlation with our changes (Fix A wheelbase, Fix B off-tracking
compensation, the R1S/R1T selector, or the compensation gain).

Run from repo root (~/openpilot), with the venv that has capnp active:
    source .venv/bin/activate
    python3 check_lkas_fault.py /path/to/the/uploaded/rlog.zst
"""
import sys

sys.path.insert(0, "openpilot")
from openpilot.tools.lib.logreader import LogReader  # noqa: E402

FAULT_FIELDS = ["steerFaultTemporary", "steerFaultPermanent", "invalidLkasSetting", "stockLkas"]


def main(path):
    lr = LogReader(path, sort_by_time=True)

    init_data = None
    car_params = None
    car_state_hist = []  # (t, dict of relevant fields)
    control_hist = []    # (t, desiredCurvature, raw modelV2 curvature)
    events_hist = []     # (t, [event names])

    for msg in lr:
        which = msg.which()
        t = msg.logMonoTime / 1e9

        if which == "initData" and init_data is None:
            init_data = msg.initData

        elif which == "carParams" and car_params is None:
            car_params = msg.carParams

        elif which == "carState":
            cs = msg.carState
            car_state_hist.append((t, {
                "vEgo": cs.vEgo,
                "steeringAngleDeg": cs.steeringAngleDeg,
                "steeringTorque": cs.steeringTorque,
                "steeringPressed": cs.steeringPressed,
                **{f: getattr(cs, f) for f in FAULT_FIELDS},
            }))

        elif which == "controlsState":
            control_hist.append((t, "controlsState", msg.controlsState.desiredCurvature))

        elif which == "modelV2":
            try:
                raw_curv = msg.modelV2.action.desiredCurvature
            except Exception:
                raw_curv = None
            control_hist.append((t, "modelV2", raw_curv))

        elif which == "onroadEvents":
            names = [str(e.name) for e in msg.onroadEvents]
            if names:
                events_hist.append((t, names))

    print("=" * 70)
    print("VERSION / BRANCH INFO")
    print("=" * 70)
    if init_data is not None:
        print(f"  version:       {init_data.version}")
        print(f"  gitBranch:     {init_data.gitBranch}")
        print(f"  gitCommit:     {init_data.gitCommit}")
        print(f"  gitRemote:     {init_data.gitRemote}")
        print(f"  gitCommitDate: {init_data.gitCommitDate}")
    else:
        print("  No initData message found in this log.")

    print()
    print("=" * 70)
    print("CAR PARAMS (wheelbase/geometry -- tells us if Fix A / R1S override applied)")
    print("=" * 70)
    if car_params is not None:
        print(f"  brand:         {car_params.brand}")
        print(f"  carFingerprint:{car_params.carFingerprint}")
        print(f"  wheelbase:     {car_params.wheelbase:.4f} m")
        print(f"  centerToFront: {car_params.centerToFront:.4f} m")
    else:
        print("  No carParams message found in this log.")

    print()
    print("=" * 70)
    print("FAULT SCAN (carState.steerFault*/invalidLkasSetting/stockLkas)")
    print("=" * 70)
    prev = {f: False for f in FAULT_FIELDS}
    fault_onsets = []
    for t, fields in car_state_hist:
        for f in FAULT_FIELDS:
            if fields[f] and not prev[f]:
                fault_onsets.append((t, f))
            prev[f] = fields[f]

    if not fault_onsets:
        print("  No fault flags ever went True in this log's carState stream.")
    else:
        for t, f in fault_onsets:
            print(f"  t={t:.2f}s  {f} went TRUE")

    print()
    print("=" * 70)
    print("RELEVANT onroadEvents (steer/lkas related only)")
    print("=" * 70)
    steer_related = {"steerUnavailable", "steerTempUnavailable", "steerTempUnavailableSilent",
                      "steerSaturated", "steerOverride", "steerDisengage", "steerTimeLimit",
                      "belowSteerSpeed", "invalidLkasSetting", "stockLkas"}
    any_shown = False
    for t, names in events_hist:
        hits = [n for n in names if n in steer_related]
        if hits:
            print(f"  t={t:.2f}s  {hits}")
            any_shown = True
    if not any_shown:
        print("  None found.")

    print()
    print("=" * 70)
    print("CONTEXT AROUND EACH FAULT ONSET (±2.0s window)")
    print("=" * 70)
    if not fault_onsets:
        print("  (no faults to show context for)")
    for onset_t, onset_f in fault_onsets:
        print(f"\n  --- fault: {onset_f} at t={onset_t:.2f}s ---")
        window = [(t, f) for t, f in car_state_hist if abs(t - onset_t) <= 2.0]
        print(f"  {'t':>8} {'vEgo':>7} {'steerAngle':>11} {'steerTorque':>12} {'pressed':>8}")
        for t, f in window:
            marker = "  <== FAULT ONSET" if abs(t - onset_t) < 0.05 else ""
            print(f"  {t - onset_t:8.2f} {f['vEgo']:7.2f} {f['steeringAngleDeg']:11.2f} "
                  f"{f['steeringTorque']:12.2f} {str(f['steeringPressed']):>8}{marker}")

        # curvature context: raw model vs. commanded, in the same window
        curv_window = [(t, src, c) for t, src, c in control_hist if c is not None and abs(t - onset_t) <= 2.0]
        if curv_window:
            print(f"\n  curvature (raw modelV2 vs. commanded controlsState) near this fault:")
            print(f"  {'t':>8} {'source':>14} {'curvature (1/m)':>16}")
            for t, src, c in curv_window:
                print(f"  {t - onset_t:8.2f} {src:>14} {c:16.5f}")

    print()
    print("=" * 70)
    print("DONE. Paste this whole output back for review.")
    print("=" * 70)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 check_lkas_fault.py /path/to/rlog.zst")
        sys.exit(1)
    main(sys.argv[1])
