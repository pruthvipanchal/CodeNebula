// CodeNebula - C++11 Example: is_convertible
// Compile: g++ -std=c++11 -Wall -Wextra -o example is_convertible.cpp

// Demonstrates std::is_convertible to check if one type can be
// implicitly converted to another. Checks From -> To direction.

#include <iostream>
#include <type_traits>
#include <string>

class Base {};
class Derived : public Base {};

class Explicit {
public:
    explicit Explicit(int) {}  // explicit prevents implicit conversion
};

int main() {
    std::cout << "=== std::is_convertible ===" << std::endl;

    // Numeric conversions
    std::cout << "int -> double:       "
              << std::is_convertible<int, double>::value << std::endl;
    std::cout << "double -> int:       "
              << std::is_convertible<double, int>::value << std::endl;
    std::cout << "int -> bool:         "
              << std::is_convertible<int, bool>::value << std::endl;

    // Pointer conversions with inheritance
    std::cout << "Derived* -> Base*:   "
              << std::is_convertible<Derived*, Base*>::value << std::endl;
    std::cout << "Base* -> Derived*:   "
              << std::is_convertible<Base*, Derived*>::value << std::endl;

    // String conversions
    std::cout << "const char* -> string: "
              << std::is_convertible<const char*, std::string>::value << std::endl;
    std::cout << "string -> const char*: "
              << std::is_convertible<std::string, const char*>::value << std::endl;

    // Explicit constructors block implicit conversion
    std::cout << "int -> Explicit:     "
              << std::is_convertible<int, Explicit>::value << std::endl;

    static_assert(std::is_convertible<Derived*, Base*>::value, "upcasting works");
    static_assert(!std::is_convertible<Base*, Derived*>::value, "no implicit downcast");

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::is_convertible ===
// int -> double:       1
// double -> int:       1
// int -> bool:         1
// Derived* -> Base*:   1
// Base* -> Derived*:   0
// const char* -> string: 1
// string -> const char*: 0
// int -> Explicit:     0
//
// All checks passed!
