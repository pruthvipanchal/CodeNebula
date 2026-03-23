// CodeNebula - C++11 Example: is_floating_point
// Compile: g++ -std=c++11 -Wall -Wextra -o example is_floating_point.cpp

// Demonstrates std::is_floating_point to check if a type is a
// floating-point type (float, double, or long double).

#include <iostream>
#include <type_traits>

int main() {
    std::cout << "=== std::is_floating_point ===" << std::endl;

    std::cout << "float:       " << std::is_floating_point<float>::value << std::endl;
    std::cout << "double:      " << std::is_floating_point<double>::value << std::endl;
    std::cout << "long double: " << std::is_floating_point<long double>::value << std::endl;
    std::cout << "int:         " << std::is_floating_point<int>::value << std::endl;
    std::cout << "bool:        " << std::is_floating_point<bool>::value << std::endl;
    std::cout << "char:        " << std::is_floating_point<char>::value << std::endl;

    // Compile-time checks
    static_assert(std::is_floating_point<float>::value, "float is floating point");
    static_assert(std::is_floating_point<double>::value, "double is floating point");
    static_assert(!std::is_floating_point<int>::value, "int is not floating point");

    // cv-qualified types still match
    std::cout << "\nconst double:    " << std::is_floating_point<const double>::value << std::endl;
    std::cout << "volatile float:  " << std::is_floating_point<volatile float>::value << std::endl;
    std::cout << "float&:          " << std::is_floating_point<float&>::value << std::endl;
    std::cout << "float*:          " << std::is_floating_point<float*>::value << std::endl;

    static_assert(std::is_floating_point<const float>::value, "const float matches");
    static_assert(!std::is_floating_point<float*>::value, "float* does not match");

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::is_floating_point ===
// float:       1
// double:      1
// long double: 1
// int:         0
// bool:        0
// char:        0
//
// const double:    1
// volatile float:  1
// float&:          0
// float*:          0
//
// All checks passed!
