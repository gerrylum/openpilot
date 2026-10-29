import json

from openpilot.cereal import log
from openpilot.system.webrtc import opview_slim


def _reader(service, build):
  ev = log.Event.new_message()
  build(ev.init(service))
  return getattr(ev.as_reader(), service)


def test_every_listed_field_exists():
  # a typo or a schema change must fail here, not leave the app without a readout
  for service in opview_slim.OPVIEW_FIELDS:
    ev = log.Event.new_message()
    ev.init(service, 1) if service == "onroadEvents" else ev.init(service)
    json.dumps(opview_slim.slim(service, getattr(ev.as_reader(), service)))


def test_keeps_only_listed_fields_and_rounds():
  def build(cs):
    cs.vEgo = 17.123456789
    cs.gearShifter = "drive"
    cs.cruiseState.enabled = True
    cs.steeringPressed = True  # not read by opview
  out = opview_slim.slim("carState", _reader("carState", build))
  assert out["vEgo"] == 17.123 and out["gearShifter"] == "drive" and out["cruiseState"] == {"enabled": True}
  assert "steeringPressed" not in out


def test_union_lists_and_model():
  out = opview_slim.slim("controlsState", _reader("controlsState", lambda cs: cs.lateralControlState.init("torqueState")))
  assert out["lateralControlState"] == {"torqueState": {"saturated": False}}
  ev = log.Event.new_message()
  ev.init("onroadEvents", 1)[0].overrideLongitudinal = True
  assert opview_slim.slim("onroadEvents", ev.as_reader().onroadEvents)[0]["overrideLongitudinal"] is True

  def build(m):
    m.position.x = [1.23456]
    m.init("laneLines", 1)[0].y = [0.98765]
  out = opview_slim.slim("modelV2", _reader("modelV2", build))
  assert out["position"]["x"] == [1.235] and out["laneLines"][0]["y"] == [0.988]


def test_unlisted_service_sent_whole_and_rates():
  out = opview_slim.slim("gpsLocationExternal", _reader("gpsLocationExternal", lambda g: setattr(g, "latitude", 45.123456789)))
  assert out["latitude"] == 45.123
  assert opview_slim.min_gap_s("modelV2") == 0.
  assert opview_slim.min_gap_s("longitudinalPlan") > opview_slim.min_gap_s("carState") == 0.9 / 20.
