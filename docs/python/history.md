# Python — History & Evolution

## Birth of Python (1989–1991)

**Explanation**: Python was created by Guido van Rossum during the Christmas holidays of 1989 at Centrum Wiskunde & Informatica (CWI) in the Netherlands. Guido wanted a successor to the ABC language that fixed its shortcomings — better error handling, extensibility via C modules, and a cleaner syntax. He named it after Monty Python's Flying Circus. The first public release, Python 0.9.0, appeared in February 1991 on the alt.sources newsgroup.

**Real-World Scenario**: ABC was excellent for teaching but couldn't interface with the OS or C libraries. Guido's immediate need was scripting the Amoeba distributed OS — tasks that required a language both expressive enough for rapid scripting and powerful enough to call C code. Python 0.9.0 already had classes with inheritance, exception handling, and functions.

**What Python 0.9.0 Introduced**:
- Classes with inheritance and exception handling
- Functions as first-class objects
- Core types: list, dict, str, int, float
- Modules via `import`
- `lambda`, `map`, `filter`, `reduce`
- Interactive REPL for rapid experimentation

```python
# Python's philosophy from day one: readable, explicit, simple
def greet(name):
    return f"Hello, {name}!"

print(greet("World"))
```

**Example**: [birth_of_python.py](../../examples/python/history/birth_of_python.py)

---

## Python 2.0 — List Comprehensions & Unicode (2000)

**Explanation**: Python 2.0 was released on October 16, 2000. It introduced list comprehensions (borrowed from Haskell), a garbage collector for cyclic references, Unicode strings, and the `zip()`, `map()`, and `filter()` builtins in their modern form. Crucially, the development process moved to open source with Sourceforge — marking Python's transition to true community governance.

**Real-World Scenario**: Before list comprehensions, building a filtered list required `filter()` + `lambda` or explicit `for` loops. `[x**2 for x in range(10) if x % 2 == 0]` reads as English — this readability philosophy became Python's signature trait.

**Python 2.x Notable Milestones**:
| Version | Year | Key Addition |
|---------|------|-------------|
| 2.0     | 2000 | List comprehensions, Unicode, GC for cycles |
| 2.2     | 2001 | New-style classes, generators (`yield`) |
| 2.3     | 2003 | `set` type, `enumerate()`, `datetime` module |
| 2.4     | 2004 | Decorators (`@`), `subprocess`, generator expressions |
| 2.5     | 2006 | `with` statement (PEP 343), conditional expressions |
| 2.6     | 2008 | Forward compat with Python 3, `multiprocessing` |
| 2.7     | 2010 | Final 2.x release, backported set literals, dict comprehensions |

```python
# List comprehension (Python 2.0+) — revolutionary readability
squares = [x**2 for x in range(1, 11)]
evens = [x for x in range(20) if x % 2 == 0]
matrix_flat = [cell for row in [[1,2],[3,4]] for cell in row]
print(squares[:5])  # [1, 4, 9, 16, 25]
```

**Example**: [python2_features.py](../../examples/python/history/python2_features.py)

---

## Python 3.0 — The Great Divide (2008)

**Explanation**: Python 3.0 ("Py3k") was released December 3, 2008. It deliberately broke backward compatibility to fix design warts that had accumulated over 17 years: `print` became a function, `unicode` became the default string type (`str`), integer division was fixed (`/` → float), and `range()` returned an iterator instead of a list. The division lasted over a decade — major libraries like NumPy and Django supported both `2.7` and `3.x` simultaneously until Python 2 EOL in 2020.

**Real-World Scenario**: `print "hello"` becoming `print("hello")` was trivially fixable. The real friction was Unicode — Python 2 had `str` (bytes) and `unicode` (text), with implicit conversion causing subtle bugs. Python 3 made the distinction explicit: `str` is always text, `bytes` is always binary. Every library that did I/O had to be rewritten.

**Python 3.x Founding Decisions**:
- `str` = Unicode text; `bytes` = raw bytes; no implicit coercion
- `print()` is a function (PEP 3105)
- `3 / 2 == 1.5` (not `1`); use `//` for floor division
- `range()` returns an iterator (memory-efficient)
- `dict.keys()`, `.values()`, `.items()` return views not lists
- All classes implicitly inherit from `object`

