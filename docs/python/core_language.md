# Python — Core Language

## Variables and Types

**Explanation**: Python is dynamically typed — a variable is just a name bound to an object; the type lives on the object, not the variable. Everything is an object: integers, strings, functions, classes. Python's built-in types include `int`, `float`, `complex`, `bool`, `str`, `bytes`, `list`, `tuple`, `dict`, `set`, `frozenset`, and `NoneType`. `type()` returns an object's type; `isinstance()` checks inheritance.

**Real-World Scenario**: When reading config files you get strings like `"42"` and `"true"`. `int("42")` and `"true".lower() == "true"` convert them safely. Python's dynamic typing lets you write polymorphic functions that work on any type with the right interface — duck typing in action.

```python
x = 42            # int
y = 3.14          # float
z = 1 + 2j        # complex
s = "hello"       # str
b = b"bytes"      # bytes
t = (1, 2, 3)     # tuple (immutable)
lst = [1, 2, 3]   # list (mutable)
d = {"a": 1}      # dict
nothing = None    # NoneType

print(type(x), isinstance(x, int))   # <class 'int'> True
print(type(s), len(s))               # <class 'str'> 5
```

**Example**: [variables_and_types.py](../../examples/python/core_language/variables_and_types.py)

---

## Control Flow

**Explanation**: Python's control flow uses `if`/`elif`/`else`, `for` (iterating any iterable), `while`, `break`, `continue`, and `else` clauses on loops (the `else` runs if the loop wasn't broken out of). Conditional expressions (`x if cond else y`) provide ternary-style logic. Python has no `switch`; use `match`/`case` (3.10+) or dicts for dispatch tables.

**Real-World Scenario**: Searching a list for a target value: use a `for`/`else` — the `else` block only runs if the loop completes without `break`, making "not found" logic explicit without a sentinel variable.

```python
# for/else — runs else only if loop wasn't broken
def find_prime(n: int) -> bool:
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0:
            break
    else:
        return True  # No divisor found
    return False

print([x for x in range(2, 20) if find_prime(x)])
# [2, 3, 5, 7, 11, 13, 17, 19]

# Conditional expression
score = 85
grade = "pass" if score >= 60 else "fail"
```

**Example**: [control_flow.py](../../examples/python/core_language/control_flow.py)

---

## Functions — *args, **kwargs, and Defaults

**Explanation**: Python functions support positional args, keyword args, defaults, variadic positional (`*args` → tuple), variadic keyword (`**kwargs` → dict), positional-only params (before `/`), and keyword-only params (after `*`). Functions are first-class: they can be passed, returned, and stored. The default value is evaluated once at definition time — a common gotcha with mutable defaults.

**Real-World Scenario**: A logging function `log(message, level="INFO", *tags, timestamp=True, **extra)` demonstrates the full parameter spectrum: required positional, default, variadic, keyword-only with default, and extra keywords — all in one signature.

```python
def create_connection(host, port=5432, /, *, timeout=30, **options):
    # host, port: positional-only (before /)
    # timeout: keyword-only (after *)
    # options: extra keyword args
    print(f"Connecting to {host}:{port} (timeout={timeout})")
    print(f"Extra options: {options}")

create_connection("localhost", 5433, timeout=10, ssl=True, retry=3)

# *args and **kwargs forwarding
def wrapper(*args, **kwargs):
    print(f"args={args}, kwargs={kwargs}")
    return sum(args)

print(wrapper(1, 2, 3, label="sum"))
```

**Example**: [functions.py](../../examples/python/core_language/functions.py)

---

## Lambda Functions

**Explanation**: `lambda` creates an anonymous single-expression function. It's syntactically limited — no statements, no docstrings, no multiple expressions — by design. Lambdas are most useful as short callbacks to `sorted()`, `map()`, `filter()`, or `functools.reduce()`. For anything more complex, a named `def` is clearer.

**Real-World Scenario**: Sorting a list of employee dicts by department then salary requires a compound key. `sorted(employees, key=lambda e: (e["dept"], -e["salary"]))` expresses the sort criterion inline without defining a named comparator.

