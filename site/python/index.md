---
title: Python
description: Python concepts organized by topic — history, core language, standard library, concurrency, and advanced patterns.
---

# 🐍 Python

Python is a high-level, dynamically typed, interpreted language emphasising readability and developer productivity. Created by Guido van Rossum in 1991, it has become the world's most popular language for data science, web development, automation, and AI.

## Topics

| Topic | Description | Concepts |
|-------|-------------|---------|
| [📜 History & Evolution](/python/history) | Birth, Python 2→3, JIT, free-threading | 8 |
| [🔧 Core Language](/python/core) | Types, functions, classes, generators, decorators | 18 |
| [📦 Standard Library](/python/stdlib) | os, pathlib, json, collections, asyncio, typing | 14 |
| [⚡ Concurrency](/python/concurrency) | GIL, threading, multiprocessing, asyncio, futures | 11 |
| [🚀 Advanced](/python/advanced) | Metaclasses, descriptors, protocols, profiling | 11 |

## Quick Start

```python
# Python hello world
print("Hello, Python!")

# List comprehension
squares = [x**2 for x in range(1, 6)]
print(squares)  # [1, 4, 9, 16, 25]

# Generator (memory-efficient)
def fibonacci():
    a, b = 0, 1
    while True:
        yield a
        a, b = b, a + b

import itertools
fibs = list(itertools.islice(fibonacci(), 8))
print(fibs)  # [0, 1, 1, 2, 3, 5, 8, 13]
```

## Run Python

All examples run with:
```
python3 <file>.py
```

Python 3.12+ is recommended. Check your version with `python3 --version`.
