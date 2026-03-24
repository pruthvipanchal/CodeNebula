// CodeNebula - C++20 Example: char8_t
// Compile: g++ -std=c++20 -Wall -Wextra -o example char8_t.cpp

// Demonstrates the C++20 char8_t type for UTF-8 encoded character data,
// u8 string literals, and conversion between char8_t and char.

#include <iostream>
#include <string>
#include <cstring>
#include <type_traits>

// ------------------------------------------------------------------
// Helper: convert u8string to regular string for printing
// ------------------------------------------------------------------
std::string to_string(const std::u8string& u8s) {
    return std::string(reinterpret_cast<const char*>(u8s.data()), u8s.size());
}

std::string to_string(const char8_t* u8s) {
    return std::string(reinterpret_cast<const char*>(u8s));
}

int main()
{
    // ------------------------------------------------------------------
    // 1. char8_t is a distinct type in C++20
    // ------------------------------------------------------------------
    std::cout << "=== char8_t Type Properties ===" << std::endl;
    std::cout << "  sizeof(char8_t):  " << sizeof(char8_t) << std::endl;
    std::cout << "  sizeof(char):     " << sizeof(char) << std::endl;
    std::cout << "  same as char?     "
              << std::is_same_v<char8_t, char> << std::endl;
    std::cout << "  same as unsigned char? "
              << std::is_same_v<char8_t, unsigned char> << std::endl;
    std::cout << "  is unsigned?      " << std::is_unsigned_v<char8_t> << std::endl;

    // ------------------------------------------------------------------
    // 2. u8 character and string literals produce char8_t
    // ------------------------------------------------------------------
    std::cout << "\n=== u8 Literals ===" << std::endl;
    char8_t ch = u8'A';
    std::cout << "  u8'A' value: " << static_cast<int>(ch) << std::endl;

    const char8_t* u8lit = u8"Hello, UTF-8!";
    std::cout << "  u8 literal: " << to_string(u8lit) << std::endl;

    // ------------------------------------------------------------------
    // 3. std::u8string
    // ------------------------------------------------------------------
    std::cout << "\n=== std::u8string ===" << std::endl;
    std::u8string u8s = u8"C++20 char8_t";
    std::cout << "  Content: " << to_string(u8s) << std::endl;
    std::cout << "  Size:    " << u8s.size() << " code units" << std::endl;
    std::cout << "  Empty?   " << u8s.empty() << std::endl;

    // ------------------------------------------------------------------
    // 4. Multi-byte UTF-8 sequences
    // ------------------------------------------------------------------
    std::cout << "\n=== Multi-byte UTF-8 ===" << std::endl;
    std::u8string emoji = u8"\xC2\xA9";  // copyright sign (2 bytes)
    std::cout << "  Copyright sign bytes: " << emoji.size() << std::endl;

    std::u8string euro = u8"\xE2\x82\xAC";  // euro sign (3 bytes)
    std::cout << "  Euro sign bytes: " << euro.size() << std::endl;

    // ------------------------------------------------------------------
    // 5. Concatenation and operations
    // ------------------------------------------------------------------
    std::cout << "\n=== u8string Operations ===" << std::endl;
    std::u8string greeting = u8"Hello";
    std::u8string world = u8" World";
    std::u8string combined = greeting + world;
    std::cout << "  Concat: " << to_string(combined) << std::endl;
    std::cout << "  Length: " << combined.size() << std::endl;

    auto pos = combined.find(u8"World");
    std::cout << "  'World' found at position: " << pos << std::endl;

    std::u8string sub = combined.substr(6, 5);
    std::cout << "  Substr(6,5): " << to_string(sub) << std::endl;

    // ------------------------------------------------------------------
    // 6. Iterating over code units
    // ------------------------------------------------------------------
    std::cout << "\n=== Iterating Code Units ===" << std::endl;
    std::u8string abc = u8"ABC";
    std::cout << "  Code units of 'ABC':";
    for (char8_t c : abc) {
        std::cout << " " << static_cast<int>(c);
    }
    std::cout << std::endl;

    return 0;
}

/*
Expected output:

=== char8_t Type Properties ===
  sizeof(char8_t):  1
  sizeof(char):     1
  same as char?     0
  same as unsigned char? 0
  is unsigned?      1

=== u8 Literals ===
  u8'A' value: 65
  u8 literal: Hello, UTF-8!

=== std::u8string ===
  Content: C++20 char8_t
  Size:    13 code units
  Empty?   0

=== Multi-byte UTF-8 ===
  Copyright sign bytes: 2
  Euro sign bytes: 3

=== u8string Operations ===
  Concat: Hello World
  Length: 11
  'World' found at position: 6
  Substr(6,5): World

=== Iterating Code Units ===
  Code units of 'ABC': 65 66 67
*/
