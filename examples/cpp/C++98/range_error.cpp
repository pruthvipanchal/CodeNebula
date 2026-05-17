// CodeNebula - C++98 Example: std::range_error
// Compile: g++ -std=c++98 -Wall -Wextra -o example range_error.cpp

#include <iostream>
#include <stdexcept>
#include <limits>

// A function that checks if a result can be stored in an int
int safe_cast_to_int(double value) {
    if (value > static_cast<double>(std::numeric_limits<int>::max()) ||
        value < static_cast<double>(std::numeric_limits<int>::min())) {
        throw std::range_error("value out of int range");
    }
    return static_cast<int>(value);
}

// A function that produces results that might be out of range
double compute(double x) {
    double result = x * x * x;
    if (result > 1e15) {
        throw std::range_error("computed result exceeds allowed range");
    }
    return result;
}

int main() {
    // Safe cast within range
    try {
        int val = safe_cast_to_int(42.7);
        std::cout << "Cast 42.7 to int: " << val << std::endl;
    } catch (const std::range_error& e) {
        std::cout << "Range error: " << e.what() << std::endl;
    }

    // Safe cast out of range
    try {
        int val = safe_cast_to_int(1e18);
        std::cout << "Cast: " << val << std::endl;
    } catch (const std::range_error& e) {
        std::cout << "Range error: " << e.what() << std::endl;
    }

    // Computation in range
    try {
        std::cout << "10^3 = " << compute(10) << std::endl;
    } catch (const std::range_error& e) {
        std::cout << "Range error: " << e.what() << std::endl;
    }

    // Computation out of range
    try {
        std::cout << "1e6^3 = " << compute(1e6) << std::endl;
    } catch (const std::range_error& e) {
        std::cout << "Range error: " << e.what() << std::endl;
    }

    return 0;
}

// Expected output:
// Cast 42.7 to int: 42
// Range error: value out of int range
// 10^3 = 1000
// Range error: computed result exceeds allowed range
