# Compile: python3 pathlib_basics.py
# Output:
# Written to result.txt

from pathlib import Path
import tempfile

# Build paths with / operator
with tempfile.TemporaryDirectory() as tmp:
    base   = Path(tmp)
    output = base / "result.txt"
    tmp_f  = output.with_suffix(".tmp")

    # Write atomically
    tmp_f.write_text("processed data\n", encoding="utf-8")
    tmp_f.rename(output)
    print(f"Written to {output.name}")

    # Read back
    content = output.read_text(encoding="utf-8")
    print(f"Content: {content.strip()!r}")

    # Glob
    (base / "a.py").write_text("# a")
    (base / "b.py").write_text("# b")
    py_files = sorted(base.glob("*.py"))
    print(f"Python files: {[f.name for f in py_files]}")

# Path components
p = Path("/home/user/projects/app/main.py")
print(f"stem:   {p.stem}")    # main
print(f"suffix: {p.suffix}")  # .py
print(f"parent: {p.parent}")  # /home/user/projects/app
print(f"parts:  {p.parts[:3]}")
