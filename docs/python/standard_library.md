# Python — Standard Library

## `os` and `sys` — System Interface

**Explanation**: `os` provides a portable interface to operating system services: file/directory operations (`os.path`, `os.listdir`, `os.makedirs`, `os.remove`), environment variables (`os.environ`), process info (`os.getpid`, `os.getcwd`). `sys` exposes the Python interpreter's state: `sys.argv` (command-line args), `sys.path` (import search path), `sys.stdin`/`stdout`/`stderr`, `sys.exit()`, and `sys.version`.

**Real-World Scenario**: A deployment script reads `DATABASE_URL` from `os.environ`, calls `os.makedirs("logs", exist_ok=True)` to ensure the log directory exists, then launches a subprocess. `sys.exit(1)` signals failure to the calling shell or CI pipeline.

```python
import os
import sys

# Environment variables with defaults
db_url = os.environ.get("DATABASE_URL", "sqlite:///dev.db")
debug  = os.environ.get("DEBUG", "false").lower() == "true"

# Directory operations
os.makedirs("output/reports", exist_ok=True)
print(os.path.abspath("output/reports"))

# Process info
print(f"PID: {os.getpid()}, CWD: {os.getcwd()}")
print(f"Python: {sys.version_info.major}.{sys.version_info.minor}")
print(f"Args: {sys.argv}")
```

**Example**: [os_sys_basics.py](../../examples/python/standard_library/os_sys_basics.py)

---

## `pathlib` — Object-Oriented File Paths

**Explanation**: `pathlib.Path` (Python 3.4+) replaces string-based path manipulation with an object-oriented API. Paths are composed with `/`: `base / "subdir" / "file.txt"`. Key methods: `Path.read_text()`, `Path.write_text()`, `Path.glob("**/*.py")`, `Path.rglob()`, `Path.exists()`, `Path.mkdir(parents=True, exist_ok=True)`, `Path.stat()`. `Path.home()` and `Path.cwd()` give the home/current directory.

**Real-World Scenario**: Finding all Python files in a project and reporting their line counts: `list(Path(".").rglob("*.py"))` — one line replaces `os.walk` + filtering. Reading a config file from the same directory as the script: `Path(__file__).parent / "config.json"`.

```python
from pathlib import Path

# Build paths with / operator
project_root = Path(__file__).parent.parent
config_path  = project_root / "config" / "settings.json"

# Glob for all Python source files
py_files = sorted(project_root.rglob("*.py"))
print(f"Found {len(py_files)} Python files")

# Safe read with fallback
if config_path.exists():
    text = config_path.read_text(encoding="utf-8")
    print(f"Config size: {len(text)} bytes")

# Write atomically by writing to temp then rename
output = Path("result.txt")
tmp    = output.with_suffix(".tmp")
tmp.write_text("processed data\n", encoding="utf-8")
tmp.rename(output)
print(f"Written to {output.resolve()}")
```

**Example**: [pathlib_basics.py](../../examples/python/standard_library/pathlib_basics.py)

---

## `json` — JSON Encoding and Decoding

**Explanation**: `json.dumps()` serializes Python objects to JSON strings; `json.loads()` parses JSON strings. `json.dump()` / `json.load()` work with file objects. The `default` parameter of `dumps` handles non-serializable types (e.g., `datetime`). `object_hook` in `loads` transforms decoded dicts. `indent` pretty-prints; `sort_keys` ensures deterministic output for diffs.

**Real-World Scenario**: A REST API endpoint receives a JSON body, processes it, and returns a JSON response. `json.loads(request.body)` parses the input; `json.dumps(result, default=str)` serializes the response — `default=str` handles `datetime`, `Decimal`, and other non-standard types by falling back to their string representation.

```python
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

# Serialize with custom handler
json_str = json.dumps(payload, default=serialize, indent=2)
print(json_str)

# Parse back
data = json.loads(json_str)
print(data["timestamp"])  # "2024-03-15T10:30:00"
```

**Example**: [json_basics.py](../../examples/python/standard_library/json_basics.py)

---

## `re` — Regular Expressions

**Explanation**: The `re` module provides Perl-compatible regular expressions. Key functions: `re.match` (anchored at start), `re.search` (anywhere in string), `re.findall` (all matches), `re.finditer` (iterator of match objects), `re.sub` (replace), `re.split`. Compile patterns with `re.compile()` for reuse. Flags: `re.IGNORECASE`, `re.MULTILINE`, `re.DOTALL`. Groups: `()` for capture, `(?:...)` for non-capture, `(?P<name>...)` for named groups.

