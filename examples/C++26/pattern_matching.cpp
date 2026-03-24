// CodeNebula - C++26 Example: Pattern Matching (inspect)
// Compile: g++ -std=c++26 -Wall -Wextra -o example pattern_matching.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// C++26 proposes pattern matching via the 'inspect' expression.
// It generalizes switch to work with any type, supporting structured
// bindings, variant matching, type matching, and guards.

#include <iostream>
#include <variant>
#include <string>
#include <tuple>

// --- C++26 Pattern Matching Syntax (proposed) ---
//
// // Basic value matching (like enhanced switch)
// int x = 2;
// inspect (x) {
//     1 => { std::cout << "one"; }
//     2 => { std::cout << "two"; }
//     _ => { std::cout << "other"; }  // wildcard
// };
//
// // Variant matching
// std::variant<int, double, std::string> v = "hello";
// inspect (v) {
//     <int> i    => { std::cout << "int: " << i; }
//     <double> d => { std::cout << "double: " << d; }
//     <std::string> s => { std::cout << "string: " << s; }
// };
//
// // Structured pattern matching with guards
// auto point = std::tuple{3, 4};
// inspect (point) {
//     [0, 0]          => { std::cout << "origin"; }
//     [x, 0]          => { std::cout << "x-axis"; }
//     [0, y]          => { std::cout << "y-axis"; }
//     [x, y] if (x==y) => { std::cout << "diagonal"; }
//     [x, y]          => { std::cout << "(" << x << "," << y << ")"; }
// };

// --- Simulation using C++20 features ---

using Value = std::variant<int, double, std::string>;

std::string inspect_value(const Value& v) {
    return std::visit([](const auto& val) -> std::string {
        using T = std::decay_t<decltype(val)>;
        if constexpr (std::is_same_v<T, int>)
            return "int: " + std::to_string(val);
        else if constexpr (std::is_same_v<T, double>)
            return "double: " + std::to_string(val);
        else
            return "string: " + val;
    }, v);
}

std::string inspect_point(int x, int y) {
    if (x == 0 && y == 0) return "origin";
    if (y == 0) return "on x-axis at x=" + std::to_string(x);
    if (x == 0) return "on y-axis at y=" + std::to_string(y);
    if (x == y) return "on diagonal at " + std::to_string(x);
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

int main() {
    std::cout << "=== C++26 Pattern Matching (Simulated) ===" << std::endl;

    // Variant matching
    std::cout << "Variant matching:" << std::endl;
    std::cout << "  " << inspect_value(42) << std::endl;
    std::cout << "  " << inspect_value(3.14) << std::endl;
    std::cout << "  " << inspect_value(std::string("hello")) << std::endl;

    // Structured pattern matching with guards
    std::cout << "Point matching:" << std::endl;
    std::cout << "  (0,0): " << inspect_point(0, 0) << std::endl;
    std::cout << "  (5,0): " << inspect_point(5, 0) << std::endl;
    std::cout << "  (0,3): " << inspect_point(0, 3) << std::endl;
    std::cout << "  (4,4): " << inspect_point(4, 4) << std::endl;
    std::cout << "  (3,7): " << inspect_point(3, 7) << std::endl;

    std::cout << "Pattern matching replaces visitor boilerplate with inspect." << std::endl;
    return 0;
}

// Expected output:
// === C++26 Pattern Matching (Simulated) ===
// Variant matching:
//   int: 42
//   double: 3.140000
//   string: hello
// Point matching:
//   (0,0): origin
//   (5,0): on x-axis at x=5
//   (0,3): on y-axis at y=3
//   (4,4): on diagonal at 4
//   (3,7): (3, 7)
// Pattern matching replaces visitor boilerplate with inspect.
