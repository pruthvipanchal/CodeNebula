// CodeNebula - C++11 Example: std::random_device
// Compile: g++ -std=c++11 -Wall -Wextra -o example random_device.cpp

// std::random_device provides non-deterministic random numbers using
// hardware entropy sources. It's typically used to seed pseudo-random
// engines rather than for bulk generation (it may be slow).

#include <iostream>
#include <random>
#include <string>
#include <set>

int main() {
    std::random_device rd;

    // Basic properties
    std::cout << "random_device properties:" << std::endl;
    std::cout << "  min: " << std::random_device::min() << std::endl;
    std::cout << "  max: " << std::random_device::max() << std::endl;
    std::cout << "  entropy: " << rd.entropy() << std::endl;

    // Generate some random numbers
    std::cout << "\n5 random unsigned ints:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "  " << rd() << std::endl;
    }

    // Common use: seed a PRNG engine
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);
    std::cout << "\nSeeded mt19937, 5 random [1,100]:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "  " << dist(gen) << std::endl;
    }

    // Seed with multiple random values for better seeding
    std::seed_seq seed{rd(), rd(), rd(), rd(), rd()};
    std::mt19937 gen2(seed);
    std::cout << "\nSeed-seq seeded mt19937: " << dist(gen2) << std::endl;

    // Practical: generate a random token
    const std::string chars =
        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::uniform_int_distribution<std::size_t> char_dist(0, chars.size() - 1);
    std::string token;
    for (int i = 0; i < 16; ++i) {
        token += chars[char_dist(gen)];
    }
    std::cout << "\nRandom token: " << token << std::endl;

    // Show that each call produces different values (uniqueness test)
    std::set<unsigned int> unique_values;
    for (int i = 0; i < 100; ++i) {
        unique_values.insert(rd());
    }
    std::cout << "\n100 calls produced " << unique_values.size()
              << " unique values" << std::endl;

    return 0;
}

// Expected output (values will differ each run):
// random_device properties:
//   min: 0
//   max: 4294967295
//   entropy: 32
//
// 5 random unsigned ints:
//   <random values>
//
// Seeded mt19937, 5 random [1,100]:
//   <random values>
//
// Seed-seq seeded mt19937: <random value>
//
// Random token: <16-char string>
//
// 100 calls produced 100 unique values
