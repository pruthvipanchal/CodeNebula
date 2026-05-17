// CodeNebula - C++23 Example: std::variant Monadic Operations
// Compile: g++ -std=c++23 -Wall -Wextra -o example variant_monadic.cpp
// Note: Requires GCC 13+ / Clang 17+

#include <iostream>
#include <string>
#include <variant>

// C++23 adds std::visit improvements for variants:
// - Deducing this enables visit as a member-like pattern
// - Overload set pattern is more ergonomic
// Note: True monadic operations (and_then/transform) are not part of
// std::variant in C++23, but visit improvements make similar patterns easier.

// A simple result type using variant
using Result = std::variant<int, std::string>;

// Overload helper (now cleaner with C++23 CTAD improvements)
template <class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };

// Process variant with visitor
Result parse_value(const std::string& input) {
    try {
        return std::stoi(input);
    } catch (...) {
        return "Error: '" + input + "' is not a number";
    }
}

// Transform a Result: double the int, or prefix the error
Result transform_result(const Result& r) {
    return std::visit(overloaded{
        [](int v) -> Result { return v * 2; },
        [](const std::string& err) -> Result {
            return "Transformed: " + err;
        }
    }, r);
}

// Chain: only proceed if int, else keep error
Result and_then_positive(const Result& r) {
    return std::visit(overloaded{
        [](int v) -> Result {
            if (v > 0) return v;
            return std::string("Error: value is not positive");
        },
        [](const std::string& err) -> Result { return err; }
    }, r);
}

void print_result(const char* label, const Result& r) {
    std::cout << label << ": ";
    std::visit(overloaded{
        [](int v)                  { std::cout << "int(" << v << ")\n"; },
        [](const std::string& s)   { std::cout << "string(\"" << s << "\")\n"; }
    }, r);
}

int main() {
    std::cout << "=== std::variant monadic-style operations ===\n\n";

    // Parse and process
    auto r1 = parse_value("42");
    auto r2 = parse_value("hello");
    auto r3 = parse_value("-5");

    print_result("parse(\"42\")", r1);
    print_result("parse(\"hello\")", r2);
    print_result("parse(\"-5\")", r3);

    // Transform (map-like)
    std::cout << "\n--- transform (double int / prefix error) ---\n";
    print_result("transform(42)", transform_result(r1));
    print_result("transform(hello)", transform_result(r2));

    // and_then (flatmap-like)
    std::cout << "\n--- and_then (check positive) ---\n";
    print_result("positive(42)", and_then_positive(r1));
    print_result("positive(-5)", and_then_positive(r3));
    print_result("positive(hello)", and_then_positive(r2));

    // Chaining operations
    std::cout << "\n--- Chaining ---\n";
    auto chain = [](const std::string& input) {
        auto parsed = parse_value(input);
        auto positive = and_then_positive(parsed);
        return transform_result(positive);
    };

    print_result("chain(\"42\")", chain("42"));
    print_result("chain(\"-5\")", chain("-5"));
    print_result("chain(\"abc\")", chain("abc"));

    return 0;
}

// Expected output:
// === std::variant monadic-style operations ===
//
// parse("42"): int(42)
// parse("hello"): string("Error: 'hello' is not a number")
// parse("-5"): int(-5)
//
// --- transform (double int / prefix error) ---
// transform(42): int(84)
// transform(hello): string("Transformed: Error: 'hello' is not a number")
//
// --- and_then (check positive) ---
// positive(42): int(42)
// positive(-5): string("Error: value is not positive")
// positive(hello): string("Error: 'hello' is not a number")
//
// --- Chaining ---
// chain("42"): int(84)
// chain("-5"): string("Transformed: Error: value is not positive")
// chain("abc"): string("Transformed: Error: 'abc' is not a number")