```python
# Python 3 string model — explicit text vs bytes
text = "café"          # str: Unicode text
raw  = b"caf\xc3\xa9"  # bytes: encoded sequence

print(type(text))   # <class 'str'>
print(type(raw))    # <class 'bytes'>
print(text.encode("utf-8") == raw)  # True
```

**Example**: [python3_changes.py](../../examples/python/history/python3_changes.py)

---

## The 2-to-3 Migration (2008–2020)

**Explanation**: For 12 years, Python 2 and Python 3 coexisted. The migration tools (`2to3`, `six`, `future`) let libraries ship code compatible with both. Python 2.7 received security patches until January 1, 2020, when official support ended. The migration cost the ecosystem enormous effort but resulted in a cleaner, more consistent language.

**Real-World Scenario**: NumPy completed its Python 3 port in 2012; Django in 2013; SciPy and Matplotlib around 2014. By 2019, PyPI had over 90% of the top 360 packages Python-3 compatible. The migration is an object lesson in the cost of breaking changes in popular ecosystems.

**Migration Tools and Strategies**:
- `2to3` — automated source-code fixer (limited for large codebases)
- `six` library — compatibility shim (`six.text_type`, `six.moves`)
- `__future__` imports — backport Python 3 behavior to 2.7
- `tox` — test against both interpreters in CI

```python
# The __future__ import pattern used during migration
from __future__ import annotations, division, print_function

# After migration: clean Python 3 only
def process(data: bytes) -> str:
    return data.decode("utf-8")

print(process(b"hello"))  # hello
```

**Example**: [migration_pattern.py](../../examples/python/history/migration_pattern.py)

---

## CPython and Alternative Runtimes

**Explanation**: CPython is the reference implementation — the C-based interpreter that Guido created and that ships as `python3` on every OS. But Python the language has been implemented many times: PyPy (JIT-compiled, often 5-10× faster for CPU-bound loops), Jython (JVM), IronPython (.NET), MicroPython (microcontrollers), and Brython (browser). Understanding CPython's internals — the Global Interpreter Lock (GIL), bytecode compilation, reference counting GC — explains many Python performance characteristics.

**Real-World Scenario**: A data pipeline processing millions of records was taking 40 minutes in CPython. Switching to PyPy 3 (drop-in replacement for pure-Python code) cut it to 5 minutes with zero code changes. For NumPy-heavy workloads, CPython with C extensions is often faster than PyPy due to overhead at the Python-C boundary.

**Runtime Comparison**:
| Runtime | Backend | Best For |
|---------|---------|---------|
| CPython | C | General purpose, C extensions (NumPy, etc.) |
| PyPy    | RPython + JIT | CPU-bound pure-Python loops |
| Jython  | JVM | Java interop |
| MicroPython | C (tiny) | Microcontrollers (ESP32, RP2040) |
| GraalPy | GraalVM | Polyglot (Python + JS + Java) |

```python
import sys
import platform

print(f"Runtime:    {platform.python_implementation()}")
print(f"Version:    {sys.version}")
print(f"GIL active: {sys._is_gil_enabled() if hasattr(sys, '_is_gil_enabled') else 'n/a'}")
```

**Example**: [runtime_info.py](../../examples/python/history/runtime_info.py)

---

## Python 3.10 — Structural Pattern Matching (2021)

**Explanation**: Python 3.10 introduced `match`/`case` (PEP 634), the most syntactically significant addition since 2.0. Unlike a simple switch/case, Python's `match` is structural — it destructures data, matches by type, and binds variables in one expression. It was paired with 3.10's improved error messages (pointing at the exact column of a syntax error) and `ParamSpec` for typed higher-order functions.

**Real-World Scenario**: Processing HTTP responses, AST nodes, or command dispatch tables used to require chains of `isinstance` checks. `match` makes such code read like a spec rather than an implementation — the pattern mirrors the data structure you're destructuring.

