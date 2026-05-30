# Compile: python3 fstrings.py
# Output:
# 3.1416
# a|b|c

import math

pi     = math.pi
salary = 123456.789

print(f"{pi:.4f}")
print(f"{salary:>15,.2f}")
print(f"{42:#010b}")

# Debug shorthand (Python 3.8+)
x = [1, 2, 3]
print(f"{x=}")

# Nested f-string
items = ["a", "b", "c"]
print(f"{'|'.join(items)}")

# Multiline f-string
name  = "Alice"
score = 98.5
report = (
    f"Student: {name}\n"
    f"Score:   {score:.1f}\n"
    f"Grade:   {'A' if score >= 90 else 'B'}"
)
print(report)
