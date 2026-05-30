# Compile: python3 coroutines.py
# Output:
# === Sequential ===
# === Concurrent ===

import asyncio

async def slow_operation(name: str, delay: float) -> str:
    await asyncio.sleep(delay)
    return f"{name}: done"

async def sequential() -> None:
    import time
    start = time.perf_counter()
    r1 = await slow_operation("A", 0.05)
    r2 = await slow_operation("B", 0.03)
    r3 = await slow_operation("C", 0.02)
    elapsed = time.perf_counter() - start
    print(f"Sequential: {[r1, r2, r3]} ({elapsed:.3f}s)")

async def concurrent() -> None:
    import time
    start = time.perf_counter()
    t1 = asyncio.create_task(slow_operation("X", 0.05))
    t2 = asyncio.create_task(slow_operation("Y", 0.03))
    t3 = asyncio.create_task(slow_operation("Z", 0.02))
    results = await asyncio.gather(t1, t2, t3)
    elapsed = time.perf_counter() - start
    print(f"Concurrent: {results} ({elapsed:.3f}s)")

print("=== Sequential ===")
asyncio.run(sequential())
print("\n=== Concurrent ===")
asyncio.run(concurrent())