**Real-World Scenario**: Parsing log lines: `re.compile(r'(?P<ip>\d+\.\d+\.\d+\.\d+) .* "(?P<method>GET|POST) (?P<path>/\S*)"')` extracts IP, method, and path from Apache access logs — far more readable than string splitting.

```python
import re

LOG_PATTERN = re.compile(
    r"(?P<ip>\d+\.\d+\.\d+\.\d+)\s+"
    r"\[(?P<date>[^\]]+)\]\s+"
    r'"(?P<method>\w+)\s+(?P<path>\S+)"'
    r"\s+(?P<status>\d+)"
)

log_line = '192.168.1.1 [15/Mar/2024:10:30:00] "GET /api/users" 200'
if m := LOG_PATTERN.search(log_line):
    print(f"IP: {m.group('ip')}")
    print(f"Path: {m.group('path')}")
    print(f"Status: {m.group('status')}")

# Substitution with backreferences
text = "John Smith, Jane Doe"
swapped = re.sub(r"(\w+) (\w+)", r"\2, \1", text)
print(swapped)  # Smith, John, Doe, Jane
```

**Example**: [regex_basics.py](../../examples/python/standard_library/regex_basics.py)

---

## `datetime` — Dates, Times, and Timezones

**Explanation**: The `datetime` module provides `date`, `time`, `datetime`, `timedelta`, and `timezone`. `datetime.now()` returns local time (tz-naive); `datetime.now(timezone.utc)` returns UTC-aware. Always store timestamps as UTC; convert to local time at display. `timedelta` supports arithmetic. Python 3.9+ added `zoneinfo` for IANA timezone database (e.g., `"America/New_York"`).

**Real-World Scenario**: A scheduler must fire a job "every Monday at 9 AM New York time". Storing the next-run time as UTC in the database, then converting to New York time for display, avoids daylight-saving bugs. `timedelta(weeks=1)` gives the repeat interval.

```python
from datetime import datetime, timedelta, timezone
from zoneinfo import ZoneInfo  # Python 3.9+

# Always use aware datetimes in applications
utc_now = datetime.now(timezone.utc)
ny_tz   = ZoneInfo("America/New_York")
ny_time = utc_now.astimezone(ny_tz)

print(f"UTC:      {utc_now.isoformat()}")
print(f"New York: {ny_time.strftime('%Y-%m-%d %H:%M %Z')}")

# Arithmetic
deadline = datetime(2024, 12, 31, tzinfo=timezone.utc)
remaining = deadline - utc_now
print(f"Days until deadline: {remaining.days}")

# Parsing
event_str = "2024-03-15T10:30:00Z"
event_dt  = datetime.fromisoformat(event_str.replace("Z", "+00:00"))
print(f"Event: {event_dt}")
```

**Example**: [datetime_basics.py](../../examples/python/standard_library/datetime_basics.py)

---

## `collections` — High-Performance Containers

**Explanation**: The `collections` module provides specialized container types. `Counter` counts hashable objects; `defaultdict` returns a default value for missing keys; `deque` is a double-ended queue with O(1) appends/pops from both ends; `OrderedDict` remembers insertion order (built-in `dict` also does since Python 3.7, but `OrderedDict` has `move_to_end`); `namedtuple` creates tuple subclasses with named fields; `ChainMap` combines multiple mappings into a single view.

**Real-World Scenario**: Word frequency analysis: `Counter(text.lower().split()).most_common(10)` gives the top 10 words in one line. A BFS algorithm uses `deque` as a queue — `deque.appendleft`/`popleft` are O(1), unlike `list.insert(0, ...)` which is O(n).

```python
from collections import Counter, defaultdict, deque, namedtuple

# Counter
words = "the quick brown fox jumps over the lazy dog the".split()
freq = Counter(words)
print(freq.most_common(3))   # [('the', 3), ('quick', 1), ('brown', 1)]

# defaultdict — no KeyError for missing keys
graph: dict[str, list[str]] = defaultdict(list)
for u, v in [("A","B"), ("A","C"), ("B","D")]:
    graph[u].append(v)

# deque — O(1) queue for BFS
queue = deque(["A"])
visited = set()
while queue:
    node = queue.popleft()
    if node not in visited:
        visited.add(node)
        queue.extend(graph[node])
print(visited)  # {'A', 'B', 'C', 'D'}

# namedtuple
Point = namedtuple("Point", ["x", "y"])
p = Point(3, 4)
print(p.x, p.y, p._asdict())
```

