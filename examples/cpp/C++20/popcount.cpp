// CodeNebula - C++20 Example: std::popcount
// Compile: g++ -std=c++20 -Wall -Wextra -o example popcount.cpp

#include <bit>
#include <bitset>
#include <cstdint>
#include <iostream>

int main() {
    std::cout << "=== std::popcount - count number of set bits ===\n\n";

    // Basic usage
    for (unsigned i = 0; i <= 15; ++i) {
        std::cout << "popcount(" << std::bitset<4>(i) << " = " << i << ") = "
                  << std::popcount(i) << "\n";
    }

    std::cout << "\n=== Powers of 2 have exactly 1 bit set ===\n";
    for (unsigned p = 0; p <= 10; ++p) {
        unsigned val = 1u << p;
        std::cout << "popcount(" << val << ") = " << std::popcount(val) << "\n";
    }

    std::cout << "\n=== All bits set ===\n";
    std::cout << "popcount(uint8_t  max) = "
              << std::popcount(static_cast<uint8_t>(0xFF)) << "\n";
    std::cout << "popcount(uint16_t max) = "
              << std::popcount(static_cast<uint16_t>(0xFFFF)) << "\n";
    std::cout << "popcount(uint32_t max) = "
              << std::popcount(static_cast<uint32_t>(0xFFFFFFFF)) << "\n";

    std::cout << "\n=== Practical: Hamming distance ===\n";
    // Hamming distance = number of positions where bits differ
    auto hamming = [](unsigned a, unsigned b) { return std::popcount(a ^ b); };

    unsigned x = 0b10110010;
    unsigned y = 0b10011010;
    std::cout << "a = " << std::bitset<8>(x) << "\n";
    std::cout << "b = " << std::bitset<8>(y) << "\n";
    std::cout << "Hamming distance: " << hamming(x, y) << "\n";

    std::cout << "\n=== Practical: permission analysis ===\n";
    uint32_t user_permissions   = 0b11010110;
    uint32_t admin_permissions  = 0b11111111;
    uint32_t guest_permissions  = 0b00000010;

    std::cout << "User permissions  (" << std::bitset<8>(user_permissions)
              << "): " << std::popcount(user_permissions) << " active\n";
    std::cout << "Admin permissions (" << std::bitset<8>(admin_permissions)
              << "): " << std::popcount(admin_permissions) << " active\n";
    std::cout << "Guest permissions (" << std::bitset<8>(guest_permissions)
              << "): " << std::popcount(guest_permissions) << " active\n";

    std::cout << "\n=== Practical: subset counting ===\n";
    // Number of subsets of a set with n elements = 2^n
    // Subsets of size k = C(n,k), iterate by popcount
    unsigned n = 4;
    for (unsigned k = 0; k <= n; ++k) {
        unsigned count = 0;
        for (unsigned mask = 0; mask < (1u << n); ++mask) {
            if (std::popcount(mask) == static_cast<int>(k)) ++count;
        }
        std::cout << "Subsets of {0,1,2,3} with " << k << " elements: " << count << "\n";
    }

    return 0;
}
