# C++14 Core Language Concepts

This document covers new or evolved C++14 core language concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../../examples/C++14/). Only additions or evolutions from C++98/C++03/C++11 are included.

## Generic Lambda Expressions

**Explanation**: Lambdas can use `auto` in parameter declarations, allowing polymorphic behavior without writing explicit template functions. The compiler generates a templated `operator()` behind the scenes, making lambdas truly generic.

**Real-World Scenario**: A data pipeline framework needs a single comparator that works with integers, floating-point numbers, and strings when sorting heterogeneous columns in a table engine.

**Snippet**:
```cpp
#include <algorithm>
#include <vector>
#include <string>

auto compare = [](const auto& a, const auto& b) { return a < b; };

std::vector<int> scores = {88, 42, 95, 67};
std::sort(scores.begin(), scores.end(), compare);

std::vector<std::string> names = {"Zara", "Alice", "Mona"};
std::sort(names.begin(), names.end(), compare);
```

**Example**: [generic_lambda_expressions.cpp](../../examples/C++14/generic_lambda_expressions.cpp)

## Lambda Capture Initializers

**Explanation**: Lambdas can initialize captured variables with arbitrary expressions, including move semantics. This feature, also known as generalized lambda capture, enables transferring ownership of move-only types into closures and creating new variables scoped to the lambda.

**Real-World Scenario**: An asynchronous task scheduler needs to transfer ownership of a database connection handle into a lambda that will execute on a worker thread, ensuring no accidental sharing of the resource.

**Snippet**:
```cpp
#include <memory>
#include <iostream>
#include <functional>

auto connection = std::make_unique<int>(42); // simulated DB handle

auto task = [conn = std::move(connection), attempt = 1]() mutable {
    std::cout << "Handle: " << *conn << ", attempt: " << attempt++ << "\n";
};

task(); // Handle: 42, attempt: 1
task(); // Handle: 42, attempt: 2
```

**Example**: [lambda_capture_initializers.cpp](../../examples/C++14/lambda_capture_initializers.cpp)

## Return Type Deduction for Functions

**Explanation**: Functions declared with `auto` as the return type have their return type deduced by the compiler from the `return` statement. This removes redundancy in function signatures, especially for templates and short utility functions where the return type mirrors the expression type.

**Real-World Scenario**: A math library provides a generic `clamp` function that works with any numeric type, and the return type is automatically deduced to match the input type without repeating a trailing return type.

**Snippet**:
```cpp
#include <iostream>

auto add(int a, int b) {
    return a + b; // return type deduced as int
}

template<typename T>
auto square(T value) {
    return value * value; // return type deduced from T
}

int main() {
    std::cout << add(3, 4) << "\n";         // 7
    std::cout << square(2.5) << "\n";       // 6.25
}
```

**Example**: [return_type_deduction.cpp](../../examples/C++14/return_type_deduction.cpp)

## decltype(auto)

**Explanation**: Deduces the type of a variable or return value using `decltype` semantics rather than `auto` semantics. While `auto` always strips references and top-level qualifiers, `decltype(auto)` preserves them, making it essential for perfect forwarding of return values in generic code.

**Real-World Scenario**: A caching proxy wraps access to a configuration store. Using `decltype(auto)`, the proxy returns a reference to the underlying value so callers can modify it in-place rather than receiving a copy.

**Snippet**:
```cpp
#include <iostream>
#include <vector>

std::vector<int> data = {10, 20, 30};

decltype(auto) getElement(size_t index) {
    return data[index]; // returns int&, not int
}

int main() {
    getElement(1) = 99;  // modifies data[1] in place
    std::cout << data[1] << "\n"; // 99
}
```

**Example**: [decltype_auto.cpp](../../examples/C++14/decltype_auto.cpp)

## Variable Templates

**Explanation**: Variables can now be templated, allowing a single definition to produce different constants or variables for different types. This is cleaner than wrapping constants inside class templates or function templates and is particularly useful for mathematical and physical constants.

**Real-World Scenario**: A 3D rendering engine defines mathematical constants like pi and epsilon as variable templates so that the same constant name works seamlessly with `float`, `double`, and `long double` pipelines without loss of precision.

**Snippet**:
```cpp
#include <iostream>
#include <iomanip>

template<typename T>
constexpr T pi = T(3.14159265358979323846L);

template<typename T>
constexpr T epsilon = T(1e-7L);

int main() {
    float  area_f = pi<float>  * 5.0f * 5.0f;
    double area_d = pi<double> * 5.0  * 5.0;
    std::cout << std::setprecision(15) << area_f << "\n" << area_d << "\n";
}
```

**Example**: [variable_templates.cpp](../../examples/C++14/variable_templates.cpp)

## Binary Literals

**Explanation**: Integer literals can be written in binary using the `0b` or `0B` prefix, making bit-level operations explicit and self-documenting. This is especially valuable in embedded, networking, and graphics code where individual bit patterns have specific meanings.

