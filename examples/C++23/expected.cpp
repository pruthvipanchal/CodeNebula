// CodeNebula - C++23 Example: std::expected
// Compile: g++ -std=c++23 -Wall -Wextra -o example expected.cpp
// Note: Requires GCC 12+ / Clang 16+ / MSVC 19.33+

// std::expected<T, E> holds either a value of type T or an error of type E.
// It provides a monadic, exception-free error handling mechanism.
// Similar to Rust's Result<T, E>.

#include <iostream>
#include <expected>
#include <string>
#include <cmath>
#include <charconv>

enum class MathError { DivisionByZero, NegativeSqrt, Overflow };

std::string to_string(MathError e) {
    switch (e) {
        case MathError::DivisionByZero: return "division by zero";
        case MathError::NegativeSqrt:   return "sqrt of negative";
        case MathError::Overflow:       return "overflow";
    }
    return "unknown";
}

// Return expected instead of throwing
std::expected<double, MathError> safe_divide(double a, double b) {
    if (b == 0.0) return std::unexpected(MathError::DivisionByZero);
    return a / b;
}

std::expected<double, MathError> safe_sqrt(double x) {
    if (x < 0.0) return std::unexpected(MathError::NegativeSqrt);
    return std::sqrt(x);
}

// Parse integer from string
std::expected<int, std::string> parse_int(std::string_view sv) {
    int result = 0;
    auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), result);
    if (ec != std::errc{}) return std::unexpected("invalid integer: " + std::string(sv));
    return result;
}

int main() {
    std::cout << "=== std::expected ===" << std::endl;

    // Basic usage
    auto r1 = safe_divide(10.0, 3.0);
    auto r2 = safe_divide(10.0, 0.0);

    std::cout << "10 / 3 = ";
    if (r1) std::cout << r1.value() << std::endl;
    else    std::cout << "Error: " << to_string(r1.error()) << std::endl;

    std::cout << "10 / 0 = ";
    if (r2) std::cout << r2.value() << std::endl;
    else    std::cout << "Error: " << to_string(r2.error()) << std::endl;

    // value_or: provide default on error
    std::cout << "\n=== value_or ===" << std::endl;
    std::cout << "sqrt(25) or -1: " << safe_sqrt(25).value_or(-1) << std::endl;
    std::cout << "sqrt(-4) or -1: " << safe_sqrt(-4).value_or(-1) << std::endl;

    // Monadic operations: and_then, transform, or_else
    std::cout << "\n=== Monadic chaining ===" << std::endl;
    auto result = safe_divide(100.0, 4.0)
        .and_then([](double v) { return safe_sqrt(v); })
        .transform([](double v) { return v * 2; });

    std::cout << "sqrt(100/4) * 2 = " << result.value() << std::endl;

    // Chain that produces an error
    auto bad = safe_divide(100.0, 0.0)
        .and_then([](double v) { return safe_sqrt(v); })
        .transform([](double v) { return v * 2; });

    std::cout << "Error chain: " << to_string(bad.error()) << std::endl;

    // Parsing example
    std::cout << "\n=== Parsing ===" << std::endl;
    for (auto s : {"42", "abc", "100"}) {
        auto parsed = parse_int(s);
        if (parsed) std::cout << "'" << s << "' -> " << *parsed << std::endl;
        else        std::cout << "'" << s << "' -> Error: " << parsed.error() << std::endl;
    }

    return 0;
}

/*
Expected output:
=== std::expected ===
10 / 3 = 3.33333
10 / 0 = Error: division by zero

=== value_or ===
sqrt(25) or -1: 5
sqrt(-4) or -1: -1

=== Monadic chaining ===
sqrt(100/4) * 2 = 10
Error chain: division by zero

=== Parsing ===
'42' -> 42
'abc' -> Error: invalid integer: abc
'100' -> 100
*/
