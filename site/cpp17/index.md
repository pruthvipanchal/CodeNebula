---
title: "C++17 — The Pragmatic"
description: "C++17 added structured bindings, if-constexpr, std::optional, std::variant, parallel algorithms, and filesystem. 97 concepts documented."
---

# C++17 — The Pragmatic

**Year:** 2017 · **Concepts:** 97 (19 core + 78 STL)

C++17 focused on practical improvements to everyday programming — reducing boilerplate, adding powerful vocabulary types, and enabling safer, more expressive code.

## Sections

- [**Core Language** (19 concepts)](/cpp17/core) — Structured bindings, `if constexpr`, class template argument deduction, fold expressions, `if`/`switch` initializers.
- [**STL & Library** (78 concepts)](/cpp17/stl) — `std::optional`, `std::variant`, `std::any`, `std::string_view`, parallel algorithms, `std::filesystem`.

## Key Features

- **Structured bindings** — `auto [x, y] = pair;`
- **`if constexpr`** — compile-time branching
- **Class template argument deduction (CTAD)** — `std::vector v{1, 2, 3};`
- **Fold expressions** — variadic template expansion
- **`std::optional<T>`** — nullable value type
- **`std::variant<T...>`** — type-safe union
- **`std::string_view`** — non-owning string reference
- **`std::filesystem`** — portable file system operations
- **Parallel STL** — `std::execution::par` policies

## Navigation

| Section | Concepts | Link |
|---------|----------|------|
| Core Language | 19 | [Browse →](/cpp17/core) |
| STL & Library | 78 | [Browse →](/cpp17/stl) |
