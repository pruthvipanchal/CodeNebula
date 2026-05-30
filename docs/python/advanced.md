# Python — Advanced

## Metaclasses

**Explanation**: A metaclass is the class of a class — it controls how classes are created. `type` is the default metaclass of all Python classes. Custom metaclasses override `__new__` and `__init__` to intercept class creation: adding methods, validating class definitions, registering classes, or enforcing interfaces. The `__init_subclass__` hook (Python 3.6+) is a simpler alternative for many metaclass use cases. `abc.ABCMeta` is the most widely used metaclass — it powers `@abstractmethod`.

**Real-World Scenario**: Django's ORM uses a metaclass to transform class-level field declarations (`name = CharField(max_length=100)`) into a table schema and query interface. The metaclass intercepts class creation and replaces `CharField` instances with descriptors wired to the database.

```python
class SingletonMeta(type):
    """Metaclass that ensures only one instance per class."""
    _instances: dict = {}

    def __call__(cls, *args, **kwargs):
        if cls not in cls._instances:
            cls._instances[cls] = super().__call__(*args, **kwargs)
        return cls._instances[cls]

class Config(metaclass=SingletonMeta):
    def __init__(self):
        self.debug = False
        self.version = "1.0"

a = Config()
b = Config()
print(a is b)       # True — same instance
a.debug = True
print(b.debug)      # True — same object

# __init_subclass__ — simpler registration pattern
class Plugin:
    _registry: dict[str, type] = {}

    def __init_subclass__(cls, name: str = "", **kwargs):
        super().__init_subclass__(**kwargs)
        if name:
            Plugin._registry[name] = cls

class AuthPlugin(Plugin, name="auth"):
    def run(self): return "auth"

print(Plugin._registry)  # {'auth': <class 'AuthPlugin'>}
```

**Example**: [metaclasses.py](../../examples/python/advanced/metaclasses.py)

---

## Descriptors

**Explanation**: A descriptor is an object that defines `__get__`, `__set__`, or `__delete__`. When stored as a class attribute, Python calls these methods instead of the normal attribute access. This is how `@property`, `@classmethod`, `@staticmethod`, and all ORM fields work. Data descriptors define both `__get__` and `__set__`; non-data descriptors define only `__get__`. Python's attribute lookup order: data descriptors > instance dict > non-data descriptors.

**Real-World Scenario**: A `Validated` descriptor enforces type and range constraints on model fields. One descriptor class handles validation for all fields — add `age = Validated(int, min=0, max=150)` to any class and it automatically validates on assignment.

```python
class Typed:
    """Descriptor that enforces a type constraint."""
    def __set_name__(self, owner, name: str) -> None:
        self._name = f"_{name}"
        self._public = name

    def __init__(self, expected_type: type):
        self._type = expected_type

    def __get__(self, obj, objtype=None):
        if obj is None:
            return self  # Class-level access returns the descriptor itself
        return getattr(obj, self._name, None)

    def __set__(self, obj, value) -> None:
        if not isinstance(value, self._type):
            raise TypeError(f"{self._public} must be {self._type.__name__}, got {type(value).__name__}")
        setattr(obj, self._name, value)

class Person:
    name = Typed(str)
    age  = Typed(int)

    def __init__(self, name: str, age: int):
        self.name = name
        self.age  = age

p = Person("Alice", 30)
print(p.name, p.age)  # Alice 30
try:
    p.age = "thirty"
except TypeError as e:
    print(e)  # age must be int, got str
```

**Example**: [descriptors.py](../../examples/python/advanced/descriptors.py)

---

## Abstract Base Classes (ABCs)

**Explanation**: `abc.ABC` (or `metaclass=abc.ABCMeta`) lets you define interfaces that subclasses must implement. Methods decorated with `@abstractmethod` must be overridden — instantiating a class with unimplemented abstract methods raises `TypeError`. ABCs also support `register()` for virtual subclass registration: `ABC.register(SomeClass)` makes `isinstance(obj, ABC)` return `True` without inheritance. The `collections.abc` module defines ABCs for built-in protocols (`Iterable`, `Mapping`, `Sequence`).

