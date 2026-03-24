// CodeNebula - C++23 Example: std::expected Monadic Operations
// Compile: g++ -std=c++23 -Wall -Wextra -o example expected_monadic.cpp
// Note: Requires GCC 13+ / Clang 17+

#include <expected>
#include <iostream>
#include <string>
#include <cmath>

// std::expected<T, E> (C++23) holds either a value T or an error E.
// It supports monadic operations:
//   and_then(f) - flatmap: if has value, call f(value) -> expected
//   transform(f) - map: if has value, wrap f(value) in expected
//   or_else(f)   - if has error, call f(error) -> expected
//   transform_error(f) - map the error type

enum class MathError { DivByZero, Negative, Overflow };

std::string to_string(MathError e) {
    switch (e) {
        case MathError::DivByZero: return "division by zero";
        case MathError::Negative:  return "negative input";
        case MathError::Overflow:  return "overflow";
    }
    return "unknown";
}

using Result = std::expected<double, MathError>;

Result safe_divide(double a, double b) {
    if (b == 0.0) return std::unexpected(MathError::DivByZero);
    return a / b;
}

Result safe_sqrt(double x) {
    if (x < 0.0) return std::unexpected(MathError::Negative);
    return std::sqrt(x);
}

Result safe_reciprocal(double x) {
    return safe_divide(1.0, x);
}

int main() {
    std::cout << "=== std::expected monadic operations ===\n\n";

    // --- Basic usage ---
    auto r1 = safe_divide(10.0, 3.0);
    auto r2 = safe_divide(10.0, 0.0);
    std::cout << "10/3 = " << (r1 ? std::to_string(*r1) : to_string(r1.error())) << "\n";
    std::cout << "10/0 = " << (r2 ? std::to_string(*r2) : to_string(r2.error())) << "\n\n";

    // --- and_then: chain failable operations ---
    std::cout << "--- and_then ---\n";
    auto chain1 = safe_divide(100.0, 4.0).and_then(safe_sqrt);
    std::cout << "sqrt(100/4) = " << chain1.value() << "\n";

    auto chain2 = safe_divide(100.0, 0.0).and_then(safe_sqrt);
    std::cout << "sqrt(100/0) = " << to_string(chain2.error()) << "\n";

    auto chain3 = safe_divide(-16.0, 1.0).and_then(safe_sqrt);
    std::cout << "sqrt(-16/1) = " << to_string(chain3.error()) << "\n\n";

    // --- transform: apply function to value ---
    std::cout << "--- transform ---\n";
    auto doubled = safe_divide(10.0, 4.0)
        .transform([](double v) { return v * 2.0; });
    std::cout << "(10/4) * 2 = " << doubled.value() << "\n";

    auto fail_transform = safe_divide(1.0, 0.0)
        .transform([](double v) { return v * 2.0; });
    std::cout << "(1/0) * 2 = " << to_string(fail_transform.error()) << "\n\n";

    // --- or_else: recover from errors ---
    std::cout << "--- or_else ---\n";
    auto recovered = safe_divide(1.0, 0.0)
        .or_else([](MathError e) -> Result {
            std::cout << "  Recovering from: " << to_string(e) << "\n";
            return 0.0;  // Default value on error
        });
    std::cout << "Recovered value: " << recovered.value() << "\n\n";

    // --- Full chain ---
    std::cout << "--- Full chain: divide -> sqrt -> reciprocal ---\n";
    auto full = safe_divide(100.0, 4.0)
        .and_then(safe_sqrt)
        .and_then(safe_reciprocal)
        .transform([](double v) { return std::round(v * 1000) / 1000; });
    std::cout << "1/sqrt(100/4) = " << full.value() << "\n";

    return 0;
}

// Expected output:
// === std::expected monadic operations ===
//
// 10/3 = 3.333333
// 10/0 = division by zero
//
// --- and_then ---
// sqrt(100/4) = 5
// sqrt(100/0) = division by zero
// sqrt(-16/1) = negative input
//
// --- transform ---
// (10/4) * 2 = 5
// (1/0) * 2 = division by zero
//
// --- or_else ---
//   Recovering from: division by zero
// Recovered value: 0
//
// --- Full chain: divide -> sqrt -> reciprocal ---
// 1/sqrt(100/4) = 0.2
