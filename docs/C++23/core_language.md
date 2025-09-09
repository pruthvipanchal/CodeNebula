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