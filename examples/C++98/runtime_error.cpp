// CodeNebula - C++98 Example: std::runtime_error
// Compile: g++ -std=c++98 -Wall -Wextra -o example runtime_error.cpp

#include <iostream>
#include <stdexcept>
#include <cstdlib>

double safe_divide(double a, double b) {
    if (b == 0.0) {
        throw std::runtime_error("division by zero");
    }
    return a / b;
}

int read_positive_int(int val) {
    if (val <= 0) {
        throw std::runtime_error("expected positive integer");
    }
    return val;
}

int main() {
    // Catch division by zero
    try {
        double result = safe_divide(10.0, 0.0);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Runtime error: " << e.what() << std::endl;
    }

    // Successful division
    try {
        double result = safe_divide(10.0, 3.0);
        std::cout << "10 / 3 = " << result << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Catch as base class
    try {
        read_positive_int(-5);
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}

// Expected output:
// Runtime error: division by zero
// 10 / 3 = 3.33333
// Exception: expected positive integer