**Example**: [collections_basics.py](../../examples/python/standard_library/collections_basics.py)

---

## `itertools` — Iterator Building Blocks

**Explanation**: `itertools` provides memory-efficient combinatoric and functional iterators. Infinite: `count(start, step)`, `cycle(iterable)`, `repeat(obj, n)`. Finite: `islice`, `takewhile`, `dropwhile`, `filterfalse`, `compress`. Combinatoric: `product`, `permutations`, `combinations`, `combinations_with_replacement`. Grouping: `groupby`. Chaining: `chain`, `chain.from_iterable`. All are lazy (return iterators, not lists).

**Real-World Scenario**: Generating all possible parameter combinations for a grid search: `itertools.product([0.01, 0.1], [32, 64, 128], [True, False])` gives the Cartesian product of learning rates, batch sizes, and dropout flags — exactly what a hyperparameter sweep needs.

```python
import itertools

# Groupby — consecutive groups (data must be sorted first)
data = [("A", 1), ("A", 2), ("B", 3), ("B", 4), ("A", 5)]
data.sort(key=lambda x: x[0])
for key, group in itertools.groupby(data, key=lambda x: x[0]):
    print(f"{key}: {[v for _, v in group]}")
# A: [1, 2, 5]   B: [3, 4]

# Batching with islice
def batched(iterable, n):
    it = iter(iterable)
    while batch := list(itertools.islice(it, n)):
        yield batch

for batch in batched(range(10), 3):
    print(batch)
# [0, 1, 2]  [3, 4, 5]  [6, 7, 8]  [9]

# Combinatoric
pairs = list(itertools.combinations("ABCD", 2))
print(f"{len(pairs)} pairs: {pairs[:3]}")
```

**Example**: [itertools_basics.py](../../examples/python/standard_library/itertools_basics.py)

---

## `functools` — Higher-Order Functions

**Explanation**: `functools` provides tools for higher-order functions. `lru_cache` (and `cache`) memoize function results — essential for recursive algorithms. `partial` pre-fills function arguments. `reduce` folds a sequence. `wraps` preserves function metadata when writing decorators. `total_ordering` auto-derives comparison methods from `__eq__` and one of `__lt__`, `__le__`, `__gt__`, `__ge__`.

**Real-World Scenario**: `@lru_cache(maxsize=128)` on a Fibonacci function turns the exponential naive recursion into O(n) — the cache turns repeated sub-computations into O(1) lookups. `partial(json.dumps, indent=2, default=str)` creates a pre-configured serializer used throughout a codebase.

```python
import functools
import time

@functools.lru_cache(maxsize=None)  # Unbounded cache
def fib(n: int) -> int:
    if n < 2:
        return n
    return fib(n - 1) + fib(n - 2)

start = time.perf_counter()
print(fib(50))  # 12586269025
print(f"Computed in {time.perf_counter() - start:.6f}s")
print(fib.cache_info())  # CacheInfo(hits=48, misses=51, maxsize=None, currsize=51)

# partial — freeze some arguments
def power(base, exp):
    return base ** exp

square = functools.partial(power, exp=2)
cube   = functools.partial(power, exp=3)
print([square(x) for x in range(1, 6)])  # [1, 4, 9, 16, 25]

# reduce
product = functools.reduce(lambda a, b: a * b, range(1, 6))
print(product)  # 120 (5!)
```

**Example**: [functools_basics.py](../../examples/python/standard_library/functools_basics.py)

---

## `contextlib` — Context Manager Utilities

**Explanation**: `contextlib` provides utilities for creating and composing context managers. `@contextmanager` turns a generator function into a context manager. `suppress(*exceptions)` silences specific exceptions. `ExitStack` dynamically composes a variable number of context managers. `nullcontext` is a no-op context manager useful as a conditional placeholder. `closing` wraps objects with a `close()` method.

**Real-World Scenario**: An integration test needs to open a variable number of temporary files (count known only at runtime). `ExitStack` opens each file and registers it — all are guaranteed closed when the `with` block exits, even if some openings fail mid-loop.

