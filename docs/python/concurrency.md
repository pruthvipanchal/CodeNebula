# Python — Concurrency

## The Global Interpreter Lock (GIL)

**Explanation**: The GIL is a mutex in CPython that allows only one thread to execute Python bytecode at a time, even on multi-core CPUs. It exists because CPython's memory management (reference counting) is not thread-safe. The GIL makes single-threaded programs faster (no locking overhead) and C extension writing simpler. The consequence: CPU-bound multi-threaded Python programs don't scale across cores. I/O-bound workloads are largely unaffected — the GIL is released while waiting for I/O. Python 3.13 introduced an optional free-threaded build (`python3.13t`) that removes the GIL.

**Real-World Scenario**: Two threads computing prime numbers simultaneously on a 16-core machine run at the same total speed as one thread — the GIL serializes them. The same two threads making HTTP requests run twice as fast — each thread releases the GIL while waiting for the network, so they truly overlap.

```python
import threading
import time

def cpu_bound(n: int) -> int:
    """Count-down loop — pure Python, GIL-bound."""
    while n > 0:
        n -= 1
    return n

N = 10_000_000

# Single-threaded baseline
start = time.perf_counter()
cpu_bound(N)
cpu_bound(N)
single = time.perf_counter() - start

# Multi-threaded — GIL prevents true parallelism
t1 = threading.Thread(target=cpu_bound, args=(N,))
t2 = threading.Thread(target=cpu_bound, args=(N,))
start = time.perf_counter()
t1.start(); t2.start()
t1.join(); t2.join()
multi = time.perf_counter() - start

print(f"Single: {single:.2f}s")
print(f"Multi:  {multi:.2f}s  (should be ~same or slower due to GIL)")
```

**Example**: [gil_demo.py](../../examples/python/concurrency/gil_demo.py)

---

## `threading` — OS-Level Threads

**Explanation**: `threading.Thread` runs a callable in an OS thread. Threads share the process's memory — communication is via shared objects, protected by `threading.Lock`, `RLock`, `Semaphore`, `Event`, `Condition`, and `Barrier`. `threading.local()` provides thread-local storage. Threads are well-suited for I/O-bound concurrency: database queries, HTTP requests, file I/O. A `Daemon` thread dies automatically when the main thread exits.

**Real-World Scenario**: A web scraper fetches 100 URLs concurrently using 20 threads. Each thread blocks on network I/O — the GIL is released during `socket.recv`, so threads truly run concurrently at the network level. Total time ≈ max single-URL latency, not sum.

```python
import threading
import time
import random
from queue import Queue

results: Queue[tuple[str, int]] = Queue()

def fetch(url: str) -> None:
    """Simulates an HTTP request with random latency."""
    time.sleep(random.uniform(0.05, 0.3))
    status = 200 if random.random() > 0.1 else 500
    results.put((url, status))

urls = [f"https://api.example.com/item/{i}" for i in range(10)]

# Thread pool via list
start = time.perf_counter()
threads = [threading.Thread(target=fetch, args=(u,)) for u in urls]
for t in threads: t.start()
for t in threads: t.join()
elapsed = time.perf_counter() - start

print(f"Fetched {results.qsize()} URLs in {elapsed:.2f}s")
successes = sum(1 for _ in range(results.qsize()) if results.get()[1] == 200)
```

**Example**: [threading_basics.py](../../examples/python/concurrency/threading_basics.py)

---

## `multiprocessing` — True Parallelism

**Explanation**: `multiprocessing.Process` launches a separate Python interpreter process — no GIL, true CPU parallelism. `Pool.map()` distributes work across N worker processes. `multiprocessing.Queue` and `Pipe` enable inter-process communication (IPC). `Value` and `Array` provide shared memory. The `spawn` start method (default on Windows/macOS) re-imports the module in each worker — guard the entry point with `if __name__ == "__main__":`. `ProcessPoolExecutor` (from `concurrent.futures`) is the higher-level API.

**Real-World Scenario**: Compressing 1,000 images: `Pool(os.cpu_count()).map(compress_image, image_paths)` distributes the CPU-bound work across all cores — linear speedup with core count (no GIL interference).

