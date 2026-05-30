# Compile: python3 protocols.py
# Output:
# Circle(r=5.0) — area: 78.54
# Rect(3.0x4.0) — area: 12.00
# True

from typing import Protocol, runtime_checkable

@runtime_checkable
class Drawable(Protocol):
    def draw(self) -> str: ...
    def area(self) -> float: ...

class Circle:
    def __init__(self, r: float): self.r = r
    def draw(self) -> str:   return f"Circle(r={self.r})"
    def area(self) -> float: return 3.14159 * self.r ** 2

class Rectangle:
    def __init__(self, w: float, h: float): self.w, self.h = w, h
    def draw(self) -> str:   return f"Rect({self.w}x{self.h})"
    def area(self) -> float: return self.w * self.h

def render(shape: Drawable) -> None:
    print(f"{shape.draw()} — area: {shape.area():.2f}")

shapes: list[Drawable] = [Circle(5), Rectangle(3, 4)]
for s in shapes:
    render(s)

print(isinstance(Circle(1), Drawable))   # True
print(isinstance("not drawable", Drawable))  # False
