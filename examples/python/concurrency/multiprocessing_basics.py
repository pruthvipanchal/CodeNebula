# Compile: python3 multiprocessing_basics.py
# Output:
# Primes below 50000 and time printed

import multiprocessing
import os
import time

def is_prime(n: int) -> bool:
    if n < 2: return False
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0: return False
    return True

def count_primes_in_range(args: tuple) -> int:
    lo, hi = args
    return sum(1 for n in range(lo, hi) if is_prime(n))

if __name__ == "__main__":
    N = 50_000
    num_workers = min(os.cpu_count() or 2, 4)
    chunk_size  = N // num_workers
    ranges = [(i * chunk_size, (i + 1) * chunk_size) for i in range(num_workers)]

    start = time.perf_counter()
    with multiprocessing.Pool(num_workers) as pool:
        counts = pool.map(count_primes_in_range, ranges)
    elapsed = time.perf_counter() - start

    print(f"Primes below {N}: {sum(counts)}")
    print(f"Time ({num_workers} workers): {elapsed:.3f}s")
