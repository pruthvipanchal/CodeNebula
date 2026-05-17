// CodeNebula - C++11 Example: std::to_string
// Compile: g++ -std=c++11 -Wall -Wextra -o example to_string.cpp

// std::to_string converts numeric types to std::string, similar to
// sprintf but type-safe. It handles int, long, long long, unsigned
// variants, float, double, and long double.

#include <iostream>
#include <string>

int main() {
    // Integer conversions
    std::string s1 = std::to_string(42);
    std::string s2 = std::to_string(-17);
    std::string s3 = std::to_string(0);
    std::cout << "int:       \"" << s1 << "\"" << std::endl;
    std::cout << "negative:  \"" << s2 << "\"" << std::endl;
    std::cout << "zero:      \"" << s3 << "\"" << std::endl;

    // Long and long long
    long big = 2147483647L;
    long long huge = 9223372036854775807LL;
    std::cout << "long:      \"" << std::to_string(big) << "\"" << std::endl;
    std::cout << "long long: \"" << std::to_string(huge) << "\"" << std::endl;

    // Unsigned types
    unsigned int u = 4294967295u;
    unsigned long long ull = 18446744073709551615ULL;
    std::cout << "unsigned:  \"" << std::to_string(u) << "\"" << std::endl;
    std::cout << "ull:       \"" << std::to_string(ull) << "\"" << std::endl;

    // Floating-point conversions (note: always includes decimal digits)
    std::cout << "\nFloating-point:" << std::endl;
    std::cout << "float:     \"" << std::to_string(3.14f) << "\"" << std::endl;
    std::cout << "double:    \"" << std::to_string(2.71828) << "\"" << std::endl;
    std::cout << "precise:   \"" << std::to_string(1.0/3.0) << "\"" << std::endl;
    std::cout << "whole:     \"" << std::to_string(100.0) << "\"" << std::endl;

    // Practical uses: string concatenation with numbers
    int count = 5;
    std::string msg = "Found " + std::to_string(count) + " items";
    std::cout << "\nConcatenation: " << msg << std::endl;

    // Building formatted output
    double price = 9.99;
    int qty = 3;
    std::string receipt = std::to_string(qty) + " x $" + std::to_string(price);
    std::cout << "Receipt: " << receipt << std::endl;

    // Loop with string conversion
    std::cout << "\nFile names:" << std::endl;
    for (int i = 1; i <= 4; ++i) {
        std::string filename = "data_" + std::to_string(i) + ".txt";
        std::cout << "  " << filename << std::endl;
    }

    return 0;
}

// Expected output:
// int:       "42"
// negative:  "-17"
// zero:      "0"
// long:      "2147483647"
// long long: "9223372036854775807"
// unsigned:  "4294967295"
// ull:       "18446744073709551615"
//
// Floating-point:
// float:     "3.140000"
// double:    "2.718280"
// precise:   "0.333333"
// whole:     "100.000000"
//
// Concatenation: Found 5 items
// Receipt: 3 x $9.990000
//
// File names:
//   data_1.txt
//   data_2.txt
//   data_3.txt
//   data_4.txt
