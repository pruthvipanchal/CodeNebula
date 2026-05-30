# Compile: python3 decorators.py
# Output:
# fetch_data took

import functools
import time

def timer(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        start = time.perf_counter()
        result = func(*args, **kwargs)
        elapsed = time.perf_counter() - start
        print(f"{func.__name__} took {elapsed:.4f}s")
        return result
    return wrapper

def retry(max_attempts=3):
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            for attempt in range(1, max_attempts + 1):
                try:
                    return func(*args, **kwargs)
                except Exception as e:
                    if attempt == max_attempts:
                        raise
                    print(f"Attempt {attempt} failed: {e}. Retrying...")
        return wrapper
    return decorator

@timer
@retry(max_attempts=3)
def fetch_data(url: str) -> str:
    return f"data from {url}"

result = fetch_data("https://example.com")
print(result[:20])

# Verify @functools.wraps preserves metadata
print(fetch_data.__name__)   # fetch_data (not 'wrapper')
