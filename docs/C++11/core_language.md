# C++11 Core Language Concepts

This document covers new or evolved C++11 core language concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../examples/C++11/). Only additions or evolutions from C++98/C++03 are included.

## Rvalue References (C++11 Addition)
**Explanation**: References to temporary objects (`&&`), enabling move semantics for efficient resource transfer.  
**Real-World Scenario**: Optimize data transfer in a file copy operation by moving large buffers.  
**Snippet**:  
```cpp
void process(int&& rvalue) {}
```
**Example**: [rvalue_references.cpp](../examples/C++11/rvalue_references.cpp)

## Move Semantics (C++11 Addition)
**Explanation**: Transfers resources from temporary objects, avoiding copies, using rvalue references.  
**Real-World Scenario**: Move large data buffers in a network application to reduce overhead.  
**Snippet**:  
```cpp
std::vector<int> vec; vec = std::move(otherVec);
```
**Example**: [move_semantics.cpp](../examples/C++11/move_semantics.cpp)

## std::move (C++11 Addition)
**Explanation**: Converts an lvalue to an rvalue, enabling move semantics.  
**Real-World Scenario**: Transfer ownership of a resource in a resource manager.  
**Snippet**:  
```cpp
#include <utility> std::vector<int> vec = std::move(otherVec);
```
**Example**: [move.cpp](../examples/C++11/move.cpp)

## std::forward (C++11 Addition)
**Explanation**: Preserves value category (lvalue/rvalue) in template forwarding.  
**Real-World Scenario**: Write a generic wrapper function for a logging system.  
**Snippet**:  
```cpp
template<typename T> void forward(T&& arg) { func(std::forward<T>(arg)); }
```
**Example**: [forward.cpp](../examples/C++11/forward.cpp)

## Lambda Expressions (C++11 Addition)
**Explanation**: Anonymous functions for concise, inline logic, with capture lists for accessing variables.  
**Real-World Scenario**: Sort a list of players by score in a game using a custom comparator.  
**Snippet**:  
```cpp
auto lambda = [](int a, int b) { return a > b; };
```
**Example**: [lambda_expressions.cpp](../examples/C++11/lambda_expressions.cpp)

## Delegating Constructors (C++11 Addition)
**Explanation**: Constructors can call other constructors in the same class, reducing code duplication.  
**Real-World Scenario**: Initialize a player object with default values in a game.  
**Snippet**:  
```cpp
class Player { Player() : Player(100) {} Player(int health) {} };
```
**Example**: [delegating_constructors.cpp](../examples/C++11/delegating_constructors.cpp)

## Defaulted and Deleted Functions (C++11 Addition)
**Explanation**: Explicitly default or delete special member functions (e.g., copy constructor).  
**Real-World Scenario**: Prevent copying of a unique resource in a system.  
**Snippet**:  
```cpp
class Resource { Resource(const Resource&) = delete; };
```
**Example**: [defaulted_deleted_functions.cpp](../examples/C++11/defaulted_deleted_functions.cpp)

## Override Specifier (C++11 Addition)
**Explanation**: Ensures a function overrides a virtual function, improving code clarity.  
**Real-World Scenario**: Ensure correct overriding in a game’s enemy hierarchy.  
**Snippet**:  
```cpp
class Enemy { virtual void attack() {} }; class Boss : public Enemy { void attack() override {} };
```
**Example**: [override_specifier.cpp](../examples/C++11/override_specifier.cpp)

## Final Specifier (C++11 Addition)
**Explanation**: Prevents class inheritance or function overriding for safety.  
**Real-World Scenario**: Lock a critical class in a security system.  
**Snippet**:  
```cpp
class Secure final {};
```
**Example**: [final_specifier.cpp](../examples/C++11/final_specifier.cpp)

## Variadic Templates (C++11 Addition)
**Explanation**: Templates with a variable number of arguments for flexible generic programming.  
**Real-World Scenario**: Create a generic logger for multiple data types.  
**Snippet**:  
```cpp
template<typename... Args> void log(Args... args) {}
```
**Example**: [variadic_templates.cpp](../examples/C++11/variadic_templates.cpp)

## Template Aliases (C++11 Addition)
**Explanation**: Simplifies template types using `using` declarations.  
**Real-World Scenario**: Simplify complex container types in a data processor.  
**Snippet**:  
```cpp
template<typename T> using Vec = std::vector<T>;
```
**Example**: [template_aliases.cpp](../examples/C++11/template_aliases.cpp)

## noexcept Specifier (C++11 Addition)
**Explanation**: Specifies whether a function can throw exceptions, aiding optimization.  
**Real-World Scenario**: Optimize performance in a critical system by guaranteeing no exceptions.  
**Snippet**:  
```cpp
void safeFunc() noexcept {}
```
**Example**: [noexcept_specifier.cpp](../examples/C++11/noexcept_specifier.cpp)

## Inline Namespaces (C++11 Addition)
**Explanation**: Automatically includes namespace contents in parent scope for versioning.  
**Real-World Scenario**: Version library functions without explicit scoping.  
**Snippet**:  
```cpp
inline namespace V1 { void func() {} }
```
**Example**: [inline_namespaces.cpp](../examples/C++11/inline_namespaces.cpp)

