// CodeNebula - C++20 Example: std::countr_zero and std::countr_one
// Compile: g++ -std=c++20 -Wall -Wextra -o example countr.cpp

#include <bit>
#include <bitset>
#include <cstdint>
#include <iostream>

template <typename T>
void show_countr(T val) {
    constexpr int bits = sizeof(T) * 8;
    std::cout << "  " << std::bitset<bits>(val)
              << " (" << static_cast<uint64_t>(val) << ")"
              << "  countr_zero=" << std::countr_zero(val)
              << "  countr_one=" << std::countr_one(val) << "\n";
}

int main() {
    std::cout << "=== std::countr_zero - count trailing zeros ===\n";
    std::cout << "(Counts consecutive 0-bits from the least significant bit)\n\n";

    std::cout << "uint8_t examples:\n";
    show_countr(static_cast<uint8_t>(0));     // 8 trailing zeros
    show_countr(static_cast<uint8_t>(1));     // 0 trailing zeros
    show_countr(static_cast<uint8_t>(2));     // 1 trailing zero
    show_countr(static_cast<uint8_t>(4));     // 2 trailing zeros
    show_countr(static_cast<uint8_t>(8));     // 3 trailing zeros
    show_countr(static_cast<uint8_t>(12));    // 2 trailing zeros
    show_countr(static_cast<uint8_t>(128));   // 7 trailing zeros

    std::cout << "\n=== std::countr_one - count trailing ones ===\n";
    std::cout << "(Counts consecutive 1-bits from the least significant bit)\n\n";

    std::cout << "uint8_t examples:\n";
    show_countr(static_cast<uint8_t>(0xFF)); // 8 trailing ones
    show_countr(static_cast<uint8_t>(0x0F)); // 4 trailing ones
    show_countr(static_cast<uint8_t>(0x07)); // 3 trailing ones
    show_countr(static_cast<uint8_t>(0x03)); // 2 trailing ones
    show_countr(static_cast<uint8_t>(0x01)); // 1 trailing one
    show_countr(static_cast<uint8_t>(0x00)); // 0 trailing ones

    std::cout << "\n=== 32-bit examples ===\n";
    std::cout << "countr_zero(1u)    = " << std::countr_zero(1u) << "\n";
    std::cout << "countr_zero(16u)   = " << std::countr_zero(16u) << "\n";
    std::cout << "countr_zero(1024u) = " << std::countr_zero(1024u) << "\n";
    std::cout << "countr_one(0xFFu)  = " << std::countr_one(0xFFu) << "\n";

    std::cout << "\n=== Practical: find alignment of address ===\n";
    // Trailing zeros indicate the alignment power
    for (uintptr_t addr : {0x1000uL, 0x1004uL, 0x1008uL, 0x1010uL, 0x1040uL}) {
        auto tz = std::countr_zero(static_cast<unsigned long>(addr));
        std::cout << "Address 0x" << std::hex << addr << std::dec
                  << ": aligned to 2^" << tz << " = " << (1uL << tz) << " bytes\n";
    }

    std::cout << "\n=== Practical: iterate set bits ===\n";
    uint32_t flags = 0b10110100;
    std::cout << "Set bits in " << std::bitset<8>(flags) << ": ";
    uint32_t tmp = flags;
    while (tmp != 0) {
        int pos = std::countr_zero(tmp);
        std::cout << pos << " ";
        tmp &= tmp - 1;  // Clear lowest set bit
    }
    std::cout << "\n";

    return 0;
}
