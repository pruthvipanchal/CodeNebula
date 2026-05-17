// CodeNebula - C++98 Example: std::numeric_limits
// Compile: g++ -std=c++98 -Wall -Wextra -o example numeric_limits.cpp

#include <iostream>
#include <limits>

int main() {
    // Integer type properties
    std::cout << "=== int ===" << std::endl;
    std::cout << "min:    " << std::numeric_limits<int>::min() << std::endl;
    std::cout << "max:    " << std::numeric_limits<int>::max() << std::endl;
    std::cout << "digits: " << std::numeric_limits<int>::digits << std::endl;
    std::cout << "signed: " << std::numeric_limits<int>::is_signed << std::endl;

    std::cout << "\n=== unsigned int ===" << std::endl;
    std::cout << "min: " << std::numeric_limits<unsigned int>::min() << std::endl;
    std::cout << "max: " << std::numeric_limits<unsigned int>::max() << std::endl;

    // Floating-point properties
    std::cout << "\n=== double ===" << std::endl;
    std::cout << "min:        " << std::numeric_limits<double>::min() << std::endl;
    std::cout << "max:        " << std::numeric_limits<double>::max() << std::endl;
    std::cout << "epsilon:    " << std::numeric_limits<double>::epsilon() << std::endl;
    std::cout << "digits10:   " << std::numeric_limits<double>::digits10 << std::endl;
    std::cout << "has_inf:    " << std::numeric_limits<double>::has_infinity << std::endl;
    std::cout << "has_nan:    " << std::numeric_limits<double>::has_quiet_NaN << std::endl;

    // Check if a type is specialized
    std::cout << "\n=== bool ===" << std::endl;
    std::cout << "is_specialized: " << std::numeric_limits<bool>::is_specialized << std::endl;
    std::cout << "is_integer:     " << std::numeric_limits<bool>::is_integer << std::endl;

    return 0;
}

// Expected output (values are platform-dependent):
// === int ===
// min:    -2147483648
// max:    2147483647
// digits: 31
// signed: 1
//
// === unsigned int ===
// min: 0
// max: 4294967295
//
// === double ===
// min:        2.22507e-308
// max:        1.79769e+308
// epsilon:    2.22045e-16
// digits10:   15
// has_inf:    1
// has_nan:    1
//
// === bool ===
// is_specialized: 1
// is_integer:     1
