# Compile: python3 generators.py
# Output:
# [0, 1, 1, 2, 3, 5, 8, 13, 21, 34]
# 55

import itertools

def fibonacci():
    a, b = 0, 1
    while True:
        yield a
        a, b = b, a + b

fibs = list(itertools.islice(fibonacci(), 10))
print(fibs)

# Sum the next Fibonacci number
gen = fibonacci()
for _ in range(10):
    next(gen)
print(next(gen))  # 55

# Generator pipeline — lazy processing
def read_lines(text):
    for line in text.splitlines():
        yield line.strip()

def filter_nonempty(lines):
    for line in lines:
        if line:
            yield line

def to_upper(lines):
    for line in lines:
        yield line.upper()

data = "\n  hello  \n\n  world  \n"
pipeline = to_upper(filter_nonempty(read_lines(data)))
print(list(pipeline))  # ['HELLO', 'WORLD']
