# C++23 Core Language Concepts

This document covers new or evolved C++23 core language concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../examples/C++23/). Only additions or evolutions from C++98/C++03/C++11/C++14/C++17/C++20 are included.

## Range-based For Loop with Initializer (C++23 Addition)
**Explanation**: Allows initializing variables directly in a range-based for loop, limiting scope.  
**Real-World Scenario**: Initialize a counter while iterating over a game’s inventory.  
**Snippet**:  
```cpp
for (int i = 0; auto& item : inventory) { ++i; }
```
**Example**: [range_for_initializer.cpp](../examples/C++23/range_for_initializer.cpp)

## Explicit This Parameter in Lambdas (Deducing This) (C++23 Addition)
**Explanation**: Lambdas can use an explicit `this` parameter, enabling recursive lambdas and `this` deduction.  
**Real-World Scenario**: Write a recursive lambda to traverse a game’s scene graph.  
**Snippet**:  
```cpp
auto factorial = [](this auto self, int n) { return n == 0 ? 1 : n * self(n - 1); };
```
**Example**: [deducing_this.cpp](../examples/C++23/deducing_this.cpp)

## [[assume]] Attribute (C++23 Addition)
**Explanation**: Informs the compiler of an assumed condition for optimization, undefined if false.  
**Real-World Scenario**: Optimize a loop in a rendering engine by assuming valid input.  
**Snippet**:  
```cpp
[[assume(ptr != nullptr)]]; *ptr = 42;
```
**Example**: [assume_attribute.cpp](../examples/C++23/assume_attribute.cpp)

## Multidimensional Array Subscript Operator (C++23 Addition)
**Explanation**: Supports `operator[]` with multiple arguments for multidimensional arrays.  
**Real-World Scenario**: Access a 2D grid in a game with a single `operator[]` call.  
**Snippet**:  
```cpp
struct Grid { int operator[](int x, int y) { return data[x][y]; } };
```
**Example**: [multidim_subscript.cpp](../examples/C++23/multidim_subscript.cpp)

## Static operator() (C++23 Addition)
**Explanation**: Function objects can have `static operator()`, enabling stateless callables.  
**Real-World Scenario**: Define a stateless functor for a math library’s operations.  
**Snippet**:  
```cpp
struct Math { static int operator()(int x) { return x * x; } };
```
**Example**: [static_operator_call.cpp](../examples/C++23/static_operator_call.cpp)

## Static operator[] (C++23 Addition)
**Explanation**: Allows `operator[]` to be static for stateless indexing.  
**Real-World Scenario**: Implement a lookup table with static indexing in a configuration system.  
**Snippet**:  
```cpp
struct Table { static int operator[](int i) { return values[i]; } };
```
**Example**: [static_operator_subscript.cpp](../examples/C++23/static_operator_subscript.cpp)

## if consteval (C++23 Addition)
**Explanation**: Branch based on whether code is in a `consteval` context, simplifying compile-time logic.  
**Real-World Scenario**: Use different code paths for compile-time vs. runtime in a math library.  
**Snippet**:  
```cpp
if consteval { return 42; } else { return compute(); }
```
**Example**: [if_consteval.cpp](../examples/C++23/if_consteval.cpp)

## size_t Literal Suffix (uz/zu)
**Explanation**: The `uz` or `zu` suffix creates a `std::size_t` literal directly, eliminating the need for casts in size-related expressions.
**Real-World Scenario**: Write loop bounds matching container `size()` return type without signed/unsigned mismatch warnings.
**Snippet**:
```cpp
for (auto i = 0uz; i < vec.size(); ++i) { /* no warning */ }
```
**Example**: [size_t_literal.cpp](../examples/C++23/size_t_literal.cpp)

## #warning Preprocessor Directive
**Explanation**: A standardized preprocessor directive that emits a compiler warning with a custom message during compilation.
**Real-World Scenario**: Warn developers that a deprecated API path is being compiled and should be migrated.
**Snippet**:
```cpp
#warning "This module uses the legacy API — migrate to v2 before Q4"
```
**Example**: [warning_directive.cpp](../examples/C++23/warning_directive.cpp)

## #elifdef / #elifndef Preprocessor Directives
**Explanation**: Shorthand for `#elif defined(...)` and `#elif !defined(...)`, simplifying conditional compilation chains.
**Real-World Scenario**: Select platform-specific implementations in a cross-platform build system.
**Snippet**:
```cpp
#ifdef _WIN32
  // Windows
#elifdef __linux__
  // Linux
#elifdef __APPLE__
  // macOS
#endif
```
**Example**: [elifdef.cpp](../examples/C++23/elifdef.cpp)

## auto(x) and auto{x} Decay-Copy Expressions
**Explanation**: Explicitly creates a decay-copy of an expression, applying array-to-pointer and function-to-pointer conversions.
**Real-World Scenario**: Safely capture a string literal or array as a decayed pointer type in a generic context.
**Snippet**:
```cpp
void process(auto val) {
    auto copy = auto(val); // guaranteed decay-copy
}
```
**Example**: [decay_copy.cpp](../examples/C++23/decay_copy.cpp)

## Constexpr Improvements
**Explanation**: C++23 permits more operations in `constexpr` functions, including `goto`, labels, and `static`/`thread_local` variables under certain conditions.
**Real-World Scenario**: Implement a compile-time state machine with jumps for a protocol parser.
**Snippet**:
```cpp
constexpr int compute(int n) {
    int result = 0;
    for (int i = 0; i < n; ++i) result += i;
    return result;
}
static_assert(compute(5) == 10);
```
**Example**: [constexpr_improvements.cpp](../examples/C++23/constexpr_improvements.cpp)

## Lambda Trailing Return Type Scope Changes
**Explanation**: Name lookup in a lambda's trailing return type now sees the lambda's own captures and parameters, fixing a longstanding inconsistency.
**Real-World Scenario**: Use a captured variable's type in the lambda's return type declaration without workarounds.
**Snippet**:
```cpp
auto make_adder(int x) {
    return [x](int y) -> decltype(x + y) { return x + y; };
}
```
**Example**: [lambda_return_scope.cpp](../examples/C++23/lambda_return_scope.cpp)