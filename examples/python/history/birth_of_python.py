# Compile: python3 birth_of_python.py
# Output:
# Hello, World!
# Type: <class 'list'>
# First-class function: 8

def greet(name):
    return f"Hello, {name}!"

print(greet("World"))

# Everything is an object — functions are first-class
def apply(func, value):
    return func(value)

double = lambda x: x * 2
print(f"Type: {type([])}")
print(f"First-class function: {apply(double, 4)}")