**Real-World Scenario**: A plugin architecture defines `class DataSource(ABC)` with abstract methods `connect()`, `read_batch()`, `close()`. Each data connector (S3, Kafka, Postgres) implements the interface. Application code depends only on `DataSource` — swapping connectors requires no changes.

```python
from abc import ABC, abstractmethod
from typing import Iterator

class DataSource(ABC):
    @abstractmethod
    def connect(self) -> None: ...

    @abstractmethod
    def read_batch(self, size: int) -> list[dict]: ...

    @abstractmethod
    def close(self) -> None: ...

    def read_all(self, batch_size: int = 100) -> Iterator[list[dict]]:
        """Template method — uses abstract read_batch."""
        self.connect()
        try:
            while batch := self.read_batch(batch_size):
                yield batch
        finally:
            self.close()

class MemorySource(DataSource):
    def __init__(self, data: list[dict]):
        self._data = data
        self._pos = 0

    def connect(self) -> None: pass
    def close(self) -> None:   pass

    def read_batch(self, size: int) -> list[dict]:
        batch = self._data[self._pos:self._pos + size]
        self._pos += size
        return batch

src = MemorySource([{"id": i} for i in range(5)])
for batch in src.read_all(batch_size=2):
    print(batch)
```

**Example**: [abstract_base_classes.py](../../examples/python/advanced/abstract_base_classes.py)

---

## Protocols (PEP 544) — Structural Subtyping

**Explanation**: `typing.Protocol` (Python 3.8+) defines structural interfaces — any class that implements the required methods satisfies the protocol, without explicit inheritance. This is static duck typing: `mypy` and `pyright` verify compliance at type-check time, not runtime. Use `@runtime_checkable` to enable `isinstance` checks. Protocols capture what code *does* rather than what it *inherits* — perfect for third-party classes you can't modify.

**Real-World Scenario**: A logging system accepts any object with a `write(message: str) -> None` method. `class Writable(Protocol): def write(self, msg: str) -> None: ...` lets `sys.stdout`, `io.StringIO`, a custom `SlackSink`, and a no-op `DevNull` all work with the same type-annotated code.

```python
from typing import Protocol, runtime_checkable

@runtime_checkable
class Drawable(Protocol):
    def draw(self) -> str: ...
    def area(self) -> float: ...

class Circle:
    def __init__(self, r: float): self.r = r
    def draw(self) -> str:  return f"Circle(r={self.r})"
    def area(self) -> float: return 3.14159 * self.r ** 2

class Rectangle:
    def __init__(self, w: float, h: float): self.w, self.h = w, h
    def draw(self) -> str:  return f"Rect({self.w}x{self.h})"
    def area(self) -> float: return self.w * self.h

def render(shape: Drawable) -> None:
    print(f"{shape.draw()} — area: {shape.area():.2f}")

shapes: list[Drawable] = [Circle(5), Rectangle(3, 4)]
for s in shapes:
    render(s)

print(isinstance(Circle(1), Drawable))    # True (runtime_checkable)
```

**Example**: [protocols.py](../../examples/python/advanced/protocols.py)

---

## `__slots__` — Memory Optimization

**Explanation**: By default, Python stores instance attributes in a `__dict__` per instance — flexible but memory-heavy (each dict has overhead). Declaring `__slots__ = ("x", "y")` on a class replaces the instance dict with a fixed-size array, reducing memory by 40-70% and slightly speeding attribute access. Trade-offs: no arbitrary attributes, no `__dict__` (unless you include it), and subclasses must also declare slots for the full benefit. Python 3.10's `@dataclass(slots=True)` generates slots automatically.