```python
# Sort by multiple keys inline
employees = [
    {"name": "Alice", "dept": "eng", "salary": 120000},
    {"name": "Bob",   "dept": "eng", "salary": 95000},
    {"name": "Carol", "dept": "hr",  "salary": 80000},
]
ranked = sorted(employees, key=lambda e: (e["dept"], -e["salary"]))
for e in ranked:
    print(f"{e['dept']:5} {e['salary']:>7,}  {e['name']}")

# Lambda with map and filter
nums = range(1, 11)
evens_sq = list(map(lambda x: x**2, filter(lambda x: x % 2 == 0, nums)))
print(evens_sq)  # [4, 16, 36, 64, 100]
```

**Example**: [lambda_functions.py](../../examples/python/core_language/lambda_functions.py)

---

## Comprehensions

**Explanation**: Python has four comprehension forms: list `[expr for x in it if cond]`, dict `{k: v for ...}`, set `{expr for ...}`, and generator `(expr for ...)`. Comprehensions are faster than equivalent `for` loops (the loop variable is local, avoiding global lookup) and more readable. Nested comprehensions are legal but keep nesting shallow — beyond two levels, a named generator is clearer.

**Real-World Scenario**: Inverting a mapping (swapping keys and values) with a dict comprehension: `{v: k for k, v in mapping.items()}`. Flattening a 2D matrix into a 1D list: `[cell for row in matrix for cell in row]` — the order matches reading the nested loop left-to-right.

```python
# List, dict, set, generator comprehensions
matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
flat   = [x for row in matrix for x in row]
evens  = {x for x in flat if x % 2 == 0}
sq_map = {x: x**2 for x in range(1, 6)}
gen    = (x**3 for x in range(1, 6))  # lazy

print(flat)              # [1, 2, 3, 4, 5, 6, 7, 8, 9]
print(evens)             # {2, 4, 6, 8}
print(sq_map)            # {1: 1, 2: 4, 3: 9, 4: 16, 5: 25}
print(list(gen))         # [1, 8, 27, 64, 125]
```

**Example**: [comprehensions.py](../../examples/python/core_language/comprehensions.py)

---

## Generators and the `yield` Keyword

**Explanation**: A generator function uses `yield` instead of `return` — calling it returns a generator object (an iterator). Execution pauses at each `yield` and resumes on the next `next()` call. Generators are memory-efficient for large sequences: instead of building a full list in memory, values are produced on demand. `yield from` delegates to a sub-generator, enabling generator pipelines and recursive generators.

**Real-World Scenario**: Reading a 10 GB log file line by line: `for line in open("huge.log")` already uses a generator under the hood. A custom pipeline `parse(decompress(read_chunks("data.gz")))` where each step is a generator processes terabytes without loading the file into RAM.

```python
import itertools

def fibonacci():
    """Infinite Fibonacci generator."""
    a, b = 0, 1
    while True:
        yield a
        a, b = b, a + b

# Take first 10 Fibonacci numbers
fibs = list(itertools.islice(fibonacci(), 10))
print(fibs)  # [0, 1, 1, 2, 3, 5, 8, 13, 21, 34]

def read_in_chunks(file_obj, chunk_size=1024):
    """Generator that yields file content in fixed-size chunks."""
    while chunk := file_obj.read(chunk_size):
        yield chunk
```

**Example**: [generators.py](../../examples/python/core_language/generators.py)

---

## Decorators

**Explanation**: A decorator is a callable that takes a function and returns a (usually modified) function. The `@decorator` syntax is syntactic sugar for `func = decorator(func)`. Decorators are used for cross-cutting concerns: logging, timing, access control, caching, retry logic, and input validation — without modifying the decorated function's body. `functools.wraps` preserves the wrapped function's metadata (`__name__`, `__doc__`).

**Real-World Scenario**: A web framework registers URL routes with `@app.route("/users")`. An internal API enforces authentication with `@require_auth`. A data pipeline retries flaky network calls with `@retry(max_attempts=3)`. All these are decorators — the business logic is untouched, and behaviour is composed.

