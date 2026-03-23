// CodeNebula - C++11 Example: make_signed_unsigned
// Compile: g++ -std=c++11 -Wall -Wextra -o example make_signed_unsigned.cpp

// Demonstrates std::make_signed and std::make_unsigned to convert
// between signed and unsigned variants of integer types.

#include <iostream>
#include <type_traits>
#include <cstdint>

int main() {
    std::cout << "=== std::make_signed / std::make_unsigned ===" << std::endl;

    // make_unsigned: signed -> unsigned
    using UnsignedInt = std::make_unsigned<int>::type;
    using UnsignedChar = std::make_unsigned<char>::type;
    using UnsignedLong = std::make_unsigned<long long>::type;

    static_assert(std::is_same<UnsignedInt, unsigned int>::value, "int -> unsigned int");
    static_assert(std::is_same<UnsignedLong, unsigned long long>::value, "ll -> ull");

    std::cout << "make_unsigned<int> is unsigned int:            "
              << std::is_same<UnsignedInt, unsigned int>::value << std::endl;
    std::cout << "make_unsigned<char> is unsigned char:          "
              << std::is_same<UnsignedChar, unsigned char>::value << std::endl;
    std::cout << "make_unsigned<long long> is unsigned long long: "
              << std::is_same<UnsignedLong, unsigned long long>::value << std::endl;

    // make_signed: unsigned -> signed
    using SignedUint = std::make_signed<unsigned int>::type;
    using SignedSize = std::make_signed<size_t>::type;

    static_assert(std::is_same<SignedUint, int>::value, "unsigned int -> int");

    std::cout << "\nmake_signed<unsigned int> is int: "
              << std::is_same<SignedUint, int>::value << std::endl;
    std::cout << "make_signed<size_t> is signed:    "
              << std::is_signed<SignedSize>::value << std::endl;

    // Practical: safe conversion
    unsigned int big = 4000000000u;
    auto signed_val = static_cast<std::make_signed<decltype(big)>::type>(big);
    std::cout << "\nunsigned: " << big << std::endl;
    std::cout << "signed:   " << signed_val << " (overflow expected)" << std::endl;

    // Size is preserved
    std::cout << "\nsizeof(int): " << sizeof(int)
              << " == sizeof(make_unsigned<int>): "
              << sizeof(std::make_unsigned<int>::type) << std::endl;

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::make_signed / std::make_unsigned ===
// make_unsigned<int> is unsigned int:            1
// make_unsigned<char> is unsigned char:          1
// make_unsigned<long long> is unsigned long long: 1
//
// make_signed<unsigned int> is int: 1
// make_signed<size_t> is signed:    1
//
// unsigned: 4000000000
// signed:   -294967296 (overflow expected)
//
// sizeof(int): 4 == sizeof(make_unsigned<int>): 4
//
// All checks passed!
