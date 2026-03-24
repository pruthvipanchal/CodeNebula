// CodeNebula - C++23 Example: std::ranges::zip_view
// Compile: g++ -std=c++23 -Wall -Wextra -o example ranges_zip_view.cpp
// Note: Requires GCC 13+ / Clang 17+

// std::ranges::zip_view combines multiple ranges into a single view of tuples,
// where each tuple contains one element from each source range. Iteration stops
// when the shortest range is exhausted.

#include <iostream>
#include <ranges>
#include <vector>
#include <string>
#include <array>

int main() {
    std::vector<int> ids = {1, 2, 3, 4};
    std::vector<std::string> names = {"Alice", "Bob", "Charlie", "Diana"};
    std::array<double, 4> scores = {95.5, 87.3, 92.1, 88.7};

    // Basic zip of two ranges
    std::cout << "=== Zip two ranges (ids + names) ===" << std::endl;
    for (auto [id, name] : std::views::zip(ids, names)) {
        std::cout << "  ID: " << id << ", Name: " << name << std::endl;
    }

    // Zip three ranges together
    std::cout << "\n=== Zip three ranges (ids + names + scores) ===" << std::endl;
    for (auto [id, name, score] : std::views::zip(ids, names, scores)) {
        std::cout << "  ID: " << id << " | " << name << " | Score: " << score << std::endl;
    }

    // Zip with ranges of different lengths (stops at shortest)
    std::vector<int> short_vec = {10, 20};
    std::vector<int> long_vec = {100, 200, 300, 400, 500};
    std::cout << "\n=== Zip with different lengths (2 vs 5 elements) ===" << std::endl;
    for (auto [a, b] : std::views::zip(short_vec, long_vec)) {
        std::cout << "  (" << a << ", " << b << ")" << std::endl;
    }

    // Zip view elements are references - modification is possible
    std::cout << "\n=== Modifying through zip view ===" << std::endl;
    for (auto [id, score] : std::views::zip(ids, scores)) {
        score += 1.0;  // Add bonus point
    }
    for (auto [id, score] : std::views::zip(ids, scores)) {
        std::cout << "  ID " << id << " adjusted score: " << score << std::endl;
    }

    return 0;
}

// Expected output:
// === Zip two ranges (ids + names) ===
//   ID: 1, Name: Alice
//   ID: 2, Name: Bob
//   ID: 3, Name: Charlie
//   ID: 4, Name: Diana
//
// === Zip three ranges (ids + names + scores) ===
//   ID: 1 | Alice | Score: 95.5
//   ID: 2 | Bob | Score: 87.3
//   ID: 3 | Charlie | Score: 92.1
//   ID: 4 | Diana | Score: 88.7
//
// === Zip with different lengths (2 vs 5 elements) ===
//   (10, 100)
//   (20, 200)
//
// === Modifying through zip view ===
//   ID 1 adjusted score: 96.5
//   ID 2 adjusted score: 88.3
//   ID 3 adjusted score: 93.1
//   ID 4 adjusted score: 89.7