## std::unique_ptr (C++11 Addition)
**Explanation**: Smart pointer with single ownership semantics, replacing `std::auto_ptr`.  
**Real-World Scenario**: Manage a unique resource in a system without leaks.  
**Snippet**:  
```cpp
#include <memory> std::unique_ptr<int> ptr = std::make_unique<int>(5);
```
**Example**: [unique_ptr.cpp](../examples/C++11/unique_ptr.cpp)

## std::shared_ptr (C++11 Addition)
**Explanation**: Smart pointer with shared ownership, tracking reference counts.  
**Real-World Scenario**: Share a resource across multiple game objects.  
**Snippet**:  
```cpp
#include <memory> std::shared_ptr<int> ptr = std::make_shared<int>(5);
```
**Example**: [shared_ptr.cpp](../examples/C++11/shared_ptr.cpp)

## std::weak_ptr (C++11 Addition)
**Explanation**: Non-owning reference to a `shared_ptr` resource, prevents circular references.  
**Real-World Scenario**: Break circular references in a resource manager.  
**Snippet**:  
```cpp
#include <memory> std::weak_ptr<int> wptr;
```
**Example**: [weak_ptr.cpp](../examples/C++11/weak_ptr.cpp)

## static_assert (C++11 Addition)
**Explanation**: Compile-time assertions for type or condition checking.  
**Real-World Scenario**: Ensure template types meet requirements in a library.  
**Snippet**:  
```cpp
static_assert(sizeof(int) == 4, "Int size must be 4 bytes");
```
**Example**: [static_assert.cpp](../examples/C++11/static_assert.cpp)

## Type Traits (C++11 Addition)
**Explanation**: Provides compile-time type information (e.g., `is_integral`).  
**Real-World Scenario**: Check if a type is integral in a generic algorithm.  
**Snippet**:  
```cpp
#include <type_traits> std::is_integral<int>::value;
```
**Example**: [type_traits.cpp](../examples/C++11/type_traits.cpp)

## auto (C++11 Addition)
**Explanation**: Automatically deduces variable types, simplifying declarations.  
**Real-World Scenario**: Simplify iterator declarations in a loop.  
**Snippet**:  
```cpp
auto x = 10; // int
```
**Example**: [auto.cpp](../examples/C++11/auto.cpp)

## decltype (C++11 Addition)
**Explanation**: Deduce type of an expression at compile time.  
**Real-World Scenario**: Define return types in generic functions.  
**Snippet**:  
```cpp
decltype(10 + 20.0) x; // double
```
**Example**: [decltype.cpp](../examples/C++11/decltype.cpp)

## Range-based For Loop (C++11 Addition)
**Explanation**: Simplified loop syntax for iterating containers.  
**Real-World Scenario**: Print all items in a shopping cart.  
**Snippet**:  
```cpp
for (int x : std::vector<int>{1, 2, 3}) {}
```
**Example**: [range_based_for.cpp](../examples/C++11/range_based_for.cpp)

## nullptr (C++11 Addition)
**Explanation**: Type-safe null pointer constant, replacing `NULL`.  
**Real-World Scenario**: Initialize pointers safely in a system.  
**Snippet**:  
```cpp
int* ptr = nullptr;
```
**Example**: [nullptr.cpp](../examples/C++11/nullptr.cpp)

## Uniform Initialization (C++11 Addition)
**Explanation**: Consistent initialization syntax using braces.  
**Real-World Scenario**: Initialize complex objects in a game.  
**Snippet**:  
```cpp
struct Point { int x, y; }; Point p{1, 2};
```
**Example**: [uniform_initialization.cpp](../examples/C++11/uniform_initialization.cpp)

## Initializer Lists (C++11 Addition)
**Explanation**: Initialize containers or objects with brace-enclosed lists.  
**Real-World Scenario**: Initialize a vector of scores in a game.  
**Snippet**:  
```cpp
#include <initializer_list> std::vector<int> vec{1, 2, 3};
```
**Example**: [initializer_lists.cpp](../examples/C++11/initializer_lists.cpp)

## constexpr (C++11 Addition)
**Explanation**: Evaluates expressions at compile time for performance.  
**Real-World Scenario**: Compute constants for physics calculations.  
**Snippet**:  
```cpp
constexpr int square(int x) { return x * x; }
```
**Example**: [constexpr.cpp](../examples/C++11/constexpr.cpp)

## enum class (C++11 Addition)
**Explanation**: Scoped enumerations with stronger type safety.  
**Real-World Scenario**: Define game states without name conflicts.  
**Snippet**:  
```cpp
enum class State { Idle, Running };
```
**Example**: [enum_class.cpp](../examples/C++11/enum_class.cpp)

## Attributes (C++11 Addition)
**Explanation**: Add metadata to code (e.g., `[[noreturn]]`).  
**Real-World Scenario**: Mark a function that never returns in a system.  
**Snippet**:  
```cpp
[[noreturn]] void exit() {}
```
**Example**: [attributes.cpp](../examples/C++11/attributes.cpp)

## alignas and alignof (C++11 Addition)
**Explanation**: Control and query alignment of variables for optimization.  
**Real-World Scenario**: Optimize memory layout in a performance-critical app.  
**Snippet**:  
```cpp
alignas(16) int x; alignof(int);
```
**Example**: [alignment.cpp](../examples/C++11/alignment.cpp)