```python
import multiprocessing
import os
import time

def is_prime(n: int) -> bool:
    if n < 2: return False
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0: return False
    return True

def count_primes_in_range(args: tuple[int, int]) -> int:
    lo, hi = args
    return sum(1 for n in range(lo, hi) if is_prime(n))

if __name__ == "__main__":
    N = 200_000
    num_workers = os.cpu_count() or 4
    chunk_size  = N // num_workers
    ranges = [(i * chunk_size, (i + 1) * chunk_size) for i in range(num_workers)]

    start = time.perf_counter()
    with multiprocessing.Pool(num_workers) as pool:
        counts = pool.map(count_primes_in_range, ranges)
    elapsed = time.perf_counter() - start

    print(f"Primes below {N}: {sum(counts)}")
    print(f"Time ({num_workers} workers): {elapsed:.2f}s")
```

**Example**: [multiprocessing_basics.py](../../examples/python/concurrency/multiprocessing_basics.py)

---

## `concurrent.futures` — High-Level Executor Interface

**Explanation**: `concurrent.futures` provides `ThreadPoolExecutor` (threads, good for I/O) and `ProcessPoolExecutor` (processes, good for CPU). Both expose `submit()` → `Future` and `map()`. `Future.result()` blocks until complete; `as_completed()` yields futures as they finish (fastest first). The executor is a context manager — `__exit__` calls `shutdown(wait=True)`. Switching between thread and process pools requires changing only one import.

**Real-World Scenario**: A pipeline downloads files (I/O-bound → `ThreadPoolExecutor`) then processes them (CPU-bound → `ProcessPoolExecutor`). `as_completed` shows a progress bar as results arrive rather than waiting for the slowest task.

```python
from concurrent.futures import ThreadPoolExecutor, as_completed
import time
import random

def download(url: str) -> tuple[str, int]:
    """Simulates downloading a file."""
    time.sleep(random.uniform(0.1, 0.5))
    size = random.randint(1024, 1_048_576)
    return url, size

urls = [f"https://cdn.example.com/file{i}.dat" for i in range(12)]

with ThreadPoolExecutor(max_workers=4) as executor:
    futures = {executor.submit(download, url): url for url in urls}

    total_bytes = 0
    for future in as_completed(futures):
        url = futures[future]
        _, size = future.result()
        total_bytes += size
        print(f"  Downloaded {url.split('/')[-1]} ({size:,} bytes)")

print(f"\nTotal: {total_bytes:,} bytes across {len(urls)} files")
```

**Example**: [concurrent_futures.py](../../examples/python/concurrency/concurrent_futures.py)

---

## `asyncio` — Cooperative Concurrency

**Explanation**: `asyncio` runs many coroutines on a single thread using cooperative multitasking. A coroutine (defined with `async def`) yields control at `await` points. The event loop drives execution, switching between coroutines whenever one awaits I/O. `asyncio.run()` is the entry point. `asyncio.gather()` runs multiple coroutines concurrently. `asyncio.sleep(0)` yields control without actually sleeping. All I/O must use `async`-aware libraries (`aiohttp`, `asyncpg`, `aiofiles`) — calling blocking I/O inside a coroutine blocks the entire event loop.

**Real-World Scenario**: A high-throughput API server handling 10,000 simultaneous connections: `asyncio` interleaves waiting coroutines on one thread with near-zero memory per "connection" compared to spawning a thread per connection.

```python
import asyncio
import random

async def fetch(session_id: int, url: str) -> dict:
    """Simulates an async HTTP request."""
    await asyncio.sleep(random.uniform(0.05, 0.3))
    return {"session": session_id, "url": url, "status": 200}

async def main() -> None:
    urls = [f"https://api.example.com/v1/item/{i}" for i in range(8)]

    # Run all concurrently, collect results
    tasks = [fetch(i, url) for i, url in enumerate(urls)]
    results = await asyncio.gather(*tasks)

    for r in results:
        print(f"[{r['session']}] {r['url']} → {r['status']}")

    print(f"\nCompleted {len(results)} requests")

asyncio.run(main())
```

**Example**: [asyncio_basics.py](../../examples/python/concurrency/asyncio_basics.py)

---

## Coroutines and `async`/`await`

**Explanation**: A coroutine is a function defined with `async def` that returns a coroutine object when called (it does not run immediately). `await expr` suspends the coroutine until the awaitable (coroutine, `Task`, or `Future`) completes. `async for` iterates an async iterable; `async with` uses an async context manager. `asyncio.create_task()` schedules a coroutine as a background task — unlike `await`, the caller continues without waiting.

**Real-World Scenario**: A data ingestion pipeline: `async for record in async_db_cursor:` streams rows from a database without loading the full result set. Each `await` on the cursor gives the event loop a chance to run other coroutines — the pipeline stays responsive while waiting for slow DB rows.

