// CodeNebula - C++20 Example: std::is_constant_evaluated()
// Compile: g++ -std=c++20 -Wall -Wextra -o example is_constant_evaluated.cpp

// std::is_constant_evaluated() lets a constexpr function detect whether
// it is being evaluated at compile time or at runtime, enabling
// dual-path code: one optimized for compile time, one for runtime.

#include <iostream>
#include <type_traits>
#include <cmath>
#include <cstring>

// A constexpr function with dual paths
constexpr double my_power(double base, int exp) {
    if (std::is_constant_evaluated()) {
        // Compile-time path: manual loop (no std::pow available)
        double result = 1.0;
        for (int i = 0; i < exp; ++i)
            result *= base;
        return result;
    } else {
        // Runtime path: use the optimized library function
        return std::pow(base, exp);
    }
}

// Another example: string length with dual paths
constexpr std::size_t my_strlen(const char* s) {
    if (std::is_constant_evaluated()) {
        // Compile-time: manual counting
        std::size_t len = 0;
        while (s[len] != '\0') ++len;
        return len;
    } else {
        // Runtime: use optimized C library
        return std::strlen(s);
    }
}

// Demonstrating the detection in different contexts
constexpr int detect_context() {
    if (std::is_constant_evaluated()) {
        return 1;   // compile-time path
    } else {
        return 2;   // runtime path
    }
}

int main() {
    // --- Compile-time evaluation ---
    constexpr double ct_power = my_power(2.0, 10);
    std::cout << "Compile-time: my_power(2.0, 10) = " << ct_power << "\n";

    constexpr std::size_t ct_len = my_strlen("Hello");
    std::cout << "Compile-time: my_strlen(\"Hello\") = " << ct_len << "\n";

    // --- Runtime evaluation ---
    double base = 2.0;
    int exp = 10;
    double rt_power = my_power(base, exp);
    std::cout << "Runtime:      my_power(2.0, 10) = " << rt_power << "\n";

    const char* str = "Hello";
    std::size_t rt_len = my_strlen(str);
    std::cout << "Runtime:      my_strlen(\"Hello\") = " << rt_len << "\n";

    // --- Context detection ---
    constexpr int ct_val = detect_context();  // compile-time -> 1
    int rt_val = detect_context();            // runtime -> 2

    std::cout << "detect_context() at compile time: " << ct_val << "\n";
    std::cout << "detect_context() at runtime:      " << rt_val << "\n";

    // static_assert works because my_power is evaluated at compile time
    static_assert(my_power(3.0, 3) == 27.0, "3^3 should be 27");
    static_assert(my_strlen("C++20") == 5, "Length should be 5");

    std::cout << "All static_assert checks passed.\n";

    return 0;
}

// Expected output:
// Compile-time: my_power(2.0, 10) = 1024
// Compile-time: my_strlen("Hello") = 5
// Runtime:      my_power(2.0, 10) = 1024
// Runtime:      my_strlen("Hello") = 5
// detect_context() at compile time: 1
// detect_context() at runtime:      2
// All static_assert checks passed.
