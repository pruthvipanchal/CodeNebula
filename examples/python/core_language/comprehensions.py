# Compile: python3 comprehensions.py
# Output:
# [1, 2, 3, 4, 5, 6, 7, 8, 9]
# {2, 4, 6, 8}
# {1: 1, 2: 4, 3: 9, 4: 16, 5: 25}
# [1, 8, 27, 64, 125]

matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
flat   = [x for row in matrix for x in row]
evens  = {x for x in flat if x % 2 == 0}
sq_map = {x: x**2 for x in range(1, 6)}
gen    = (x**3 for x in range(1, 6))

print(flat)
print(evens)
print(sq_map)
print(list(gen))

# Transpose a matrix using comprehension
transposed = [[row[i] for row in matrix] for i in range(3)]
print(transposed)

# Invert a dict
original = {"a": 1, "b": 2, "c": 3}
inverted = {v: k for k, v in original.items()}
print(inverted)