**Real-World Scenario**: A spatial index stores millions of `Point(x, y, z)` objects. Without `__slots__`, each instance has a `__dict__` taking ~232 bytes. With `__slots__`, the same object drops to ~56 bytes — a 4× memory reduction that keeps the entire index in L3 cache.

```python
import sys

class PointDict:
    def __init__(self, x, y, z):
        self.x, self.y, self.z = x, y, z

class PointSlots:
    __slots__ = ("x", "y", "z")
    def __init__(self, x, y, z):
        self.x, self.y, self.z = x, y, z

pd = PointDict(1.0, 2.0, 3.0)
ps = PointSlots(1.0, 2.0, 3.0)

print(f"PointDict  size: {sys.getsizeof(pd)} bytes + {sys.getsizeof(pd.__dict__)} dict")
print(f"PointSlots size: {sys.getsizeof(ps)} bytes (no __dict__)")
print(f"Has __dict__: PointDict={hasattr(pd, '__dict__')}, PointSlots={hasattr(ps, '__dict__')}")

# Slots with inheritance (child must also declare slots)
class Point4D(PointSlots):
    __slots__ = ("w",)
    def __init__(self, x, y, z, w):
        super().__init__(x, y, z)
        self.w = w
```

**Example**: [slots.py](../../examples/python/advanced/slots.py)

---

## Memory Management and the `gc` Module

**Explanation**: CPython uses reference counting as its primary GC mechanism — an object is freed as soon as its reference count drops to zero. A cycle detector handles reference cycles (objects pointing to each other). The `gc` module controls the cycle collector: `gc.collect()` forces a collection, `gc.disable()` turns it off, `gc.get_threshold()` returns collection thresholds. `weakref` creates references that don't increase the reference count — useful for caches and observer patterns without preventing garbage collection.

**Real-World Scenario**: A cache holding 10,000 objects: if the cache holds strong references, the objects never get garbage collected. Using `weakref.WeakValueDictionary` instead means the cache automatically shrinks when objects are no longer used elsewhere — no manual eviction needed.

```python
import gc
import weakref
import sys

class Node:
    def __init__(self, value):
        self.value = value
        self.next: "Node | None" = None

# Reference cycle — would leak without cycle GC
a = Node("A")
b = Node("B")
a.next = b
b.next = a  # Cycle!

print(f"GC before collect: {gc.get_count()}")  # (counts objects in each gen)
del a, b
collected = gc.collect()
print(f"Cycle GC collected {collected} objects")

# weakref — cache that doesn't prevent GC
class ExpensiveObject:
    def __init__(self, key): self.key = key

cache: weakref.WeakValueDictionary = weakref.WeakValueDictionary()
obj = ExpensiveObject("config")
cache["config"] = obj
print(cache.get("config"))  # <ExpensiveObject ...>
del obj
gc.collect()
print(cache.get("config"))  # None — auto-evicted
```

**Example**: [memory_management.py](../../examples/python/advanced/memory_management.py)

---

## CPython Internals — Bytecode and `dis`

**Explanation**: CPython compiles Python source to bytecode (`.pyc` files), which the CPython virtual machine executes. The `dis` module disassembles bytecode into human-readable instructions. Each instruction has an opcode and optional argument. `code.co_consts`, `co_varnames`, `co_names` store constants, local variable names, and global names. Understanding bytecode explains Python performance characteristics: attribute lookups (`LOAD_ATTR`) are expensive; local variables (`LOAD_FAST`) are fast; function calls have non-trivial overhead.

**Real-World Scenario**: Profiling shows a tight loop is slow. Disassembling with `dis.dis` reveals 8 `LOAD_ATTR` instructions per iteration — a cached local reference (`fast = obj.method`) replaces them with 1 `LOAD_FAST`, cutting the loop time by 30%.

