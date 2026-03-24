// CodeNebula - C++20 Example: std::bit_floor
// Compile: g++ -std=c++20 -Wall -Wextra -o example bit_floor.cpp

#include <bit>
#include <cstdint>
#include <iostream>

int main() {
    std::cout << "=== std::bit_floor - largest power of 2 <= value ===\n\n";

    // bit_floor returns the largest power of 2 not greater than the input
    // Returns 0 if input is 0
    std::cout << "bit_floor(0) = " << std::bit_floor(0u) << "\n";
    std::cout << "bit_floor(1) = " << std::bit_floor(1u) << "\n";
    std::cout << "bit_floor(2) = " << std::bit_floor(2u) << "\n";
    std::cout << "bit_floor(3) = " << std::bit_floor(3u) << "\n";
    std::cout << "bit_floor(4) = " << std::bit_floor(4u) << "\n";
    std::cout << "bit_floor(5) = " << std::bit_floor(5u) << "\n";
    std::cout << "bit_floor(7) = " << std::bit_floor(7u) << "\n";
    std::cout << "bit_floor(8) = " << std::bit_floor(8u) << "\n";
    std::cout << "bit_floor(9) = " << std::bit_floor(9u) << "\n";

    std::cout << "\n=== Range of values ===\n";
    for (unsigned v = 1; v <= 20; ++v) {
        std::cout << "bit_floor(" << v << ") = " << std::bit_floor(v) << "\n";
    }

    std::cout << "\n=== Different unsigned types ===\n";
    std::cout << "uint8_t:  bit_floor(200) = "
              << static_cast<int>(std::bit_floor(static_cast<uint8_t>(200))) << "\n";
    std::cout << "uint16_t: bit_floor(50000) = "
              << std::bit_floor(static_cast<uint16_t>(50000)) << "\n";
    std::cout << "uint64_t: bit_floor(1000000000) = "
              << std::bit_floor(static_cast<uint64_t>(1000000000)) << "\n";

    std::cout << "\n=== Practical: largest aligned block ===\n";
    unsigned memory_sizes[] = {100, 300, 500, 1000, 2048, 3000, 4096};
    for (auto size : memory_sizes) {
        auto block = std::bit_floor(size);
        std::cout << "Available: " << size
                  << " -> Largest aligned block: " << block
                  << " (remainder: " << (size - block) << ")\n";
    }

    std::cout << "\n=== Practical: texture mipmap levels ===\n";
    unsigned texture_width = 300;
    std::cout << "Texture width: " << texture_width << "\n";
    std::cout << "Mipmap levels (powers of 2):\n";
    unsigned level = std::bit_floor(texture_width);
    int mip = 0;
    while (level > 0) {
        std::cout << "  Level " << mip++ << ": " << level << "x" << level << "\n";
        level /= 2;
    }

    return 0;
}
