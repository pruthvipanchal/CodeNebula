# Compile: python3 runtime_info.py
# Output:
# Runtime:    CPython
# Python version info printed

import sys
import platform

print(f"Runtime:    {platform.python_implementation()}")
print(f"Version:    {sys.version_info.major}.{sys.version_info.minor}.{sys.version_info.micro}")
print(f"Platform:   {sys.platform}")
print(f"Executable: {sys.executable}")
print(f"GIL active: {sys._is_gil_enabled() if hasattr(sys, '_is_gil_enabled') else 'yes (pre-3.13)'}")
