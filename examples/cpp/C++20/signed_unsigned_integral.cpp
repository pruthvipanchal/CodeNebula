// CodeNebula - C++20 Example: std::signed_integral and std::unsigned_integral
// Compile: g++ -std=c++20 -Wall -Wextra -o example signed_unsigned_integral.cpp

// std::signed_integral matches integral types that are signed (int, long, etc.).
// std::unsigned_integral matches unsigned integral types (unsigned int, size_t, etc.).

#include <concepts>
#include <iostream>

// Only accept signed integers
template <std::signed_integral T>
T absolute_value(T value) {
    return value < 0 ? -value : value;
}

// Only accept unsigned integers
template <std::unsigned_integral T>
T safe_subtract(T a, T b) {
    if (b > a) {
        std::cout << "  Clamped to zero (would underflow)\n";
        return 0;
    }
    return a - b;
}

// Distinguish signed vs unsigned at compile time
template <typename T>
    requires std::integral<T>
void classify(T value) {
    std::cout << "Value " << value << " is ";
    if constexpr (std::signed_integral<T>) {
        std::cout << "signed integral\n";
    } else if constexpr (std::unsigned_integral<T>) {
        std::cout << "unsigned integral\n";
    }
}

int main() {
    // absolute_value works with signed types
    std::cout << "abs(-42) = " << absolute_value(-42) << "\n";
    std::cout << "abs(17L) = " << absolute_value(17L) << "\n";
    // absolute_value(42u);  // Compile error: unsigned int not signed

    // safe_subtract works with unsigned types
    std::cout << "safe_subtract(10u, 3u) = " << safe_subtract(10u, 3u) << "\n";
    std::cout << "safe_subtract(3u, 10u) = ";
    auto r = safe_subtract(3u, 10u);
    std::cout << "  Result: " << r << "\n";

    // Classify various types
    std::cout << "\nClassification:\n";
    classify(42);
    classify(-7L);
    classify(100u);
    classify(static_cast<unsigned short>(5));

    // Concept checks
    std::cout << "\nConcept checks:\n";
    std::cout << "int signed: " << std::signed_integral<int> << "\n";
    std::cout << "unsigned int signed: " << std::signed_integral<unsigned int> << "\n";
    std::cout << "unsigned int unsigned: " << std::unsigned_integral<unsigned int> << "\n";
    std::cout << "bool unsigned: " << std::unsigned_integral<bool> << "\n";

    return 0;
}

// Expected output:
// abs(-42) = 42
// abs(17L) = 17
// safe_subtract(10u, 3u) = 7
// safe_subtract(3u, 10u) =   Clamped to zero (would underflow)
//   Result: 0
//
// Classification:
// Value 42 is signed integral
// Value -7 is signed integral
// Value 100 is unsigned integral
// Value 5 is unsigned integral
//
// Concept checks:
// int signed: 1
// unsigned int signed: 0
// unsigned int unsigned: 1
// bool unsigned: 1
