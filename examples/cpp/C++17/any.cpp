// CodeNebula - C++17 Example: std::any
// Compile: g++ -std=c++17 -Wall -Wextra -o example any.cpp

// Demonstrates std::any, a type-erased container that can hold a value of any
// copy-constructible type. Unlike std::variant, the set of types is not fixed
// at compile time. Use std::any_cast to retrieve the stored value.

#include <iostream>
#include <any>
#include <string>
#include <vector>
#include <typeinfo>

// ------------------------------------------------------------------
// Helper: print the contents of an any object
// ------------------------------------------------------------------
void describe(const std::any& a) {
    if (!a.has_value()) {
        std::cout << "  (empty)" << std::endl;
        return;
    }
    std::cout << "  type: " << a.type().name();

    // Try common types
    if (a.type() == typeid(int)) {
        std::cout << ", value: " << std::any_cast<int>(a);
    } else if (a.type() == typeid(double)) {
        std::cout << ", value: " << std::any_cast<double>(a);
    } else if (a.type() == typeid(std::string)) {
        std::cout << ", value: " << std::any_cast<std::string>(a);
    } else if (a.type() == typeid(bool)) {
        std::cout << ", value: " << std::boolalpha << std::any_cast<bool>(a);
    } else {
        std::cout << ", value: (unknown type)";
    }
    std::cout << std::endl;
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic construction
    // ------------------------------------------------------------------
    std::cout << "=== construction ===" << std::endl;
    std::any a1;                         // empty
    std::any a2 = 42;                    // int
    std::any a3 = 3.14;                  // double
    std::any a4 = std::string("hello");  // std::string

    describe(a1);
    describe(a2);
    describe(a3);
    describe(a4);

    // ------------------------------------------------------------------
    // 2. std::any_cast: safe value extraction
    // ------------------------------------------------------------------
    std::cout << "\n=== any_cast ===" << std::endl;
    int val = std::any_cast<int>(a2);
    std::cout << "  any_cast<int>(a2) = " << val << std::endl;

    // Bad cast throws std::bad_any_cast
    try {
        double bad = std::any_cast<double>(a2);  // a2 holds int, not double
        std::cout << "  (unexpected) " << bad << std::endl;
    } catch (const std::bad_any_cast& e) {
        std::cout << "  bad_any_cast: " << e.what() << std::endl;
    }

    // ------------------------------------------------------------------
    // 3. any_cast with pointer (returns nullptr on mismatch, no throw)
    // ------------------------------------------------------------------
    std::cout << "\n=== any_cast pointer ===" << std::endl;
    if (auto* p = std::any_cast<int>(&a2)) {
        std::cout << "  a2 is int: " << *p << std::endl;
    }
    if (auto* p = std::any_cast<double>(&a2)) {
        std::cout << "  a2 is double: " << *p << std::endl;
    } else {
        std::cout << "  a2 is NOT double (pointer is null)" << std::endl;
    }

    // ------------------------------------------------------------------
    // 4. Reassignment to a different type
    // ------------------------------------------------------------------
    std::cout << "\n=== type change ===" << std::endl;
    std::any flexible = 100;
    std::cout << "  before: "; describe(flexible);
    flexible = std::string("now a string");
    std::cout << "  after:  "; describe(flexible);
    flexible = true;
    std::cout << "  again:  "; describe(flexible);

    // ------------------------------------------------------------------
    // 5. reset and has_value
    // ------------------------------------------------------------------
    std::cout << "\n=== reset ===" << std::endl;
    std::any obj = 42;
    std::cout << "  has_value: " << std::boolalpha << obj.has_value() << std::endl;
    obj.reset();
    std::cout << "  after reset: " << obj.has_value() << std::endl;

    // ------------------------------------------------------------------
    // 6. emplace: construct in-place
    // ------------------------------------------------------------------
    std::cout << "\n=== emplace ===" << std::endl;
    std::any em;
    em.emplace<std::string>(5, '!');  // constructs string "!!!!!"
    std::cout << "  emplace<string>(5, '!'): "
              << std::any_cast<std::string>(em) << std::endl;

    // ------------------------------------------------------------------
    // 7. Heterogeneous container
    // ------------------------------------------------------------------
    std::cout << "\n=== heterogeneous vector ===" << std::endl;
    std::vector<std::any> items = {42, 3.14, std::string("mixed"), true};
    for (const auto& item : items) {
        describe(item);
    }

    return 0;
}

/*
Expected output:

=== construction ===
  (empty)
  type: i, value: 42
  type: d, value: 3.14
  type: ..., value: hello

=== any_cast ===
  any_cast<int>(a2) = 42
  bad_any_cast: bad any_cast

=== any_cast pointer ===
  a2 is int: 42
  a2 is NOT double (pointer is null)

=== type change ===
  before:   type: i, value: 100
  after:    type: ..., value: now a string
  again:    type: b, value: true

=== reset ===
  has_value: true
  after reset: false

=== emplace ===
  emplace<string>(5, '!'): !!!!!

=== heterogeneous vector ===
  type: i, value: 42
  type: d, value: 3.14
  type: ..., value: mixed
  type: b, value: true
*/
