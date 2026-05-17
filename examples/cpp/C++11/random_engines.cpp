// CodeNebula - C++11 Example: Random Engines (linear_congruential, subtract_with_carry, adaptors)
// Compile: g++ -std=c++11 -Wall -Wextra -o example random_engines.cpp

// C++11 provides three engine families and two adaptors. Each offers
// different trade-offs in speed, quality, and state size. The predefined
// typedefs (minstd_rand, ranlux24, etc.) are ready to use.

#include <iostream>
#include <random>
#include <iomanip>
#include <vector>

// Helper: print 5 values from any engine
template<typename Engine>
void show_values(const char* name, Engine eng) {
    std::cout << name << ": ";
    for (int i = 0; i < 5; ++i) {
        std::cout << eng() << " ";
    }
    std::cout << std::endl;
}

int main() {
    const unsigned seed = 42;

    // === Linear Congruential Engines ===
    // Formula: x(n+1) = (a * x(n) + c) mod m
    // Fast, small state (single integer), lower quality
    std::cout << "=== Linear Congruential ===" << std::endl;
    show_values("minstd_rand0", std::minstd_rand0(seed));
    show_values("minstd_rand ", std::minstd_rand(seed));

    // Custom linear congruential engine
    using my_lcg = std::linear_congruential_engine<
        unsigned long, 16807, 0, 2147483647>;
    show_values("custom LCG   ", my_lcg(seed));

    // === Subtract-with-Carry Engines ===
    // Lagged Fibonacci variant; larger state, better quality
    std::cout << "\n=== Subtract-with-Carry ===" << std::endl;

    // ranlux24_base: underlying engine for ranlux24
    std::ranlux24_base rwc24(seed);
    std::cout << "ranlux24_base: ";
    for (int i = 0; i < 5; ++i) std::cout << rwc24() << " ";
    std::cout << std::endl;

    // ranlux48_base: 48-bit subtract_with_carry
    std::ranlux48_base rwc48(seed);
    std::cout << "ranlux48_base: ";
    for (int i = 0; i < 5; ++i) std::cout << rwc48() << " ";
    std::cout << std::endl;

    // === Discard Block Adaptor ===
    // Improves quality by generating P values and keeping R
    std::cout << "\n=== Discard Block Adaptor ===" << std::endl;
    std::ranlux24 rl24(seed);  // discard_block_engine<ranlux24_base, 223, 23>
    std::cout << "ranlux24: ";
    for (int i = 0; i < 5; ++i) std::cout << rl24() << " ";
    std::cout << std::endl;

    std::ranlux48 rl48(seed);  // discard_block_engine<ranlux48_base, 389, 11>
    std::cout << "ranlux48: ";
    for (int i = 0; i < 5; ++i) std::cout << rl48() << " ";
    std::cout << std::endl;

    // === Shuffle Order Adaptor ===
    // Maintains a table of K values, outputs randomly selected entries
    std::cout << "\n=== Shuffle Order Adaptor ===" << std::endl;
    std::knuth_b kb(seed);  // shuffle_order_engine<minstd_rand0, 256>
    std::cout << "knuth_b: ";
    for (int i = 0; i < 5; ++i) std::cout << kb() << " ";
    std::cout << std::endl;

    // === Comparison: distribution quality ===
    std::cout << "\n=== Distribution Test [0,9] histogram ===" << std::endl;
    std::minstd_rand lcg(seed);
    std::uniform_int_distribution<int> dist(0, 9);
    std::vector<int> counts(10, 0);
    for (int i = 0; i < 10000; ++i) ++counts[dist(lcg)];
    for (int i = 0; i < 10; ++i) {
        std::cout << "  " << i << ": " << std::setw(4) << counts[i]
                  << " " << std::string(counts[i] / 100, '#') << std::endl;
    }

    return 0;
}

// Expected output (exact values depend on seed):
// === Linear Congruential ===
// minstd_rand0: <5 values>
// minstd_rand : <5 values>
// custom LCG   : <5 values>
//
// === Subtract-with-Carry ===
// ranlux24_base: <5 values>
// ranlux48_base: <5 values>
//
// === Discard Block Adaptor ===
// ranlux24: <5 values>
// ranlux48: <5 values>
//
// === Shuffle Order Adaptor ===
// knuth_b: <5 values>
//
// === Distribution Test [0,9] histogram ===
//   0: ~1000 ##########
//   1: ~1000 ##########
//   ...
