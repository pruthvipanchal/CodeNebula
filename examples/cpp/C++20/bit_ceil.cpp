// CodeNebula - C++20 Example: std::bit_ceil
// Compile: g++ -std=c++20 -Wall -Wextra -o example bit_ceil.cpp

#include <bit>
#include <cstdint>
#include <iostream>

int main() {
    std::cout << "=== std::bit_ceil - smallest power of 2 >= value ===\n\n";

    // bit_ceil returns the smallest power of 2 not less than the input
    std::cout << "bit_ceil(0) = " << std::bit_ceil(0u) << "\n";
    std::cout << "bit_ceil(1) = " << std::bit_ceil(1u) << "\n";
    std::cout << "bit_ceil(2) = " << std::bit_ceil(2u) << "\n";
    std::cout << "bit_ceil(3) = " << std::bit_ceil(3u) << "\n";
    std::cout << "bit_ceil(4) = " << std::bit_ceil(4u) << "\n";
    std::cout << "bit_ceil(5) = " << std::bit_ceil(5u) << "\n";
    std::cout << "bit_ceil(7) = " << std::bit_ceil(7u) << "\n";
    std::cout << "bit_ceil(8) = " << std::bit_ceil(8u) << "\n";
    std::cout << "bit_ceil(9) = " << std::bit_ceil(9u) << "\n";

    std::cout << "\n=== Powers of 2 stay unchanged ===\n";
    for (unsigned i = 1; i <= 256; i *= 2) {
        std::cout << "bit_ceil(" << i << ") = " << std::bit_ceil(i) << "\n";
    }

    std::cout << "\n=== Different unsigned types ===\n";
    std::cout << "uint8_t:  bit_ceil(100) = "
              << static_cast<int>(std::bit_ceil(static_cast<uint8_t>(100))) << "\n";
    std::cout << "uint16_t: bit_ceil(1000) = "
              << std::bit_ceil(static_cast<uint16_t>(1000)) << "\n";
    std::cout << "uint32_t: bit_ceil(1000000) = "
              << std::bit_ceil(static_cast<uint32_t>(1000000)) << "\n";
    std::cout << "uint64_t: bit_ceil(1000000000) = "
              << std::bit_ceil(static_cast<uint64_t>(1000000000)) << "\n";

    std::cout << "\n=== Practical: buffer size rounding ===\n";
    unsigned requested_sizes[] = {100, 250, 500, 1000, 2000, 4096, 5000};
    for (auto size : requested_sizes) {
        auto aligned = std::bit_ceil(size);
        std::cout << "Requested: " << size
                  << " -> Allocated: " << aligned
                  << " (wasted: " << (aligned - size) << ")\n";
    }

    std::cout << "\n=== Practical: hash table sizing ===\n";
    unsigned element_count = 750;
    // Round up to power of 2 for efficient modulo via bitmask
    unsigned table_size = std::bit_ceil(element_count);
    unsigned mask = table_size - 1;
    std::cout << "Elements: " << element_count << "\n";
    std::cout << "Table size: " << table_size << "\n";
    std::cout << "Bitmask: 0x" << std::hex << mask << std::dec << "\n";
    std::cout << "Hash(42) % table = " << (42u & mask) << "\n";

    return 0;
}
