# Compile: python3 import_system.py
# Output:
# json cached: True
# Same object: True

import importlib
import sys

print(f"json cached: {'json' in sys.modules}")
import json
cached = sys.modules["json"]
print(f"Same object: {cached is json}")

# Dynamic import
def load_module(name: str):
    try:
        module = importlib.import_module(name)
        print(f"Loaded: {module.__name__}")
        return module
    except ImportError as e:
        print(f"Failed: {e}")
        return None

load_module("json")
load_module("nonexistent_module")

# Inspect a module's public API
import math
public_api = [name for name in dir(math) if not name.startswith("_")]
print(f"math public names: {len(public_api)}")
print(f"First 5: {public_api[:5]}")

# Reload (rarely needed)
original_pi = math.pi
importlib.reload(math)
print(f"After reload: math.pi == {math.pi} (same: {math.pi == original_pi})")

# sys.path — where Python looks for modules
print(f"\nModule search paths (first 2):")
for p in sys.path[:2]:
    print(f"  {p!r}")
