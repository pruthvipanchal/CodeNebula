// CodeNebula - C++20 Example: std::rotl and std::rotr (Bit Rotation)
// Compile: g++ -std=c++20 -Wall -Wextra -o example rotl_rotr.cpp

#include <bit>
#include <bitset>
#include <cstdint>
#include <iostream>

int main() {
    std::cout << "=== std::rotl - rotate bits left ===\n\n";

    uint8_t val = 0b10110001;
    std::cout << "Original:  " << std::bitset<8>(val) << " (0x" << std::hex
              << static_cast<int>(val) << std::dec << ")\n";

    for (int shift = 1; shift <= 8; ++shift) {
        auto result = std::rotl(val, shift);
        std::cout << "rotl(val, " << shift << "): " << std::bitset<8>(result) << "\n";
    }

    std::cout << "\n=== std::rotr - rotate bits right ===\n\n";

    std::cout << "Original:  " << std::bitset<8>(val) << "\n";
    for (int shift = 1; shift <= 8; ++shift) {
        auto result = std::rotr(val, shift);
        std::cout << "rotr(val, " << shift << "): " << std::bitset<8>(result) << "\n";
    }

    std::cout << "\n=== Rotation preserves all bits ===\n";
    uint32_t x = 0xDEADBEEF;
    std::cout << "Original:   0x" << std::hex << x << "\n";
    std::cout << "rotl(x, 8): 0x" << std::rotl(x, 8) << "\n";
    std::cout << "rotr(x, 8): 0x" << std::rotr(x, 8) << "\n";

    // rotl by n == rotr by (width - n)
    std::cout << "rotl(x,12): 0x" << std::rotl(x, 12) << "\n";
    std::cout << "rotr(x,20): 0x" << std::rotr(x, 20) << "\n";
    std::cout << "Equal: " << (std::rotl(x, 12) == std::rotr(x, 20)) << std::dec << "\n";

    std::cout << "\n=== Negative rotation count ===\n";
    // rotl with negative count rotates right and vice versa
    uint8_t v = 0b11000011;
    std::cout << "Original:     " << std::bitset<8>(v) << "\n";
    std::cout << "rotl(v, 2):   " << std::bitset<8>(std::rotl(v, 2)) << "\n";
    std::cout << "rotl(v, -2):  " << std::bitset<8>(std::rotl(v, -2)) << "\n";
    std::cout << "rotr(v, 2):   " << std::bitset<8>(std::rotr(v, 2)) << "\n";
    std::cout << "rotl(-2)==rotr(2): "
              << (std::rotl(v, -2) == std::rotr(v, 2)) << "\n";

    std::cout << "\n=== Practical: simple hash mixing ===\n";
    auto mix = [](uint32_t h) {
        h ^= std::rotr(h, 7);
        h ^= std::rotl(h, 13);
        h ^= std::rotr(h, 11);
        return h;
    };
    for (uint32_t seed : {0u, 1u, 42u, 12345u}) {
        std::cout << "mix(" << seed << ") = " << mix(seed) << "\n";
    }

    std::cout << "\n=== 64-bit rotation ===\n";
    uint64_t big = 0x0123456789ABCDEFuLL;
    std::cout << "Original:     0x" << std::hex << big << "\n";
    std::cout << "rotl(big, 16): 0x" << std::rotl(big, 16) << "\n";
    std::cout << "rotr(big, 16): 0x" << std::rotr(big, 16) << std::dec << "\n";

    return 0;
}
