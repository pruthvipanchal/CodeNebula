# C++17 Core Language Concepts

This document covers new or evolved C++17 core language concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../../examples/C++17/). Only additions or evolutions from C++98/C++03/C++11/C++14 are included.

## Structured Bindings

**Explanation**: Decomposes aggregates (e.g., tuples, structs, arrays) into individually named variables, making it far easier to work with multi-value returns and key-value pairs without verbose `.first`/`.second` or `std::get<>` calls.

**Real-World Scenario**: Extract position and velocity from a tuple in a physics simulation.

**Snippet**:
```cpp
#include <tuple>
#include <map>

auto [x, y] = std::make_tuple(3.14, 2.71);

std::map<std::string, int> scores = {{"Alice", 95}, {"Bob", 87}};
for (const auto& [name, score] : scores) {
    std::cout << name << ": " << score << "\n";
}
```

**Example**: [structured_bindings.cpp](../../examples/C++17/structured_bindings.cpp)

## if constexpr

**Explanation**: Enables compile-time conditional evaluation inside templates. The discarded branch is not instantiated, eliminating the need for SFINAE or tag-dispatch tricks in many generic programming scenarios.

**Real-World Scenario**: Select different serialization logic paths in a generic function depending on whether the type is arithmetic or a string.

**Snippet**:
```cpp
#include <type_traits>
#include <string>

template<typename T>
std::string serialize(const T& value) {
    if constexpr (std::is_arithmetic_v<T>) {
        return std::to_string(value);
    } else {
        return std::string(value);
    }
}
```

**Example**: [if_constexpr.cpp](../../examples/C++17/if_constexpr.cpp)

## Init-statements for if and switch

**Explanation**: Allows declaring and initializing a variable directly within an `if` or `switch` statement, confining it to the narrowest possible scope and reducing accidental misuse of temporary variables.

**Real-World Scenario**: Acquire a lock and check a condition atomically in a thread-safe cache lookup.

**Snippet**:
```cpp
#include <map>
#include <string>

std::map<int, std::string> users = {{1, "Alice"}, {2, "Bob"}};

if (auto it = users.find(1); it != users.end()) {
    std::cout << "Found: " << it->second << "\n";
}
// 'it' is not accessible here -- scope is limited to the if block
```

**Example**: [if_switch_initializers.cpp](../../examples/C++17/if_switch_initializers.cpp)

## Inline Variables

**Explanation**: Variables declared `inline` can be defined in header files without causing multiple-definition linker errors, following the same rules as inline functions. This is essential for header-only libraries.

**Real-World Scenario**: Define a global configuration constant in a shared header used across multiple translation units in a library.

**Snippet**:
```cpp
// config.h
inline constexpr int MAX_CONNECTIONS = 256;
inline std::string APP_NAME = "MyApp";
```

**Example**: [inline_variables.cpp](../../examples/C++17/inline_variables.cpp)

## Fold Expressions

**Explanation**: Provides a concise syntax to apply a binary operator across all elements of a parameter pack, eliminating recursive template instantiations for common variadic patterns like summing, concatenation, or logical checks.

**Real-World Scenario**: Build a variadic logging function that prints all arguments separated by spaces.

**Snippet**:
```cpp
#include <iostream>

template<typename... Args>
void log(Args&&... args) {
    (std::cout << ... << args) << "\n";  // Binary left fold
}

template<typename... Args>
auto sum(Args... args) {
    return (args + ...);  // Unary right fold
}
```

**Example**: [fold_expressions.cpp](../../examples/C++17/fold_expressions.cpp)

## Template Argument Deduction for Class Templates

**Explanation**: The compiler can automatically deduce template arguments for class templates from constructor arguments, removing the need to explicitly specify template parameters in many common cases.

**Real-World Scenario**: Simplify container and smart pointer initialization without spelling out the template type.

**Snippet**:
```cpp
#include <vector>
#include <mutex>

std::vector vec = {1, 2, 3};           // deduced as std::vector<int>
std::pair  p   = {42, "hello"};        // deduced as std::pair<int, const char*>
std::lock_guard lk(myMutex);           // deduced from mutex type
```

**Example**: [template_argument_deduction.cpp](../../examples/C++17/template_argument_deduction.cpp)

## Class Template Argument Deduction (CTAD)

**Explanation**: CTAD extends template argument deduction for class templates with user-defined deduction guides, allowing library authors to control how template parameters are inferred from constructor calls. This is the mechanism that makes deduction guides possible.

**Real-World Scenario**: Write a custom wrapper class that automatically deduces its template parameter from the constructor argument, simplifying client code in a plugin system.

