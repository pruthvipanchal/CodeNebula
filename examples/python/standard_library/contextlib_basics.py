# Compile: python3 contextlib_basics.py
# Output:
# File removed or didn't exist
# Created 3 temp files

import contextlib
import tempfile
from pathlib import Path

with contextlib.suppress(FileNotFoundError):
    Path("nonexistent_file.txt").unlink()
print("File removed or didn't exist")

with contextlib.ExitStack() as stack:
    temps = [
        stack.enter_context(tempfile.NamedTemporaryFile(suffix=".txt"))
        for _ in range(3)
    ]
    for i, f in enumerate(temps):
        f.write(f"File {i}".encode())
        f.flush()
    print(f"Created {len(temps)} temp files")

@contextlib.contextmanager
def temp_directory():
    import shutil
    d = tempfile.mkdtemp()
    try:
        yield Path(d)
    finally:
        shutil.rmtree(d)

with temp_directory() as td:
    (td / "test.txt").write_text("hello")
    files = list(td.glob("*"))
    print(f"Files in temp dir: {[f.name for f in files]}")
print("Temp dir cleaned up")