```python
import functools
import time

def timer(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        start = time.perf_counter()
        result = func(*args, **kwargs)
        elapsed = time.perf_counter() - start
        print(f"{func.__name__} took {elapsed:.4f}s")
        return result
    return wrapper

def retry(max_attempts=3):
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            for attempt in range(1, max_attempts + 1):
                try:
                    return func(*args, **kwargs)
                except Exception as e:
                    if attempt == max_attempts:
                        raise
                    print(f"Attempt {attempt} failed: {e}. Retrying...")
        return wrapper
    return decorator

@timer
@retry(max_attempts=3)
def fetch_data(url: str) -> str:
    return f"data from {url}"

print(fetch_data("https://example.com"))
```

**Example**: [decorators.py](../../examples/python/core_language/decorators.py)

---

## Classes and Object-Oriented Programming

**Explanation**: Python uses class-based OOP with dynamic dispatch. `__init__` is the initializer (not a constructor — `__new__` allocates the object). Instance attributes are set on `self`; class attributes are shared across instances. `@classmethod` receives the class as first arg; `@staticmethod` receives neither. Properties (`@property`) give attribute-style access to computed values.

**Real-World Scenario**: A `BankAccount` class encapsulates balance state. The balance property enforces a read-only interface, `deposit`/`withdraw` enforce business rules (no negative balances), and `@classmethod from_dict` provides an alternate constructor for deserialising from JSON.

```python
class BankAccount:
    interest_rate = 0.02  # class attribute

    def __init__(self, owner: str, balance: float = 0.0):
        self._owner = owner
        self._balance = balance

    @property
    def balance(self) -> float:
        return self._balance

    def deposit(self, amount: float) -> None:
        if amount <= 0:
            raise ValueError("Deposit must be positive")
        self._balance += amount

    def withdraw(self, amount: float) -> None:
        if amount > self._balance:
            raise ValueError("Insufficient funds")
        self._balance -= amount

    @classmethod
    def from_dict(cls, data: dict) -> "BankAccount":
        return cls(data["owner"], data.get("balance", 0.0))

    def __repr__(self) -> str:
        return f"BankAccount(owner={self._owner!r}, balance={self._balance:.2f})"

acc = BankAccount.from_dict({"owner": "Alice", "balance": 1000})
acc.deposit(500)
acc.withdraw(200)
print(acc)  # BankAccount(owner='Alice', balance=1300.00)
```

**Example**: [classes.py](../../examples/python/core_language/classes.py)

---

## Inheritance and MRO

**Explanation**: Python supports multiple inheritance. The Method Resolution Order (MRO) determines which class's method is called when multiple bases define the same name. Python uses the C3 linearization algorithm — `ClassName.__mro__` shows the order. `super()` follows the MRO, making cooperative multiple inheritance possible (all `__init__` methods in the hierarchy can be called in sequence using `super()`).

**Real-World Scenario**: A Django model (`MyModel(TimeStampedMixin, SoftDeleteMixin, models.Model)`) uses multiple inheritance to layer created/updated timestamps and soft-delete behaviour on top of the ORM base. Each mixin calls `super().__init__()` so all initializers run in MRO order.

```python
class A:
    def who(self): return "A"

class B(A):
    def who(self): return f"B -> {super().who()}"

class C(A):
    def who(self): return f"C -> {super().who()}"

class D(B, C):
    def who(self): return f"D -> {super().who()}"

d = D()
print(d.who())      # D -> B -> C -> A
print(D.__mro__)    # (<class 'D'>, <class 'B'>, <class 'C'>, <class 'A'>, <class 'object'>)
```

**Example**: [inheritance_mro.py](../../examples/python/core_language/inheritance_mro.py)

---

## Dunder (Magic) Methods

**Explanation**: Dunder methods (`__method__`) let classes integrate with Python's built-in operators and protocols. `__repr__` / `__str__` control string representation. `__len__`, `__getitem__`, `__setitem__`, `__iter__` implement the sequence and mapping protocols. `__enter__` / `__exit__` enable the `with` statement. `__eq__`, `__lt__`, `__hash__` control equality and hashing. `__call__` makes instances callable.

**Real-World Scenario**: A `Matrix` class implementing `__add__`, `__mul__`, `__getitem__`, and `__repr__` works with `+`, `*`, `[]`, and `print()` — the same interface as built-in numeric types. This is how NumPy arrays feel like "native" objects.

