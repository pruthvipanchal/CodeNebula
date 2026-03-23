// CodeNebula - C++11 Example: is_trivially_constructible
// Compile: g++ -std=c++11 -Wall -Wextra -o example is_trivially_constructible.cpp

// Demonstrates std::is_trivially_constructible and related traits.
// A trivial constructor does nothing (compiler-generated default).

#include <iostream>
#include <type_traits>
#include <string>

struct Trivial { int x; double y; };

struct NonTrivial {
    NonTrivial() : x(42) {}  // user-defined constructor
    int x;
};

struct WithDefault {
    WithDefault() = default;  // explicitly defaulted is still trivial
    int x;
};

struct WithString {
    std::string name;  // string has non-trivial constructor
};

int main() {
    std::cout << "=== std::is_trivially_constructible ===" << std::endl;

    // Default constructible (no args)
    std::cout << "Trivial:        "
              << std::is_trivially_constructible<Trivial>::value << std::endl;
    std::cout << "NonTrivial:     "
              << std::is_trivially_constructible<NonTrivial>::value << std::endl;
    std::cout << "WithDefault:    "
              << std::is_trivially_constructible<WithDefault>::value << std::endl;
    std::cout << "WithString:     "
              << std::is_trivially_constructible<WithString>::value << std::endl;
    std::cout << "int:            "
              << std::is_trivially_constructible<int>::value << std::endl;

    // Also check trivially default constructible
    std::cout << "\n--- is_trivially_default_constructible ---" << std::endl;
    std::cout << "Trivial:        "
              << std::is_trivially_default_constructible<Trivial>::value << std::endl;
    std::cout << "int:            "
              << std::is_trivially_default_constructible<int>::value << std::endl;
    std::cout << "std::string:    "
              << std::is_trivially_default_constructible<std::string>::value << std::endl;

    static_assert(std::is_trivially_constructible<int>::value, "int is trivial");
    static_assert(!std::is_trivially_constructible<NonTrivial>::value, "custom ctor");

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::is_trivially_constructible ===
// Trivial:        1
// NonTrivial:     0
// WithDefault:    1
// WithString:     0
// int:            1
//
// --- is_trivially_default_constructible ---
// Trivial:        1
// int:            1
// std::string:    0
//
// All checks passed!
