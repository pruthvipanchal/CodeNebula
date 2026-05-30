# Compile: python3 memory_management.py
# Output:
# Cycle GC collected objects
# None (auto-evicted)

import gc
import weakref

class Node:
    def __init__(self, value):
        self.value = value
        self.next = None

a = Node("A")
b = Node("B")
a.next = b
b.next = a  # Reference cycle

del a, b
collected = gc.collect()
print(f"Cycle GC collected {collected} objects")

# weakref — cache that doesn't prevent GC
class ExpensiveObject:
    def __init__(self, key): self.key = key
    def __repr__(self): return f"ExpensiveObject({self.key!r})"

cache: weakref.WeakValueDictionary = weakref.WeakValueDictionary()
obj = ExpensiveObject("config")
cache["config"] = obj
print(f"In cache: {cache.get('config')}")

del obj
gc.collect()
print(f"After del: {cache.get('config')}")  # None

# Reference counting basics
import sys
x = [1, 2, 3]
print(f"Ref count for x: {sys.getrefcount(x)}")  # 2 (x + getrefcount arg)
y = x
print(f"Ref count after y=x: {sys.getrefcount(x)}")  # 3
del y
print(f"Ref count after del y: {sys.getrefcount(x)}")  # 2
