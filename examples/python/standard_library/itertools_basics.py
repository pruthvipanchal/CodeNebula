# Compile: python3 itertools_basics.py
# Output:
# A: [1, 2]
# B: [3, 4]
# A: [5]

import itertools

data = [("A", 1), ("A", 2), ("B", 3), ("B", 4), ("A", 5)]
data.sort(key=lambda x: x[0])
for key, group in itertools.groupby(data, key=lambda x: x[0]):
    print(f"{key}: {[v for _, v in group]}")

def batched(iterable, n):
    it = iter(iterable)
    while batch := list(itertools.islice(it, n)):
        yield batch

for batch in batched(range(10), 3):
    print(batch)

pairs = list(itertools.combinations("ABCD", 2))
print(f"{len(pairs)} pairs: {pairs[:3]}")

# chain — concatenate iterables
combined = list(itertools.chain([1, 2], [3, 4], [5]))
print(combined)

# product — Cartesian product
params = list(itertools.product([0.01, 0.1], ["sgd", "adam"]))
print(params)

# takewhile / dropwhile
print(list(itertools.takewhile(lambda x: x < 5, range(10))))
print(list(itertools.dropwhile(lambda x: x < 5, range(10))))