```python
import contextlib
import tempfile
from pathlib import Path

# suppress — clean alternative to try/except/pass
with contextlib.suppress(FileNotFoundError):
    Path("nonexistent_file.txt").unlink()
print("File removed or didn't exist")

# ExitStack — dynamic set of context managers
with contextlib.ExitStack() as stack:
    temps = [
        stack.enter_context(tempfile.NamedTemporaryFile(suffix=".txt"))
        for _ in range(3)
    ]
    for i, f in enumerate(temps):
        f.write(f"File {i}".encode())
        f.flush()
    print(f"Created {len(temps)} temp files")
    # All closed automatically here

# Reusable context manager factory
@contextlib.contextmanager
def temp_directory():
    import tempfile, shutil
    d = tempfile.mkdtemp()
    try:
        yield Path(d)
    finally:
        shutil.rmtree(d)
```

**Example**: [contextlib_basics.py](../../examples/python/standard_library/contextlib_basics.py)

---

## `logging` — Structured Logging

**Explanation**: The `logging` module provides a configurable, hierarchical logging system. Loggers are arranged in a dotted-name hierarchy (`__name__` is idiomatic). Handlers direct log records to outputs (stderr, files, sockets, HTTP). Formatters control the output format. Log levels: DEBUG < INFO < WARNING < ERROR < CRITICAL. Python 3.12 added `logging.getLogger(__name__)` convenience and Python 3.11 added `logging.getLevelNamesMapping()`. Use `structlog` or Python 3.12's `logging.getLogger` for structured JSON logging in production.

**Real-World Scenario**: A microservice uses one logger per module (`logger = logging.getLogger(__name__)`). A JSON formatter in production emits structured logs that Elasticsearch or Loki can index and search. Log levels control verbosity between development (DEBUG) and production (WARNING).

```python
import logging
import json
import sys

class JSONFormatter(logging.Formatter):
    def format(self, record: logging.LogRecord) -> str:
        log_entry = {
            "level": record.levelname,
            "message": record.getMessage(),
            "module": record.module,
            "line": record.lineno,
        }
        if record.exc_info:
            log_entry["exception"] = self.formatException(record.exc_info)
        return json.dumps(log_entry)

logger = logging.getLogger("myapp.service")
handler = logging.StreamHandler(sys.stdout)
handler.setFormatter(JSONFormatter())
logger.addHandler(handler)
logger.setLevel(logging.DEBUG)

logger.info("Service started")
logger.debug("Connecting to %s", "localhost:5432")
try:
    1 / 0
except ZeroDivisionError:
    logger.error("Unexpected error", exc_info=True)
```

**Example**: [logging_basics.py](../../examples/python/standard_library/logging_basics.py)

---

## `unittest` — Testing Framework

**Explanation**: `unittest` is Python's built-in xUnit-style testing framework. Test cases extend `unittest.TestCase` and name methods `test_*`. `setUp`/`tearDown` run before/after each test; `setUpClass`/`tearDownClass` run once per class. Key assertions: `assertEqual`, `assertRaises`, `assertAlmostEqual`, `assertIn`, `assertIsInstance`, `assertRegex`. Run with `python -m unittest discover`. Modern projects often use `pytest` (which still runs `unittest.TestCase` tests) for its simpler fixtures and richer output.

**Real-World Scenario**: A `Calculator` class ships with a `TestCalculator` in the same repository. CI runs `python -m unittest discover tests/` on every PR. The `assertRaises` context manager verifies that invalid input raises the expected exception type.

```python
import unittest
from functools import lru_cache

@lru_cache
def factorial(n: int) -> int:
    if n < 0:
        raise ValueError(f"Factorial undefined for {n}")
    return 1 if n == 0 else n * factorial(n - 1)

class TestFactorial(unittest.TestCase):
    def test_base_cases(self):
        self.assertEqual(factorial(0), 1)
        self.assertEqual(factorial(1), 1)

    def test_positive(self):
        self.assertEqual(factorial(5), 120)
        self.assertEqual(factorial(10), 3628800)

    def test_negative_raises(self):
        with self.assertRaises(ValueError):
            factorial(-1)

    def test_type_error(self):
        with self.assertRaises(TypeError):
            factorial(1.5)

if __name__ == "__main__":
    unittest.main()
```

**Example**: [unittest_basics.py](../../examples/python/standard_library/unittest_basics.py)

---

## `subprocess` — Running External Commands

**Explanation**: `subprocess.run()` (Python 3.5+) is the recommended way to run shell commands. `capture_output=True` captures stdout/stderr; `text=True` decodes them as strings; `check=True` raises `CalledProcessError` on non-zero exit. `subprocess.Popen` gives full control for interactive processes or streaming output. Never pass `shell=True` with untrusted user input — it creates a shell injection vulnerability.