**Real-World Scenario**: An embedded firmware driver configures a sensor’s control register by setting specific bits for sampling rate, power mode, and interrupt enable, with binary literals making each bit’s purpose immediately visible.

**Snippet**:
```cpp
#include <iostream>
#include <bitset>

constexpr uint8_t POWER_ON       = 0b0000’0001;
constexpr uint8_t HIGH_PRECISION = 0b0000’0010;
constexpr uint8_t IRQ_ENABLE     = 0b0001’0000;

int main() {
    uint8_t config = POWER_ON | HIGH_PRECISION | IRQ_ENABLE; // 0b00010011
    std::cout << "Register: " << std::bitset<8>(config) << "\n";
}
```

**Example**: [binary_literals.cpp](../../examples/C++14/binary_literals.cpp)

## Digit Separators

**Explanation**: The single-quote character (`’`) can be inserted between digits in any numeric literal (integer, floating-point, binary, hexadecimal) to improve readability. The compiler ignores these separators entirely.

**Real-World Scenario**: A financial application defines monetary constants and account number masks where grouping digits by thousands or by nibbles makes the values immediately understandable during code review.

**Snippet**:
```cpp
#include <iostream>

int main() {
    long long budget       = 1’000’000’000;  // one billion
    double    exchange_rate = 1’234.567’89;
    int       color_rgba   = 0xFF’A5’00’FF;  // orange, fully opaque
    int       flags        = 0b1010’0011’0000’1111;

    std::cout << "Budget: " << budget << "\n";
    std::cout << "Color:  0x" << std::hex << color_rgba << "\n";
}
```

**Example**: [digit_separators.cpp](../../examples/C++14/digit_separators.cpp)

## Relaxed constexpr Restrictions

**Explanation**: C++14 significantly relaxes the rules for `constexpr` functions compared to C++11. Functions may now contain local variables, loops, multiple `return` statements, `if`/`switch` branches, and mutation of local state, enabling real algorithms to execute at compile time.

**Real-World Scenario**: A compile-time lookup table generator computes CRC-32 values for all 256 byte values using loops and bitwise operations, eliminating the need for an external code-generation step.

**Snippet**:
```cpp
#include <iostream>
#include <array>

constexpr int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i)
        result *= i;
    return result;
}

constexpr auto build_table() {
    std::array<int, 10> table{};
    for (int i = 0; i < 10; ++i)
        table[i] = factorial(i);
    return table;
}

int main() {
    constexpr auto table = build_table();
    for (auto v : table) std::cout << v << " ";
    // 1 1 2 6 24 120 720 5040 40320 362880
}
```

**Example**: [relaxed_constexpr.cpp](../../examples/C++14/relaxed_constexpr.cpp)

## [[deprecated]] Attribute

**Explanation**: The `[[deprecated]]` attribute marks declarations (functions, classes, variables, typedefs, enumerators) as deprecated, causing the compiler to emit a warning whenever they are used. An optional string message can explain the replacement.

**Real-World Scenario**: A networking library is migrating from a synchronous `connect()` API to an asynchronous `async_connect()`. Marking the old function as deprecated nudges users toward the new API while maintaining backward compatibility during the transition period.

**Snippet**:
```cpp
#include <iostream>

[[deprecated("Use async_connect() instead")]]
bool connect(const char* host, int port) {
    return true;
}

bool async_connect(const char* host, int port) {
    return true;
}

int main() {
    // connect("example.com", 80);  // compiler warning: deprecated
    async_connect("example.com", 80); // preferred
}
```

**Example**: [deprecated_attribute.cpp](../../examples/C++14/deprecated_attribute.cpp)

## Aggregate Member Initialization Relaxation

**Explanation**: C++14 relaxes aggregate initialization rules to allow classes with default member initializers (in-class brace-or-equal initializers) to still qualify as aggregates. In C++11, any default member initializer disqualified a class from aggregate initialization. C++14 removes this restriction, so you can combine both features naturally.

**Real-World Scenario**: A game engine defines a `RenderSettings` struct with sensible defaults for resolution, anti-aliasing, and VSync. Users can aggregate-initialize only the fields they want to override while relying on defaults for the rest.

**Snippet**:
```cpp
#include <iostream>

struct RenderSettings {
    int  width  = 1920;
    int  height = 1080;
    bool vsync  = true;
    int  msaa   = 4;
};

int main() {
    RenderSettings low_quality{1280, 720, false, 1};
    RenderSettings custom{3840, 2160}; // vsync=true, msaa=4 from defaults

    std::cout << custom.width << "x" << custom.height
              << " VSync:" << custom.vsync << " MSAA:" << custom.msaa << "\n";
    // 3840x2160 VSync:1 MSAA:4
}
```

**Example**: [aggregate_member_init.cpp](../../examples/C++14/aggregate_member_init.cpp)