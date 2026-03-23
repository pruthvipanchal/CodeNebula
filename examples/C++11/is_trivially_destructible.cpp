// CodeNebula - C++11 Example: is_trivially_destructible
// Compile: g++ -std=c++11 -Wall -Wextra -o example is_trivially_destructible.cpp

// Demonstrates std::is_trivially_destructible to check if a type has
// a trivial (compiler-generated, do-nothing) destructor.

#include <iostream>
#include <type_traits>
#include <string>
#include <vector>

struct Trivial { int x; double y; };

struct WithVirtualDtor {
    virtual ~WithVirtualDtor() {}
};

struct WithCustomDtor {
    ~WithCustomDtor() { /* cleanup */ }
};

struct WithStringMember {
    std::string name;  // string has non-trivial destructor
};

int main() {
    std::cout << "=== std::is_trivially_destructible ===" << std::endl;

    std::cout << "int:              " << std::is_trivially_destructible<int>::value << std::endl;
    std::cout << "double:           " << std::is_trivially_destructible<double>::value << std::endl;
    std::cout << "Trivial:          " << std::is_trivially_destructible<Trivial>::value << std::endl;
    std::cout << "WithVirtualDtor:  " << std::is_trivially_destructible<WithVirtualDtor>::value << std::endl;
    std::cout << "WithCustomDtor:   " << std::is_trivially_destructible<WithCustomDtor>::value << std::endl;
    std::cout << "WithStringMember: " << std::is_trivially_destructible<WithStringMember>::value << std::endl;
    std::cout << "std::string:      " << std::is_trivially_destructible<std::string>::value << std::endl;
    std::cout << "std::vector<int>: " << std::is_trivially_destructible<std::vector<int>>::value << std::endl;

    static_assert(std::is_trivially_destructible<int>::value, "int is trivially destructible");
    static_assert(std::is_trivially_destructible<Trivial>::value, "POD is trivially destructible");
    static_assert(!std::is_trivially_destructible<std::string>::value, "string is not");

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::is_trivially_destructible ===
// int:              1
// double:           1
// Trivial:          1
// WithVirtualDtor:  0
// WithCustomDtor:   0
// WithStringMember: 0
// std::string:      0
// std::vector<int>: 0
//
// All checks passed!
