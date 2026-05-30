# Compile: python3 descriptors.py
# Output:
# Alice 30
# age must be int, got str

class Typed:
    def __set_name__(self, owner, name: str) -> None:
        self._name = f"_{name}"
        self._public = name

    def __init__(self, expected_type: type):
        self._type = expected_type

    def __get__(self, obj, objtype=None):
        if obj is None:
            return self
        return getattr(obj, self._name, None)

    def __set__(self, obj, value) -> None:
        if not isinstance(value, self._type):
            raise TypeError(
                f"{self._public} must be {self._type.__name__}, "
                f"got {type(value).__name__}"
            )
        setattr(obj, self._name, value)

class Person:
    name = Typed(str)
    age  = Typed(int)

    def __init__(self, name: str, age: int):
        self.name = name
        self.age  = age

p = Person("Alice", 30)
print(p.name, p.age)

try:
    p.age = "thirty"
except TypeError as e:
    print(e)

# Class-level access returns the descriptor itself
print(type(Person.name))  # <class '__main__.Typed'>
