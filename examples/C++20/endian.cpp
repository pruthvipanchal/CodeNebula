// CodeNebula - C++20 Example: std::endian
// Compile: g++ -std=c++20 -Wall -Wextra -o example endian.cpp

// std::endian (from <bit>) provides a portable, standard way to detect
// the byte order of the current platform at compile time. No more
// platform-specific macros or runtime tricks.

#include <iostream>
#include <bit>
#include <cstdint>
#include <cstring>
#include <array>

// Detect and print the platform's endianness
void print_endianness() {
    if constexpr (std::endian::native == std::endian::little) {
        std::cout << "Platform is LITTLE-endian\n";
    } else if constexpr (std::endian::native == std::endian::big) {
        std::cout << "Platform is BIG-endian\n";
    } else {
        std::cout << "Platform has MIXED endianness\n";
    }
}

// Show how bytes are arranged in memory for a 32-bit integer
void show_byte_layout(std::uint32_t value) {
    std::array<unsigned char, 4> bytes{};
    std::memcpy(bytes.data(), &value, sizeof(value));

    std::cout << "Value 0x" << std::hex << value << std::dec << " in memory: ";
    for (auto b : bytes) {
        std::cout << "0x" << std::hex << static_cast<int>(b) << " ";
    }
    std::cout << std::dec << "\n";
}

// A byte-swap function that uses endianness info
constexpr std::uint32_t to_big_endian(std::uint32_t value) {
    if constexpr (std::endian::native == std::endian::big) {
        return value;  // already big-endian
    } else {
        // Byte swap for little-endian
        return ((value & 0xFF000000u) >> 24u) |
               ((value & 0x00FF0000u) >>  8u) |
               ((value & 0x0000FF00u) <<  8u) |
               ((value & 0x000000FFu) << 24u);
    }
}

constexpr std::uint16_t swap_bytes_16(std::uint16_t value) {
    return static_cast<std::uint16_t>((value >> 8) | (value << 8));
}

int main() {
    std::cout << "=== std::endian — Byte Order Detection ===\n\n";

    // Detect endianness
    print_endianness();
    std::cout << "\n";

    // Show byte layout in memory
    show_byte_layout(0x01020304);
    show_byte_layout(0xDEADBEEF);
    std::cout << "\n";

    // Endian conversion
    std::uint32_t native_val = 0x01020304;
    std::uint32_t big_val = to_big_endian(native_val);
    std::cout << "Native: 0x" << std::hex << native_val << "\n";
    std::cout << "Big-endian: 0x" << big_val << "\n\n";

    // Compile-time endianness checks
    std::cout << std::dec;
    std::cout << "Compile-time checks:\n";
    std::cout << "  std::endian::little != std::endian::big: "
              << std::boolalpha
              << (std::endian::little != std::endian::big) << "\n";

    constexpr bool is_little = (std::endian::native == std::endian::little);
    constexpr bool is_big    = (std::endian::native == std::endian::big);
    std::cout << "  is_little_endian: " << is_little << "\n";
    std::cout << "  is_big_endian:    " << is_big << "\n";

    // 16-bit byte swap
    std::uint16_t val16 = 0xABCD;
    std::cout << "\n16-bit swap: 0x" << std::hex << val16
              << " -> 0x" << swap_bytes_16(val16) << "\n";

    return 0;
}

// Expected output (on little-endian x86/x64):
// === std::endian — Byte Order Detection ===
//
// Platform is LITTLE-endian
//
// Value 0x1020304 in memory: 0x4 0x3 0x2 0x1
// Value 0xdeadbeef in memory: 0xef 0xbe 0xad 0xde
//
// Native: 0x1020304
// Big-endian: 0x4030201
//
// Compile-time checks:
//   std::endian::little != std::endian::big: true
//   is_little_endian: true
//   is_big_endian:    false
//
// 16-bit swap: 0xabcd -> 0xcdab
