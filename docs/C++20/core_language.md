# C++20 Core Language Concepts

This document covers new or evolved C++20 core language concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../examples/C++20/). Only additions or evolutions from C++98/C++03/C++11/C++14/C++17 are included.

## Concepts (C++20 Addition)
**Explanation**: Define constraints on template parameters, improving type checking and error messages.  
**Real-World Scenario**: Restrict a generic function to numeric types in a math library.  
**Snippet**:  
```cpp
#include <concepts> template<std::integral T> void process(T t) {}
```
**Example**: [concepts.cpp](../examples/C++20/concepts.cpp)

## Constraints and Requires Clauses (C++20 Addition)
**Explanation**: Specify requirements for template parameters using `requires` clauses.  
**Real-World Scenario**: Ensure a template function accepts only floating-point types in a physics engine.  
**Snippet**:  
```cpp
template<typename T> requires std::floating_point<T> void compute(T t) {}
```
**Example**: [constraints_requires.cpp](../examples/C++20/constraints_requires.cpp)

## Constrained Templates (C++20 Addition)
**Explanation**: Use concepts directly in template declarations for concise constraints.  
**Real-World Scenario**: Define a generic container that requires comparable types for sorting.  
**Snippet**:  
```cpp
template<std::totally_ordered T> class SortedContainer {};
```
**Example**: [constrained_templates.cpp](../examples/C++20/constrained_templates.cpp)

## Abbreviated Function Templates (C++20 Addition)
**Explanation**: Use `auto` in function templates for simpler syntax.  
**Real-World Scenario**: Write a generic function for a logging system without verbose templates.  
**Snippet**:  
```cpp
auto process(auto x) { return x; }
```
**Example**: [abbreviated_function_templates.cpp](../examples/C++20/abbreviated_function_templates.cpp)

## Three-Way Comparison Operator (Spaceship Operator, <=>) (C++20 Addition)
**Explanation**: Single operator for comparing objects, returning `std::strong_ordering` or similar.  
**Real-World Scenario**: Simplify sorting of game entities by multiple criteria.  
**Snippet**:  
```cpp
struct Item { int id; auto operator<=>(const Item& other) const { return id <=> other.id; } };
```
**Example**: [spaceship_operator.cpp](../examples/C++20/spaceship_operator.cpp)

## std::strong_ordering (C++20 Addition)
**Explanation**: Comparison result type for strict total order (e.g., integers).  
**Real-World Scenario**: Compare database keys ensuring strict ordering in a query system.  
**Snippet**:  
```cpp
#include <compare> std::strong_ordering result = 5 <=> 10;
```
**Example**: [strong_ordering.cpp](../examples/C++20/strong_ordering.cpp)

## std::weak_ordering (C++20 Addition)
**Explanation**: Comparison result type for weak ordering (e.g., case-insensitive strings).  
**Real-World Scenario**: Sort usernames case-insensitively in a user management system.  
**Snippet**:  
```cpp
#include <compare> std::weak_ordering result = str1 <=> str2;
```
**Example**: [weak_ordering.cpp](../examples/C++20/weak_ordering.cpp)

## std::partial_ordering (C++20 Addition)
**Explanation**: Comparison result type for partial ordering (e.g., floating-point with NaN).  
**Real-World Scenario**: Compare measurements with NaN in a scientific application.  
**Snippet**:  
```cpp
#include <compare> std::partial_ordering result = 1.0 <=> std::numeric_limits<double>::quiet_NaN();
```
**Example**: [partial_ordering.cpp](../examples/C++20/partial_ordering.cpp)

## Lambda Improvements (C++20 Evolution)
**Explanation**: Lambdas support `constexpr`, explicit template parameters, and capture of `this` by value.  
**Real-World Scenario**: Use a lambda in a compile-time context for a math library.  
**Snippet**:  
```cpp
constexpr auto lambda = []<typename T>(T x) { return x * x; };
```
**Example**: [lambda_enhancements.cpp](../examples/C++20/lambda_enhancements.cpp)

## Stateless Lambda Call Operator as consteval (C++20 Addition)
**Explanation**: Stateless lambdas can have `consteval` call operators for compile-time execution.  
**Real-World Scenario**: Generate compile-time constants in a configuration system.  
**Snippet**:  
```cpp
auto lambda = []() consteval { return 42; };
```
**Example**: [consteval_lambda.cpp](../examples/C++20/consteval_lambda.cpp)

## Lambda Capture of [this] by Value (C++20 Evolution)
**Explanation**: Lambdas can capture `this` by value, copying the object.  
**Real-World Scenario**: Capture a game object’s state in a callback without lifetime issues.  
**Snippet**:  
```cpp
[this] { return x; }; // Captures *this by value
```
**Example**: [lambda_this_capture.cpp](../examples/C++20/lambda_this_capture.cpp)

