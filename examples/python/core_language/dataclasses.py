# Compile: python3 dataclasses.py
# Output:
# True
# 3.11.0
# Package(name='requests', version=3.12.0, dependencies=['certifi', 'urllib3'])

from dataclasses import dataclass, field
from typing import ClassVar

@dataclass(order=True, frozen=True)
class Version:
    major: int
    minor: int
    patch: int = 0
    _registry: ClassVar[list] = []

    def __str__(self) -> str:
        return f"{self.major}.{self.minor}.{self.patch}"

@dataclass
class Package:
    name: str
    version: Version
    dependencies: list[str] = field(default_factory=list)
    _internal: str = field(default="", repr=False)

v1 = Version(3, 11)
v2 = Version(3, 12)
print(v1 < v2)
print(str(v1))

pkg = Package("requests", v2, ["certifi", "urllib3"])
print(pkg)

# post_init for derived fields
@dataclass
class Rectangle:
    width: float
    height: float
    area: float = field(init=False)

    def __post_init__(self):
        self.area = self.width * self.height

r = Rectangle(4.0, 5.0)
print(f"Rectangle area: {r.area}")
