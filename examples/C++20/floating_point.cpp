// CodeNebula - C++20 Example: std::floating_point Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example floating_point.cpp

// std::floating_point is satisfied by float, double, and long double.
// It constrains templates to work only with floating-point types.

#include <concepts>
#include <cmath>
#include <iostream>
#include <limits>

// Constrained to floating-point types only
template <std::floating_point T>
T safe_divide(T numerator, T denominator) {
    if (denominator == T{0}) {
        std::cout << "  Warning: division by zero\n";
        return std::numeric_limits<T>::infinity();
    }
    return numerator / denominator;
}

// Approximate equality for floating-point comparison
template <std::floating_point T>
bool nearly_equal(T a, T b, T epsilon = std::numeric_limits<T>::epsilon() * 100) {
    return std::abs(a - b) < epsilon;
}

// Report precision info for a floating-point type
template <std::floating_point T>
void show_precision(const char* name) {
    std::cout << name << ": digits10=" << std::numeric_limits<T>::digits10
              << ", epsilon=" << std::numeric_limits<T>::epsilon() << "\n";
}

int main() {
    // Safe division
    std::cout << "10.0 / 3.0 = " << safe_divide(10.0, 3.0) << "\n";
    std::cout << "10.0f / 0.0f = ";
    auto result = safe_divide(10.0f, 0.0f);
    std::cout << "  Result: " << result << "\n";

    // Nearly equal checks
    double a = 0.1 + 0.2;
    double b = 0.3;
    std::cout << "\n0.1 + 0.2 == 0.3: " << (a == b) << "\n";
    std::cout << "nearly_equal(0.1+0.2, 0.3): " << nearly_equal(a, b) << "\n";

    // Precision info
    std::cout << "\nPrecision info:\n";
    show_precision<float>("float");
    show_precision<double>("double");
    show_precision<long double>("long double");

    // Concept checks
    std::cout << "\nType checks:\n";
    std::cout << "float: " << std::floating_point<float> << "\n";
    std::cout << "double: " << std::floating_point<double> << "\n";
    std::cout << "int: " << std::floating_point<int> << "\n";

    return 0;
}

// Expected output:
// 10.0 / 3.0 = 3.33333
// 10.0f / 0.0f =   Warning: division by zero
//   Result: inf
//
// 0.1 + 0.2 == 0.3: 0
// nearly_equal(0.1+0.2, 0.3): 1
//
// Precision info:
// float: digits10=6, epsilon=1.19209e-07
// double: digits10=15, epsilon=2.22045e-16
// long double: digits10=18, epsilon=1.0842e-19
//
// Type checks:
// float: 1
// double: 1
// int: 0
