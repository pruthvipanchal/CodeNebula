// CodeNebula - C++17 Example: std::variant
// Compile: g++ -std=c++17 -Wall -Wextra -o example variant.cpp

// Demonstrates std::variant, a type-safe tagged union. Unlike C unions, variant
// tracks the active type, supports non-trivial types (strings, vectors), and
// provides visitor-based access via std::visit.

#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <cmath>

// ------------------------------------------------------------------
// Overloaded helper for visitor pattern
// ------------------------------------------------------------------
template <typename... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
template <typename... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

// ------------------------------------------------------------------
// Type alias for a "JSON-like" value
// ------------------------------------------------------------------
using JsonValue = std::variant<std::monostate, bool, int, double, std::string>;

std::string type_name(const JsonValue& jv) {
    return std::visit(overloaded{
        [](std::monostate)      { return std::string("null"); },
        [](bool)                { return std::string("bool"); },
        [](int)                 { return std::string("int"); },
        [](double)              { return std::string("double"); },
        [](const std::string&)  { return std::string("string"); }
    }, jv);
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic construction and access
    // ------------------------------------------------------------------
    std::cout << "=== construction ===" << std::endl;
    std::variant<int, double, std::string> v1 = 42;
    std::variant<int, double, std::string> v2 = 3.14;
    std::variant<int, double, std::string> v3 = std::string("hello");

    std::cout << "  v1 (int):    " << std::get<int>(v1) << std::endl;
    std::cout << "  v2 (double): " << std::get<double>(v2) << std::endl;
    std::cout << "  v3 (string): " << std::get<std::string>(v3) << std::endl;

    // ------------------------------------------------------------------
    // 2. index() and holds_alternative
    // ------------------------------------------------------------------
    std::cout << "\n=== type queries ===" << std::endl;
    std::cout << "  v1.index(): " << v1.index() << std::endl;
    std::cout << "  v2 holds double: " << std::boolalpha
              << std::holds_alternative<double>(v2) << std::endl;
    std::cout << "  v3 holds int: " << std::holds_alternative<int>(v3) << std::endl;

    // ------------------------------------------------------------------
    // 3. get_if: safe access via pointer (returns nullptr if wrong type)
    // ------------------------------------------------------------------
    std::cout << "\n=== get_if (safe access) ===" << std::endl;
    if (auto* p = std::get_if<int>(&v1)) {
        std::cout << "  v1 is int: " << *p << std::endl;
    }
    if (auto* p = std::get_if<double>(&v1)) {
        std::cout << "  v1 is double: " << *p << std::endl;  // not reached
    } else {
        std::cout << "  v1 is NOT double" << std::endl;
    }

    // ------------------------------------------------------------------
    // 4. Reassignment changes the active type
    // ------------------------------------------------------------------
    std::cout << "\n=== reassignment ===" << std::endl;
    v1 = std::string("now a string");
    std::cout << "  v1 is now: " << std::get<std::string>(v1) << std::endl;
    std::cout << "  v1.index(): " << v1.index() << std::endl;

    // ------------------------------------------------------------------
    // 5. std::visit with overloaded visitor
    // ------------------------------------------------------------------
    std::cout << "\n=== std::visit ===" << std::endl;
    std::variant<int, double, std::string> values[] = {10, 2.5, std::string("hi")};
    for (const auto& val : values) {
        std::visit(overloaded{
            [](int i)               { std::cout << "  int: " << i << std::endl; },
            [](double d)            { std::cout << "  double: " << d << std::endl; },
            [](const std::string& s){ std::cout << "  string: " << s << std::endl; }
        }, val);
    }

    // ------------------------------------------------------------------
    // 6. std::monostate for default-constructible variant
    // ------------------------------------------------------------------
    std::cout << "\n=== monostate (null-like) ===" << std::endl;
    JsonValue jv;  // default: monostate (first type)
    std::cout << "  default type: " << type_name(jv) << std::endl;
    jv = 42;
    std::cout << "  after = 42:   " << type_name(jv) << std::endl;
    jv = std::string("text");
    std::cout << "  after = text:  " << type_name(jv) << std::endl;

    // ------------------------------------------------------------------
    // 7. emplace: construct in-place
    // ------------------------------------------------------------------
    std::cout << "\n=== emplace ===" << std::endl;
    std::variant<std::string, std::vector<int>> sv;
    sv.emplace<std::string>(5, 'X');  // constructs string "XXXXX"
    std::cout << "  string: " << std::get<std::string>(sv) << std::endl;

    return 0;
}

/*
Expected output:

=== construction ===
  v1 (int):    42
  v2 (double): 3.14
  v3 (string): hello

=== type queries ===
  v1.index(): 0
  v2 holds double: true
  v3 holds int: false

=== get_if (safe access) ===
  v1 is int: 42
  v1 is NOT double

=== reassignment ===
  v1 is now: now a string
  v1.index(): 2

=== std::visit ===
  int: 10
  double: 2.5
  string: hi

=== monostate (null-like) ===
  default type: null
  after = 42:   int
  after = text:  string

=== emplace ===
  string: XXXXX
*/
