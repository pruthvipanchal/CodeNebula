// CodeNebula - C++98 Example: <cassert> macro
// Compile: g++ -std=c++98 -Wall -Wextra -o example cassert.cpp
// To disable asserts: g++ -std=c++98 -DNDEBUG -o example cassert.cpp

#include <iostream>
#include <cassert>

int factorial(int n) {
    // Precondition: n must be non-negative
    assert(n >= 0 && "factorial requires non-negative input");
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

double safe_divide(double a, double b) {
    // Precondition: divisor must not be zero
    assert(b != 0.0 && "division by zero");
    return a / b;
}

int main() {
    // These assertions pass
    std::cout << "5! = " << factorial(5) << std::endl;
    std::cout << "10 / 3 = " << safe_divide(10.0, 3.0) << std::endl;

    // Demonstrate assert with a simple condition
    int x = 42;
    assert(x > 0);
    std::cout << "x = " << x << " (assert passed)" << std::endl;

    // Check if NDEBUG is defined
#ifdef NDEBUG
    std::cout << "NDEBUG is defined: asserts are DISABLED" << std::endl;
#else
    std::cout << "NDEBUG not defined: asserts are ENABLED" << std::endl;
#endif

    // If you uncomment the next line, the program would abort:
    // assert(false && "This would abort the program");

    std::cout << "All assertions passed!" << std::endl;
    return 0;
}

// Expected output (without NDEBUG):
// 5! = 120
// 10 / 3 = 3.33333
// x = 42 (assert passed)
// NDEBUG not defined: asserts are ENABLED
// All assertions passed!
