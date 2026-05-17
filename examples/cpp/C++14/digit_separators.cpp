// CodeNebula - C++14 Example: Digit Separators
// Compile: g++ -std=c++14 -Wall -Wextra -o example digit_separators.cpp

// Demonstrates the apostrophe (') digit separator introduced in C++14.
// The separator is purely visual and ignored by the compiler. Real-world use:
// large constants in financial code, memory sizes, timestamps, IP addresses
// in hex, and any context where readability of long numbers matters.

#include <iostream>
#include <iomanip>
#include <cstdint>

int main()
{
    // ------------------------------------------------------------------
    // 1. Decimal integer separators (thousands grouping)
    // ------------------------------------------------------------------
    int million      = 1'000'000;
    long long billion = 1'000'000'000LL;
    int population    = 8'045'311'447;

    std::cout << "=== Decimal Separators ===" << std::endl;
    std::cout << "  1'000'000          = " << million << std::endl;
    std::cout << "  1'000'000'000      = " << billion << std::endl;
    std::cout << "  8'045'311'447      = " << population << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Hexadecimal separators (byte grouping)
    // ------------------------------------------------------------------
    uint32_t color_rgba   = 0xFF'80'00'FF;    // orange, full alpha
    uint64_t mac_address  = 0xAA'BB'CC'DD'EE'FF;

    std::cout << "=== Hexadecimal Separators ===" << std::endl;
    std::cout << std::hex << std::uppercase;
    std::cout << "  0xFF'80'00'FF      = 0x" << color_rgba << std::endl;
    std::cout << "  MAC address        = 0x" << mac_address << std::endl;
    std::cout << std::dec;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Binary separators (nibble or byte grouping)
    // ------------------------------------------------------------------
    uint8_t  status_reg = 0b1010'0011;       // nibble-grouped
    uint16_t opcode     = 0b0000'1111'1010'0101;

    std::cout << "=== Binary Separators ===" << std::endl;
    std::cout << "  0b1010'0011             = " << static_cast<int>(status_reg) << std::endl;
    std::cout << "  0b0000'1111'1010'0101   = " << opcode << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Floating-point separators
    // ------------------------------------------------------------------
    double avogadro   = 6.022'140'76e23;
    double speed_of_light = 299'792'458.0;
    float  price      = 1'234'567.89f;

    std::cout << "=== Floating-Point Separators ===" << std::endl;
    std::cout << std::setprecision(10);
    std::cout << "  Avogadro's number  = " << avogadro << std::endl;
    std::cout << "  Speed of light     = " << std::fixed << speed_of_light << " m/s" << std::endl;
    std::cout << std::setprecision(2) << std::fixed;
    std::cout << "  Price              = " << price << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Octal separators
    // ------------------------------------------------------------------
    int file_perms = 0'755;   // rwxr-xr-x
    int other_perm = 0'644;   // rw-r--r--

    std::cout << "=== Octal Separators ===" << std::endl;
    std::cout << std::oct;
    std::cout << "  0'755 (octal) = 0" << file_perms << std::endl;
    std::cout << "  0'644 (octal) = 0" << other_perm << std::endl;
    std::cout << std::dec;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 6. Proof: separators are purely cosmetic
    // ------------------------------------------------------------------
    std::cout << "=== Separators are Cosmetic ===" << std::endl;
    std::cout << std::boolalpha;
    std::cout << "  1000000 == 1'000'000 ? "
              << (1000000 == 1'000'000) << std::endl;
    std::cout << "  0xFF == 0xF'F        ? "
              << (0xFF == 0xF'F) << std::endl;

    return 0;
}

/*
Expected output:

=== Decimal Separators ===
  1'000'000          = 1000000
  1'000'000'000      = 1000000000
  8'045'311'447      = -249655849

=== Hexadecimal Separators ===
  0xFF'80'00'FF      = 0xFF8000FF
  MAC address        = 0xAABBCCDDEEFF

=== Binary Separators ===
  0b1010'0011             = 163
  0b0000'1111'1010'0101   = 4005

=== Floating-Point Separators ===
  Avogadro's number  = 6.02214076e+23
  Speed of light     = 299792458.0000000000 m/s
  Price              = 1234567.88

=== Octal Separators ===
  0'755 (octal) = 0755
  0'644 (octal) = 0644

=== Separators are Cosmetic ===
  1000000 == 1'000'000 ? true
  0xFF == 0xF'F        ? true
*/
