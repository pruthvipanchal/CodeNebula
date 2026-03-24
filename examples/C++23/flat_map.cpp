// CodeNebula - C++23 Example: std::flat_map
// Compile: g++ -std=c++23 -Wall -Wextra -o example flat_map.cpp
// Note: Requires GCC 14+ / Clang 18+ / MSVC 19.37+

// std::flat_map is a sorted associative container adaptor that stores
// keys and values in separate sorted contiguous containers (e.g., vectors).
// It provides cache-friendly iteration and lower memory overhead than std::map.

#include <iostream>
#include <flat_map>
#include <string>
#include <vector>

int main() {
    std::cout << "=== std::flat_map ===" << std::endl;

    // Construction with initializer list (keys are kept sorted)
    std::flat_map<std::string, int> scores = {
        {"Alice", 95}, {"Charlie", 87}, {"Bob", 91}, {"Diana", 78}
    };

    // Iteration: elements are in sorted key order
    std::cout << "All scores (sorted by name):" << std::endl;
    for (const auto& [name, score] : scores) {
        std::cout << "  " << name << ": " << score << std::endl;
    }

    // Insert and emplace
    scores.insert({"Eve", 88});
    scores["Frank"] = 92;

    // Lookup
    std::cout << "\n=== Lookup ===" << std::endl;
    std::cout << "Bob's score: " << scores["Bob"] << std::endl;
    if (auto it = scores.find("Eve"); it != scores.end()) {
        std::cout << "Eve found: " << it->second << std::endl;
    }
    std::cout << "Contains 'Zoe': " << scores.contains("Zoe") << std::endl;

    // Erase
    scores.erase("Charlie");
    std::cout << "\nAfter erasing Charlie, size: " << scores.size() << std::endl;

    // Access underlying containers
    std::cout << "\n=== Underlying containers ===" << std::endl;
    const auto& keys = scores.keys();
    std::cout << "Keys: ";
    for (const auto& k : keys) std::cout << k << " ";
    std::cout << std::endl;

    const auto& vals = scores.values();
    std::cout << "Values: ";
    for (int v : vals) std::cout << v << " ";
    std::cout << std::endl;

    // Construct from separate key/value containers
    std::cout << "\n=== Construct from sorted_unique ===" << std::endl;
    std::vector<int> k = {1, 2, 3};
    std::vector<std::string> v = {"one", "two", "three"};
    std::flat_map<int, std::string> nums(std::sorted_unique, std::move(k), std::move(v));
    for (const auto& [key, val] : nums) {
        std::cout << "  " << key << " -> " << val << std::endl;
    }

    return 0;
}

/*
Expected output:
=== std::flat_map ===
All scores (sorted by name):
  Alice: 95
  Bob: 91
  Charlie: 87
  Diana: 78

=== Lookup ===
Bob's score: 91
Eve found: 88
Contains 'Zoe': 0

After erasing Charlie, size: 5

=== Underlying containers ===
Keys: Alice Bob Diana Eve Frank
Values: 95 91 78 88 92

=== Construct from sorted_unique ===
  1 -> one
  2 -> two
  3 -> three
*/
