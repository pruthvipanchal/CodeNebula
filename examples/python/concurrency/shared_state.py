# Compile: python3 shared_state.py
# Output:
# Counter: 10000

import threading

class ThreadSafeCounter:
    def __init__(self) -> None:
        self._value = 0
        self._lock = threading.Lock()

    def increment(self) -> None:
        with self._lock:
            self._value += 1

    @property
    def value(self) -> int:
        with self._lock:
            return self._value

counter = ThreadSafeCounter()

def worker(n: int) -> None:
    for _ in range(n):
        counter.increment()

threads = [threading.Thread(target=worker, args=(1000,)) for _ in range(10)]
for t in threads: t.start()
for t in threads: t.join()

print(f"Counter: {counter.value}")  # Always 10000 with the lock
