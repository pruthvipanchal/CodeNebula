# Compile: python3 functions.py
# Output:
# Connecting to localhost:5433 (timeout=10)
# Extra options: {'ssl': True, 'retry': 3}
# args=(1, 2, 3), kwargs={'label': 'sum'}
# 6

def create_connection(host, port=5432, /, *, timeout=30, **options):
    # host, port: positional-only (before /)
    # timeout: keyword-only (after *)
    print(f"Connecting to {host}:{port} (timeout={timeout})")
    print(f"Extra options: {options}")

create_connection("localhost", 5433, timeout=10, ssl=True, retry=3)

def wrapper(*args, **kwargs):
    print(f"args={args}, kwargs={kwargs}")
    return sum(args)

result = wrapper(1, 2, 3, label="sum")
print(result)

# Mutable default pitfall — use None instead
def append_item(item, lst=None):
    if lst is None:
        lst = []
    lst.append(item)
    return lst

print(append_item(1))  # [1]
print(append_item(2))  # [2] — not [1, 2]!
