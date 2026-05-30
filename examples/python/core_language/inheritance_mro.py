# Compile: python3 inheritance_mro.py
# Output:
# D -> B -> C -> A
# (<class '__main__.D'>, <class '__main__.B'>, <class '__main__.C'>, <class '__main__.A'>, <class 'object'>)

class A:
    def who(self): return "A"

class B(A):
    def who(self): return f"B -> {super().who()}"

class C(A):
    def who(self): return f"C -> {super().who()}"

class D(B, C):
    def who(self): return f"D -> {super().who()}"

d = D()
print(d.who())
print(D.__mro__)

# Cooperative __init__ with super()
class TimestampMixin:
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.created_at = "2024-01-01"

class TagMixin:
    def __init__(self, tags=None, **kwargs):
        super().__init__(**kwargs)
        self.tags = tags or []

class Article(TimestampMixin, TagMixin):
    def __init__(self, title, **kwargs):
        super().__init__(**kwargs)
        self.title = title

a = Article("Hello World", tags=["python", "tutorial"])
print(a.title, a.tags, a.created_at)
