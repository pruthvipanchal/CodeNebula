# Compile: python3 pattern_matching.py
# Output:
# origin
# on y-axis at 5.0
# on x-axis at 3.0
# on diagonal at 4.0
# point (1.0, 2.0)

from dataclasses import dataclass

@dataclass
class Point:
    x: float
    y: float

def classify_point(p):
    match p:
        case Point(x=0, y=0):
            return "origin"
        case Point(x=0, y=y):
            return f"on y-axis at {y}"
        case Point(x=x, y=0):
            return f"on x-axis at {x}"
        case Point(x=x, y=y) if x == y:
            return f"on diagonal at {x}"
        case Point(x=x, y=y):
            return f"point ({x}, {y})"

for pt in [Point(0, 0), Point(0, 5), Point(3, 0), Point(4, 4), Point(1, 2)]:
    print(classify_point(pt))
