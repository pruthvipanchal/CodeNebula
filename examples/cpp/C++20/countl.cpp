// CodeNebula - C++20 Example: std::countl_zero and std::countl_one
// Compile: g++ -std=c++20 -Wall -Wextra -o example countl.cpp

#include <bit>
#include <bitset>
#include <cstdint>
#include <iostream>

template <typename T>
void show_countl(T val) {
    constexpr int bits = sizeof(T) * 8;
    std::cout << "  " << std::bitset<bits>(val)
              << " (" << static_cast<uint64_t>(val) << ")"
              << "  countl_zero=" << std::countl_zero(val)
              << "  countl_one=" << std::countl_one(val) << "\n";
}

int main() {
    std::cout << "=== std::countl_zero - count leading zeros ===\n";
    std::cout << "(Counts consecutive 0-bits from the most significant bit)\n\n";

    // 8-bit examples for clarity
    std::cout << "uint8_t examples:\n";
    show_countl(static_cast<uint8_t>(0));     // 8 leading zeros
    show_countl(static_cast<uint8_t>(1));     // 7 leading zeros
    show_countl(static_cast<uint8_t>(2));     // 6 leading zeros
    show_countl(static_cast<uint8_t>(127));   // 1 leading zero
    show_countl(static_cast<uint8_t>(128));   // 0 leading zeros
    show_countl(static_cast<uint8_t>(255));   // 0 leading zeros

    std::cout << "\n=== std::countl_one - count leading ones ===\n";
    std::cout << "(Counts consecutive 1-bits from the most significant bit)\n\n";

    std::cout << "uint8_t examples:\n";
    show_countl(static_cast<uint8_t>(0xFF)); // 8 leading ones
    show_countl(static_cast<uint8_t>(0xFE)); // 7 leading ones
    show_countl(static_cast<uint8_t>(0xF0)); // 4 leading ones
    show_countl(static_cast<uint8_t>(0xC0)); // 2 leading ones
    show_countl(static_cast<uint8_t>(0x80)); // 1 leading one
    show_countl(static_cast<uint8_t>(0x00)); // 0 leading ones

    std::cout << "\n=== 32-bit examples ===\n";
    std::cout << "countl_zero(0u)          = " << std::countl_zero(0u) << "\n";
    std::cout << "countl_zero(1u)          = " << std::countl_zero(1u) << "\n";
    std::cout << "countl_zero(0x7FFFFFFFu) = " << std::countl_zero(0x7FFFFFFFu) << "\n";
    std::cout << "countl_zero(0xFFFFFFFFu) = " << std::countl_zero(0xFFFFFFFFu) << "\n";

    std::cout << "\n=== Practical: fast log2 ===\n";
    for (unsigned v : {1u, 2u, 4u, 8u, 16u, 100u, 1024u}) {
        int log2 = 31 - std::countl_zero(v);
        std::cout << "floor(log2(" << v << ")) = " << log2 << "\n";
    }

    std::cout << "\n=== Practical: subnet mask validation ===\n";
    // Valid subnet masks have all 1s followed by all 0s
    uint32_t masks[] = {0xFFFFFF00, 0xFFFFF000, 0xFFFF0000, 0xFFF0FF00};
    for (auto mask : masks) {
        int ones = std::countl_one(mask);
        int zeros = std::countl_zero(static_cast<uint32_t>(~mask));
        bool valid = (ones + (32 - ones)) == 32 && ones == zeros;
        std::cout << "Mask 0x" << std::hex << mask << std::dec
                  << ": leading ones=" << ones
                  << " valid=" << (valid ? "yes" : "no") << "\n";
    }

    return 0;
}
