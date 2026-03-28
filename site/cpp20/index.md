---
title: "C++20 — The Big Four"
description: "C++20 introduced concepts, ranges, coroutines, and modules — the four largest features in C++ history. 284 concepts documented."
---

# C++20 — The Big Four

**Year:** 2020 · **Concepts:** 284 (39 core + 245 STL)

C++20 is the largest update to C++ since C++11. It introduces four landmark features — Concepts, Ranges, Coroutines, and Modules — alongside dozens of smaller improvements.

## Sections

- [**Core Language** (39 concepts)](/cpp20/core) — Concepts, coroutines, modules, `consteval`, `constinit`, three-way comparison, designated initializers.
- [**STL & Library** (245 concepts)](/cpp20/stl) — Ranges library, `std::span`, `std::format`, `std::jthread`, `std::barrier`, `std::latch`, `std::source_location`, and much more.

## The Big Four

### 1. Concepts
Type constraints for templates — readable, composable, and compiler-checked:
```cpp
template<typename T>
concept Addable = requires(T a, T b) { a + b; };
```

### 2. Ranges
Lazy, composable view pipelines over sequences:
```cpp
auto evens = views::iota(1, 100) | views::filter([](int n) { return n % 2 == 0; });
```

### 3. Coroutines
Suspendable functions with `co_await`, `co_yield`, `co_return`:
```cpp
generator<int> fibonacci() {
  int a = 0, b = 1;
  while (true) { co_yield a; auto c = a + b; a = b; b = c; }
}
```

### 4. Modules
Replacing `#include` with proper module imports:
```cpp
import std.core;
```

## Navigation

| Section | Concepts | Link |
|---------|----------|------|
| Core Language | 39 | [Browse →](/cpp20/core) |
| STL & Library | 245 | [Browse →](/cpp20/stl) |
