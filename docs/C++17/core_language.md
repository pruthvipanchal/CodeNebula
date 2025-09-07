# C++17 Core Language Concepts

This document covers new or evolved C++17 core language concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../examples/C++17/). Only additions or evolutions from C++98/C++03/C++11/C++14 are included.

## Structured Bindings (C++17 Addition)
**Explanation**: Decomposes aggregates (e.g., tuples, structs) into named variables for easier access.  
**Real-World Scenario**: Extract position and velocity from a tuple in a physics simulation.  
**Snippet**:  
```cpp
#include <tuple> auto [x, y] = std::make_tuple(1, "value");
```
**Example**: [structured_bindings.cpp](../examples/C++17/structured_bindings.cpp)

## if constexpr (C++17 Addition)
**Explanation**: Compile-time conditional evaluation in templates, reducing code duplication.  
**Real-World Scenario**: Select different logic paths in a generic function for a data processor.  
**Snippet**:  
```cpp
template<typename T> void process(T t) { if constexpr (std::is_integral_v<T>) {} }
```
**Example**: [if_constexpr.cpp](../examples/C++17/if_constexpr.cpp)

## if/switch Initializers (C++17 Addition)
**Explanation**: Initialize variables directly in `if` or `switch` statements, limiting scope.  
**Real-World Scenario**: Check a file’s status in a file manager with scoped variables.  
**Snippet**:  
```cpp
if (auto f = std::ifstream("file.txt"); f.is_open()) {}
```
**Example**: [if_switch_initializers.cpp](../examples/C++17/if_switch_initializers.cpp)

## Inline Variables (C++17 Addition)
**Explanation**: Variables can be declared `inline` in headers, avoiding multiple definition errors.  
**Real-World Scenario**: Define a global constant across translation units in a library.  
**Snippet**:  
```cpp
inline int globalCounter = 0;
```
**Example**: [inline_variables.cpp](../examples/C++17/inline_variables.cpp)

## constexpr Lambdas (C++17 Addition)
**Explanation**: Lambdas can be `constexpr`, allowing compile-time evaluation.  
**Real-World Scenario**: Compute constant values at compile time in a math library.  
**Snippet**:  
```cpp
constexpr auto square = [](int x) { return x * x; }; constexpr int result = square(5);
```
**Example**: [constexpr_lambdas.cpp](../examples/C++17/constexpr_lambdas.cpp)

## Fold Expressions (C++17 Addition)
**Explanation**: Simplifies variadic template operations with binary operators.  
**Real-World Scenario**: Sum multiple arguments in a generic logger function.  
**Snippet**:  
```cpp
template<typename... Args> auto sum(Args... args) { return (args + ...); }
```
**Example**: [fold_expressions.cpp](../examples/C++17/fold_expressions.cpp)

## Template Argument Deduction for Class Templates (C++17 Addition)
**Explanation**: Automatically deduces template arguments for class constructors.  
**Real-World Scenario**: Simplify vector initialization in a game’s data structure.  
**Snippet**:  
```cpp
std::vector vec = {1, 2, 3}; // Deduced as std::vector<int>
```
**Example**: [template_argument_deduction.cpp](../examples/C++17/template_argument_deduction.cpp)

## [[fallthrough]], [[maybe_unused]], [[nodiscard]] Attributes (C++17 Addition)
**Explanation**: New attributes for explicit control flow (`fallthrough`), suppressing unused warnings (`maybe_unused`), and enforcing return value use (`nodiscard`).  
**Real-World Scenario**: Mark a function’s return value as critical in a safety system.  
**Snippet**:  
```cpp
[[nodiscard]] int compute() { return 42; }
```
**Example**: [attributes.cpp](../examples/C++17/attributes.cpp)

## Nested Namespace Definitions (C++17 Addition)
**Explanation**: Simplifies nested namespace declarations with `::` syntax.  
**Real-World Scenario**: Organize a library’s utility functions in nested namespaces.  
**Snippet**:  
```cpp
namespace Util::Math { void func() {} }
```
**Example**: [nested_namespaces.cpp](../examples/C++17/nested_namespaces.cpp)

## constexpr if in constexpr Functions (C++17 Evolution)
**Explanation**: `constexpr` functions can use `if constexpr` for compile-time branching, enhancing flexibility.  
**Real-World Scenario**: Optimize compile-time calculations in a graphics engine.  
**Snippet**:  
```cpp
constexpr int select(int x) { if constexpr (sizeof(int) == 4) return x; else return 0; }
```
**Example**: [constexpr_if.cpp](../examples/C++17/constexpr_if.cpp)

## Guaranteed Copy Elision (C++17 Addition)
**Explanation**: Eliminates unnecessary copies/moves for temporary objects in certain cases.  
**Real-World Scenario**: Optimize object creation in a performance-critical game loop.  
**Snippet**:  
```cpp
struct Data { Data() {} }; Data create() { return Data(); } // No copy
```
**Example**: [copy_elision.cpp](../examples/C++17/copy_elision.cpp)

## static_assert without Message (C++17 Evolution)
**Explanation**: `static_assert` no longer requires a message string, simplifying usage.  
**Real-World Scenario**: Check type requirements in a template library without verbose messages.  
**Snippet**:  
```cpp
static_assert(sizeof(int) == 4);
```
**Example**: [static_assert.cpp](../examples/C++17/static_assert.cpp)

## Hexadecimal Floating-Point Literals (C++17 Addition)
**Explanation**: Floating-point literals can be written in hexadecimal with `0x` prefix.  
**Real-World Scenario**: Specify precise floating-point constants in a scientific application.  
**Snippet**:  
```cpp
double x = 0x1.4p3; // 1.25 * 2^3 = 10.0
```
**Example**: [hex_float_literals.cpp](../examples/C++17/hex_float_literals.cpp)

## __has_include Preprocessor Directive (C++17 Addition)
**Explanation**: Checks if a header is available during preprocessing.  
**Real-World Scenario**: Conditionally include optional dependencies in a portable library.  
**Snippet**:  
```cpp
#if __has_include(<optional>) #include <optional> #endif
```
**Example**: [has_include.cpp](../examples/C++17/has_include.cpp)