```python
class Vector:
    def __init__(self, *components):
        self._data = list(components)

    def __repr__(self): return f"Vector{tuple(self._data)}"
    def __len__(self):  return len(self._data)
    def __getitem__(self, i): return self._data[i]
    def __add__(self, other): return Vector(*(a + b for a, b in zip(self, other)))
    def __mul__(self, scalar): return Vector(*(x * scalar for x in self))
    def __eq__(self, other):  return self._data == list(other)

v1 = Vector(1, 2, 3)
v2 = Vector(4, 5, 6)
print(v1 + v2)    # Vector(5, 7, 9)
print(v1 * 3)     # Vector(3, 6, 9)
print(len(v1))    # 3
print(v1[1])      # 2
```

**Example**: [dunder_methods.py](../../examples/python/core_language/dunder_methods.py)

---

## Context Managers and `with`

**Explanation**: The `with` statement guarantees cleanup code runs even if exceptions occur. Any object implementing `__enter__` / `__exit__` is a context manager. The `contextlib.contextmanager` decorator lets you write generator-based context managers — `yield` is the body of the `with` block. `contextlib.ExitStack` composes a dynamic number of context managers.

**Real-World Scenario**: Database transactions: `with db.transaction():` commits on success, rolls back on any exception — no `try/finally` boilerplate needed. Opening multiple files simultaneously: `with open(a) as f1, open(b) as f2:` ensures both are closed even if the second `open` raises.

```python
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

with timed("demo"):
    with managed_resource("database") as res:
        print(f"Using {res}")
```

**Example**: [context_managers.py](../../examples/python/core_language/context_managers.py)

---

## Exception Handling

**Explanation**: Python exceptions are objects that inherit from `BaseException`. The hierarchy: `BaseException` → `Exception` → specific exceptions like `ValueError`, `TypeError`, `IOError`. The `try`/`except`/`else`/`finally` structure: `except` catches errors, `else` runs only if no exception occurred, `finally` always runs. Python 3.11+ added `ExceptionGroup` for handling multiple simultaneous exceptions (from `asyncio.TaskGroup`).

**Real-World Scenario**: Parsing user input: catch `ValueError` for bad numbers, `KeyError` for missing dict keys. Always be specific — catching bare `except:` or `except Exception:` hides bugs. Define custom exceptions by inheriting from `Exception` to add domain-specific error types.

```python
class InsufficientFundsError(ValueError):
    def __init__(self, balance: float, amount: float):
        self.balance = balance
        self.amount = amount
        super().__init__(f"Need {amount:.2f} but only have {balance:.2f}")

def safe_divide(a, b):
    try:
        result = a / b
    except ZeroDivisionError:
        return None
    except TypeError as e:
        raise ValueError(f"Arguments must be numbers: {e}") from e
    else:
        return result
    finally:
        pass  # cleanup always runs

print(safe_divide(10, 2))   # 5.0
print(safe_divide(10, 0))   # None

try:
    raise InsufficientFundsError(50.0, 100.0)
except InsufficientFundsError as e:
    print(e)  # Need 100.00 but only have 50.00
```

**Example**: [exception_handling.py](../../examples/python/core_language/exception_handling.py)

---

## Iterables, Iterators, and the Iterator Protocol

**Explanation**: Python's `for` loop works on any *iterable* — an object that implements `__iter__()` returning an *iterator*. An iterator implements `__next__()` raising `StopIteration` when exhausted. Built-ins like `list`, `dict`, `str`, `range`, files, and generators are all iterables. `iter(obj)` and `next(obj)` are the protocol functions. Understanding this protocol explains how `for`, comprehensions, `zip`, `map`, `filter`, and `itertools` all interoperate.

**Real-World Scenario**: A custom `DatabaseCursor` class that lazily fetches rows in batches from a remote database can implement the iterator protocol. Callers use it with a normal `for` loop — they don't need to know about the batching.