**Real-World Scenario**: A build script runs `git log`, `pytest`, and `docker build` as subprocesses. `subprocess.run(["git", "log", "--oneline", "-10"], capture_output=True, text=True, check=True)` captures the last 10 commits without a shell and raises an exception if git fails.

```python
import subprocess
import sys

def run(cmd: list[str], **kwargs) -> subprocess.CompletedProcess:
    return subprocess.run(cmd, capture_output=True, text=True, check=True, **kwargs)

# Get Python version
result = run([sys.executable, "--version"])
print(result.stdout.strip() or result.stderr.strip())

# List files (cross-platform)
import os
if os.name == "nt":
    result = run(["cmd", "/c", "dir", "/b"])
else:
    result = run(["ls", "-la"])
print(result.stdout[:200])

# Handle failure gracefully
try:
    run(["false"])  # Unix command that always exits 1
except subprocess.CalledProcessError as e:
    print(f"Command failed with exit code {e.returncode}")
except FileNotFoundError:
    print("Command not found (Windows: skipping 'false')")
```

**Example**: [subprocess_basics.py](../../examples/python/standard_library/subprocess_basics.py)

---

## `argparse` — Command-Line Argument Parsing

**Explanation**: `argparse` builds fully-featured CLI parsers from Python code. It auto-generates `--help` output, handles type conversion (`type=int`), choices validation (`choices=["debug","info","warn"]`), required vs optional arguments, subcommands (`add_subparsers`), and mutually exclusive groups. `nargs` controls how many values an argument consumes: `"?"` = 0 or 1, `"*"` = 0+, `"+"` = 1+, `N` = exactly N.

**Real-World Scenario**: A data processing CLI: `process.py --input data.csv --output results.json --verbose --workers 4`. `argparse` validates that `--workers` is an integer, that `--input` exists (add `type=argparse.FileType("r")`), and generates help text without any boilerplate.

```python
import argparse
import sys

def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Process files with configurable workers",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument("input",  help="Input file path")
    parser.add_argument("-o", "--output", default="output.json", help="Output file")
    parser.add_argument("-w", "--workers", type=int, default=4, metavar="N")
    parser.add_argument("-v", "--verbose", action="store_true")
    parser.add_argument(
        "--log-level",
        choices=["debug", "info", "warning", "error"],
        default="info",
    )
    return parser

# Simulate running with args (don't block stdin in example)
args = build_parser().parse_args(["data.csv", "-w", "8", "--verbose"])
print(f"Input: {args.input}")
print(f"Workers: {args.workers}")
print(f"Verbose: {args.verbose}")
```

**Example**: [argparse_basics.py](../../examples/python/standard_library/argparse_basics.py)

---

## `typing` — Advanced Type Annotations

**Explanation**: The `typing` module provides building blocks for complex type annotations. `TypeVar` and `Generic` enable generic classes. `Protocol` defines structural subtyping (duck typing made explicit). `TypedDict` types `dict` literals with known keys. `Literal` restricts a type to specific values. `Union` / `|` union types. `Optional[X]` = `X | None`. `cast()` tells the type checker to treat a value as a specific type (no runtime effect). `TYPE_CHECKING` guards imports that are only needed for type checking.

**Real-World Scenario**: A plugin system uses `Protocol` to define the interface plugins must satisfy: `class Plugin(Protocol): def run(self, context: Context) -> Result: ...`. Any class with a matching `run` method satisfies the protocol — no explicit inheritance required. `mypy` catches missing methods at type-check time.

```python
from typing import TypeVar, Generic, Protocol, TypedDict, Literal, TYPE_CHECKING
from collections.abc import Iterator

if TYPE_CHECKING:
    pass  # Only imported for type checks — avoids circular imports

T = TypeVar("T")
S = TypeVar("S", bound="Comparable")

class Comparable(Protocol):
    def __lt__(self: S, other: S) -> bool: ...

def minimum(items: list[S]) -> S:
    return min(items)

class Stack(Generic[T]):
    def __init__(self) -> None:
        self._items: list[T] = []
    def push(self, item: T) -> None: self._items.append(item)
    def pop(self) -> T: return self._items.pop()
    def __iter__(self) -> Iterator[T]: return iter(self._items)

class UserConfig(TypedDict):
    name: str
    role: Literal["admin", "user", "guest"]
    active: bool

cfg: UserConfig = {"name": "Alice", "role": "admin", "active": True}
print(minimum([3, 1, 4, 1, 5]))  # 1
```

**Example**: [typing_advanced.py](../../examples/python/standard_library/typing_advanced.py)
