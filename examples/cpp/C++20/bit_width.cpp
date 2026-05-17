// CodeNebula - C++20 Example: std::bit_width
// Compile: g++ -std=c++20 -Wall -Wextra -o example bit_width.cpp

#include <bit>
#include <cstdint>
#include <iostream>

int main() {
    std::cout << "=== std::bit_width - minimum bits needed to represent value ===\n\n";

    // bit_width(x) returns floor(log2(x)) + 1 for x > 0, or 0 for x == 0
    // Equivalent to: the position of the highest set bit (1-indexed)

    std::cout << "bit_width(0) = " << std::bit_width(0u) << "\n";
    std::cout << "bit_width(1) = " << std::bit_width(1u) << "  (1 in binary: 1)\n";
    std::cout << "bit_width(2) = " << std::bit_width(2u) << "  (2 in binary: 10)\n";
    std::cout << "bit_width(3) = " << std::bit_width(3u) << "  (3 in binary: 11)\n";
    std::cout << "bit_width(4) = " << std::bit_width(4u) << "  (4 in binary: 100)\n";
    std::cout << "bit_width(7) = " << std::bit_width(7u) << "  (7 in binary: 111)\n";
    std::cout << "bit_width(8) = " << std::bit_width(8u) << "  (8 in binary: 1000)\n";
    std::cout << "bit_width(255) = " << std::bit_width(255u) << " (255 in binary: 11111111)\n";
    std::cout << "bit_width(256) = " << std::bit_width(256u) << " (256 in binary: 100000000)\n";

    std::cout << "\n=== Powers of 2 ===\n";
    for (unsigned i = 1; i <= 1024; i *= 2) {
        std::cout << "bit_width(" << i << ") = " << std::bit_width(i) << "\n";
    }

    std::cout << "\n=== Different types ===\n";
    std::cout << "uint8_t(200):  " << std::bit_width(static_cast<uint8_t>(200)) << " bits\n";
    std::cout << "uint16_t(1000): " << std::bit_width(static_cast<uint16_t>(1000)) << " bits\n";
    std::cout << "uint32_t(1M):  " << std::bit_width(1000000u) << " bits\n";
    std::cout << "uint64_t(1T):  " << std::bit_width(uint64_t(1000000000000)) << " bits\n";

    std::cout << "\n=== Practical: minimum bits for encoding ===\n";
    unsigned values[] = {10, 100, 1000, 10000, 100000, 1000000};
    for (auto max_val : values) {
        auto bits = std::bit_width(max_val);
        std::cout << "Values 0.." << max_val << " need " << bits << " bits"
                  << " (max representable: " << ((1u << bits) - 1) << ")\n";
    }

    std::cout << "\n=== Practical: tree depth calculation ===\n";
    unsigned node_counts[] = {1, 3, 7, 15, 31, 100, 1000};
    for (auto n : node_counts) {
        auto depth = std::bit_width(n);
        std::cout << "Complete binary tree with " << n
                  << " nodes: depth = " << depth << "\n";
    }

    return 0;
}
