// CodeNebula - C++11 Example: conditional
// Compile: g++ -std=c++11 -Wall -Wextra -o example conditional.cpp

// Demonstrates std::conditional for compile-time type selection.
// conditional<B, T, F>::type is T if B is true, F otherwise.

#include <iostream>
#include <type_traits>
#include <cstdint>

int main() {
    std::cout << "=== std::conditional ===" << std::endl;

    // Choose type based on compile-time condition
    using SmallInt = std::conditional<(sizeof(int) >= 4), int, long>::type;
    using BigNum = std::conditional<true, double, int>::type;
    using OtherNum = std::conditional<false, double, int>::type;

    static_assert(std::is_same<BigNum, double>::value, "true selects first");
    static_assert(std::is_same<OtherNum, int>::value, "false selects second");

    std::cout << "SmallInt size: " << sizeof(SmallInt) << " bytes" << std::endl;
    std::cout << "BigNum is double: " << std::is_same<BigNum, double>::value << std::endl;
    std::cout << "OtherNum is int:  " << std::is_same<OtherNum, int>::value << std::endl;

    // Platform-adaptive type selection
    using FastType = std::conditional<(sizeof(void*) == 8),
                                      uint64_t, uint32_t>::type;
    std::cout << "\nPointer size: " << sizeof(void*) << " bytes" << std::endl;
    std::cout << "FastType size: " << sizeof(FastType) << " bytes" << std::endl;

    // Nested conditional for multi-way selection
    using Sized = std::conditional<(sizeof(int) == 1), int8_t,
                  std::conditional<(sizeof(int) == 2), int16_t,
                  std::conditional<(sizeof(int) == 4), int32_t,
                                                       int64_t>::type>::type>::type;
    std::cout << "Sized type size: " << sizeof(Sized) << " bytes" << std::endl;

    static_assert(sizeof(Sized) == sizeof(int), "Sized matches int size");

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output (64-bit platform):
// === std::conditional ===
// SmallInt size: 4 bytes
// BigNum is double: 1
// OtherNum is int:  1
//
// Pointer size: 8 bytes
// FastType size: 8 bytes
// Sized type size: 4 bytes
//
// All checks passed!