```python
import asyncio

async def slow_operation(name: str, delay: float) -> str:
    print(f"  Starting {name}")
    await asyncio.sleep(delay)
    print(f"  Finished {name}")
    return f"{name}: done"

async def sequential() -> None:
    # Each await blocks until completion — total ≈ 0.3 + 0.2 + 0.1s
    r1 = await slow_operation("A", 0.3)
    r2 = await slow_operation("B", 0.2)
    r3 = await slow_operation("C", 0.1)
    print([r1, r2, r3])

async def concurrent() -> None:
    # All three run concurrently — total ≈ max(0.3, 0.2, 0.1)s
    t1 = asyncio.create_task(slow_operation("X", 0.3))
    t2 = asyncio.create_task(slow_operation("Y", 0.2))
    t3 = asyncio.create_task(slow_operation("Z", 0.1))
    results = await asyncio.gather(t1, t2, t3)
    print(results)

print("=== Sequential ===")
asyncio.run(sequential())
print("\n=== Concurrent ===")
asyncio.run(concurrent())
```

**Example**: [coroutines.py](../../examples/python/concurrency/coroutines.py)

---

## `asyncio.Queue` — Async Producer-Consumer

**Explanation**: `asyncio.Queue` is a thread-safe, async-friendly queue for producer-consumer patterns within an asyncio event loop. `await queue.put(item)` blocks if the queue is full (maxsize > 0); `await queue.get()` blocks until an item is available. `queue.task_done()` signals completion; `await queue.join()` waits until all items are processed — the canonical pattern for bounded work queues.

**Real-World Scenario**: A web crawler: producer coroutines discover URLs and put them in a queue; consumer coroutines fetch them and put new URLs back. The queue bounds memory usage — producers pause when the queue is full, preventing runaway memory growth.

```python
import asyncio
import random

async def producer(queue: asyncio.Queue, n: int) -> None:
    for i in range(n):
        item = f"item-{i}"
        await queue.put(item)
        print(f"  Produced {item}")
        await asyncio.sleep(random.uniform(0.01, 0.05))
    # Signal consumers to stop
    for _ in range(3):  # 3 consumers
        await queue.put(None)

async def consumer(name: str, queue: asyncio.Queue) -> int:
    processed = 0
    while True:
        item = await queue.get()
        if item is None:
            queue.task_done()
            break
        await asyncio.sleep(random.uniform(0.02, 0.08))  # simulate work
        queue.task_done()
        processed += 1
    return processed

async def main() -> None:
    queue: asyncio.Queue[str | None] = asyncio.Queue(maxsize=5)
    prod = asyncio.create_task(producer(queue, 10))
    consumers = [asyncio.create_task(consumer(f"C{i}", queue)) for i in range(3)]
    await prod
    counts = await asyncio.gather(*consumers)
    print(f"Processed: {counts}, total={sum(counts)}")

asyncio.run(main())
```

**Example**: [asyncio_queue.py](../../examples/python/concurrency/asyncio_queue.py)

---

## Locks, Events, and Semaphores

**Explanation**: `threading.Lock` is a mutual exclusion lock — only one thread can hold it at a time. `RLock` (reentrant lock) can be acquired multiple times by the same thread. `threading.Event` coordinates threads: `event.wait()` blocks until `event.set()` is called. `threading.Semaphore(n)` limits concurrent access to `n` threads. `asyncio` mirrors all these: `asyncio.Lock`, `asyncio.Event`, `asyncio.Semaphore` — same semantics but `await`-based.

**Real-World Scenario**: A rate-limited API client uses `asyncio.Semaphore(10)` to allow at most 10 simultaneous requests. Without it, launching 1,000 concurrent requests would overwhelm the API and trigger 429 responses.

```python
import asyncio

async def rate_limited_fetch(sem: asyncio.Semaphore, url: str) -> str:
    async with sem:  # At most 3 concurrent requests
        await asyncio.sleep(0.1)  # simulate network I/O
        return f"OK: {url}"

async def main() -> None:
    sem = asyncio.Semaphore(3)  # max 3 concurrent
    urls = [f"https://api.example.com/{i}" for i in range(10)]
    results = await asyncio.gather(*[rate_limited_fetch(sem, u) for u in urls])
    print(f"Completed {len(results)} requests with concurrency limit 3")

asyncio.run(main())

# threading.Event example
import threading

ready = threading.Event()

def worker():
    ready.wait()  # Block until main signals
    print("Worker: starting work")

t = threading.Thread(target=worker)
t.start()
print("Main: initializing...")
import time; time.sleep(0.1)
ready.set()  # Unblock the worker
t.join()
```

