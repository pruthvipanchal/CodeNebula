# Compile: python3 concurrency_patterns.py
# Output:
# CPU result printed
# to_thread result printed

import asyncio
import concurrent.futures

def cpu_heavy(n: int) -> int:
    return sum(i * i for i in range(n))

async def mixed_workload() -> None:
    io_tasks = [asyncio.sleep(0.01) for _ in range(5)]
    await asyncio.gather(*io_tasks)

    loop = asyncio.get_event_loop()
    with concurrent.futures.ThreadPoolExecutor() as pool:
        result = await loop.run_in_executor(pool, cpu_heavy, 100_000)
    print(f"CPU result: {result}")

    result2 = await asyncio.to_thread(cpu_heavy, 50_000)
    print(f"to_thread result: {result2}")

asyncio.run(mixed_workload())

# Summary
print("\nConcurrency model guide:")
print("  I/O-bound + simple   → asyncio")
print("  I/O-bound + sync lib → threading")
print("  CPU-bound            → multiprocessing")
print("  CPU-bound in async   → asyncio.to_thread")
