// CodeNebula - C++11 Example: std::mt19937 Mersenne Twister
// Compile: g++ -std=c++11 -Wall -Wextra -o example mt19937.cpp

// std::mt19937 is a 32-bit Mersenne Twister pseudo-random number engine
// with a period of 2^19937-1. It offers excellent quality randomness
// and is the most commonly used PRNG in C++11.

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <iomanip>

int main() {
    // Create with a fixed seed (reproducible results)
    std::mt19937 gen(42);

    // Raw output: 32-bit unsigned integers
    std::cout << "First 5 raw values (seed=42):" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "  " << gen() << std::endl;
    }

    // Properties
    std::cout << "\nEngine properties:" << std::endl;
    std::cout << "  min: " << std::mt19937::min() << std::endl;
    std::cout << "  max: " << std::mt19937::max() << std::endl;

    // Discard: skip N values efficiently
    std::mt19937 gen2(42);
    gen2.discard(5);  // skip first 5 values
    std::cout << "\nAfter discard(5), next value: " << gen2() << std::endl;

    // Use with distributions
    std::mt19937 gen3(123);
    std::uniform_int_distribution<int> dice(1, 6);
    std::cout << "\nDice rolls: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << dice(gen3) << " ";
    }
    std::cout << std::endl;

    // Histogram: verify uniform distribution
    std::mt19937 gen4(456);
    std::uniform_int_distribution<int> d6(1, 6);
    std::vector<int> counts(7, 0);
    for (int i = 0; i < 6000; ++i) {
        ++counts[d6(gen4)];
    }
    std::cout << "\nDice histogram (6000 rolls):" << std::endl;
    for (int face = 1; face <= 6; ++face) {
        std::cout << "  " << face << ": " << std::setw(4) << counts[face]
                  << " " << std::string(counts[face] / 50, '*') << std::endl;
    }

    // Shuffle a vector
    std::vector<int> cards = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::mt19937 gen5(789);
    std::shuffle(cards.begin(), cards.end(), gen5);
    std::cout << "\nShuffled cards: ";
    for (int c : cards) std::cout << c << " ";
    std::cout << std::endl;

    // Seed and reseed
    std::mt19937 gen6;
    gen6.seed(42);  // reseed
    std::cout << "\nReseeded to 42, first value: " << gen6() << std::endl;

    // Same seed gives same sequence
    std::mt19937 a(999), b(999);
    std::cout << "Same seed test: " << (a() == b() ? "identical" : "different") << std::endl;

    return 0;
}

// Expected output (first 5 values are deterministic with seed=42):
// First 5 raw values (seed=42):
//   1608637542
//   3421126067
//   4083286876
//   787846414
//   3143890026
//
// Engine properties:
//   min: 0
//   max: 4294967295
//
// After discard(5), next value: 3348747335
//
// Dice rolls: 4 2 6 1 3 5 1 3 6 2
//
// Dice histogram (6000 rolls):
//   1: ~1000 ********************
//   2: ~1000 ********************
//   ...
//
// Shuffled cards: <shuffled sequence>
//
// Reseeded to 42, first value: 1608637542
// Same seed test: identical
