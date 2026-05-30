# Compile: python3 iterators.py
# Output:
# 1 2 3 4 5
# [1, 2, 3, 4, 5]

class CountUp:
    def __init__(self, start: int, stop: int):
        self._current = start
        self._stop = stop

    def __iter__(self):
        return self

    def __next__(self):
        if self._current >= self._stop:
            raise StopIteration
        val = self._current
        self._current += 1
        return val

for n in CountUp(1, 6):
    print(n, end=" ")
print()

# Generator expression — equivalent, shorter
gen = (n for n in range(1, 6))
print(list(gen))

# Protocol functions
it = iter([10, 20, 30])
print(next(it))   # 10
print(next(it))   # 20
print(next(it, "done"))  # 30
print(next(it, "done"))  # done (default, no StopIteration)

# iter() with sentinel
import io
f = io.StringIO("a\nb\n\n")
lines = list(iter(f.readline, ""))  # reads until empty string
print(lines)
