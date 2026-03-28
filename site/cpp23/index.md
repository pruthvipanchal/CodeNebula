---
title: "C++23 — The Refinement II"
description: "C++23 refines C++20's big features and adds std::print, std::expected, deducing this, and more. 89 concepts documented."
---

# C++23 — The Refinement II

**Year:** 2023 · **Concepts:** 89 (13 core + 76 STL)

C++23 builds on C++20's foundations, refining ranges and coroutines, adding important quality-of-life features, and bringing `std::print` for finally easy formatted output.

## Sections

- [**Core Language** (13 concepts)](/cpp23/core) — Deducing `this`, `if consteval`, `[[assume]]`, multidimensional subscript operator, explicit object parameters.
- [**STL & Library** (76 concepts)](/cpp23/stl) — `std::print`, `std::expected`, `std::flat_map`, `std::mdspan`, `std::generator`, ranges improvements.

## Key Features

- **Deducing `this`** — explicit object parameter for CRTP without CRTP
- **`std::print` / `std::println`** — `std::println("Hello, {}!", name);`
- **`std::expected<T, E>`** — monadic error handling without exceptions
- **`std::flat_map` / `std::flat_set`** — cache-friendly sorted containers
- **`std::mdspan`** — multidimensional span
- **`std::generator`** — standard coroutine generator
- **`if consteval`** — distinguish consteval from constexpr context
- **`[[assume(expr)]]`** — optimizer hints

## Navigation

| Section | Concepts | Link |
|---------|----------|------|
| Core Language | 13 | [Browse →](/cpp23/core) |
| STL & Library | 76 | [Browse →](/cpp23/stl) |
