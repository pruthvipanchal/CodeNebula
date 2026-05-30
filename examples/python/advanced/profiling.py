# Compile: python3 profiling.py
# Output:
# Speedup printed between slow and fast implementations

import cProfile
import pstats
import io
import timeit

def slow_sum(n: int) -> int:
    total = 0
    for i in range(n):
        total += int(str(i))
    return total

def fast_sum(n: int) -> int:
    return sum(range(n))

pr = cProfile.Profile()
pr.enable()
slow_sum(5_000)
pr.disable()

buf = io.StringIO()
ps = pstats.Stats(pr, stream=buf).sort_stats("cumulative")
ps.print_stats(3)
output = buf.getvalue()
# Print just the first few lines
for line in output.splitlines()[:8]:
    if line.strip():
        print(line)

slow_t = timeit.timeit("slow_sum(500)", globals={"slow_sum": slow_sum}, number=200)
fast_t = timeit.timeit("fast_sum(500)", globals={"fast_sum": fast_sum}, number=200)
print(f"\nslow_sum: {slow_t:.3f}s")
print(f"fast_sum: {fast_t:.3f}s")
print(f"speedup:  {slow_t/fast_t:.1f}x")
