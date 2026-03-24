// CodeNebula - C++20 Example: std::bit_cast
// Compile: g++ -std=c++20 -Wall -Wextra -o example bit_cast.cpp

#include <bit>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <array>

int main() {
    // bit_cast from float to uint32_t - inspect the binary representation
    float f = 3.14f;
    auto bits = std::bit_cast<std::uint32_t>(f);
    std::cout << "float " << f << " as uint32_t: 0x"
              << std::hex << std::setfill('0') << std::setw(8) << bits
              << std::dec << '\n';

    // Round-trip: uint32_t back to float
    float restored = std::bit_cast<float>(bits);
    std::cout << "Restored float: " << restored << '\n';
    std::cout << "Round-trip exact? " << (f == restored ? "yes" : "no") << '\n';

    // bit_cast from double to uint64_t
    double d = 2.718281828;
    auto dbits = std::bit_cast<std::uint64_t>(d);
    std::cout << "\ndouble " << d << " as uint64_t: 0x"
              << std::hex << std::setw(16) << dbits << std::dec << '\n';

    // Examine special floating-point values
    float zero = 0.0f;
    float neg_zero = -0.0f;
    auto zero_bits = std::bit_cast<std::uint32_t>(zero);
    auto neg_zero_bits = std::bit_cast<std::uint32_t>(neg_zero);
    std::cout << "\n+0.0f bits: 0x" << std::hex << std::setw(8) << zero_bits << '\n';
    std::cout << "-0.0f bits: 0x" << std::setw(8) << neg_zero_bits << std::dec << '\n';
    std::cout << "+0 == -0? " << (zero == neg_zero ? "yes" : "no") << '\n';
    std::cout << "Bits equal? " << (zero_bits == neg_zero_bits ? "yes" : "no") << '\n';

    // bit_cast between same-size aggregates
    struct Color {
        std::uint8_t r, g, b, a;
    };

    std::uint32_t packed = 0xFF8040C0;
    auto color = std::bit_cast<Color>(packed);
    std::cout << "\nPacked 0x" << std::hex << packed << std::dec << " as Color:\n"
              << "  R=" << (int)color.r << " G=" << (int)color.g
              << " B=" << (int)color.b << " A=" << (int)color.a << '\n';

    // bit_cast with std::array
    double pi = 3.141592653589793;
    auto bytes = std::bit_cast<std::array<std::uint8_t, 8>>(pi);
    std::cout << "\npi bytes: ";
    for (auto b : bytes) std::cout << std::hex << std::setw(2) << (int)b << ' ';
    std::cout << std::dec << '\n';

    return 0;
}
