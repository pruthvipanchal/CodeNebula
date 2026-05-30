# Compile: python3 migration_pattern.py
# Output:
# hello
# Running on Python 3

from __future__ import annotations

def process(data: bytes) -> str:
    return data.decode("utf-8")

print(process(b"hello"))

import sys
if sys.version_info >= (3, 0):
    print("Running on Python 3")
else:
    print("Running on Python 2")