```python
import dis
import marshal

def factorial(n: int) -> int:
    result = 1
    for i in range(2, n + 1):
        result *= i
    return result

print("=== Bytecode for factorial ===")
dis.dis(factorial)
print(f"\nConstants: {factorial.__code__.co_consts}")
print(f"Locals:    {factorial.__code__.co_varnames}")
print(f"Stack size:{factorial.__code__.co_stacksize}")

# .pyc file format note
import py_compile, pathlib, importlib.util
import tempfile, os
with tempfile.NamedTemporaryFile(suffix=".py", mode="w", delete=False) as f:
    f.write("x = 1 + 2\n")
    tmp = f.name
py_compile.compile(tmp, doraise=True)
print(f"\nCompiled to: {importlib.util.cache_from_source(tmp)}")
os.unlink(tmp)
```

**Example**: [bytecode_dis.py](../../examples/python/advanced/bytecode_dis.py)

---

## The Import System

**Explanation**: `import` triggers a multi-step process: find the module (using `sys.meta_path` finders), load it (execute the source or bytecode), and cache it in `sys.modules`. Subsequent imports return the cached module. The finder/loader protocol enables custom import hooks: `sys.meta_path` for high-level control, `sys.path_hooks` for new path-based finders. `importlib.import_module()` is the programmatic import API. `__all__` controls what `from module import *` exports; `__init__.py` makes a directory a package.

**Real-World Scenario**: A plugin system dynamically imports modules from a `plugins/` directory at startup: `importlib.import_module(f"plugins.{name}")` loads each plugin; each plugin registers itself in a global registry via `__init_subclass__` or explicit registration in `__init__`.

```python
import importlib
import sys

# Dynamic import
def load_plugin(module_name: str):
    try:
        module = importlib.import_module(module_name)
        print(f"Loaded: {module.__name__}")
        return module
    except ImportError as e:
        print(f"Failed to load {module_name}: {e}")
        return None

# sys.modules cache
import json
print(f"json cached: {'json' in sys.modules}")   # True after first import
cached = sys.modules["json"]
print(f"Same object: {cached is json}")            # True

# __all__ controls wildcard imports
print(f"json.__all__ (first 5): {json.__all__[:5] if hasattr(json, '__all__') else 'not defined'}")

# Reload a module (rarely needed, but useful in REPL development)
import math
original_pi = math.pi
importlib.reload(math)
print(f"After reload: math.pi = {math.pi}")
```

**Example**: [import_system.py](../../examples/python/advanced/import_system.py)

---

## Type Narrowing and `TypeGuard`

**Explanation**: Type narrowing is the process by which a type checker infers a more specific type after a check. `isinstance(x, str)` narrows `x: int | str` to `str` in the `if` branch. `TypeGuard[T]` (PEP 647, Python 3.10+) lets you write custom narrowing functions: a function returning `TypeGuard[SpecificType]` tells the type checker that the return value implies the argument is of `SpecificType`. Python 3.12 added `TypeIs` (PEP 742) as a stricter alternative.

**Real-World Scenario**: A function receives `data: dict[str, object]` from JSON. After validating with `is_valid_config(data)` (returning `TypeGuard[Config]`), the type checker knows `data` is `Config` — no `cast()` needed, and you get full autocomplete on `Config` attributes.

```python
from typing import TypeGuard, Union
from dataclasses import dataclass

@dataclass
class Cat:
    name: str
    indoor: bool

@dataclass
class Dog:
    name: str
    breed: str

Animal = Union[Cat, Dog]

def is_cat(animal: Animal) -> TypeGuard[Cat]:
    return isinstance(animal, Cat)

def describe(animal: Animal) -> str:
    if is_cat(animal):
        # Type checker knows animal is Cat here
        return f"Cat {animal.name}, indoor={animal.indoor}"
    else:
        # Type checker knows animal is Dog here
        return f"Dog {animal.name}, breed={animal.breed}"

animals: list[Animal] = [Cat("Whiskers", True), Dog("Rex", "Labrador")]
for a in animals:
    print(describe(a))
```

**Example**: [type_narrowing.py](../../examples/python/advanced/type_narrowing.py)

---