```python
class CountUp:
    """Iterator that counts from start to stop."""
    def __init__(self, start: int, stop: int):
        self._current = start
        self._stop = stop

    def __iter__(self):
        return self  # Iterator is its own iterable

    def __next__(self):
        if self._current >= self._stop:
            raise StopIteration
        val = self._current
        self._current += 1
        return val

for n in CountUp(1, 6):
    print(n, end=" ")  # 1 2 3 4 5

# Equivalent generator expression
gen = (n for n in range(1, 6))
print(list(gen))  # [1, 2, 3, 4, 5]
```

**Example**: [iterators.py](../../examples/python/core_language/iterators.py)

---

## Type Hints (PEP 484)

**Explanation**: Python 3.5 introduced type hints via PEP 484. They are not enforced at runtime — they're metadata for static type checkers (`mypy`, `pyright`, `ruff`). The `typing` module provides `List`, `Dict`, `Optional`, `Union`, `Callable`, `TypeVar`, `Generic`, `Protocol`. Python 3.10+ replaced `Optional[X]` with `X | None` and `Union[X, Y]` with `X | Y`. Python 3.12 added `type` statement for type aliases.

**Real-World Scenario**: A large API client library adding type hints catches errors like passing a `str` where an `int` is expected before code reaches production. IDE autocomplete becomes precise — you get attribute suggestions specific to the return type of each function.

```python
from typing import TypeVar, Generic, Callable
from collections.abc import Iterable

T = TypeVar("T")
U = TypeVar("U")

def first(items: Iterable[T]) -> T | None:
    return next(iter(items), None)

def transform(items: list[T], fn: Callable[[T], U]) -> list[U]:
    return [fn(item) for item in items]

class Stack(Generic[T]):
    def __init__(self) -> None:
        self._items: list[T] = []

    def push(self, item: T) -> None:
        self._items.append(item)

    def pop(self) -> T:
        return self._items.pop()

stack: Stack[int] = Stack()
stack.push(1)
stack.push(2)
print(stack.pop())  # 2
print(first([10, 20, 30]))  # 10
print(transform(["a", "bb", "ccc"], len))  # [1, 2, 3]
```

**Example**: [type_hints.py](../../examples/python/core_language/type_hints.py)

---

## Walrus Operator `:=` (Python 3.8+)

**Explanation**: The walrus operator (`:=`, PEP 572) assigns a value to a variable and returns it in a single expression. It's most useful inside `while` conditions (avoiding a duplicate read), comprehension conditions (capturing an intermediate computed value), and `if` statements (avoiding re-computation). It makes imperative "compute, check, use" patterns more concise without sacrificing readability when used judiciously.

**Real-World Scenario**: Reading a socket in a loop: `while data := sock.recv(1024):` reads data and checks for EOF (empty bytes) in one expression. Previously you needed `data = sock.recv(1024); while data:` — two lines with the read duplicated before the loop.

```python
import re

# Walrus in a while loop — read chunks until EOF
def count_chars(text: str, chunk_size: int = 4) -> int:
    total = 0
    pos = 0
    while chunk := text[pos:pos + chunk_size]:
        total += len(chunk)
        pos += chunk_size
    return total

print(count_chars("Hello, World!"))  # 13

# Walrus in comprehension — avoid recomputing expensive fn
data = [1, -2, 3, -4, 5]
results = [y for x in data if (y := x * x) > 4]
print(results)  # [4, 9, 16, 25] — wait, condition is y > 4
# => [9, 16, 25]

# Walrus in regex match
text = "Order #12345 placed"
if m := re.search(r"#(\d+)", text):
    print(f"Order ID: {m.group(1)}")  # Order ID: 12345
```

**Example**: [walrus_operator.py](../../examples/python/core_language/walrus_operator.py)

---

## Structural Pattern Matching (`match`/`case`, Python 3.10+)

**Explanation**: `match`/`case` (PEP 634) is not a simple switch — it performs structural decomposition. Patterns can match literals, variable capture (`case Point(x, y):`), sequences (`case [first, *rest]:`), mappings (`case {"action": action}:`), class patterns, OR patterns (`|`), and guards (`if condition`). Captured variables are bound in the case body. The `_` wildcard matches anything without binding.

