// CodeNebula - C++23 Example: if consteval
// Compile: g++ -std=c++23 -Wall -Wextra -o example if_consteval.cpp
// Note: Requires GCC 12+ / Clang 14+ / MSVC 19.33+

// 'if consteval' checks whether the current evaluation is a constant expression.
// It replaces std::is_constant_evaluated() with cleaner syntax.
// The true-branch is a consteval context; the false-branch is a runtime context.

#include <iostream>
#include <cmath>

// Different implementations for compile-time vs runtime
constexpr double my_sqrt(double x) {
    if consteval {
        // Compile-time: use a simple Newton's method approximation
        if (x < 0) throw "negative input";  // constexpr-friendly error
        double guess = x / 2.0;
        for (int i = 0; i < 20; ++i)
            guess = (guess + x / guess) / 2.0;
        return guess;
    } else {
        // Runtime: use the optimized standard library version
        return std::sqrt(x);
    }
}

constexpr int compute(int x) {
    if consteval {
        // Compile-time: can use consteval-only functions
        return x * x + 1;  // Simple compile-time path
    } else {
        // Runtime path: may use non-constexpr operations
        std::cout << "  (computed at runtime)" << std::endl;
        return x * x + 1;
    }
}

// Negated form: if !consteval
constexpr int maybe_log(int value) {
    if !consteval {
        std::cout << "  Logging value: " << value << std::endl;
    }
    return value * 2;
}

int main() {
    std::cout << "=== if consteval ===" << std::endl;

    // Compile-time evaluation
    constexpr double sqrt2 = my_sqrt(2.0);
    std::cout << "constexpr sqrt(2) = " << sqrt2 << std::endl;

    // Runtime evaluation
    double x = 2.0;
    double rt_sqrt = my_sqrt(x);
    std::cout << "runtime   sqrt(2) = " << rt_sqrt << std::endl;

    std::cout << "\n=== Compile-time vs runtime path ===" << std::endl;
    constexpr int ct = compute(5);
    std::cout << "constexpr compute(5) = " << ct << std::endl;

    int val = 5;
    int rt = compute(val);
    std::cout << "runtime   compute(5) = " << rt << std::endl;

    std::cout << "\n=== if !consteval (negated form) ===" << std::endl;
    constexpr int ct2 = maybe_log(10);  // No logging at compile time
    std::cout << "constexpr maybe_log(10) = " << ct2 << std::endl;

    int v = 10;
    int rt2 = maybe_log(v);  // Logs at runtime
    std::cout << "runtime   maybe_log(10) = " << rt2 << std::endl;

    return 0;
}

/*
Expected output:
=== if consteval ===
constexpr sqrt(2) = 1.41421
runtime   sqrt(2) = 1.41421

=== Compile-time vs runtime path ===
constexpr compute(5) = 26
  (computed at runtime)
runtime   compute(5) = 26

=== if !consteval (negated form) ===
constexpr maybe_log(10) = 20
  Logging value: 10
runtime   maybe_log(10) = 20
*/
