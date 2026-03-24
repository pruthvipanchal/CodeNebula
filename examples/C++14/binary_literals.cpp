// CodeNebula - C++14 Example: Binary Literals
// Compile: g++ -std=c++14 -Wall -Wextra -o example binary_literals.cpp

// Demonstrates the 0b (or 0B) prefix for binary literals introduced in C++14.
// Real-world use: hardware register manipulation, bitmask definitions,
// network protocol flags, and any code where bit patterns matter.

#include <iostream>
#include <bitset>
#include <cstdint>

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic binary literals
    // ------------------------------------------------------------------
    auto byte_val  = 0b11001010;    // 202 in decimal
    auto nibble    = 0b1111;        // 15
    auto single    = 0b1;           // 1
    auto zero      = 0b0;           // 0

    std::cout << "=== Basic Binary Literals ===" << std::endl;
    std::cout << "  0b11001010 = " << byte_val << std::endl;
    std::cout << "  0b1111     = " << nibble << std::endl;
    std::cout << "  0b1        = " << single << std::endl;
    std::cout << "  0b0        = " << zero << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Hardware register flags (e.g., SPI control register)
    // ------------------------------------------------------------------
    constexpr uint8_t SPI_ENABLE    = 0b00000001;   // bit 0
    constexpr uint8_t SPI_MASTER    = 0b00000100;   // bit 2
    constexpr uint8_t SPI_CPOL      = 0b00001000;   // bit 3
    constexpr uint8_t SPI_CPHA      = 0b00010000;   // bit 4
    constexpr uint8_t SPI_SPEED_DIV = 0b01100000;   // bits 5-6

    uint8_t spi_config = SPI_ENABLE | SPI_MASTER | SPI_CPOL;

    std::cout << "=== Hardware Register Flags ===" << std::endl;
    std::cout << "  SPI_ENABLE    : " << std::bitset<8>(SPI_ENABLE) << std::endl;
    std::cout << "  SPI_MASTER    : " << std::bitset<8>(SPI_MASTER) << std::endl;
    std::cout << "  SPI_CPOL      : " << std::bitset<8>(SPI_CPOL) << std::endl;
    std::cout << "  SPI_CPHA      : " << std::bitset<8>(SPI_CPHA) << std::endl;
    std::cout << "  SPI_SPEED_DIV : " << std::bitset<8>(SPI_SPEED_DIV) << std::endl;
    std::cout << "  Combined cfg  : " << std::bitset<8>(spi_config)
              << " (decimal " << static_cast<int>(spi_config) << ")" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Bitmask operations with binary literals
    // ------------------------------------------------------------------
    uint8_t permissions = 0b00000000;
    constexpr uint8_t READ    = 0b00000100;  // r bit
    constexpr uint8_t WRITE   = 0b00000010;  // w bit
    constexpr uint8_t EXECUTE = 0b00000001;  // x bit

    permissions |= READ | WRITE;    // grant read + write

    std::cout << "=== File Permission Bitmasks ===" << std::endl;
    std::cout << "  READ    : " << std::bitset<3>(READ) << std::endl;
    std::cout << "  WRITE   : " << std::bitset<3>(WRITE) << std::endl;
    std::cout << "  EXECUTE : " << std::bitset<3>(EXECUTE) << std::endl;
    std::cout << "  Current : " << std::bitset<3>(permissions)
              << " (rw-)" << std::endl;

    permissions |= EXECUTE;
    std::cout << "  +exec   : " << std::bitset<3>(permissions)
              << " (rwx)" << std::endl;

    permissions &= ~WRITE;
    std::cout << "  -write  : " << std::bitset<3>(permissions)
              << " (r-x)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Comparing with other bases
    // ------------------------------------------------------------------
    std::cout << "=== Same Value in Different Bases ===" << std::endl;
    std::cout << "  Binary : 0b11111111 = " << 0b11111111 << std::endl;
    std::cout << "  Octal  : 0377       = " << 0377 << std::endl;
    std::cout << "  Decimal: 255        = " << 255 << std::endl;
    std::cout << "  Hex    : 0xFF       = " << 0xFF << std::endl;

    return 0;
}

/*
Expected output:

=== Basic Binary Literals ===
  0b11001010 = 202
  0b1111     = 15
  0b1        = 1
  0b0        = 0

=== Hardware Register Flags ===
  SPI_ENABLE    : 00000001
  SPI_MASTER    : 00000100
  SPI_CPOL      : 00001000
  SPI_CPHA      : 00010000
  SPI_SPEED_DIV : 01100000
  Combined cfg  : 00001101 (decimal 13)

=== File Permission Bitmasks ===
  READ    : 100
  WRITE   : 010
  EXECUTE : 001
  Current : 110 (rw-)
  +exec   : 111 (rwx)
  -write  : 101 (r-x)

=== Same Value in Different Bases ===
  Binary : 0b11111111 = 255
  Octal  : 0377       = 255
  Decimal: 255        = 255
  Hex    : 0xFF       = 255
*/
