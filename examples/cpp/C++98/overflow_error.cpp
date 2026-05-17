// CodeNebula - C++98 Example: std::overflow_error
// Compile: g++ -std=c++98 -Wall -Wextra -o example overflow_error.cpp

#include <iostream>
#include <stdexcept>
#include <limits>

long factorial(int n) {
    if (n < 0) throw std::invalid_argument("negative factorial");
    long result = 1;
    for (int i = 2; i <= n; ++i) {
        if (result > std::numeric_limits<long>::max() / i) {
            throw std::overflow_error("factorial overflow");
        }
        result *= i;
    }
    return result;
}

int safe_add(int a, int b) {
    if (b > 0 && a > std::numeric_limits<int>::max() - b) {
        throw std::overflow_error("integer addition overflow");
    }
    if (b < 0 && a < std::numeric_limits<int>::min() - b) {
        throw std::overflow_error("integer addition underflow");
    }
    return a + b;
}

int main() {
    // Successful factorial
    try {
        std::cout << "10! = " << factorial(10) << std::endl;
    } catch (const std::overflow_error& e) {
        std::cout << "Overflow: " << e.what() << std::endl;
    }

    // Factorial overflow
    try {
        std::cout << "100! = " << factorial(100) << std::endl;
    } catch (const std::overflow_error& e) {
        std::cout << "Overflow: " << e.what() << std::endl;
    }

    // Safe addition overflow
    try {
        int big = std::numeric_limits<int>::max();
        safe_add(big, 1);
    } catch (const std::overflow_error& e) {
        std::cout << "Overflow: " << e.what() << std::endl;
    }

    return 0;
}

// Expected output:
// 10! = 3628800
// Overflow: factorial overflow
// Overflow: integer addition overflow
