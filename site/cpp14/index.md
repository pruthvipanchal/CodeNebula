---
title: "C++14 — The Polish"
description: "C++14 refined C++11 with generic lambdas, extended constexpr, and library improvements. 23 concepts documented."
---

# C++14 — The Polish

**Year:** 2014 · **Concepts:** 23 (10 core + 13 STL)

C++14 is a smaller, incremental update to C++11 that polishes rough edges, extends features, and adds convenience improvements without introducing major new paradigms.

## Sections

- [**Core Language** (10 concepts)](/cpp14/core) — Generic lambdas, extended `constexpr`, variable templates, `auto` return type deduction.
- [**STL & Library** (13 concepts)](/cpp14/stl) — `std::make_unique`, digit separators, user-defined literals, `std::exchange`.

## Key Features

- **Generic lambdas** — `[](auto x) { return x * 2; }`
- **Extended `constexpr`** — loops and local variables in `constexpr` functions
- **Variable templates** — `template<typename T> constexpr T pi = T(3.14159);`
- **`auto` return type deduction** — no need to specify return type
- **`std::make_unique`** — finally available
- **Digit separators** — `1'000'000` for readability

## Navigation

| Section | Concepts | Link |
|---------|----------|------|
| Core Language | 10 | [Browse →](/cpp14/core) |
| STL & Library | 13 | [Browse →](/cpp14/stl) |
