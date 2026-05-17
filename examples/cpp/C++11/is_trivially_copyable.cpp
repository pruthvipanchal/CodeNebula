// CodeNebula - C++11 Example: is_trivially_copyable
// Compile: g++ -std=c++11 -Wall -Wextra -o example is_trivially_copyable.cpp

// Demonstrates std::is_trivially_copyable to check if a type can be
// safely copied with memcpy. Types with virtual functions, non-trivial
// copy constructors, or destructors are NOT trivially copyable.

#include <iostream>
#include <type_traits>
#include <string>

struct Simple { int x; double y; };

struct WithVirtual {
    virtual void foo() {}
};

struct WithString {
    std::string name;  // std::string is not trivially copyable
};

struct WithCopyCtor {
    WithCopyCtor() = default;
    WithCopyCtor(const WithCopyCtor&) { /* custom logic */ }
};

int main() {
    std::cout << "=== std::is_trivially_copyable ===" << std::endl;

    std::cout << "int:           " << std::is_trivially_copyable<int>::value << std::endl;
    std::cout << "double:        " << std::is_trivially_copyable<double>::value << std::endl;
    std::cout << "Simple:        " << std::is_trivially_copyable<Simple>::value << std::endl;
    std::cout << "int[5]:        " << std::is_trivially_copyable<int[5]>::value << std::endl;
    std::cout << "WithVirtual:   " << std::is_trivially_copyable<WithVirtual>::value << std::endl;
    std::cout << "WithString:    " << std::is_trivially_copyable<WithString>::value << std::endl;
    std::cout << "WithCopyCtor:  " << std::is_trivially_copyable<WithCopyCtor>::value << std::endl;
    std::cout << "std::string:   " << std::is_trivially_copyable<std::string>::value << std::endl;

    static_assert(std::is_trivially_copyable<int>::value, "int is trivially copyable");
    static_assert(std::is_trivially_copyable<Simple>::value, "Simple is trivially copyable");
    static_assert(!std::is_trivially_copyable<std::string>::value, "string is not");

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::is_trivially_copyable ===
// int:           1
// double:        1
// Simple:        1
// int[5]:        1
// WithVirtual:   0
// WithString:    0
// WithCopyCtor:  0
// std::string:   0
//
// All checks passed!
