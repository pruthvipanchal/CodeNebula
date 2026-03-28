---
title: "C++26 — The Future"
description: "C++26 brings reflection, contracts, std::execution (Senders/Receivers), and more. 44 concepts documented."
---

# C++26 — The Future

**Year:** 2026 · **Concepts:** 44 (11 core + 33 STL)

C++26 is the next major C++ standard, currently being finalized. It brings static reflection, contracts for design-by-contract programming, a standard execution model for async/parallel code, and further modernization.

## Sections

- [**Core Language** (11 concepts)](/cpp26/core) — Static reflection, contracts (`pre`, `post`, `assert`), pack indexing, `= delete("reason")`.
- [**STL & Library** (33 concepts)](/cpp26/stl) — `std::execution` (Senders/Receivers), `std::inplace_vector`, `std::indirect`, `std::generator` improvements.

## Key Features

- **Static Reflection** — inspect types and members at compile time
- **Contracts** — `pre` / `post` / `assert` design-by-contract
- **`std::execution`** — unified async/parallel execution framework (P2300)
- **`std::inplace_vector`** — fixed-capacity stack-allocated vector
- **Pack indexing** — `pack...[0]` to index template parameter packs
- **`= delete("reason")`** — deleted functions with explanation messages

## Navigation

| Section | Concepts | Link |
|---------|----------|------|
| Core Language | 11 | [Browse →](/cpp26/core) |
| STL & Library | 33 | [Browse →](/cpp26/stl) |
