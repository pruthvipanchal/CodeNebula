# Compile: python3 typing_advanced.py
# Output:
# 1
# [1, 2, 3]

from typing import TypeVar, Generic, Protocol, TypedDict, Literal, runtime_checkable
from collections.abc import Iterator

T = TypeVar("T")
S = TypeVar("S", bound="Orderable")

@runtime_checkable
class Orderable(Protocol):
    def __lt__(self: S, other: S) -> bool: ...

def minimum(items: list[S]) -> S:
    return min(items)

class Stack(Generic[T]):
    def __init__(self) -> None:
        self._items: list[T] = []
    def push(self, item: T) -> None: self._items.append(item)
    def pop(self) -> T: return self._items.pop()
    def __iter__(self) -> Iterator[T]: return iter(self._items)
    def __len__(self) -> int: return len(self._items)

class UserConfig(TypedDict):
    name: str
    role: Literal["admin", "user", "guest"]
    active: bool

cfg: UserConfig = {"name": "Alice", "role": "admin", "active": True}
print(cfg["name"])

stack: Stack[int] = Stack()
for n in [1, 2, 3]:
    stack.push(n)

print(list(stack))
print(minimum([3, 1, 4, 1, 5]))

# isinstance check via runtime_checkable Protocol
print(isinstance(42, Orderable))    # True (int has __lt__)
print(isinstance("hi", Orderable))  # True (str has __lt__)
