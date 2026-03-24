// CodeNebula - C++20 Example: std::common_with Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example common_with.cpp

// std::common_with<T, U> checks that two types share a common type
// (via std::common_type_t) to which both can be converted. Unlike
// common_reference_with, this involves value conversions, not references.

#include <concepts>
#include <iostream>
#include <type_traits>

// Generic max that works with any two types sharing a common type
template <typename T, typename U>
    requires std::common_with<T, U>
auto generic_max(T a, U b) -> std::common_type_t<T, U> {
    using Common = std::common_type_t<T, U>;
    return static_cast<Common>(a) > static_cast<Common>(b)
               ? static_cast<Common>(a)
               : static_cast<Common>(b);
}

// Safely add two potentially different numeric types
template <typename T, typename U>
    requires std::common_with<T, U>
auto safe_add(T a, U b) -> std::common_type_t<T, U> {
    return static_cast<std::common_type_t<T, U>>(a) +
           static_cast<std::common_type_t<T, U>>(b);
}

template <typename T, typename U>
void check_common(const char* t_name, const char* u_name) {
    std::cout << t_name << " & " << u_name
              << " are common_with: " << std::common_with<T, U> << "\n";
}

int main() {
    // generic_max with mixed types
    std::cout << "max(42, 3.14) = " << generic_max(42, 3.14) << "\n";
    std::cout << "max(100L, 50) = " << generic_max(100L, 50) << "\n";
    std::cout << "max(2.5f, 1.5) = " << generic_max(2.5f, 1.5) << "\n";

    // safe_add with mixed types
    std::cout << "\nsafe_add(10, 20L) = " << safe_add(10, 20L) << "\n";
    std::cout << "safe_add(1.5f, 2) = " << safe_add(1.5f, 2) << "\n";

    // Check which types are common_with each other
    std::cout << "\nCommon type checks:\n";
    check_common<int, double>("int", "double");
    check_common<int, long>("int", "long");
    check_common<float, double>("float", "double");
    check_common<short, int>("short", "int");
    check_common<char, int>("char", "int");

    // Show resulting common type sizes
    std::cout << "\nCommon type sizes:\n";
    std::cout << "int & float -> " << sizeof(std::common_type_t<int, float>) << " bytes\n";
    std::cout << "int & double -> " << sizeof(std::common_type_t<int, double>) << " bytes\n";

    return 0;
}

// Expected output:
// max(42, 3.14) = 42
// max(100L, 50) = 100
// max(2.5f, 1.5) = 2.5
//
// safe_add(10, 20L) = 30
// safe_add(1.5f, 2) = 3.5
//
// Common type checks:
// int & double are common_with: 1
// int & long are common_with: 1
// float & double are common_with: 1
// short & int are common_with: 1
// char & int are common_with: 1
//
// Common type sizes:
// int & float -> 4 bytes
// int & double -> 8 bytes
