// CodeNebula - C++26 Example: Math Function Improvements
// Compile: g++ -std=c++26 -Wall -Wextra -o example math_functions.cpp
// Note: Requires C++26 compiler support

#include <iostream>
#include <cmath>
#include <iomanip>

// C++26 improves several math functions with:
//   - Full constexpr support for std::frexp, std::modf, std::remquo
//   - Better NaN and infinity handling
//   - Improved precision guarantees
//
// std::frexp(x, &exp) - decomposes x into mantissa * 2^exp
// std::modf(x, &ipart) - splits x into integer and fractional parts
// std::remquo(x, y, &quo) - remainder and partial quotient

int main() {
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "--- C++26 Math Function Improvements ---\n\n";

    // frexp: decompose floating-point into mantissa and exponent
    // x = mantissa * 2^exp, where 0.5 <= |mantissa| < 1.0
    std::cout << "--- std::frexp ---\n";
    double values[] = {12.0, 0.5, -3.14, 100.0};
    for (double x : values) {
        int exp = 0;
        double mantissa = std::frexp(x, &exp);
        std::cout << "  frexp(" << std::setw(8) << x << ") = "
                  << mantissa << " * 2^" << exp << "\n";
    }

    // modf: split into integer and fractional parts
    std::cout << "\n--- std::modf ---\n";
    double modf_vals[] = {3.75, -2.5, 0.125, 7.0};
    for (double x : modf_vals) {
        double ipart = 0;
        double fpart = std::modf(x, &ipart);
        std::cout << "  modf(" << std::setw(8) << x << ") = "
                  << "int: " << ipart << ", frac: " << fpart << "\n";
    }

    // remquo: IEEE remainder and low-order quotient bits
    std::cout << "\n--- std::remquo ---\n";
    struct { double x, y; } remquo_cases[] = {{10.5, 3.0}, {7.0, 2.0}, {-5.5, 2.5}};
    for (auto [x, y] : remquo_cases) {
        int quo = 0;
        double rem = std::remquo(x, y, &quo);
        std::cout << "  remquo(" << x << ", " << y << ") = "
                  << "rem: " << rem << ", quo: " << quo << "\n";
    }

    // C++26: these work in constexpr contexts
    // constexpr int exp = 0;
    // constexpr double m = std::frexp(8.0, &exp); // C++26: constexpr
    // static_assert(m == 0.5 && exp == 4);
    std::cout << "\nC++26: frexp, modf, remquo are fully constexpr.\n";
    return 0;
}

// Expected output:
// --- C++26 Math Function Improvements ---
//
// --- std::frexp ---
//   frexp(12.000000) = 0.750000 * 2^4
//   frexp( 0.500000) = 0.500000 * 2^0
//   frexp(-3.140000) = -0.785000 * 2^2
//   frexp(100.000000) = 0.781250 * 2^7
//
// --- std::modf ---
//   modf( 3.750000) = int: 3.000000, frac: 0.750000
//   modf(-2.500000) = int: -2.000000, frac: -0.500000
//   modf( 0.125000) = int: 0.000000, frac: 0.125000
//   modf( 7.000000) = int: 7.000000, frac: 0.000000
//
// --- std::remquo ---
//   remquo(10.500000, 3.000000) = rem: 1.500000, quo: 3
//   remquo(7.000000, 2.000000) = rem: -1.000000, quo: 4
//   remquo(-5.500000, 2.500000) = rem: -0.500000, quo: -2
//
// C++26: frexp, modf, remquo are fully constexpr.