## Performance Profiling

**Explanation**: `cProfile` is CPython's built-in deterministic profiler — it records every function call, call count, and cumulative time. Run with `python -m cProfile -s cumulative script.py`. `pstats` filters and formats results. `line_profiler` (third-party) profiles per-line within a function (decorate with `@profile`, run with `kernprof -l`). `tracemalloc` tracks memory allocations (built-in). For production: `py-spy` is a sampling profiler that attaches to a running process without modifying code.

**Real-World Scenario**: A report generation script takes 45 seconds. `cProfile` reveals 80% of time is in `str.format()` called 10 million times inside a nested loop. Moving the format call outside the inner loop cuts runtime to 8 seconds — the profile told exactly where to look.

```python
import cProfile
import pstats
import io
import timeit

def slow_sum(n: int) -> int:
    """Intentionally slow version using string conversion."""
    total = 0
    for i in range(n):
        total += int(str(i))  # Silly but profiling shows it
    return total

def fast_sum(n: int) -> int:
    return sum(range(n))

# Profile slow_sum
pr = cProfile.Profile()
pr.enable()
result = slow_sum(50_000)
pr.disable()

buf = io.StringIO()
ps = pstats.Stats(pr, stream=buf).sort_stats("cumulative")
ps.print_stats(5)  # Top 5 functions
print(buf.getvalue())

# Quick benchmark
slow_t = timeit.timeit("slow_sum(1000)", globals={"slow_sum": slow_sum}, number=100)
fast_t = timeit.timeit("fast_sum(1000)", globals={"fast_sum": fast_sum}, number=100)
print(f"slow: {slow_t:.3f}s  fast: {fast_t:.3f}s  speedup: {slow_t/fast_t:.1f}x")
```

**Example**: [profiling.py](../../examples/python/advanced/profiling.py)

---

## Escape from the GIL — Subinterpreters and Free-Threading (Python 3.12+)

**Explanation**: Python 3.12 introduced per-interpreter GILs (PEP 684): each subinterpreter has its own GIL, enabling true CPU parallelism between interpreters in the same process. The experimental API is `_interpreters` (low-level) or the higher-level `interpreters` module (3.13+). Python 3.13 ships an optional free-threaded build (`python3.13t`, PEP 703) that disables the GIL entirely — regular `threading.Thread` gains true CPU parallelism. Both features are experimental in 3.13; the goal is production-ready in 3.14+.

**Real-World Scenario**: A data analysis framework needs to process 16 independent DataFrames in parallel using pure Python code (no NumPy). Previously this required `multiprocessing` (high memory, IPC overhead). Python 3.13 free-threaded mode lets 16 threads run truly in parallel with shared memory — the same pattern but 5× lower memory overhead.

```python
import sys

def demonstrate_threading_landscape():
    """Shows the evolution of Python parallelism options."""
    version = sys.version_info

    options = {
        "threading (I/O-bound)": "GIL released on I/O — works today",
        "multiprocessing":        "True parallelism via processes — works today",
        "asyncio":                "Cooperative concurrency — works today",
        "C extensions (NumPy)":   "Release GIL explicitly — works today",
    }

    if version >= (3, 12):
        options["Per-interpreter GIL"] = "PEP 684 — experimental (3.12+)"
    if version >= (3, 13):
        options["Free-threaded (no GIL)"] = "PEP 703 — use python3.13t build"

    for name, status in options.items():
        print(f"  {name:35} → {status}")

print(f"Python {sys.version_info.major}.{sys.version_info.minor} parallelism options:")
demonstrate_threading_landscape()

# Check if running in free-threaded mode
if hasattr(sys, "_is_gil_enabled"):
    print(f"\nGIL enabled: {sys._is_gil_enabled()}")
    if not sys._is_gil_enabled():
        print("  Running in FREE-THREADED mode — true CPU parallelism available!")
```

**Example**: [free_threading.py](../../examples/python/advanced/free_threading.py)
