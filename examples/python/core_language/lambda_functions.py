# Compile: python3 lambda_functions.py
# Output:
# eng    95,000  Bob
# eng   120,000  Alice
# hr     80,000  Carol
# [4, 16, 36, 64, 100]

employees = [
    {"name": "Alice", "dept": "eng", "salary": 120000},
    {"name": "Bob",   "dept": "eng", "salary": 95000},
    {"name": "Carol", "dept": "hr",  "salary": 80000},
]
ranked = sorted(employees, key=lambda e: (e["dept"], e["salary"]))
for e in ranked:
    print(f"{e['dept']:5} {e['salary']:>7,}  {e['name']}")

nums = range(1, 11)
evens_sq = list(map(lambda x: x**2, filter(lambda x: x % 2 == 0, nums)))
print(evens_sq)

# Lambda in sorted key
words = ["banana", "apple", "cherry", "date"]
print(sorted(words, key=lambda w: len(w)))
