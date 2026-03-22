// CodeNebula - C++98 Example: <climits> integer limits
// Compile: g++ -std=c++98 -Wall -Wextra -o example climits.cpp

#include <iostream>
#include <climits>

int main() {
    std::cout << "=== Character Limits ===" << std::endl;
    std::cout << "CHAR_BIT:   " << CHAR_BIT << std::endl;
    std::cout << "CHAR_MIN:   " << CHAR_MIN << std::endl;
    std::cout << "CHAR_MAX:   " << CHAR_MAX << std::endl;
    std::cout << "SCHAR_MIN:  " << SCHAR_MIN << std::endl;
    std::cout << "SCHAR_MAX:  " << SCHAR_MAX << std::endl;
    std::cout << "UCHAR_MAX:  " << UCHAR_MAX << std::endl;

    std::cout << "\n=== Short Limits ===" << std::endl;
    std::cout << "SHRT_MIN:   " << SHRT_MIN << std::endl;
    std::cout << "SHRT_MAX:   " << SHRT_MAX << std::endl;
    std::cout << "USHRT_MAX:  " << USHRT_MAX << std::endl;

    std::cout << "\n=== Int Limits ===" << std::endl;
    std::cout << "INT_MIN:    " << INT_MIN << std::endl;
    std::cout << "INT_MAX:    " << INT_MAX << std::endl;
    std::cout << "UINT_MAX:   " << UINT_MAX << std::endl;

    std::cout << "\n=== Long Limits ===" << std::endl;
    std::cout << "LONG_MIN:   " << LONG_MIN << std::endl;
    std::cout << "LONG_MAX:   " << LONG_MAX << std::endl;
    std::cout << "ULONG_MAX:  " << ULONG_MAX << std::endl;

    // Practical use: check for overflow before adding
    int a = INT_MAX - 5;
    int b = 3;
    if (b > 0 && a > INT_MAX - b) {
        std::cout << "\nAddition would overflow!" << std::endl;
    } else {
        std::cout << "\nSafe to add: " << (a + b) << std::endl;
    }

    return 0;
}

// Expected output (typical 32-bit int, 64-bit long):
// === Character Limits ===
// CHAR_BIT:   8
// CHAR_MIN:   -128
// CHAR_MAX:   127
// SCHAR_MIN:  -128
// SCHAR_MAX:  127
// UCHAR_MAX:  255
//
// === Short Limits ===
// SHRT_MIN:   -32768
// SHRT_MAX:   32767
// USHRT_MAX:  65535
//
// === Int Limits ===
// INT_MIN:    -2147483648
// INT_MAX:    2147483647
// UINT_MAX:   4294967295
//
// === Long Limits ===
// LONG_MIN:   <platform-dependent>
// LONG_MAX:   <platform-dependent>
// ULONG_MAX:  <platform-dependent>
//
// Safe to add: 2147483645
