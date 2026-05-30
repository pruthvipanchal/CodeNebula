# Compile: python3 asyncio_queue.py
# Output:
# Processed items summing to 10

import asyncio
import random

async def producer(queue: asyncio.Queue, n: int, num_consumers: int) -> None:
    for i in range(n):
        await queue.put(i)
        await asyncio.sleep(0)
    for _ in range(num_consumers):
        await queue.put(None)  # sentinel

async def consumer(name: str, queue: asyncio.Queue) -> int:
    processed = 0
    while True:
        item = await queue.get()
        if item is None:
            queue.task_done()
            break
        await asyncio.sleep(0)
        queue.task_done()
        processed += 1
    return processed

async def main() -> None:
    NUM_CONSUMERS = 3
    queue: asyncio.Queue = asyncio.Queue(maxsize=5)
    prod = asyncio.create_task(producer(queue, 10, NUM_CONSUMERS))
    consumers = [
        asyncio.create_task(consumer(f"C{i}", queue))
        for i in range(NUM_CONSUMERS)
    ]
    await prod
    counts = await asyncio.gather(*consumers)
    print(f"Processed: {counts}, total={sum(counts)}")

asyncio.run(main())
