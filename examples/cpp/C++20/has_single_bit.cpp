// CodeNebula - C++20 Example: std::has_single_bit
// Compile: g++ -std=c++20 -Wall -Wextra -o example has_single_bit.cpp

#include <bit>
#include <cstdint>
#include <iostream>
#include <vector>

int main() {
    std::cout << "=== std::has_single_bit - power of 2 check ===\n";
    std::cout << "(Returns true if exactly one bit is set, i.e., value is a power of 2)\n\n";

    for (unsigned i = 0; i <= 16; ++i) {
        std::cout << "has_single_bit(" << i << ") = "
                  << (std::has_single_bit(i) ? "true" : "false") << "\n";
    }

    std::cout << "\n=== Larger powers of 2 ===\n";
    for (unsigned p = 0; p <= 20; ++p) {
        unsigned val = 1u << p;
        std::cout << "has_single_bit(" << val << ") = "
                  << (std::has_single_bit(val) ? "true" : "false") << "\n";
    }

    std::cout << "\n=== Near powers of 2 ===\n";
    for (unsigned val : {31u, 32u, 33u, 63u, 64u, 65u, 127u, 128u, 129u}) {
        std::cout << "has_single_bit(" << val << ") = "
                  << (std::has_single_bit(val) ? "true" : "false") << "\n";
    }

    std::cout << "\n=== Different unsigned types ===\n";
    std::cout << "uint8_t(128):  " << std::has_single_bit(uint8_t(128)) << "\n";
    std::cout << "uint16_t(256): " << std::has_single_bit(uint16_t(256)) << "\n";
    std::cout << "uint64_t(1<<40): " << std::has_single_bit(uint64_t(1) << 40) << "\n";
    std::cout << "uint64_t(3<<40): " << std::has_single_bit(uint64_t(3) << 40) << "\n";

    std::cout << "\n=== Practical: validate buffer sizes ===\n";
    std::vector<unsigned> sizes = {64, 100, 256, 300, 512, 1000, 1024, 2048, 4096};
    for (auto sz : sizes) {
        if (std::has_single_bit(sz)) {
            std::cout << sz << " bytes: valid (power-of-2 aligned)\n";
        } else {
            std::cout << sz << " bytes: needs rounding to "
                      << std::bit_ceil(sz) << "\n";
        }
    }

    std::cout << "\n=== Practical: texture dimension validation ===\n";
    struct Texture { unsigned w, h; const char* name; };
    Texture textures[] = {{512, 512, "sky"}, {800, 600, "photo"}, {1024, 1024, "tile"}};
    for (const auto& t : textures) {
        bool valid = std::has_single_bit(t.w) && std::has_single_bit(t.h);
        std::cout << t.name << " (" << t.w << "x" << t.h << "): "
                  << (valid ? "GPU-ready" : "needs resize") << "\n";
    }

    return 0;
}