## Template Lambdas (C++20 Addition)
**Explanation**: Lambdas with explicit template parameters for generic programming.  
**Real-World Scenario**: Write a generic lambda for type-safe processing in a data pipeline.  
**Snippet**:  
```cpp
auto lambda = []<typename T>(T x) { return x; };
```
**Example**: [template_lambdas.cpp](../examples/C++20/template_lambdas.cpp)

## Constexpr Improvements (C++20 Evolution)
**Explanation**: `constexpr` supports virtual functions, dynamic memory, and STL types like `std::string`.  
**Real-World Scenario**: Compute complex data structures at compile time in a math library.  
**Snippet**:  
```cpp
constexpr int compute() { std::string s = "test"; return s.size(); }
```
**Example**: [constexpr_improvements.cpp](../examples/C++20/constexpr_improvements.cpp)

## Constexpr Virtual Functions (C++20 Addition)
**Explanation**: Virtual functions can be `constexpr`, enabling compile-time polymorphism.  
**Real-World Scenario**: Evaluate polymorphic behavior at compile time in a graphics engine.  
**Snippet**:  
```cpp
struct Base { virtual constexpr int f() const { return 0; } };
```
**Example**: [constexpr_virtual.cpp](../examples/C++20/constexpr_virtual.cpp)

## Constexpr Dynamic Memory Allocation (C++20 Addition)
**Explanation**: `new` and `delete` can be used in `constexpr` contexts for dynamic allocation.  
**Real-World Scenario**: Allocate compile-time arrays in a configuration system.  
**Snippet**:  
```cpp
constexpr int* alloc() { return new int[5]; }
```
**Example**: [constexpr_allocation.cpp](../examples/C++20/constexpr_allocation.cpp)

## Constexpr std::string (C++20 Evolution)
**Explanation**: `std::string` supports `constexpr` operations for compile-time string manipulation.  
**Real-World Scenario**: Generate constant strings at compile time for a parser.  
**Snippet**:  
```cpp
constexpr std::string s = "hello"; constexpr auto len = s.size();
```
**Example**: [constexpr_string.cpp](../examples/C++20/constexpr_string.cpp)

## Constexpr std::vector (C++20 Evolution)
**Explanation**: `std::vector` supports `constexpr` operations for compile-time container manipulation.  
**Real-World Scenario**: Create compile-time lookup tables in a data processor.  
**Snippet**:  
```cpp
constexpr std::vector<int> vec = {1, 2, 3};
```
**Example**: [constexpr_vector.cpp](../examples/C++20/constexpr_vector.cpp)

## Immediate Functions (consteval) (C++20 Addition)
**Explanation**: Functions guaranteed to evaluate at compile time.  
**Real-World Scenario**: Generate compile-time constants for a configuration system.  
**Snippet**:  
```cpp
consteval int getConfig() { return 42; }
```
**Example**: [immediate_functions.cpp](../examples/C++20/immediate_functions.cpp)

## Constant Evaluation for Non-Type Template Parameters (C++20 Addition)
**Explanation**: Non-type template parameters can be evaluated at compile time with `constexpr`.  
**Real-World Scenario**: Use compile-time strings as template parameters in a serializer.  
**Snippet**:  
```cpp
template<auto Val> struct S {}; S<42> s;
```
**Example**: [consteval_nttp.cpp](../examples/C++20/consteval_nttp.cpp)

## std::is_constant_evaluated (C++20 Addition)
**Explanation**: Checks if code is evaluated in a `constexpr` context.  
**Real-World Scenario**: Optimize code paths for compile-time vs. runtime in a library.  
**Snippet**:  
```cpp
#include <type_traits> if (std::is_constant_evaluated()) {}
```
**Example**: [is_constant_evaluated.cpp](../examples/C++20/is_constant_evaluated.cpp)

## Modules (C++20 Addition)
**Explanation**: Replace headers with modules for faster compilation and better encapsulation.  
**Real-World Scenario**: Modularize a game engine’s math library for cleaner dependencies.  
**Snippet**:  
```cpp
export module math; export int add(int a, int b) { return a + b; }
```
**Example**: [modules.cpp](../examples/C++20/modules.cpp)

## Import/Export Declarations (C++20 Addition)
**Explanation**: `import` and `export` manage module dependencies and interfaces.  
**Real-World Scenario**: Import a utility module in a game engine’s core.  
**Snippet**:  
```cpp
import math; int x = add(1, 2);
```
**Example**: [import_export.cpp](../examples/C++20/import_export.cpp)

## Coroutines (C++20 Addition)
**Explanation**: Functions that can suspend and resume execution, enabling asynchronous programming.  
**Real-World Scenario**: Implement a non-blocking task scheduler in a server application.  
**Snippet**:  
```cpp
#include <coroutine> std::suspend_always yield() { return {}; }
```
**Example**: [coroutines.cpp](../examples/C++20/coroutines.cpp)

