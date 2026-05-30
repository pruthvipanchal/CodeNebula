# Compile: python3 type_narrowing.py
# Output:
# Cat Whiskers, indoor=True
# Dog Rex, breed=Labrador

from typing import TypeGuard, Union
from dataclasses import dataclass

@dataclass
class Cat:
    name: str
    indoor: bool

@dataclass
class Dog:
    name: str
    breed: str

Animal = Union[Cat, Dog]

def is_cat(animal: Animal) -> TypeGuard[Cat]:
    return isinstance(animal, Cat)

def describe(animal: Animal) -> str:
    if is_cat(animal):
        return f"Cat {animal.name}, indoor={animal.indoor}"
    else:
        return f"Dog {animal.name}, breed={animal.breed}"

animals: list[Animal] = [Cat("Whiskers", True), Dog("Rex", "Labrador")]
for a in animals:
    print(describe(a))

# isinstance narrowing (built-in, no TypeGuard needed)
def process(value: int | str | list) -> str:
    if isinstance(value, int):
        return f"int: {value * 2}"
    elif isinstance(value, str):
        return f"str: {value.upper()}"
    else:
        return f"list: {len(value)} items"

print(process(21))
print(process("hello"))
print(process([1, 2, 3]))