**Pattern Matching Examples**:
```python
def handle_command(command):
    match command.split():
        case ["quit"]:
            return "Goodbye!"
        case ["go", direction] if direction in ("north", "south", "east", "west"):
            return f"Going {direction}"
        case ["get", item, *rest]:
            return f"Getting {item}" + (f" and {rest}" if rest else "")
        case _:
            return f"Unknown: {command}"

print(handle_command("go north"))   # Going north
print(handle_command("get sword"))  # Getting sword
```

**Example**: [pattern_matching.py](../../examples/python/history/pattern_matching.py)

---

## Python 3.11 — Faster CPython (2022)

**Explanation**: Python 3.11 delivered the first fruits of the "Faster CPython" project (funded by Microsoft, led by Mark Shannon). The interpreter's frame evaluation was rewritten to use "adaptive specialization" — opcodes that observe types at runtime and replace themselves with faster type-specific versions. Benchmarks showed 10–60% speedups on standard workloads. Exception handling became zero-cost for the happy path, and the new `tomllib` module for TOML parsing shipped in the standard library.

**Real-World Scenario**: Django web request benchmarks improved ~30% on 3.11 over 3.10 with no code changes. Startup time dropped because fewer module imports are needed.

**Python 3.11 Key Additions**:
- 10–60% faster in CPython benchmarks (PEP 659 adaptive interpreter)
- Fine-grained error locations in tracebacks (`^^^^^^` underline)
- `tomllib` — built-in TOML reader
- `TaskGroup` and `ExceptionGroup` in `asyncio`
- `Self` type (PEP 673), `LiteralString` type (PEP 675)

```python
# Python 3.11: fine-grained error location in tracebacks
# Before: "TypeError: ..."  After: exact column underlined
# Example of the new traceback format:
# result = obj.method()["key"]
#          ^^^^^^^^^^^^^^^^
# TypeError: 'NoneType' object is not subscriptable

import tomllib
config = tomllib.loads('[server]\nhost = "localhost"\nport = 8080')
print(config["server"]["host"])  # localhost
```

**Example**: [python311_features.py](../../examples/python/history/python311_features.py)

---

## Python 3.12–3.13 — JIT and Free-Threading (2023–2024)

**Explanation**: Python 3.12 (Oct 2023) improved f-strings (arbitrary expressions inside), added `@override` for type checkers, and removed the long-deprecated `distutils`. Python 3.13 (Oct 2024) shipped two experimental features that could reshape Python's performance story: an experimental JIT compiler (copy-and-patch, enabled with `--enable-experimental-jit`) and an optional free-threaded mode that disables the GIL (PEP 703, enabled with `--disable-gil` at build time, usable per-interpreter via `python3.13t`).

**Real-World Scenario**: A CPU-bound image processing task using `multiprocessing` had to fork 8 worker processes (heavy memory). With Python 3.13 free-threaded mode, the same task can run 8 threads sharing the same address space — dramatically reducing memory usage and improving cache locality.

**Python 3.12–3.13 Highlights**:
| Feature | Version | Impact |
|---------|---------|--------|
| f-string arbitrary exprs | 3.12 | Removes `f"{' '.join(items)}"` restriction |
| `@override` decorator | 3.12 | Type safety for subclass methods |
| New REPL | 3.13 | Multiline editing, syntax highlighting |
| Experimental JIT | 3.13 | 5–30% faster on some benchmarks |
| Free-threaded mode (no GIL) | 3.13 | True multi-core Python threads |
| `locals()` semantics fixed | 3.13 | Consistent with spec (PEP 667) |

```python
import sys

# Python 3.12+ f-string: arbitrary expressions allowed
items = ["a", "b", "c"]
result = f"{'|'.join(items)}"  # Previously a SyntaxError
print(result)  # a|b|c

# Check if running in free-threaded mode (3.13+)
if hasattr(sys, "_is_gil_enabled"):
    print(f"GIL enabled: {sys._is_gil_enabled()}")
else:
    print(f"Python {sys.version_info.major}.{sys.version_info.minor}")
```

**Example**: [python313_features.py](../../examples/python/history/python313_features.py)
