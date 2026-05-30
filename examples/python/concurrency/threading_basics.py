# Compile: python3 threading_basics.py
# Output:
# Fetched 10 URLs

import threading
import time
import random
from queue import Queue

results: Queue = Queue()

def fetch(url: str) -> None:
    time.sleep(random.uniform(0.01, 0.05))
    status = 200 if random.random() > 0.1 else 500
    results.put((url, status))

urls = [f"https://api.example.com/item/{i}" for i in range(10)]

start = time.perf_counter()
threads = [threading.Thread(target=fetch, args=(u,)) for u in urls]
for t in threads: t.start()
for t in threads: t.join()
elapsed = time.perf_counter() - start

fetched = []
while not results.empty():
    fetched.append(results.get())

print(f"Fetched {len(fetched)} URLs in {elapsed:.3f}s")
successes = sum(1 for _, s in fetched if s == 200)
print(f"Success: {successes}/{len(fetched)}")

# Thread-local storage
local = threading.local()

def worker(name: str) -> None:
    local.name = name
    time.sleep(0.01)
    print(f"Thread sees: {local.name}")

threads = [threading.Thread(target=worker, args=(f"worker-{i}",)) for i in range(3)]
for t in threads: t.start()
for t in threads: t.join()
