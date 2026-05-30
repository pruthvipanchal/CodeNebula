# Compile: python3 python311_features.py
# Output:
# localhost

import sys

# Python 3.11 feature: tomllib (built-in TOML parser)
if sys.version_info >= (3, 11):
    import tomllib
    config = tomllib.loads('[server]\nhost = "localhost"\nport = 8080')
    print(config["server"]["host"])
else:
    # Fallback for older Python
    config = {"server": {"host": "localhost", "port": 8080}}
    print(config["server"]["host"])

print(f"Python {sys.version_info.major}.{sys.version_info.minor}")
print("3.11 features: fine-grained tracebacks, tomllib, TaskGroup, faster interpreter")
