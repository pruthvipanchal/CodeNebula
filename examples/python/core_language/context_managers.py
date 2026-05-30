# Compile: python3 context_managers.py
# Output:
# Acquiring database
# Using DATABASE
# Releasing database

import contextlib
import time

@contextlib.contextmanager
def timed(label: str):
    start = time.perf_counter()
    try:
        yield
    finally:
        elapsed = time.perf_counter() - start
        print(f"{label}: {elapsed:.4f}s")

@contextlib.contextmanager
def managed_resource(name: str):
    print(f"Acquiring {name}")
    try:
        yield name.upper()
    finally:
        print(f"Releasing {name}")

with managed_resource("database") as res:
    print(f"Using {res}")

# __enter__ / __exit__ directly
class TempDirectory:
    def __enter__(self):
        import tempfile, os
        self.path = tempfile.mkdtemp()
        return self.path

    def __exit__(self, exc_type, exc_val, exc_tb):
        import shutil
        shutil.rmtree(self.path, ignore_errors=True)
        return False  # Don't suppress exceptions

with TempDirectory() as tmpdir:
    print(f"Temp dir: {tmpdir}")
print("Temp dir cleaned up")
