# C++14 Core Language Concepts

This document covers new or evolved C++14 core language concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../examples/C++14/). Only additions or evolutions from C++98/C++03/C++11 are included.

## Generic Lambdas (C++14 Addition)
**Explanation**: Lambdas can use `auto` in parameter declarations, allowing polymorphic behavior.  
**Real-World Scenario**: Write a generic sorting function for different data types in a leaderboard system.  
**Snippet**:  
```cpp
auto lambda = [](auto a, auto b) { return a < b; };
```
**Example**: [generic_lambdas.cpp](../examples/C++14/generic_lambdas.cpp)

## Lambda Capture Initializers (C++14 Addition)
**Explanation**: Lambdas can initialize captured variables with arbitrary expressions, including move semantics.  
**Real-World Scenario**: Capture a moved resource in a logging function for a resource manager.  
**Snippet**:  
```cpp
auto ptr = std::make_unique<int>(5); auto lambda = [p = std::move(ptr)] { return *p; };
```
**Example**: [lambda_capture_initializers.cpp](../examples/C++14/lambda_capture_initializers.cpp)

## Variable Templates (C++14 Addition)
**Explanation**: Templates for variables, allowing generic constants or variables.  
**Real-World Scenario**: Define a generic constant for physics calculations across types in a simulation.  
**Snippet**:  
```cpp
template<typename T> constexpr T pi = T(3.141592653589793); float f = pi<float>;
```
**Example**: [variable_templates.cpp](../examples/C++14/variable_templates.cpp)

## decltype(auto) (C++14 Addition)
**Explanation**: Deduce type like `auto`, but preserve reference and cv-qualifiers from `decltype`.  
**Real-World Scenario**: Return correct type in a generic wrapper function for a data processor.  
**Snippet**:  
```cpp
decltype(auto) getValue() { static int x = 10; return x; }
```
**Example**: [decltype_auto.cpp](../examples/C++14/decltype_auto.cpp)

## Relaxed constexpr (C++14 Evolution)
**Explanation**: `constexpr` functions can include multiple statements, loops, and local variables, unlike C++11’s single-expression limit.  
**Real-World Scenario**: Compute complex constants at compile time in a physics engine.  
**Snippet**:  
```cpp
constexpr int factorial(int n) { int r = 1; for (int i = 1; i <= n; ++i) r *= i; return r; }
```
**Example**: [constexpr_relaxed.cpp](../examples/C++14/constexpr_relaxed.cpp)

## [[deprecated]] Attribute (C++14 Addition)
**Explanation**: Marks functions or types as deprecated, generating compiler warnings.  
**Real-World Scenario**: Warn users about an outdated API in a library migration.  
**Snippet**:  
```cpp
[[deprecated]] void oldFunction() {}
```
**Example**: [deprecated_attribute.cpp](../examples/C++14/deprecated_attribute.cpp)

## Binary Literals (C++14 Addition)
**Explanation**: Integer literals can be written in binary using `0b` or `0B` prefix.  
**Real-World Scenario**: Define bitmasks for hardware registers in embedded systems.  
**Snippet**:  
```cpp
int mask = 0b1010;
```
**Example**: [binary_literals.cpp](../examples/C++14/binary_literals.cpp)

## Digit Separators (C++14 Addition)
**Explanation**: Use single quotes (`'`) to separate digits in numeric literals for readability.  
**Real-World Scenario**: Improve readability of large constants in a financial application.  
**Snippet**:  
```cpp
int large = 1'000'000;
```
**Example**: [digit_separators.cpp](../examples/C++14/digit_separators.cpp)