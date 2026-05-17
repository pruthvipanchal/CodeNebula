// CodeNebula - C++11 Example: is_integral
// Compile: g++ -std=c++11 -Wall -Wextra -o example is_integral.cpp

// Demonstrates std::is_integral to check if a type is an integer type.
// Integral types include bool, char, short, int, long, long long, and
// their signed/unsigned variants.

#include <iostream>
#include <type_traits>

int main() {
    std::cout << "=== std::is_integral ===" << std::endl;

    // Check various types
    std::cout << "int:         " << std::is_integral<int>::value << std::endl;
    std::cout << "bool:        " << std::is_integral<bool>::value << std::endl;
    std::cout << "char:        " << std::is_integral<char>::value << std::endl;
    std::cout << "long long:   " << std::is_integral<long long>::value << std::endl;
    std::cout << "unsigned:    " << std::is_integral<unsigned>::value << std::endl;
    std::cout << "float:       " << std::is_integral<float>::value << std::endl;
    std::cout << "double:      " << std::is_integral<double>::value << std::endl;
    std::cout << "int*:        " << std::is_integral<int*>::value << std::endl;

    // static_assert validates at compile time
    static_assert(std::is_integral<int>::value, "int must be integral");
    static_assert(!std::is_integral<double>::value, "double is not integral");
    static_assert(std::is_integral<const int>::value, "const int is integral");

    // Practical use: SFINAE-friendly template constraint
    std::cout << "\nconst int:   " << std::is_integral<const int>::value << std::endl;
    std::cout << "volatile int:" << std::is_integral<volatile int>::value << std::endl;

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::is_integral ===
// int:         1
// bool:        1
// char:        1
// long long:   1
// unsigned:    1
// float:       0
// double:      0
// int*:        0
//
// const int:   1
// volatile int:1
//
// All checks passed!
