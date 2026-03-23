// CodeNebula - C++11 Example: std::mt19937_64
// Compile: g++ -std=c++11 -Wall -Wextra -o example mt19937_64.cpp

// std::mt19937_64 is the 64-bit variant of the Mersenne Twister.
// It generates 64-bit unsigned integers natively, making it more
// efficient than mt19937 when 64-bit values are needed.

#include <iostream>
#include <random>
#include <vector>
#include <iomanip>
#include <cstdint>

int main() {
    // Create with fixed seed
    std::mt19937_64 gen(42);

    // 64-bit raw values
    std::cout << "First 5 raw 64-bit values (seed=42):" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "  " << gen() << std::endl;
    }

    // Range comparison: 64-bit vs 32-bit
    std::cout << "\nRange comparison:" << std::endl;
    std::cout << "  mt19937    max: " << std::mt19937::max() << std::endl;
    std::cout << "  mt19937_64 max: " << std::mt19937_64::max() << std::endl;

    // Use with distributions
    std::mt19937_64 gen2(100);
    std::uniform_int_distribution<uint64_t> big_dist(0, UINT64_MAX);
    std::cout << "\nLarge random uint64_t values:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        uint64_t val = big_dist(gen2);
        std::cout << "  " << val << " (0x" << std::hex << val << std::dec
                  << ")" << std::endl;
    }

    // 64-bit uniform doubles have better precision
    std::mt19937_64 gen3(200);
    std::uniform_real_distribution<double> real_dist(0.0, 1.0);
    std::cout << "\nHigh-precision doubles [0, 1):" << std::endl;
    std::cout << std::setprecision(17);
    for (int i = 0; i < 5; ++i) {
        std::cout << "  " << real_dist(gen3) << std::endl;
    }
    std::cout << std::setprecision(6);

    // Reproducibility: same seed -> same sequence
    std::mt19937_64 a(999), b(999);
    bool same = true;
    for (int i = 0; i < 100; ++i) {
        if (a() != b()) { same = false; break; }
    }
    std::cout << "\nSame seed reproducibility: " << (same ? "yes" : "no") << std::endl;

    // Discard and state
    std::mt19937_64 gen4(42);
    gen4.discard(1000);
    std::cout << "\nAfter discard(1000): " << gen4() << std::endl;

    // Practical: generating UUIDs (simplified)
    std::mt19937_64 uuid_gen(std::random_device{}());
    uint64_t hi = uuid_gen();
    uint64_t lo = uuid_gen();
    std::cout << "\nPseudo-UUID: " << std::hex << std::setfill('0')
              << std::setw(8) << (hi >> 32) << "-"
              << std::setw(4) << ((hi >> 16) & 0xFFFF) << "-"
              << std::setw(4) << (hi & 0xFFFF) << "-"
              << std::setw(4) << (lo >> 48) << "-"
              << std::setw(12) << (lo & 0xFFFFFFFFFFFFULL)
              << std::dec << std::endl;

    return 0;
}

// Expected output (random values vary for UUID):
// First 5 raw 64-bit values (seed=42):
//   13930160852258120406
//   ...
//
// Range comparison:
//   mt19937    max: 4294967295
//   mt19937_64 max: 18446744073709551615
//
// Large random uint64_t values:
//   <large 64-bit values>
//
// High-precision doubles [0, 1):
//   <17-digit precision values>
//
// Same seed reproducibility: yes
//
// After discard(1000): <deterministic value>
//
// Pseudo-UUID: xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
