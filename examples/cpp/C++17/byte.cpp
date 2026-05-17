// CodeNebula - C++17 Example: std::byte
// Compile: g++ -std=c++17 -Wall -Wextra -o example byte.cpp

// Demonstrates std::byte, a distinct type for raw byte manipulation.
// Unlike char or unsigned char, std::byte only supports bitwise operations,
// preventing accidental arithmetic and improving type safety.

#include <iostream>
#include <cstddef>

int main()
{
    // ------------------------------------------------------------------
    // 1. Creating std::byte values
    // ------------------------------------------------------------------
    std::byte b1{0x3A};  // Braces-only initialization (no implicit conversion)
    std::byte b2{0x0F};
    std::byte zero{0};

    std::cout << "=== Creating std::byte ===" << std::endl;
    std::cout << "  b1 = 0x3A (" << std::to_integer<int>(b1) << ")" << std::endl;
    std::cout << "  b2 = 0x0F (" << std::to_integer<int>(b2) << ")" << std::endl;

    // ------------------------------------------------------------------
    // 2. Bitwise operations (the ONLY operations allowed on std::byte)
    // ------------------------------------------------------------------
    std::byte bor  = b1 | b2;   // OR
    std::byte band = b1 & b2;   // AND
    std::byte bxor = b1 ^ b2;   // XOR
    std::byte bnot = ~b1;       // NOT
    std::byte bshl = b2 << 4;   // Shift left
    std::byte bshr = b1 >> 2;   // Shift right

    std::cout << "\n=== Bitwise Operations ===" << std::endl;
    std::cout << "  b1 | b2  = " << std::to_integer<int>(bor)  << std::endl;
    std::cout << "  b1 & b2  = " << std::to_integer<int>(band) << std::endl;
    std::cout << "  b1 ^ b2  = " << std::to_integer<int>(bxor) << std::endl;
    std::cout << "  ~b1      = " << std::to_integer<int>(bnot) << std::endl;
    std::cout << "  b2 << 4  = " << std::to_integer<int>(bshl) << std::endl;
    std::cout << "  b1 >> 2  = " << std::to_integer<int>(bshr) << std::endl;

    // ------------------------------------------------------------------
    // 3. Compound assignment operators
    // ------------------------------------------------------------------
    std::byte b3{0xFF};
    b3 &= std::byte{0x0F};  // Mask lower nibble
    std::cout << "\n=== Compound Assignment ===" << std::endl;
    std::cout << "  0xFF &= 0x0F -> " << std::to_integer<int>(b3) << std::endl;

    b3 |= std::byte{0xA0};
    std::cout << "  0x0F |= 0xA0 -> " << std::to_integer<int>(b3) << std::endl;

    // ------------------------------------------------------------------
    // 4. Converting back to integer with std::to_integer
    // ------------------------------------------------------------------
    unsigned char uc = std::to_integer<unsigned char>(b1);
    int           iv = std::to_integer<int>(b1);

    std::cout << "\n=== std::to_integer ===" << std::endl;
    std::cout << "  As unsigned char: " << static_cast<int>(uc) << std::endl;
    std::cout << "  As int          : " << iv << std::endl;

    // ------------------------------------------------------------------
    // 5. Comparison
    // ------------------------------------------------------------------
    std::cout << "\n=== Comparison ===" << std::endl;
    std::cout << "  b1 == b2 : " << (b1 == b2 ? "true" : "false") << std::endl;
    std::cout << "  zero == 0: " << (zero == std::byte{0} ? "true" : "false") << std::endl;

    return 0;
}

/*
Expected output:

=== Creating std::byte ===
  b1 = 0x3A (58)
  b2 = 0x0F (15)

=== Bitwise Operations ===
  b1 | b2  = 63
  b1 & b2  = 10
  b1 ^ b2  = 53
  ~b1      = 197
  b2 << 4  = 240
  b1 >> 2  = 14

=== Compound Assignment ===
  0xFF &= 0x0F -> 15
  0x0F |= 0xA0 -> 175

=== std::to_integer ===
  As unsigned char: 58
  As int          : 58

=== Comparison ===
  b1 == b2 : false
  zero == 0: true
*/
