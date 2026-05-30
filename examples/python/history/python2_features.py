# Compile: python3 python2_features.py
# Output:
# [1, 4, 9, 16, 25]
# [0, 2, 4, 6, 8, 10, 12, 14, 16, 18]
# [1, 2, 3, 4]

# List comprehension (introduced Python 2.0)
squares = [x**2 for x in range(1, 6)]
print(squares)

# Filtered comprehension
evens = [x for x in range(20) if x % 2 == 0]
print(evens)

# Nested comprehension — flatten a 2D matrix
matrix = [[1, 2], [3, 4]]
flat = [cell for row in matrix for cell in row]
print(flat)
