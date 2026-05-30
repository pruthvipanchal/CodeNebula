# Compile: python3 task_group.py
# Output:
# Some services failed (Python 3.11+) or error caught

import asyncio
import sys
import random

async def fetch_service(name: str, fail: bool = False) -> str:
    await asyncio.sleep(random.uniform(0.01, 0.05))
    if fail:
        raise ValueError(f"{name} returned an error")
    return f"{name}: OK"

async def main_with_task_group() -> None:
    if sys.version_info < (3, 11):
        print("TaskGroup requires Python 3.11+")
        print(f"Running Python {sys.version_info.major}.{sys.version_info.minor}")
        return

    try:
        async with asyncio.TaskGroup() as tg:
            t1 = tg.create_task(fetch_service("auth"))
            t2 = tg.create_task(fetch_service("inventory"))
            t3 = tg.create_task(fetch_service("pricing", fail=True))
    except* ValueError as eg:
        print(f"Some services failed: {[str(e) for e in eg.exceptions]}")
    else:
        print([t1.result(), t2.result(), t3.result()])

async def main_with_gather() -> None:
    results = await asyncio.gather(
        fetch_service("auth"),
        fetch_service("inventory"),
        fetch_service("pricing", fail=True),
        return_exceptions=True,
    )
    for r in results:
        if isinstance(r, Exception):
            print(f"Error: {r}")
        else:
            print(r)

print("=== TaskGroup (3.11+) ===")
asyncio.run(main_with_task_group())
print("\n=== gather with return_exceptions ===")
asyncio.run(main_with_gather())
