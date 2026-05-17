// CodeNebula - C++17 Example: if constexpr
// Compile: g++ -std=c++17 -Wall -Wextra -o example if_constexpr.cpp

// Demonstrates if constexpr for compile-time branching. The discarded branch
// is not instantiated, enabling template code that would otherwise fail to compile.

#include <iostream>
#include <string>
#include <type_traits>

// ------------------------------------------------------------------
// 1. Type-dependent formatting: only the matching branch is compiled
// ------------------------------------------------------------------
template <typename T>
std::string to_description(T value) {
    if constexpr (std::is_integral_v<T>) {
        return "integer(" + std::to_string(value) + ")";
    } else if constexpr (std::is_floating_point_v<T>) {
        return "float(" + std::to_string(value) + ")";
    } else {
        // T must be convertible to string
        return "other(" + std::string(value) + ")";
    }
}

// ------------------------------------------------------------------
// 2. Safe member access: check for pointer vs value
// ------------------------------------------------------------------
template <typename T>
auto get_value(T t) {
    if constexpr (std::is_pointer_v<T>) {
        return *t;  // dereference pointer
    } else {
        return t;   // return by value
    }
}

// ------------------------------------------------------------------
// 3. Compile-time recursion with variadic templates
// ------------------------------------------------------------------
template <typename T, typename... Rest>
void print_all(T first, Rest... rest) {
    std::cout << "  " << first;
    if constexpr (sizeof...(rest) > 0) {
        std::cout << ",";
        print_all(rest...);  // only instantiated when rest is non-empty
    } else {
        std::cout << std::endl;
    }
}

int main()
{
    // ------------------------------------------------------------------
    // Type-dependent formatting
    // ------------------------------------------------------------------
    std::cout << "=== to_description ===" << std::endl;
    std::cout << "  " << to_description(42) << std::endl;
    std::cout << "  " << to_description(3.14) << std::endl;
    std::cout << "  " << to_description("hello") << std::endl;

    // ------------------------------------------------------------------
    // Safe pointer/value access
    // ------------------------------------------------------------------
    int x = 99;
    int* px = &x;
    std::cout << "\n=== get_value ===" << std::endl;
    std::cout << "  from int:  " << get_value(x) << std::endl;
    std::cout << "  from int*: " << get_value(px) << std::endl;

    // ------------------------------------------------------------------
    // Variadic print using compile-time recursion
    // ------------------------------------------------------------------
    std::cout << "\n=== print_all ===" << std::endl;
    print_all(1, 2.5, "three", 'Z');

    return 0;
}

/*
Expected output:

=== to_description ===
  integer(42)
  float(3.140000)
  other(hello)

=== get_value ===
  from int:  99
  from int*: 99

=== print_all ===
  1,  2.5,  three,  Z
*/
