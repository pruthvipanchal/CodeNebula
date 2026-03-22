<div align="center">

```
   ██████╗ ██████╗ ██████╗ ███████╗
  ██╔════╝██╔═══██╗██╔══██╗██╔════╝
  ██║     ██║   ██║██║  ██║█████╗
  ██║     ██║   ██║██║  ██║██╔══╝
  ╚██████╗╚██████╔╝██████╔╝███████╗
   ╚═════╝ ╚═════╝ ╚═════╝ ╚══════╝
  ███╗   ██╗███████╗██████╗ ██╗   ██╗██╗      █████╗
  ████╗  ██║██╔════╝██╔══██╗██║   ██║██║     ██╔══██╗
  ██╔██╗ ██║█████╗  ██████╔╝██║   ██║██║     ███████║
  ██║╚██╗██║██╔══╝  ██╔══██╗██║   ██║██║     ██╔══██║
  ██║ ╚████║███████╗██████╔╝╚██████╔╝███████╗██║  ██║
  ╚═╝  ╚═══╝╚══════╝╚═════╝  ╚═════╝ ╚══════╝╚═╝  ╚═╝
```

**The definitive C++ reference — from C++98 to C++26.**

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![C++ Standards](https://img.shields.io/badge/C++-98%20%7C%2003%20%7C%2011%20%7C%2014%20%7C%2017%20%7C%2020%20%7C%2023%20%7C%2026-00599C?logo=cplusplus)](docs/)
[![Concepts](https://img.shields.io/badge/Concepts-968-blueviolet)](#whats-inside)
[![Contributions Welcome](https://img.shields.io/badge/Contributions-Welcome-brightgreen)](CONTRIBUTING.md)

*968 concepts · 8 standards · Real-world scenarios · Production-ready examples*

---

</div>

## Table of Contents

- [What's Inside](#whats-inside)
- [Quick Start](#quick-start)
- [Documentation Format](#documentation-format)
- [Repository Structure](#repository-structure)
- [How to Use This Repo](#how-to-use-this-repo)
- [Compiler Support](#compiler-support)
- [Contributing](#contributing)
- [License](#license)
- [Community](#community)

---

## What's Inside

CodeNebula covers every major C++ standard with **core language** and **STL** documentation:

| Standard | Year | Core Language | STL | Highlights |
|:--------:|:----:|:------------:|:---:|:-----------|
| **C++98** | 1998 | [View](docs/C++98/core_language.md) | [View](docs/C++98/stl_concepts.md) | Classes, templates, STL foundations |
| **C++03** | 2003 | [View](docs/C++03/core_language.md) | [View](docs/C++03/stl_concepts.md) | Value initialization, bug fixes |
| **C++11** | 2011 | [View](docs/C++11/core_language.md) | [View](docs/C++11/stl_concepts.md) | Move semantics, lambdas, auto, threads |
| **C++14** | 2014 | [View](docs/C++14/core_language.md) | [View](docs/C++14/stl_concepts.md) | Generic lambdas, `make_unique` |
| **C++17** | 2017 | [View](docs/C++17/core_language.md) | [View](docs/C++17/stl_concepts.md) | `optional`, structured bindings, `if constexpr` |
| **C++20** | 2020 | [View](docs/C++20/core_language.md) | [View](docs/C++20/stl_concepts.md) | Concepts, ranges, coroutines, modules |
| **C++23** | 2023 | [View](docs/C++23/core_language.md) | [View](docs/C++23/stl_concepts.md) | `expected`, `print`, deducing this |
| **C++26** | 2026 | [View](docs/C++26/core_language.md) | [View](docs/C++26/stl_concepts.md) | Contracts, reflection, senders/receivers |

> 📖 Browse the complete **[Master Concepts Index](docs/cpp_concepts_master.md)** — all 968 concepts in one document.

---

## Quick Start

<details>
<summary><b>🟢 Beginner</b> — New to C++</summary>

<br>

1. Start with [C++98 Core Language](docs/C++98/core_language.md) to build your foundation
2. Work through [C++98 STL](docs/C++98/stl_concepts.md) to learn containers and algorithms
3. Move to [C++11](docs/C++11/core_language.md) for modern C++ essentials
4. Try compiling the [examples](examples/) to see concepts in action

</details>

<details>
<summary><b>🟡 Intermediate</b> — Know the basics, want modern C++</summary>

<br>

1. Skim C++98/03 docs as a refresher, then focus on [C++11](docs/C++11/core_language.md) and [C++14](docs/C++14/core_language.md)
2. Study [C++17](docs/C++17/core_language.md) for widely-adopted modern features
3. Explore [C++20](docs/C++20/core_language.md) for concepts, ranges, and coroutines
4. Use the [Master Index](docs/cpp_concepts_master.md) to find specific topics

</details>

<details>
<summary><b>🔴 Advanced</b> — Staying on the cutting edge</summary>

<br>

1. Dive into [C++20 STL](docs/C++20/stl_concepts.md) and [C++23](docs/C++23/core_language.md) for the latest ratified features
2. Explore [C++26](docs/C++26/core_language.md) for upcoming features (contracts, reflection)
3. Use this repo as a quick-reference when reviewing or writing modern code
4. Consider [contributing](#contributing) your expertise

</details>

---

## Documentation Format

Every concept follows a consistent four-part structure:

```
## Concept Name
Explanation   →  What it is and why it matters
Scenario      →  A real-world use case
Snippet       →  Minimal code demonstrating the concept
Example       →  Link to a full, compilable example file
```

**Here's a real entry** (from C++11 Core Language):

> ### Lambda Expressions
> **Explanation**: Anonymous functions that can capture variables from their scope.
> **Real-World Scenario**: In a GUI application, lambdas define button click handlers inline without separate named functions.
> **Snippet**:
> ```cpp
> auto greet = [](const std::string& name) { return "Hello, " + name; };
> ```
> **Example**: [lambda_expressions.cpp](examples/C++11/lambda_expressions.cpp)

---

## Repository Structure

```
CodeNebula/
│
├── README.md                        # You are here
├── LICENSE                          # MIT License
├── .gitignore                       # C++ build artifacts & IDE files
├── CONTRIBUTING.md                  # How to contribute
│
├── docs/
│   ├── cpp_concepts_master.md       # 📖 Master index — all 968 concepts
│   │
│   ├── C++98/
│   │   ├── core_language.md         # Classes, templates, OOP, pointers...
│   │   └── stl_concepts.md          # Containers, algorithms, iterators...
│   ├── C++03/
│   │   ├── core_language.md         # Value initialization refinements
│   │   └── stl_concepts.md          # Minor algorithm fixes
│   ├── C++11/
│   │   ├── core_language.md         # auto, lambdas, move semantics...
│   │   └── stl_concepts.md          # Smart pointers, threads, regex...
│   ├── C++14/
│   │   ├── core_language.md         # Generic lambdas, variable templates...
│   │   └── stl_concepts.md          # make_unique, shared_timed_mutex...
│   ├── C++17/
│   │   ├── core_language.md         # Structured bindings, if constexpr...
│   │   └── stl_concepts.md          # optional, variant, filesystem...
│   ├── C++20/
│   │   ├── core_language.md         # Concepts, coroutines, modules...
│   │   └── stl_concepts.md          # Ranges, format, span, jthread...
│   ├── C++23/
│   │   ├── core_language.md         # Deducing this, if consteval...
│   │   └── stl_concepts.md          # expected, print, flat_map...
│   └── C++26/
│       ├── core_language.md         # Contracts, reflection...
│       └── stl_concepts.md          # simd, execution, inplace_vector...
│
└── examples/
    └── C++98/
        └── basic_types.cpp          # Demonstrates all fundamental types
```

---

## How to Use This Repo

**1. Clone the repository**
```bash
git clone https://github.com/pruthvipanchal/CodeNebula.git
cd CodeNebula
```

**2. Browse documentation** — open any `core_language.md` or `stl_concepts.md` in the `docs/` folder

**3. Compile an example**
```bash
g++ -std=c++98 -Wall -Wextra -pedantic -o basic_types examples/C++98/basic_types.cpp
./basic_types
```

**4. Explore by standard** — use the [table above](#whats-inside) or the [Master Index](docs/cpp_concepts_master.md)

---

## Compiler Support

| Standard | GCC (`g++`) | Clang (`clang++`) | MSVC (`cl`) |
|:--------:|:-----------:|:-----------------:|:-----------:|
| C++98 | `-std=c++98` | `-std=c++98` | `/std:c++14`* |
| C++11 | `-std=c++11` | `-std=c++11` | `/std:c++14`* |
| C++14 | `-std=c++14` | `-std=c++14` | `/std:c++14` |
| C++17 | `-std=c++17` | `-std=c++17` | `/std:c++17` |
| C++20 | `-std=c++20` | `-std=c++20` | `/std:c++20` |
| C++23 | `-std=c++23` | `-std=c++23` | `/std:c++latest` |
| C++26 | `-std=c++26` | `-std=c++2c` | `/std:c++latest` |

> \*MSVC does not have separate C++98/11 modes; `/std:c++14` is the minimum.

**Recommended**: always add `-Wall -Wextra -pedantic` (GCC/Clang) or `/W4` (MSVC) for thorough warnings.

---

## Contributing

Contributions are welcome! Whether it's fixing a typo, adding an example, or documenting a new concept — every improvement helps the community.

Please read the **[Contributing Guide](CONTRIBUTING.md)** before submitting a pull request.

---

## License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

---

## Community

If CodeNebula helped you learn or reference C++, consider giving it a ⭐ — it helps others discover this resource.

---

<div align="center">

**Built with patience and passion for C++.**

Made by [Pruthvi](https://github.com/pruthvipanchal)

</div>
