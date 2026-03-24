// CodeNebula - C++26 Example: Contracts
// Compile: g++ -std=c++26 -Wall -Wextra -o example contracts.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// C++26 introduces contracts: preconditions, postconditions, and assertions.
// These allow functions to declare expectations on inputs, outputs, and
// intermediate state, enabling runtime checking and static analysis.

#include <iostream>
#include <cmath>

// --- C++26 Contract Syntax (not yet compilable) ---
//
// double sqrt_safe(double x)
//     pre(x >= 0.0)                   // precondition: caller must ensure
//     post(r: r >= 0.0)               // postcondition: 'r' names the return value
// {
//     contract_assert(x == x);        // in-body assertion (x is not NaN)
//     return std::sqrt(x);
// }
//
// int divide(int a, int b)
//     pre(b != 0)                     // prevent division by zero
//     post(r: r * b <= a)             // postcondition on result
// {
//     return a / b;
// }

// --- Simulation using C++20 features ---

#include <stdexcept>
#include <cassert>

// Simulate preconditions and postconditions with manual checks
double sqrt_safe(double x) {
    // Simulated pre(x >= 0.0)
    if (x < 0.0) throw std::invalid_argument("precondition failed: x >= 0.0");

    assert(x == x); // Simulated contract_assert (x is not NaN)

    double result = std::sqrt(x);

    // Simulated post(r: r >= 0.0)
    if (result < 0.0) throw std::logic_error("postcondition failed: r >= 0.0");

    return result;
}

int divide(int a, int b) {
    // Simulated pre(b != 0)
    if (b == 0) throw std::invalid_argument("precondition failed: b != 0");

    return a / b;
}

int main() {
    std::cout << "=== C++26 Contracts (Simulated) ===" << std::endl;

    std::cout << "sqrt_safe(25.0) = " << sqrt_safe(25.0) << std::endl;
    std::cout << "sqrt_safe(2.0)  = " << sqrt_safe(2.0) << std::endl;
    std::cout << "divide(10, 3)   = " << divide(10, 3) << std::endl;

    try {
        sqrt_safe(-1.0); // Violates precondition
    } catch (const std::exception& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    try {
        divide(5, 0); // Violates precondition
    } catch (const std::exception& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    std::cout << "Contracts help catch bugs at function boundaries." << std::endl;
    return 0;
}

// Expected output:
// === C++26 Contracts (Simulated) ===
// sqrt_safe(25.0) = 5
// sqrt_safe(2.0)  = 1.41421
// divide(10, 3)   = 3
// Caught: precondition failed: x >= 0.0
// Caught: precondition failed: b != 0
// Contracts help catch bugs at function boundaries.
