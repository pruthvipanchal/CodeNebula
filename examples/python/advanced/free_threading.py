# Compile: python3 free_threading.py
# Output:
# Python version and parallelism options printed

import sys

def demonstrate_threading_landscape():
    version = sys.version_info
    options = {
        "threading (I/O-bound)": "GIL released on I/O — works today",
        "multiprocessing":        "True parallelism via processes — works today",
        "asyncio":                "Cooperative concurrency — works today",
        "C extensions (NumPy)":   "Release GIL explicitly — works today",
    }
    if version >= (3, 12):
        options["Per-interpreter GIL"] = "PEP 684 — available (3.12+)"
    if version >= (3, 13):
        options["Free-threaded (no GIL)"] = "PEP 703 — use python3.13t build"

    for name, status in options.items():
        print(f"  {name:35} → {status}")

print(f"Python {sys.version_info.major}.{sys.version_info.minor} parallelism options:")
demonstrate_threading_landscape()

if hasattr(sys, "_is_gil_enabled"):
    print(f"\nGIL enabled: {sys._is_gil_enabled()}")
    if not sys._is_gil_enabled():
        print("  Running in FREE-THREADED mode!")
else:
    print("\nGIL: enabled (pre-3.13 or standard build)")
