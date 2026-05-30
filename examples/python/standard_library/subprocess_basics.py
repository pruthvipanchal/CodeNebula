# Compile: python3 subprocess_basics.py
# Output:
# Python version printed

import subprocess
import sys

def run(cmd: list[str], **kwargs) -> subprocess.CompletedProcess:
    return subprocess.run(cmd, capture_output=True, text=True, check=True, **kwargs)

result = run([sys.executable, "--version"])
version = result.stdout.strip() or result.stderr.strip()
print(version)

# List files in current directory
import os
if os.name == "nt":
    result = subprocess.run(
        ["cmd", "/c", "dir", "/b"],
        capture_output=True, text=True
    )
else:
    result = subprocess.run(
        ["ls"],
        capture_output=True, text=True
    )
lines = result.stdout.strip().splitlines()
print(f"Found {len(lines)} entries")

# Handle failure gracefully
try:
    subprocess.run(
        [sys.executable, "-c", "import sys; sys.exit(1)"],
        check=True
    )
except subprocess.CalledProcessError as e:
    print(f"Command failed with exit code {e.returncode}")
