# C++26 Core Language Concepts

This document covers new or evolved C++26 core language concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../../examples/C++26/). Only additions or evolutions from C++98/C++03/C++11/C++14/C++17/C++20/C++23 are included. Note: Some features (e.g., contracts, pattern matching, reflection) are proposed and may be deferred to post-C++26.

## Contracts (C++26 Proposed, Deferred to Post-C++26)
**Explanation**: Specify preconditions, postconditions, and assertions for functions (proposed, likely deferred).  
**Real-World Scenario**: Enforce input validation for a game engine’s API.  
**Snippet**:  
```cpp
void process(int x) [[pre: x > 0]]; // Proposed syntax
```
**Example**: [contracts.cpp](../../examples/C++26/contracts.cpp)

## Pattern Matching (C++26 Proposed)
**Explanation**: Match expressions against patterns, simplifying complex conditionals (proposed).  
**Real-World Scenario**: Parse game events with structured pattern matching in a state machine.  
**Snippet**:  
```cpp
inspect (value) { <pattern> => expr; }; // Proposed syntax
```
**Example**: [pattern_matching.cpp](../../examples/C++26/pattern_matching.cpp)

## Reflection (P2996, Static Reflection)
**Explanation**: Compile-time introspection of types, members, and namespaces via static reflection (P2996). Enables querying type properties, enumerating members, and generating code based on type structure -- all at compile time without runtime overhead.
**Real-World Scenario**: Automatically generate serialization and deserialization code for game objects by reflecting over their data members at compile time.
**Snippet**:
```cpp
#include <meta>

struct Player { std::string name; int score; };

// Reflect over members of Player at compile time
constexpr auto members = std::meta::members_of(^Player);
static_assert(members.size() == 2);
// Access member name: std::meta::name_of(members[0]) == "name"
```
**Example**: [reflection.cpp](../../examples/C++26/reflection.cpp)

## std::meta (Meta-Programming, Proposed)
**Explanation**: Meta-programming facilities for manipulating code as data (proposed).  
**Real-World Scenario**: Generate compile-time data structures for a configuration system.  
**Snippet**:  
```cpp
#include <meta> auto meta = std::meta::info<decltype(obj)>(); // Proposed
```
**Example**: [meta_programming.cpp](../../examples/C++26/meta_programming.cpp)

## Extended Floating-Point Types (C++26 Addition)
**Explanation**: Adds `std::float16_t`, `std::float32_t`, `std::float64_t`, `std::float128_t` for precise floating-point control.  
**Real-World Scenario**: Use `std::float16_t` for memory-efficient graphics calculations.  
**Snippet**:  
```cpp
#include <stdfloat> std::float16_t x = 1.0f16;
```
**Example**: [extended_float.cpp](../../examples/C++26/extended_float.cpp)

## Pack Indexing
**Explanation**: Allows direct indexing into a parameter pack using `Pack...[N]` syntax, eliminating the need for recursive template tricks or `std::tuple` to access a specific element in a variadic pack.
**Real-World Scenario**: In a plugin system with variadic template arguments, retrieve a specific argument by index without writing boilerplate helper templates.
**Snippet**:
```cpp
template <typename... Ts>
using Third = Ts...[2]; // Access the third type in the pack

template <typename... Ts>
constexpr auto get_first(Ts... args) {
    return args...[0]; // Access the first value in the pack
}

static_assert(get_first(10, 20, 30) == 10);
```
**Example**: [pack_indexing.cpp](../../examples/C++26/pack_indexing.cpp)

## Placeholder Variables with Multiple _
**Explanation**: Allows using the identifier `_` as a placeholder for variables that are intentionally unused. Multiple declarations of `_` in the same scope do not conflict, making it clear that the values are discarded.
**Real-World Scenario**: When destructuring a complex struct, ignore irrelevant fields cleanly without triggering compiler warnings.
**Snippet**:
```cpp
auto [x, _, _, w] = std::tuple{1, 2, 3, 4}; // Ignore second and third elements
// x == 1, w == 4; both _ bindings are discarded

for (auto [key, _] : my_map) {
    process(key); // Only the key matters
}
```
**Example**: [placeholder_variables.cpp](../../examples/C++26/placeholder_variables.cpp)

## Structured Bindings as Conditions
**Explanation**: Enables structured bindings directly within `if` and `switch` conditions, combining decomposition and conditional testing in a single statement. This reduces boilerplate when a function returns a struct or pair and you want to test one field while binding others.
**Real-World Scenario**: Check the success flag of an API response and bind the payload in one step within a network client.
**Snippet**:
```cpp
std::map<std::string, int> scores;
if (auto [it, inserted] = scores.emplace("Alice", 100); inserted) {
    std::println("Added {} with score {}", it->first, it->second);
}

// Also works with custom types
struct Result { bool ok; std::string data; };
if (auto [ok, data] = fetch_data(); ok) {
    process(data);
}
```
**Example**: [structured_bindings_conditions.cpp](../../examples/C++26/structured_bindings_conditions.cpp)

## constexpr Cast from void*
**Explanation**: Allows `static_cast` from `void*` to a typed pointer in `constexpr` contexts. Previously, `void*` casts were forbidden at compile time, limiting what could be done in constant expressions involving type-erased storage.
**Real-World Scenario**: Implement a compile-time type-erased allocator or small buffer optimization that needs to cast between `void*` and concrete types during constant evaluation.
**Snippet**:
```cpp
constexpr int test() {
    int value = 42;
    void* vp = &value;
    int* ip = static_cast<int*>(vp); // Now valid in constexpr
    return *ip;
}

static_assert(test() == 42);
```
**Example**: [constexpr_void_cast.cpp](../../examples/C++26/constexpr_void_cast.cpp)

## Erroneous Behavior for Uninitialized Reads
**Explanation**: Reading an uninitialized variable is now classified as erroneous behavior rather than undefined behavior. The compiler may produce a predictable (but unspecified) value instead of enabling arbitrary miscompilation. This improves safety while giving implementations freedom to trap or diagnose.
**Real-World Scenario**: In safety-critical embedded firmware, an accidental read of an uninitialized sensor buffer no longer risks silent data corruption or optimized-away checks -- the behavior is constrained and diagnosable.
**Snippet**:
```cpp
int x; // uninitialized
int y = x; // C++26: erroneous behavior (not undefined)
// The implementation may produce a valid-but-unspecified int value
// Compilers can issue warnings or trap, but cannot assume "this never happens"
```
**Example**: [erroneous_behavior.cpp](../../examples/C++26/erroneous_behavior.cpp)

## User-Generated static_assert Messages
**Explanation**: Allows `static_assert` to accept a message generated at compile time from a user-defined object (e.g., a constexpr string or any type with `size()` and `data()` members), rather than only string literals. This enables far more informative compile-time diagnostics.
**Real-World Scenario**: A template library reports the exact mismatched type name in a static assertion, rather than a generic "type mismatch" literal.
**Snippet**:
```cpp
#include <string>
#include <format>

template <typename T>
constexpr void validate() {
    constexpr auto msg = std::format("Type {} does not meet requirements", typeid(T).name());
    static_assert(std::is_integral_v<T>, msg); // User-generated message
}
// Compiler output includes the formatted type name in the error
```
**Example**: [static_assert_message.cpp](../../examples/C++26/static_assert_message.cpp)