**Example**: [locks_events.py](../../examples/python/concurrency/locks_events.py)

---

## Shared State and Thread Safety

**Explanation**: Sharing mutable state between threads without synchronization causes race conditions. Use `threading.Lock` to protect shared state. `queue.Queue` is inherently thread-safe — prefer it over passing data via shared variables. Immutable objects (tuples, frozensets, numbers) need no locking. `collections.deque` is thread-safe for `appendleft`/`popleft` from different ends. Avoid `global` mutable state in threaded code — encapsulate in locked objects or thread-local storage.

**Real-World Scenario**: A counter tracking requests processed by multiple threads: `counter += 1` is not atomic in Python (read + increment + write are three bytecode operations). A race condition drops counts. `threading.Lock()` or `threading.atomic` (3.13+) fixes it.

```python
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
```

**Example**: [shared_state.py](../../examples/python/concurrency/shared_state.py)

---

## Performance Patterns — Choosing the Right Concurrency Model

**Explanation**: Python offers three concurrency models: `threading` (I/O-bound, shared memory, GIL limited), `multiprocessing` (CPU-bound, process isolation, higher overhead), and `asyncio` (I/O-bound, single-thread, highest concurrency per memory). The rules: I/O-bound + simple → `asyncio`; I/O-bound + sync libraries → `threading`; CPU-bound → `multiprocessing` or C extensions (NumPy, Cython). Mix: use `asyncio.to_thread()` to run blocking code in a thread pool from an async context.

**Real-World Scenario**: A FastAPI endpoint makes several database queries and an HTTP call. `async def` with `asyncpg` (async Postgres driver) and `httpx.AsyncClient` keeps it on a single thread with high throughput. If the endpoint also needs to run a CPU-heavy image resize, `await asyncio.to_thread(resize_image, img)` offloads it to a thread pool without blocking the event loop.

```python
import asyncio
import time
import concurrent.futures

def cpu_heavy(n: int) -> int:
    """Blocks the thread — not suitable to call directly in async."""
    return sum(i * i for i in range(n))

async def mixed_workload() -> None:
    # I/O-bound: run concurrently in the event loop
    io_tasks = [asyncio.sleep(0.1) for _ in range(5)]
    await asyncio.gather(*io_tasks)

    # CPU-bound: offload to a thread pool
    loop = asyncio.get_event_loop()
    with concurrent.futures.ThreadPoolExecutor() as pool:
        result = await loop.run_in_executor(pool, cpu_heavy, 1_000_000)
    print(f"CPU result: {result}")

    # Python 3.9+ shorthand
    result2 = await asyncio.to_thread(cpu_heavy, 500_000)
    print(f"to_thread result: {result2}")

asyncio.run(mixed_workload())
```

**Example**: [concurrency_patterns.py](../../examples/python/concurrency/concurrency_patterns.py)

---

## `asyncio.TaskGroup` and `ExceptionGroup` (Python 3.11+)

**Explanation**: `asyncio.TaskGroup` (PEP 654) is the structured concurrency primitive for asyncio: all tasks in a group are cancelled if one raises, and multiple exceptions are bundled into an `ExceptionGroup`. `except*` syntax handles specific exception types from a group, ignoring others. This replaces the fragile pattern of manually cancelling tasks on failure and re-raising the first exception — common bugs with bare `gather()`.

**Real-World Scenario**: Fetching data from 5 microservices simultaneously: with `gather`, one failure means you either get all results (if `return_exceptions=True`) or only the first exception. With `TaskGroup`, all in-flight requests are cancelled immediately on the first failure, and all exceptions are collected — no requests are left running without a consumer.

```python
import asyncio
import random

async def fetch_service(name: str, fail: bool = False) -> str:
    await asyncio.sleep(random.uniform(0.05, 0.2))
    if fail:
        raise ValueError(f"{name} returned an error")
    return f"{name}: OK"

async def main() -> None:
    # TaskGroup: structured concurrency (Python 3.11+)
    try:
        async with asyncio.TaskGroup() as tg:
            t1 = tg.create_task(fetch_service("auth"))
            t2 = tg.create_task(fetch_service("inventory"))
            t3 = tg.create_task(fetch_service("pricing", fail=True))
    except* ValueError as eg:
        print(f"Some services failed: {[str(e) for e in eg.exceptions]}")
        return

    print([t1.result(), t2.result(), t3.result()])

asyncio.run(main())
```

**Example**: [task_group.py](../../examples/python/concurrency/task_group.py)
