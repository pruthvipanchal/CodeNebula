# Compile: python3 concurrent_futures.py
# Output:
# Downloaded files and total bytes printed

from concurrent.futures import ThreadPoolExecutor, as_completed
import time
import random

def download(url: str) -> tuple:
    time.sleep(random.uniform(0.02, 0.1))
    size = random.randint(1024, 65536)
    return url, size

urls = [f"https://cdn.example.com/file{i}.dat" for i in range(8)]

with ThreadPoolExecutor(max_workers=4) as executor:
    futures = {executor.submit(download, url): url for url in urls}

    total_bytes = 0
    completed = 0
    for future in as_completed(futures):
        url = futures[future]
        _, size = future.result()
        total_bytes += size
        completed += 1

print(f"Downloaded {completed} files, total {total_bytes:,} bytes")

# map — simpler when order doesn't matter
with ThreadPoolExecutor(max_workers=4) as ex:
    results = list(ex.map(download, urls[:4]))
print(f"map: {len(results)} results")
