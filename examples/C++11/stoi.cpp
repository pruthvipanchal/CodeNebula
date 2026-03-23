// CodeNebula - C++11 Example: std::stoi, std::stol, std::stoll
// Compile: g++ -std=c++11 -Wall -Wextra -o example stoi.cpp

// std::stoi, std::stol, and std::stoll convert strings to integer types.
// They support different bases (decimal, hex, octal) and report the
// position where parsing stopped. They throw on invalid input or overflow.

#include <iostream>
#include <string>
#include <stdexcept>

int main() {
    // Basic stoi usage
    int a = std::stoi("42");
    int b = std::stoi("-17");
    int c = std::stoi("  100  ");  // leading whitespace is skipped
    std::cout << "stoi(\"42\") = " << a << std::endl;
    std::cout << "stoi(\"-17\") = " << b << std::endl;
    std::cout << "stoi(\"  100  \") = " << c << std::endl;

    // Parsing with position tracking
    std::string input = "123abc";
    std::size_t pos = 0;
    int val = std::stoi(input, &pos);
    std::cout << "\nstoi(\"123abc\"): value=" << val
              << ", stopped at pos=" << pos << std::endl;

    // Different bases
    int dec = std::stoi("255", nullptr, 10);    // decimal
    int hex = std::stoi("FF", nullptr, 16);     // hexadecimal
    int oct = std::stoi("377", nullptr, 8);     // octal
    int bin = std::stoi("11111111", nullptr, 2); // binary
    std::cout << "\nBase conversions (all equal 255):" << std::endl;
    std::cout << "  decimal \"255\":      " << dec << std::endl;
    std::cout << "  hex \"FF\":           " << hex << std::endl;
    std::cout << "  octal \"377\":        " << oct << std::endl;
    std::cout << "  binary \"11111111\":  " << bin << std::endl;

    // Auto-detect base with base=0
    int auto1 = std::stoi("0xFF", nullptr, 0);   // hex prefix
    int auto2 = std::stoi("077", nullptr, 0);     // octal prefix
    int auto3 = std::stoi("42", nullptr, 0);      // decimal
    std::cout << "\nAuto-detect base:" << std::endl;
    std::cout << "  \"0xFF\" = " << auto1 << std::endl;
    std::cout << "  \"077\" = " << auto2 << std::endl;
    std::cout << "  \"42\" = " << auto3 << std::endl;

    // stol and stoll for larger types
    long big = std::stol("2147483647");
    long long huge = std::stoll("9223372036854775807");
    std::cout << "\nstol: " << big << std::endl;
    std::cout << "stoll: " << huge << std::endl;

    // Error handling
    try {
        std::stoi("not_a_number");
    } catch (const std::invalid_argument& e) {
        std::cout << "\ninvalid_argument: " << e.what() << std::endl;
    }

    try {
        std::stoi("99999999999999999999");
    } catch (const std::out_of_range& e) {
        std::cout << "out_of_range: " << e.what() << std::endl;
    }

    return 0;
}

// Expected output:
// stoi("42") = 42
// stoi("-17") = -17
// stoi("  100  ") = 100
//
// stoi("123abc"): value=123, stopped at pos=3
//
// Base conversions (all equal 255):
//   decimal "255":      255
//   hex "FF":           255
//   octal "377":        255
//   binary "11111111":  255
//
// Auto-detect base:
//   "0xFF" = 255
//   "077" = 63
//   "42" = 42
//
// stol: 2147483647
// stoll: 9223372036854775807
//
// invalid_argument: stoi
// out_of_range: stoi
