# Compile: python3 gil_demo.py
# Output:
# Single and multi-threaded times printed (multi ~= single due to GIL)

import threading
import time

def cpu_bound(n: int) -> int:
    while n > 0:
        n -= 1
    return n

N = 2_000_000

start = time.perf_counter()
cpu_bound(N)
cpu_bound(N)
single = time.perf_counter() - start

t1 = threading.Thread(target=cpu_bound, args=(N,))
t2 = threading.Thread(target=cpu_bound, args=(N,))
start = time.perf_counter()
t1.start(); t2.start()
t1.join(); t2.join()
multi = time.perf_counter() - start

print(f"Single-threaded: {single:.3f}s")
print(f"Multi-threaded:  {multi:.3f}s")
print(f"Ratio: {multi/single:.2f}x (expect ~1.0 due to GIL)")
print("For CPU-bound work, use multiprocessing instead.")