**Snippet**:
```cpp
template<typename T>
struct Wrapper {
    T value;
    Wrapper(T v) : value(v) {}
};

// Deduction guide: Wrapper constructed from const char* deduces as Wrapper<std::string>
Wrapper(const char*) -> Wrapper<std::string>;

Wrapper w1(42);        // Wrapper<int>
Wrapper w2("hello");   // Wrapper<std::string> via deduction guide
```

**Example**: [ctad.cpp](../../examples/C++17/ctad.cpp)

## Nested Namespace Definitions

**Explanation**: Allows declaring deeply nested namespaces in a single compact statement using `::` separators, eliminating verbose multi-level braces and reducing indentation clutter in large codebases.

**Real-World Scenario**: Organize a large library's internal modules without multiple nested braces.

**Snippet**:
```cpp
// Before C++17
namespace Company { namespace Project { namespace Module {
    void func() {}
}}}

// C++17
namespace Company::Project::Module {
    void func() {}
}
```

**Example**: [nested_namespaces.cpp](../../examples/C++17/nested_namespaces.cpp)

## __has_include Preprocessor Directive

**Explanation**: A preprocessor test that checks whether a header file is available before including it, enabling portable code that gracefully adapts to different platforms and optional dependencies.

**Real-World Scenario**: Conditionally use `<optional>` if available, falling back to a polyfill on older compilers.

**Snippet**:
```cpp
#if __has_include(<optional>)
    #include <optional>
    #define HAS_OPTIONAL 1
#elif __has_include(<experimental/optional>)
    #include <experimental/optional>
    #define HAS_OPTIONAL 1
#else
    #define HAS_OPTIONAL 0
#endif
```

**Example**: [has_include.cpp](../../examples/C++17/has_include.cpp)

## [[nodiscard]] Attribute

**Explanation**: Warns the caller if a function's return value is discarded. This catches a common class of bugs where important results (error codes, allocated resources, computed values) are silently ignored.

**Real-World Scenario**: Prevent callers from ignoring the error code returned by a database connection function.

**Snippet**:
```cpp
[[nodiscard]] bool connect(const std::string& host) {
    // returns false on failure
    return true;
}

// connect("db.example.com");  // WARNING: discarding return value
bool ok = connect("db.example.com");  // Correct usage
```

**Example**: [nodiscard.cpp](../../examples/C++17/nodiscard.cpp)

## [[maybe_unused]] Attribute

**Explanation**: Suppresses compiler warnings about unused variables, parameters, or functions. This is invaluable for platform-specific code, debug-only variables, and callback signatures where not every parameter is always used.

**Real-World Scenario**: Silence warnings for a debug-only timing variable in a release build.

**Snippet**:
```cpp
void callback([[maybe_unused]] int errorCode, const std::string& message) {
    // errorCode used only in debug builds
    #ifndef NDEBUG
    std::cerr << "Error " << errorCode << ": " << message << "\n";
    #else
    std::cerr << message << "\n";
    #endif
}

[[maybe_unused]] static void helperDebug() {
    // Only called in debug builds
}
```

**Example**: [maybe_unused.cpp](../../examples/C++17/maybe_unused.cpp)

## [[fallthrough]] Attribute

**Explanation**: Explicitly indicates that falling through from one `case` label to the next in a `switch` statement is intentional, silencing compiler warnings and documenting the programmer's intent.

**Real-World Scenario**: Implement a command parser where several commands share common setup logic before diverging.

**Snippet**:
```cpp
enum class LogLevel { Fatal, Error, Warning, Info };

void handleLog(LogLevel level, const std::string& msg) {
    switch (level) {
        case LogLevel::Fatal:
            notifyAdmin(msg);
            [[fallthrough]];
        case LogLevel::Error:
            writeToErrorLog(msg);
            [[fallthrough]];
        case LogLevel::Warning:
            writeToWarningLog(msg);
            break;
        case LogLevel::Info:
            writeToInfoLog(msg);
            break;
    }
}
```

**Example**: [fallthrough.cpp](../../examples/C++17/fallthrough.cpp)

## Guaranteed Copy Elision

**Explanation**: The compiler is now required (not merely permitted) to elide copies and moves when a prvalue is used to initialize an object of the same type. This means types that are neither copyable nor movable can be returned from functions by value.

**Real-World Scenario**: Return a non-movable RAII resource handle from a factory function without any performance penalty.

**Snippet**:
```cpp
struct DatabaseConnection {
    DatabaseConnection(const std::string& connStr) { /* open */ }
    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection(DatabaseConnection&&) = delete;
};

// Valid in C++17: guaranteed copy elision means no copy/move is needed
DatabaseConnection connect(const std::string& host) {
    return DatabaseConnection(host);
}

auto conn = connect("db.example.com");
```

**Example**: [copy_elision.cpp](../../examples/C++17/copy_elision.cpp)

## std::launder

**Explanation**: Provides a pointer laundering facility that obtains a pointer to an object created in storage where a different object of the same type previously resided. It is needed when placement new is used to create an object with a different value for a const or reference member in the same storage.

