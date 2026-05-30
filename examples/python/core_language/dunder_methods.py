# Compile: python3 dunder_methods.py
# Output:
# Vector(5, 7, 9)
# Vector(3, 6, 9)
# 3
# 2

class Vector:
    def __init__(self, *components):
        self._data = list(components)

    def __repr__(self): return f"Vector{tuple(self._data)}"
    def __len__(self):  return len(self._data)
    def __getitem__(self, i): return self._data[i]
    def __add__(self, other): return Vector(*(a + b for a, b in zip(self, other)))
    def __mul__(self, scalar): return Vector(*(x * scalar for x in self))
    def __eq__(self, other): return self._data == list(other)
    def __iter__(self): return iter(self._data)
    def __contains__(self, item): return item in self._data

v1 = Vector(1, 2, 3)
v2 = Vector(4, 5, 6)
print(v1 + v2)
print(v1 * 3)
print(len(v1))
print(v1[1])
print(2 in v1)   # True
print(v1 == Vector(1, 2, 3))  # True

# __call__ — makes instances callable
class Multiplier:
    def __init__(self, factor): self.factor = factor
    def __call__(self, x): return x * self.factor

double = Multiplier(2)
print(double(5))   # 10
print(double(10))  # 20