## co_await (C++20 Addition)
**Explanation**: Suspends a coroutine until an awaited operation completes.  
**Real-World Scenario**: Wait for an async I/O operation in a network server.  
**Snippet**:  
```cpp
#include <coroutine> auto task() { co_await std::suspend_always{}; }
```
**Example**: [co_await.cpp](../examples/C++20/co_await.cpp)

## co_yield (C++20 Addition)
**Explanation**: Yields a value from a coroutine, suspending execution.  
**Real-World Scenario**: Generate a sequence of game events incrementally.  
**Snippet**:  
```cpp
#include <coroutine> auto gen() { co_yield 42; }
```
**Example**: [co_yield.cpp](../examples/C++20/co_yield.cpp)

## co_return (C++20 Addition)
**Explanation**: Returns a value from a coroutine, completing it.  
**Real-World Scenario**: Return the result of an async computation in a server.  
**Snippet**:  
```cpp
#include <coroutine> auto task() { co_return 42; }
```
**Example**: [co_return.cpp](../examples/C++20/co_return.cpp)

## std::source_location (C++20 Addition)
**Explanation**: Provides compile-time information about the source code (e.g., file, line).  
**Real-World Scenario**: Log the source location of errors in a debugging system.  
**Snippet**:  
```cpp
#include <source_location> auto loc = std::source_location::current();
```
**Example**: [source_location.cpp](../examples/C++20/source_location.cpp)

## std::endian (C++20 Addition)
**Explanation**: Queries the endianness of the platform.  
**Real-World Scenario**: Handle endianness in a cross-platform network protocol.  
**Snippet**:  
```cpp
#include <bit> auto is_big = std::endian::native == std::endian::big;
```
**Example**: [endian.cpp](../examples/C++20/endian.cpp)

## Designated Initializers (C++20 Addition)
**Explanation**: Initialize struct members by name, improving readability.  
**Real-World Scenario**: Initialize a game character’s attributes clearly.  
**Snippet**:  
```cpp
struct Player { int health; int score; }; Player p = { .health = 100, .score = 0 };
```
**Example**: [designated_initializers.cpp](../examples/C++20/designated_initializers.cpp)

## [[no_unique_address]] Attribute (C++20 Addition)
**Explanation**: Allows empty non-static data members to occupy no space, optimizing memory.  
**Real-World Scenario**: Optimize memory in a tightly packed data structure for a game.  
**Snippet**:  
```cpp
struct Empty {}; struct Data { [[no_unique_address]] Empty e; int x; };
```
**Example**: [no_unique_address.cpp](../examples/C++20/no_unique_address.cpp)

## constinit (C++20 Addition)
**Explanation**: Ensures static variables are initialized at compile time, avoiding runtime overhead.  
**Real-World Scenario**: Initialize a global configuration constant in a system.  
**Snippet**:  
```cpp
constinit int globalConfig = 42;
```
**Example**: [constinit.cpp](../examples/C++20/constinit.cpp)

## Explicit bool in Conditionals (C++20 Addition)
**Explanation**: Explicitly specify `bool` in conditionals for clarity and safety.  
**Real-World Scenario**: Ensure a condition in a control system evaluates to `bool`.  
**Snippet**:  
```cpp
if (explicit bool flag = compute(); flag) {}
```
**Example**: [explicit_bool.cpp](../examples/C++20/explicit_bool.cpp)

## Aggregate Initialization with Parentheses (C++20 Evolution)
**Explanation**: Aggregates can be initialized with parentheses, not just braces.  
**Real-World Scenario**: Initialize a struct in a game with a constructor-like syntax.  
**Snippet**:  
```cpp
struct Point { int x, y; }; Point p(1, 2);
```
**Example**: [aggregate_initialization.cpp](../examples/C++20/aggregate_initialization.cpp)

## using enum (C++20 Addition)
**Explanation**: Imports enum values into the current scope, avoiding qualification.  
**Real-World Scenario**: Simplify state handling in a game’s state machine.  
**Snippet**:  
```cpp
enum class State { Idle, Running }; using enum State; auto s = Idle;
```
**Example**: [using_enum.cpp](../examples/C++20/using_enum.cpp)

## Class Template Argument Deduction Enhancements (C++20 Evolution)
**Explanation**: Improved deduction for aggregates and aliases, simplifying instantiation.  
**Real-World Scenario**: Create a pair in a data processor without specifying types.  
**Snippet**:  
```cpp
std::pair p = {1, "value"}; // Deduced as std::pair<int, std::string>
```
**Example**: [ctad_enhancements.cpp](../examples/C++20/ctad_enhancements.cpp)

## [[likely]] and [[unlikely]] Attributes (C++20 Addition)
**Explanation**: Hints to the compiler about branch prediction optimization.  
**Real-World Scenario**: Optimize performance in a hot path of a game loop.  
**Snippet**:  
```cpp
if (condition) [[likely]] {}
```
**Example**: [likely_unlikely.cpp](../examples/C++20/likely_unlikely.cpp)