# Compile: python3 asyncio_basics.py
# Output:
# Completed 8 requests

import asyncio
import random

async def fetch(session_id: int, url: str) -> dict:
    await asyncio.sleep(random.uniform(0.01, 0.05))
    return {"session": session_id, "url": url, "status": 200}

async def main() -> None:
    urls = [f"https://api.example.com/v1/item/{i}" for i in range(8)]
    tasks = [fetch(i, url) for i, url in enumerate(urls)]
    results = await asyncio.gather(*tasks)

    for r in results:
        print(f"[{r['session']}] status={r['status']}")

    print(f"\nCompleted {len(results)} requests")

asyncio.run(main())
