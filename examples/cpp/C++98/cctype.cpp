// CodeNebula - C++98 Example: <cctype> character classification
// Compile: g++ -std=c++98 -Wall -Wextra -o example cctype.cpp

#include <iostream>
#include <cctype>
#include <cstring>

int main() {
    // Character classification functions
    char test[] = "Hello World 123!@#";

    std::cout << "Testing: \"" << test << "\"" << std::endl;
    std::cout << std::endl;

    int alpha = 0, digit = 0, space = 0, punct = 0, upper = 0, lower = 0;
    for (std::size_t i = 0; i < std::strlen(test); ++i) {
        unsigned char c = static_cast<unsigned char>(test[i]);
        if (std::isalpha(c)) ++alpha;
        if (std::isdigit(c)) ++digit;
        if (std::isspace(c)) ++space;
        if (std::ispunct(c)) ++punct;
        if (std::isupper(c)) ++upper;
        if (std::islower(c)) ++lower;
    }

    std::cout << "alpha: " << alpha << std::endl;
    std::cout << "digit: " << digit << std::endl;
    std::cout << "space: " << space << std::endl;
    std::cout << "punct: " << punct << std::endl;
    std::cout << "upper: " << upper << std::endl;
    std::cout << "lower: " << lower << std::endl;

    // toupper / tolower conversion
    char msg[] = "Hello World";
    std::cout << "\nOriginal:  " << msg << std::endl;

    std::cout << "Uppercase: ";
    for (std::size_t i = 0; i < std::strlen(msg); ++i) {
        std::cout << static_cast<char>(std::toupper(static_cast<unsigned char>(msg[i])));
    }
    std::cout << std::endl;

    std::cout << "Lowercase: ";
    for (std::size_t i = 0; i < std::strlen(msg); ++i) {
        std::cout << static_cast<char>(std::tolower(static_cast<unsigned char>(msg[i])));
    }
    std::cout << std::endl;

    // isalnum check
    std::cout << "\nisalnum('A'): " << (std::isalnum('A') ? "yes" : "no") << std::endl;
    std::cout << "isalnum('5'): " << (std::isalnum('5') ? "yes" : "no") << std::endl;
    std::cout << "isalnum('!'): " << (std::isalnum('!') ? "yes" : "no") << std::endl;

    return 0;
}

// Expected output:
// Testing: "Hello World 123!@#"
//
// alpha: 10
// digit: 3
// space: 2
// punct: 3
// upper: 2
// lower: 8
//
// Original:  Hello World
// Uppercase: HELLO WORLD
// Lowercase: hello world
//
// isalnum('A'): yes
// isalnum('5'): yes
// isalnum('!'): no