**Real-World Scenario**: A command-line tool parser dispatches commands. An HTTP router matches request objects. A compiler's AST walk pattern-matches on node types. All these were previously written as `isinstance` chains — `match` makes the structure of the data the structure of the code.

```python
from dataclasses import dataclass

@dataclass
class Point:
    x: float
    y: float

def classify_point(p):
    match p:
        case Point(x=0, y=0):
            return "origin"
        case Point(x=0, y=y):
            return f"on y-axis at {y}"
        case Point(x=x, y=0):
            return f"on x-axis at {x}"
        case Point(x=x, y=y) if x == y:
            return f"on diagonal at {x}"
        case Point(x=x, y=y):
            return f"point ({x}, {y})"

for pt in [Point(0, 0), Point(0, 5), Point(3, 0), Point(4, 4), Point(1, 2)]:
    print(classify_point(pt))
```

**Example**: [pattern_matching.py](../../examples/python/core_language/pattern_matching.py)

---

## Dataclasses (Python 3.7+)

**Explanation**: `@dataclass` auto-generates `__init__`, `__repr__`, `__eq__` (and optionally `__lt__`, `__hash__`, `__post_init__`) from class-level annotations. With `frozen=True` the class is immutable (and hashable). `field()` controls defaults, whether a field appears in `__repr__`, and `default_factory` for mutable defaults. Python 3.10 added `slots=True` for automatic `__slots__` (lower memory, faster attribute access).

**Real-World Scenario**: API response models, configuration objects, and database row types are all naturally dataclasses: lots of fields, equality by value, serializable. They eliminate the boilerplate of writing `__init__` + `__repr__` + `__eq__` by hand — which is a constant source of maintenance bugs.

```python
from dataclasses import dataclass, field
from typing import ClassVar

@dataclass(order=True, frozen=True)
class Version:
    major: int
    minor: int
    patch: int = 0
    _registry: ClassVar[list] = []  # ClassVar excluded from __init__

    def __str__(self) -> str:
        return f"{self.major}.{self.minor}.{self.patch}"

@dataclass
class Package:
    name: str
    version: Version
    dependencies: list[str] = field(default_factory=list)
    _internal: str = field(default="", repr=False)

v1 = Version(3, 11)
v2 = Version(3, 12)
print(v1 < v2)   # True (order=True generates __lt__)
print(str(v1))   # 3.11.0

pkg = Package("requests", v2, ["certifi", "urllib3"])
print(pkg)
# Package(name='requests', version=3.12.0, dependencies=['certifi', 'urllib3'])
```

**Example**: [dataclasses.py](../../examples/python/core_language/dataclasses.py)

---

## f-Strings and String Formatting

**Explanation**: f-strings (PEP 498, Python 3.6+) embed expressions in string literals: `f"{expr}"`. They call `__format__` on the object with an optional format spec after `:`. Python 3.12 removed the restriction that f-string expressions couldn't contain the same quote type as the outer string. `=` suffix (`f"{value=}"`) prints both the expression text and its value — a debug shorthand.

**Real-World Scenario**: Formatting financial reports, generating SQL (carefully — prefer parameterized queries), building log messages, and rendering templates all use f-strings in modern Python. The `format_spec` mini-language handles padding, alignment, number formatting, and date formatting without importing a library.

```python
import math
from datetime import datetime

# Format spec: [[fill]align][sign][#][0][width][grouping][.prec][type]
pi      = math.pi
salary  = 123456.789
now     = datetime.now()

print(f"{pi:.4f}")            # 3.1416
print(f"{salary:>15,.2f}")    # 123,456.79 (right-aligned, 15 wide)
print(f"{42:#010b}")          # 0b00101010 (binary with prefix, 10 wide)
print(f"{now:%Y-%m-%d}")      # 2024-01-15 (date format)

# Debug shorthand (Python 3.8+)
x = [1, 2, 3]
print(f"{x=}")                # x=[1, 2, 3]

# Nested f-strings and Python 3.12 same-quote expressions
items = ["a", "b", "c"]
print(f"{'|'.join(items)}")   # a|b|c (Python 3.12+: same quote inside)
```

**Example**: [fstrings.py](../../examples/python/core_language/fstrings.py)
