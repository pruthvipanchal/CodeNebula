// CodeNebula - C++20 Example: Mathematical Constants (std::numbers)
// Compile: g++ -std=c++20 -Wall -Wextra -o example math_constants.cpp

#include <iomanip>
#include <iostream>
#include <numbers>

int main() {
    std::cout << std::setprecision(18);

    std::cout << "=== std::numbers mathematical constants (double) ===\n\n";

    std::cout << "pi          = " << std::numbers::pi << "\n";
    std::cout << "e           = " << std::numbers::e << "\n";
    std::cout << "sqrt2       = " << std::numbers::sqrt2 << "\n";
    std::cout << "sqrt3       = " << std::numbers::sqrt3 << "\n";
    std::cout << "ln2         = " << std::numbers::ln2 << "\n";
    std::cout << "ln10        = " << std::numbers::ln10 << "\n";
    std::cout << "log2e       = " << std::numbers::log2e << "\n";
    std::cout << "log10e      = " << std::numbers::log10e << "\n";
    std::cout << "phi         = " << std::numbers::phi << "\n";
    std::cout << "inv_pi      = " << std::numbers::inv_pi << "\n";
    std::cout << "inv_sqrtpi  = " << std::numbers::inv_sqrtpi << "\n";
    std::cout << "egamma      = " << std::numbers::egamma << "\n";

    std::cout << "\n=== Float versions (via _v template) ===\n\n";
    std::cout << std::setprecision(9);

    std::cout << "pi_v<float>      = " << std::numbers::pi_v<float> << "\n";
    std::cout << "e_v<float>       = " << std::numbers::e_v<float> << "\n";
    std::cout << "phi_v<float>     = " << std::numbers::phi_v<float> << "\n";

    std::cout << "\n=== Long double versions ===\n\n";
    std::cout << std::setprecision(21);

    std::cout << "pi_v<long double>  = " << std::numbers::pi_v<long double> << "\n";
    std::cout << "e_v<long double>   = " << std::numbers::e_v<long double> << "\n";

    std::cout << "\n=== Verifying relationships ===\n\n";
    std::cout << std::setprecision(15);

    std::cout << "ln2 * log2e  ~= " << std::numbers::ln2 * std::numbers::log2e
              << " (should be 1)\n";
    std::cout << "ln10 * log10e ~= " << std::numbers::ln10 * std::numbers::log10e
              << " (should be 1)\n";
    std::cout << "pi * inv_pi   ~= " << std::numbers::pi * std::numbers::inv_pi
              << " (should be 1)\n";
    std::cout << "sqrt2 * sqrt2 ~= " << std::numbers::sqrt2 * std::numbers::sqrt2
              << " (should be 2)\n";
    std::cout << "sqrt3 * sqrt3 ~= " << std::numbers::sqrt3 * std::numbers::sqrt3
              << " (should be 3)\n";
    std::cout << "phi = (1+sqrt(5))/2 ~= " << (1.0 + std::sqrt(5.0)) / 2.0
              << " (golden ratio)\n";

    return 0;
}
