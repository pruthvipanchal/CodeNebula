# Compile: python3 slots.py
# Output:
# PointDict and PointSlots sizes printed

import sys

class PointDict:
    def __init__(self, x, y, z):
        self.x, self.y, self.z = x, y, z

class PointSlots:
    __slots__ = ("x", "y", "z")
    def __init__(self, x, y, z):
        self.x, self.y, self.z = x, y, z

pd = PointDict(1.0, 2.0, 3.0)
ps = PointSlots(1.0, 2.0, 3.0)

dict_overhead = sys.getsizeof(pd.__dict__) if hasattr(pd, "__dict__") else 0
print(f"PointDict  size: {sys.getsizeof(pd)} + {dict_overhead} dict = {sys.getsizeof(pd) + dict_overhead} bytes")
print(f"PointSlots size: {sys.getsizeof(ps)} bytes (no __dict__)")
print(f"Memory saved: ~{sys.getsizeof(pd) + dict_overhead - sys.getsizeof(ps)} bytes per instance")

# Verify no __dict__ on slotted class
print(f"PointDict  has __dict__: {hasattr(pd, '__dict__')}")
print(f"PointSlots has __dict__: {hasattr(ps, '__dict__')}")

# Slots with inheritance
class Point4D(PointSlots):
    __slots__ = ("w",)
    def __init__(self, x, y, z, w):
        super().__init__(x, y, z)
        self.w = w

p4 = Point4D(1, 2, 3, 4)
print(f"Point4D: ({p4.x}, {p4.y}, {p4.z}, {p4.w})")
