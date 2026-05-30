# Compile: python3 python313_features.py
# Output:
# a|b|c

import sys

# Python 3.12+ f-string: arbitrary expressions (same quote type) allowed
items = ["a", "b", "c"]
result = f"{'|'.join(items)}"
print(result)

print(f"Python {sys.version_info.major}.{sys.version_info.minor}")

# Free-threaded check (Python 3.13+)
if hasattr(sys, "_is_gil_enabled"):
    gil = sys._is_gil_enabled()
    print(f"GIL enabled: {gil}")
    if not gil:
        print("Running in free-threaded mode (python3.13t)")
else:
    print("GIL: always enabled on this Python version")
