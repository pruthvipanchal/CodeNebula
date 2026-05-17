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

**A multi-language systems programming reference — real-world scenarios, runnable examples, deep concept coverage.**

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![C++](https://img.shields.io/badge/C++-98%20%7C%2003%20%7C%2011%20%7C%2014%20%7C%2017%20%7C%2020%20%7C%2023%20%7C%2026-00599C?logo=cplusplus)](docs/cpp/)
[![Go](https://img.shields.io/badge/Go-Topics%20%7C%20Concurrency%20%7C%20Stdlib-00ACD7?logo=go)](docs/go/)
[![Contributions Welcome](https://img.shields.io/badge/Contributions-Welcome-brightgreen)](CONTRIBUTING.md)

*968 C++ concepts · 8 standards · 48 Go concepts · 5 topics · Real-world scenarios · Runnable examples*

---

</div>

## Table of Contents

- [Languages](#languages)
- [C++ Reference](#c-reference)
- [Go Reference](#go-reference)
- [Documentation Format](#documentation-format)
- [Repository Structure](#repository-structure)
- [How to Use This Repo](#how-to-use-this-repo)
- [Compiler & Runtime Support](#compiler--runtime-support)
- [Contributing](#contributing)
- [License](#license)

---

## Languages

| Language | Organization | Concepts | Docs |
|----------|-------------|----------|------|
| **C++** | By standard version (C++98 → C++26) | 968 | [Browse →](docs/cpp/) |
| **Go** | By topic (History, Core, Concurrency, Stdlib, Advanced) | 48+ | [Browse →](docs/go/) |

More languages coming. The repo is structured so any language can be added without touching existing content.

---

## C++ Reference

968 concepts across 8 standards — core language and STL for each:

| Standard | Year | Core Language | STL | Highlights |
|:--------:|:----:|:------------:|:---:|:-----------|
| **C++98** | 1998 | [View](docs/cpp/C++98/core_language.md) | [View](docs/cpp/C++98/stl_concepts.md) | Classes, templates, STL foundations |
| **C++03** | 2003 | [View](docs/cpp/C++03/core_language.md) | [View](docs/cpp/C++03/stl_concepts.md) | Value initialization, bug fixes |
| **C++11** | 2011 | [View](docs/cpp/C++11/core_language.md) | [View](docs/cpp/C++11/stl_concepts.md) | Move semantics, lambdas, auto, threads |
| **C++14** | 2014 | [View](docs/cpp/C++14/core_language.md) | [View](docs/cpp/C++14/stl_concepts.md) | Generic lambdas, `make_unique` |
| **C++17** | 2017 | [View](docs/cpp/C++17/core_language.md) | [View](docs/cpp/C++17/stl_concepts.md) | `optional`, structured bindings, `if constexpr` |
| **C++20** | 2020 | [View](docs/cpp/C++20/core_language.md) | [View](docs/cpp/C++20/stl_concepts.md) | Concepts, ranges, coroutines, modules |
| **C++23** | 2023 | [View](docs/cpp/C++23/core_language.md) | [View](docs/cpp/C++23/stl_concepts.md) | `expected`, `print`, deducing this |
| **C++26** | 2026 | [View](docs/cpp/C++26/core_language.md) | [View](docs/cpp/C++26/stl_concepts.md) | Contracts, reflection, senders/receivers |

> 📖 Browse the complete **[C++ Master Index](docs/cpp/master.md)** — all 968 concepts in one document.

<details>
<summary><b>🟢 Beginner</b> — New to C++</summary>

<br>

1. Start with [C++98 Core Language](docs/cpp/C++98/core_language.md) to build your foundation
2. Work through [C++98 STL](docs/cpp/C++98/stl_concepts.md) to learn containers and algorithms
3. Move to [C++11](docs/cpp/C++11/core_language.md) for modern C++ essentials
4. Try compiling the [examples](examples/cpp/) to see concepts in action

</details>

<details>
<summary><b>🟡 Intermediate</b> — Know the basics, want modern C++</summary>

<br>

1. Skim C++98/03 docs as a refresher, then focus on [C++11](docs/cpp/C++11/core_language.md) and [C++14](docs/cpp/C++14/core_language.md)
2. Study [C++17](docs/cpp/C++17/core_language.md) for widely-adopted modern features
3. Explore [C++20](docs/cpp/C++20/core_language.md) for concepts, ranges, and coroutines
4. Use the [Master Index](docs/cpp/master.md) to find specific topics

</details>

<details>
<summary><b>🔴 Advanced</b> — Staying on the cutting edge</summary>

<br>

1. Dive into [C++20 STL](docs/cpp/C++20/stl_concepts.md) and [C++23](docs/cpp/C++23/core_language.md) for the latest ratified features
2. Explore [C++26](docs/cpp/C++26/core_language.md) for upcoming features (contracts, reflection)
3. Use this repo as a quick-reference when reviewing or writing modern code

</details>

---

## Go Reference

Go is organized by **topic** rather than version — because Go's core language is stable and the interesting divisions are conceptual, not chronological.

| Topic | Concepts | Description |
|-------|----------|-------------|
| 📜 [History & Evolution](docs/go/history.md) | 7 | Origins at Google, Go 1.0 → 1.21, generics, adoption story |
| 🔧 [Core Language](docs/go/core_language.md) | 13 | Variables, types, functions, structs, interfaces, closures, embedding |
| ⚡ [Concurrency](docs/go/concurrency.md) | 9 | Goroutines, channels, select, WaitGroup, Mutex, context, pipelines |
| 📦 [Standard Library](docs/go/standard_library.md) | 11 | fmt, errors, io, os, net/http, encoding/json, bufio, log/slog, testing |
| 🚀 [Advanced](docs/go/advanced.md) | 8 | Generics, reflection, interface composition, unsafe, CGo, PGO |

Runnable `.go` examples live in [examples/go/](examples/go/) — each file has a compile/run command in its header.

---

## Documentation Format

Every concept follows a consistent four-part structure, regardless of language:

```
## Concept Name
Explanation   →  What it is and why it matters
Scenario      →  A real-world use case
Snippet       →  Minimal code demonstrating the concept
Example       →  Link to a full, runnable example file
```

**C++ example** (from C++11 Core Language):

> ### Lambda Expressions
> **Explanation**: Anonymous functions that can capture variables from their scope.
> **Real-World Scenario**: In a GUI application, lambdas define button click handlers inline without separate named functions.
> **Snippet**:
> ```cpp
> auto greet = [](const std::string& name) { return "Hello, " + name; };
> ```
> **Example**: [lambda_expressions.cpp](examples/cpp/C++11/lambda_expressions.cpp)

**Go example** (from Concurrency):

> ## Goroutines
> **Explanation**: A goroutine is a lightweight, cooperatively-scheduled function execution managed by the Go runtime. Starting one costs roughly 2–8 KB of stack (vs. ~1 MB for an OS thread).
> **Real-World Scenario**: A web server handles each HTTP request in its own goroutine — at peak load you might have 10,000 concurrent goroutines without 10,000 OS threads.
> **Snippet**:
> ```go
> go worker(id) // launch concurrently — that's it
> ```
> **Example**: [goroutines.go](examples/go/concurrency/goroutines.go)

---

## Repository Structure

```
CodeNebula/
│
├── docs/
│   ├── languages.json           # Language registry — source of truth for all languages
│   │
│   ├── cpp/                     # C++ docs (version-based)
│   │   ├── master.md            # 📖 All 968 C++ concepts in one document
│   │   ├── C++98/
│   │   │   ├── core_language.md
│   │   │   └── stl_concepts.md
│   │   ├── C++03/ ... C++26/    # Same structure for each standard
│   │   └── ...
│   │
│   └── go/                      # Go docs (topic-based)
│       ├── history.md           # Origins, evolution, Go 1.0 → modern
│       ├── core_language.md     # Types, functions, structs, interfaces, closures
│       ├── concurrency.md       # Goroutines, channels, select, context, pipelines
│       ├── standard_library.md  # fmt, net/http, encoding/json, log/slog, testing
│       └── advanced.md          # Generics, reflection, CGo, PGO, go:generate
│
├── examples/
│   ├── cpp/                     # C++ examples (by standard)
│   │   ├── C++98/
│   │   │   └── basic_types.cpp
│   │   └── ...
│   │
│   └── go/                      # Go examples (by topic)
│       ├── core_language/
│       │   ├── variables.go
│       │   ├── interfaces.go
│       │   └── ...
│       ├── concurrency/
│       │   ├── goroutines.go
│       │   ├── channels.go
│       │   └── ...
│       ├── standard_library/
│       └── advanced/
│
└── site/                        # VitePress static site (deployed to GitHub Pages)
    ├── .vitepress/config.ts     # Multi-language nav and sidebar
    ├── index.md                 # Language selection landing page
    ├── cpp98/ ... cpp26/        # C++ standard pages
    └── go/                      # Go topic pages
        ├── index.md
        ├── history.md
        ├── core.md
        ├── concurrency.md
        ├── stdlib.md
        └── advanced.md
```

---

## How to Use This Repo

**1. Clone the repository**
```bash
git clone https://github.com/pruthvipanchal/CodeNebula.git
cd CodeNebula
```

**2. Browse documentation** — open any markdown file in `docs/cpp/` or `docs/go/`

**3. Run a C++ example**
```bash
g++ -std=c++11 -Wall -Wextra -o output examples/cpp/C++11/lambda_expressions.cpp
./output
```

**4. Run a Go example**
```bash
go run examples/go/concurrency/goroutines.go
```

**5. Use the VitePress site locally**
```bash
cd site
npm install
npm run dev     # → http://localhost:5173/CodeNebula/
```

---

## Compiler & Runtime Support

**C++**

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

**Go**

| Requirement | Version |
|------------|---------|
| Go toolchain | 1.21+ (recommended for `slices`, `maps`, `log/slog`) |
| Generics examples | Go 1.18+ |
| All other examples | Go 1.16+ |

Install Go from [go.dev/dl](https://go.dev/dl/). Run any example with `go run <file>.go`.

---

## Contributing

Contributions are welcome — whether it's fixing a typo, adding an example, documenting a new concept, or adding a new language.

Please read the **[Contributing Guide](CONTRIBUTING.md)** before submitting a pull request.

---

## License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

---

<div align="center">

**Built with patience and passion for systems programming.**

Made by [Pruthvi](https://github.com/pruthvipanchal)

</div>
