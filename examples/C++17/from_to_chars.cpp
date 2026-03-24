// CodeNebula - C++17 Example: std::from_chars / std::to_chars
// Compile: g++ -std=c++17 -Wall -Wextra -o example from_to_chars.cpp

// Demonstrates std::to_chars and std::from_chars for fast, locale-independent
// number-to-string and string-to-number conversion. These avoid the overhead
// of streams and std::stoi/stod, and never allocate memory.

#include <iostream>
#include <charconv>
#include <array>
#include <string>
#include <system_error>
#include <cstring>

int main()
{
    // ------------------------------------------------------------------
    // 1. to_chars: integer to string
    // ------------------------------------------------------------------
    std::cout << "=== to_chars (integers) ===" << std::endl;
    std::array<char, 32> buf{};

    auto [ptr1, ec1] = std::to_chars(buf.data(), buf.data() + buf.size(), 42);
    std::cout << "  42       -> \"" << std::string(buf.data(), ptr1) << "\"" << std::endl;

    auto [ptr2, ec2] = std::to_chars(buf.data(), buf.data() + buf.size(), -12345);
    std::cout << "  -12345   -> \"" << std::string(buf.data(), ptr2) << "\"" << std::endl;

    // ------------------------------------------------------------------
    // 2. to_chars with different bases
    // ------------------------------------------------------------------
    std::cout << "\n=== to_chars (bases) ===" << std::endl;

    auto [ptr3, ec3] = std::to_chars(buf.data(), buf.data() + buf.size(), 255, 16);
    std::cout << "  255 hex  -> \"" << std::string(buf.data(), ptr3) << "\"" << std::endl;

    auto [ptr4, ec4] = std::to_chars(buf.data(), buf.data() + buf.size(), 255, 2);
    std::cout << "  255 bin  -> \"" << std::string(buf.data(), ptr4) << "\"" << std::endl;

    auto [ptr5, ec5] = std::to_chars(buf.data(), buf.data() + buf.size(), 255, 8);
    std::cout << "  255 oct  -> \"" << std::string(buf.data(), ptr5) << "\"" << std::endl;

    // ------------------------------------------------------------------
    // 3. from_chars: string to integer
    // ------------------------------------------------------------------
    std::cout << "\n=== from_chars (integers) ===" << std::endl;

    const char* s1 = "9876";
    int val1 = 0;
    auto [p1, e1] = std::from_chars(s1, s1 + std::strlen(s1), val1);
    std::cout << "  \"9876\"   -> " << val1 << std::endl;

    const char* s2 = "ff";
    int val2 = 0;
    auto [p2, e2] = std::from_chars(s2, s2 + std::strlen(s2), val2, 16);
    std::cout << "  \"ff\" hex -> " << val2 << std::endl;

    // ------------------------------------------------------------------
    // 4. from_chars stops at non-numeric characters
    // ------------------------------------------------------------------
    std::cout << "\n=== Partial Parsing ===" << std::endl;
    const char* s3 = "123abc";
    int val3 = 0;
    auto [p3, e3] = std::from_chars(s3, s3 + std::strlen(s3), val3);
    std::cout << "  \"123abc\" -> " << val3
              << " (stopped at '" << *p3 << "')" << std::endl;

    // ------------------------------------------------------------------
    // 5. Error handling
    // ------------------------------------------------------------------
    std::cout << "\n=== Error Handling ===" << std::endl;

    const char* s4 = "not_a_number";
    int val4 = -1;
    auto [p4, e4] = std::from_chars(s4, s4 + std::strlen(s4), val4);
    if (e4 == std::errc::invalid_argument)
        std::cout << "  \"not_a_number\" -> invalid_argument" << std::endl;

    // Buffer too small
    std::array<char, 2> tiny{};
    auto [p5, e5] = std::to_chars(tiny.data(), tiny.data() + tiny.size(), 99999);
    if (e5 == std::errc::value_too_large)
        std::cout << "  99999 in 2-char buf -> value_too_large" << std::endl;

    return 0;
}

/*
Expected output:

=== to_chars (integers) ===
  42       -> "42"
  -12345   -> "-12345"

=== to_chars (bases) ===
  255 hex  -> "ff"
  255 bin  -> "11111111"
  255 oct  -> "377"

=== from_chars (integers) ===
  "9876"   -> 9876
  "ff" hex -> 255

=== Partial Parsing ===
  "123abc" -> 123 (stopped at 'a')

=== Error Handling ===
  "not_a_number" -> invalid_argument
  99999 in 2-char buf -> value_too_large
*/
