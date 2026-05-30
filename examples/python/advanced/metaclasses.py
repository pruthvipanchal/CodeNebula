# Compile: python3 metaclasses.py
# Output:
# True
# True
# {'auth': <class '__main__.AuthPlugin'>}

class SingletonMeta(type):
    _instances: dict = {}

    def __call__(cls, *args, **kwargs):
        if cls not in cls._instances:
            cls._instances[cls] = super().__call__(*args, **kwargs)
        return cls._instances[cls]

class Config(metaclass=SingletonMeta):
    def __init__(self):
        self.debug = False

a = Config()
b = Config()
print(a is b)       # True
a.debug = True
print(b.debug)      # True — same object

class Plugin:
    _registry: dict = {}

    def __init_subclass__(cls, name: str = "", **kwargs):
        super().__init_subclass__(**kwargs)
        if name:
            Plugin._registry[name] = cls

class AuthPlugin(Plugin, name="auth"):
    def run(self): return "auth"

print(Plugin._registry)
