#!/usr/bin/env python3
"""
Replays the raw EPAS_AdasStatus CAN signal (EPAS_EacErrorCode / EPAS_EacStatus)
from an rlog to see exactly what error code the EPAS reported around a
steerFaultPermanent/Temporary onset. These two integers aren't in the normal
capnp carState log (rivian/carstate.py keeps them as private Python instance
attributes, only exposing the derived booleans) -- getting the real values
means replaying the raw CAN bus through the same DBC-based parser carstate.py
itself uses.

Run from repo root (~/openpilot), with the venv active:
    source .venv/bin/activate
    python3 check_eac_error_code.py /path/to/rlog.zst <fault_time_seconds>

<fault_time_seconds> is the "t=...s" value printed by check_lkas_fault.py for
the fault onset (e.g. 36517.23). Prints a time series of EPAS_EacErrorCode /
EPAS_EacStatus for the 3 seconds before and after that time.
"""
import sys

sys.path.insert(0, "openpilot")
from openpilot.tools.lib.logreader import LogReader  # noqa: E402
from opendbc.can import CANParser  # noqa: E402
from opendbc.car import Bus  # noqa: E402
from opendbc.car.rivian.values import DBC  # noqa: E402

# Full value tables from opendbc/dbc/rivian_primary_actuator.dbc (VAL_ 912 lines) --
# this is the car's own EPAS ECU reporting these, not anything openpilot computes.
EAC_ERROR_CODE_NOTES = {
    0: "No_Err",
    1: "High_Angle_Cmd_Err (commanded angle out of range)",
    2: "High_Actual_Angle_Err",
    3: "High_Actual_Angle_Rate_Err",
    4: "Feature_Fault_Err",
    5: "Feature_Status_Invalid_Err",
    6: "Feature_Angle_Thd_Err",
    7: "Angle_Control_Cntr_Err (counter/timing)",
    8: "Angle_Control_Mia_Err (missing-in-action / dropout)",
    9: "Angle_Control_Crc_Err (checksum)",
    10: "Vehspd_Corrln_Failr_Err (vehicle speed correlation)",
    11: "Vehspd_Max_Thd_Err",
    12: "Hands_On_Detn_Err (driver override detected by EPAS itself -- benign)",
    13: "Ext_Angle_Plausibility_Err (commanded angle vs. vehicle geometry/sensors implausible -- WATCH if this is it, could relate to a wrong wheelbase)",
    14: "High_Delta_Angle_Err (commanded angle changed too abruptly -- WATCH if this is it, could relate to compensation/gain)",
    15: "Max_Steady_State_Err",
}
EAC_STATUS_NOTES = {
    0: "Eac_Inhibited",
    1: "Eac_Available",
    2: "Eac_Active",
    3: "Eac_Standby",
    4: "Eac_Fault",
    5: "Sna",
}


def main(path, fault_t):
    lr = LogReader(path, sort_by_time=True)

    dbc_name = DBC["RIVIAN_R1"][Bus.pt]
    cp = CANParser(dbc_name, [("EPAS_AdasStatus", 0)], 0)  # Bus.pt == bus 0, matches carstate.py's `cp`

    series = []  # (t_seconds, error_code, status)
    t0 = None
    for msg in lr:
        if msg.which() != "can":
            continue
        t = msg.logMonoTime / 1e9
        if t0 is None:
            t0 = t
        frames = [(c.address, bytes(c.dat), c.src) for c in msg.can]
        cp.update([(msg.logMonoTime, frames)])
        if "EPAS_AdasStatus" in cp.vl:
            err = cp.vl["EPAS_AdasStatus"]["EPAS_EacErrorCode"]
            status = cp.vl["EPAS_AdasStatus"]["EPAS_EacStatus"]
            series.append((t, err, status))

    print(f"Decoded {len(series)} EPAS_AdasStatus updates from {path}")
    print()

    window = [(t, e, s) for t, e, s in series if abs(t - fault_t) <= 3.0]
    if not window:
        print(f"No EPAS_AdasStatus readings found within 3s of t={fault_t}. "
              f"Full log covers t={series[0][0]:.2f}s to t={series[-1][0]:.2f}s "
              f"(relative to log start) -- check the fault_time_seconds argument.")
        return

    print(f"EPAS_EacErrorCode / EPAS_EacStatus in the 3s around t={fault_t}s:")
    print(f"{'t (rel to fault)':>18} {'EacErrorCode':>14} {'note':<45} {'EacStatus':>10} {'note':<20}")
    prev_err, prev_status = None, None
    for t, err, status in window:
        err = int(err)
        status = int(status)
        changed = (err != prev_err) or (status != prev_status)
        marker = "  <== CHANGED" if changed and prev_err is not None else ""
        err_note = EAC_ERROR_CODE_NOTES.get(err, "(see rivian DBC for meaning)")
        status_note = EAC_STATUS_NOTES.get(status, "?")
        print(f"{t - fault_t:18.3f} {err:14d} {err_note:<45} {status:10d} {status_note:<20}{marker}")
        prev_err, prev_status = err, status

    print()
    print("Paste this whole output back for review.")


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python3 check_eac_error_code.py /path/to/rlog.zst <fault_time_seconds>")
        sys.exit(1)
    main(sys.argv[1], float(sys.argv[2]))
