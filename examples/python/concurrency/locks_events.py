# Compile: python3 locks_events.py
# Output:
# Completed 10 requests with concurrency limit 3
# Worker: starting work

import asyncio
import threading
import time

async def rate_limited_fetch(sem: asyncio.Semaphore, url: str) -> str:
    async with sem:
        await asyncio.sleep(0.01)
        return f"OK: {url}"

async def async_main() -> None:
    sem = asyncio.Semaphore(3)
    urls = [f"https://api.example.com/{i}" for i in range(10)]
    results = await asyncio.gather(*[rate_limited_fetch(sem, u) for u in urls])
    print(f"Completed {len(results)} requests with concurrency limit 3")

asyncio.run(async_main())

# threading.Event
ready = threading.Event()

def worker():
    ready.wait()
    print("Worker: starting work")

t = threading.Thread(target=worker)
t.start()
time.sleep(0.05)
ready.set()
t.join()

# threading.Lock
lock = threading.Lock()
shared = 0

def increment(n):
    global shared
    for _ in range(n):
        with lock:
            shared += 1

threads = [threading.Thread(target=increment, args=(100,)) for _ in range(5)]
for t in threads: t.start()
for t in threads: t.join()
print(f"Shared counter: {shared}")  # Always 500
