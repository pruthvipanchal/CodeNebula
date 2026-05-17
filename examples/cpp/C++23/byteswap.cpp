// CodeNebula - C++23 Example: std::byteswap
// Compile: g++ -std=c++23 -Wall -Wextra -o example byteswap.cpp
// Note: Requires GCC 13+ / Clang 17+

#include <bit>
#include <cstdint>
#include <iomanip>
#include <iostream>

// std::byteswap reverses the bytes of an integral type.
// Useful for endian conversion (e.g., network byte order).

template <typename T>
void show_swap(const char* label, T value) {
    T swapped = std::byteswap(value);
    std::cout << label << ":\n"
              << "  Original: 0x" << std::hex << std::setfill('0')
              << std::setw(sizeof(T) * 2) << +value << "\n"
              << "  Swapped:  0x" << std::setw(sizeof(T) * 2) << +swapped
              << std::dec << "\n";
}

int main() {
    std::cout << "=== std::byteswap endian conversion ===\n\n";

    // 16-bit swap
    std::uint16_t port = 0x5000;  // Port 20480
    std::cout << "16-bit swap:\n";
    std::cout << "  Port host order:    0x" << std::hex << port << std::dec
              << " (" << port << ")\n";
    auto net_port = std::byteswap(port);
    std::cout << "  Port network order: 0x" << std::hex << net_port << std::dec
              << " (" << net_port << ")\n\n";

    // 32-bit swap (e.g., IPv4 address)
    std::uint32_t ipv4 = 0xC0A80001;  // 192.168.0.1
    auto swapped32 = std::byteswap(ipv4);
    std::cout << "32-bit swap (IPv4):\n"
              << "  Original: 0x" << std::hex << std::setfill('0')
              << std::setw(8) << ipv4 << "\n"
              << "  Swapped:  0x" << std::setw(8) << swapped32
              << std::dec << "\n\n";

    // 64-bit swap
    std::uint64_t val64 = 0x0102030405060708ULL;
    auto swapped64 = std::byteswap(val64);
    std::cout << "64-bit swap:\n"
              << "  Original: 0x" << std::hex << std::setfill('0')
              << std::setw(16) << val64 << "\n"
              << "  Swapped:  0x" << std::setw(16) << swapped64
              << std::dec << "\n\n";

    // Double-swap round-trip identity
    auto round_trip = std::byteswap(std::byteswap(val64));
    std::cout << "Double-swap round-trip matches: "
              << (round_trip == val64 ? "yes" : "no") << "\n";

    // Endian detection
    if constexpr (std::endian::native == std::endian::little) {
        std::cout << "System is little-endian\n";
    } else {
        std::cout << "System is big-endian\n";
    }

    return 0;
}

// Expected output (on little-endian system):
// === std::byteswap endian conversion ===
//
// 16-bit swap:
//   Port host order:    0x5000 (20480)
//   Port network order: 0x50 (80)
//
// 32-bit swap (IPv4):
//   Original: 0xc0a80001
//   Swapped:  0x0100a8c0
//
// 64-bit swap:
//   Original: 0x0102030405060708
//   Swapped:  0x0807060504030201
//
// Double-swap round-trip matches: yes
// System is little-endian
