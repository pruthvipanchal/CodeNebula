# Compile: python3 type_hints.py
# Output:
# 2
# 10
# [1, 2, 3]

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

    def __len__(self) -> int:
        return len(self._items)

stack: Stack[int] = Stack()
stack.push(1)
stack.push(2)
print(stack.pop())
print(first([10, 20, 30]))
print(transform(["a", "bb", "ccc"], len))

# Union types (Python 3.10+)
def process(value: int | str) -> str:
    return str(value).upper()

print(process(42))    # 42
print(process("hi"))  # HI
