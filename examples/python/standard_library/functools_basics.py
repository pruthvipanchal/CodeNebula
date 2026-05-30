# Compile: python3 functools_basics.py
# Output:
# 12586269025
# [1, 4, 9, 16, 25]
# 120

import functools
import time

@functools.lru_cache(maxsize=None)
def fib(n: int) -> int:
    if n < 2:
        return n
    return fib(n - 1) + fib(n - 2)

start = time.perf_counter()
print(fib(50))
elapsed = time.perf_counter() - start
print(f"Time: {elapsed:.6f}s")
print(fib.cache_info())

def power(base, exp):
    return base ** exp

square = functools.partial(power, exp=2)
cube   = functools.partial(power, exp=3)
print([square(x) for x in range(1, 6)])
print([cube(x) for x in range(1, 4)])

product = functools.reduce(lambda a, b: a * b, range(1, 6))
print(product)

# total_ordering — define just __eq__ + __lt__, get the rest
@functools.total_ordering
class Priority:
    def __init__(self, level): self.level = level
    def __eq__(self, other): return self.level == other.level
    def __lt__(self, other): return self.level < other.level

p1, p2 = Priority(1), Priority(3)
print(p1 < p2, p1 <= p2, p1 > p2, p1 >= p2)
