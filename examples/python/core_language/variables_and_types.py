# Compile: python3 variables_and_types.py
# Output:
# <class 'int'> True
# <class 'str'> 5

x = 42
y = 3.14
z = 1 + 2j
s = "hello"
b = b"bytes"
t = (1, 2, 3)
lst = [1, 2, 3]
d = {"a": 1}
nothing = None

print(type(x), isinstance(x, int))
print(type(s), len(s))
print(f"int: {x}, float: {y}, complex: {z}")
print(f"tuple: {t}, list: {lst}")
print(f"None type: {type(nothing).__name__}")

# Type conversion
print(int("42"), float("3.14"), str(99))
print(list(t), tuple(lst))
