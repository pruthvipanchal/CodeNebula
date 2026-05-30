# Compile: python3 walrus_operator.py
# Output:
# 13
# [9, 16, 25]
# Order ID: 12345

import re

def count_chars(text: str, chunk_size: int = 4) -> int:
    total = 0
    pos = 0
    while chunk := text[pos:pos + chunk_size]:
        total += len(chunk)
        pos += chunk_size
    return total

print(count_chars("Hello, World!"))

# Walrus in comprehension condition
data = [1, -2, 3, -4, 5]
results = [y for x in data if (y := x * x) > 4]
print(results)

# Walrus in regex match
text = "Order #12345 placed"
if m := re.search(r"#(\d+)", text):
    print(f"Order ID: {m.group(1)}")

# Without walrus (old style)
match = re.search(r"#(\d+)", text)
if match:
    print(f"Order ID: {match.group(1)}")  # same result