**Real-World Scenario**: Implement a memory pool or arena allocator that reuses storage for objects with const members without invoking undefined behavior.

**Snippet**:
```cpp
#include <new>

struct Config {
    const int id;
    double value;
};

alignas(Config) unsigned char buffer[sizeof(Config)];
auto* p1 = new (buffer) Config{1, 3.14};

// Destroy and recreate in the same storage with a different const member
p1->~Config();
auto* p2 = new (buffer) Config{2, 2.71};

// Must use std::launder because 'id' is const and the object changed
auto* safe = std::launder(reinterpret_cast<Config*>(buffer));
assert(safe->id == 2);
```

**Example**: [launder.cpp](../../examples/C++17/launder.cpp)

## constexpr Lambda Expressions

**Explanation**: Lambdas are implicitly `constexpr` when possible, and can be explicitly marked `constexpr`. This allows lambda expressions to be used in compile-time computations, `static_assert`, and template arguments.

**Real-World Scenario**: Compute compile-time lookup tables or hash values using lambda expressions in a header-only math library.

**Snippet**:
```cpp
constexpr auto square = [](int x) constexpr { return x * x; };
static_assert(square(5) == 25);

constexpr auto factorial = [](int n) constexpr {
    int result = 1;
    for (int i = 2; i <= n; ++i) result *= i;
    return result;
};
static_assert(factorial(6) == 720);
```

**Example**: [constexpr_lambdas.cpp](../../examples/C++17/constexpr_lambdas.cpp)

## Hexadecimal Floating-Point Literals

**Explanation**: Floating-point numbers can be expressed in hexadecimal notation using the `0x` prefix and a `p` exponent (base 2). This allows exact representation of floating-point values without rounding, which is critical in numerical computing and cross-platform reproducibility.

**Real-World Scenario**: Specify precise floating-point constants in a scientific simulation or graphics shader to guarantee bit-exact results across compilers.

**Snippet**:
```cpp
double pi_approx = 0x1.921fb54442d18p+1;  // 3.14159265358979...
double one_tenth = 0x1.999999999999ap-4;   // 0.1 (exact representation)
float  half      = 0x1.0p-1f;             // 0.5
```

**Example**: [hex_float_literals.cpp](../../examples/C++17/hex_float_literals.cpp)

## Using-declaration for Parameter Packs

**Explanation**: Extends `using` declarations to work with parameter packs, allowing a class to inherit or expose members from multiple base classes in a single statement. This is particularly powerful when building variadic overload sets from lambda-based visitors.

**Real-World Scenario**: Construct an overloaded visitor for `std::variant` by combining multiple lambdas into one callable object.

**Snippet**:
```cpp
#include <variant>

template<class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;  // Using-declaration with parameter pack
};

// Deduction guide
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

std::variant<int, double, std::string> v = "hello";
std::visit(overloaded{
    [](int i)              { std::cout << "int: " << i << "\n"; },
    [](double d)           { std::cout << "double: " << d << "\n"; },
    [](const std::string& s) { std::cout << "string: " << s << "\n"; }
}, v);
```

**Example**: [using_parameter_packs.cpp](../../examples/C++17/using_parameter_packs.cpp)

## Aggregate Initialization with Base Classes

**Explanation**: Aggregates can now have public base classes. Aggregate initialization uses braces to initialize the base class sub-objects first, followed by the derived class members. This removes the need for boilerplate constructors in simple derived types.

**Real-World Scenario**: Create a lightweight derived configuration struct that extends a base settings struct without writing any constructors.

**Snippet**:
```cpp
struct Point {
    double x, y;
};

struct LabeledPoint : Point {
    std::string label;
};

// Aggregate initialization including the base class
LabeledPoint lp = {{1.0, 2.0}, "Origin"};
std::cout << lp.label << " at (" << lp.x << ", " << lp.y << ")\n";
```

**Example**: [aggregate_init_base.cpp](../../examples/C++17/aggregate_init_base.cpp)

## Non-type Template Parameters auto

**Explanation**: Non-type template parameters can be declared with `auto`, letting the compiler deduce their type. This makes templates more flexible and reduces duplication when the exact non-type parameter type is not important to the template logic.

**Real-World Scenario**: Write a generic compile-time constant wrapper that works with any integral or pointer type without explicit type specification.

**Snippet**:
```cpp
template<auto Value>
struct Constant {
    static constexpr auto value = Value;
};

Constant<42>    intConst;    // Value deduced as int
Constant<'A'>   charConst;   // Value deduced as char
Constant<true>  boolConst;   // Value deduced as bool

static_assert(Constant<42>::value == 42);
static_assert(Constant<'A'>::value == 65);
```

**Example**: [nttp_auto.cpp](../../examples/C++17/nttp_auto.cpp)
