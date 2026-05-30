# Compile: python3 json_basics.py
# Output:
# 2024-03-15T10:30:00

import json
from datetime import datetime
from dataclasses import dataclass, asdict

@dataclass
class Event:
    name: str
    timestamp: datetime
    tags: list[str]

def serialize(obj):
    if isinstance(obj, datetime):
        return obj.isoformat()
    raise TypeError(f"Not serializable: {type(obj)}")

event = Event("deploy", datetime(2024, 3, 15, 10, 30), ["prod", "v2.1"])
payload = asdict(event)

json_str = json.dumps(payload, default=serialize, indent=2)
print(json_str)

data = json.loads(json_str)
print(data["timestamp"])

# Pretty-print sorted keys
config = {"z_last": 3, "a_first": 1, "m_middle": 2}
print(json.dumps(config, sort_keys=True))

# Nested structures round-trip
nested = {"users": [{"id": 1, "active": True}, {"id": 2, "active": False}]}
assert json.loads(json.dumps(nested)) == nested
print("Round-trip: OK")
