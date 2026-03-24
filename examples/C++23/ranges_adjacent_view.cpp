// CodeNebula - C++23 Example: std::ranges::adjacent_view
// Compile: g++ -std=c++23 -Wall -Wextra -o example ranges_adjacent_view.cpp
// Note: Requires GCC 13+ / Clang 17+

// std::ranges::adjacent_view<N> produces a view of overlapping N-tuples from
// consecutive elements. adjacent<2> gives pairs of neighbors, adjacent<3>
// gives triples, etc. The alias views::pairwise is equivalent to adjacent<2>.

#include <iostream>
#include <ranges>
#include <vector>
#include <string>

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5, 6};

    // Pairwise adjacency (adjacent<2>)
    std::cout << "=== Pairwise adjacent (sliding window of 2) ===" << std::endl;
    for (auto [a, b] : std::views::adjacent<2>(nums)) {
        std::cout << "  (" << a << ", " << b << ")" << std::endl;
    }

    // Triple adjacency (adjacent<3>)
    std::cout << "\n=== Triple adjacent (sliding window of 3) ===" << std::endl;
    for (auto [a, b, c] : std::views::adjacent<3>(nums)) {
        std::cout << "  (" << a << ", " << b << ", " << c << ")" << std::endl;
    }

    // Quadruple adjacency
    std::cout << "\n=== Quadruple adjacent (sliding window of 4) ===" << std::endl;
    for (auto [a, b, c, d] : std::views::adjacent<4>(nums)) {
        std::cout << "  (" << a << ", " << b << ", " << c << ", " << d << ")" << std::endl;
    }

    // Practical use: detect ascending pairs
    std::vector<int> data = {3, 1, 4, 1, 5, 9, 2, 6};
    std::cout << "\n=== Ascending consecutive pairs ===" << std::endl;
    for (auto [x, y] : std::views::adjacent<2>(data)) {
        if (y > x) {
            std::cout << "  " << x << " -> " << y << " (increase of " << y - x << ")" << std::endl;
        }
    }

    // With strings
    std::vector<std::string> words = {"the", "quick", "brown", "fox", "jumps"};
    std::cout << "\n=== Word pairs ===" << std::endl;
    for (auto [w1, w2] : std::views::adjacent<2>(words)) {
        std::cout << "  \"" << w1 << " " << w2 << "\"" << std::endl;
    }

    return 0;
}

// Expected output:
// === Pairwise adjacent (sliding window of 2) ===
//   (1, 2)
//   (2, 3)
//   (3, 4)
//   (4, 5)
//   (5, 6)
//
// === Triple adjacent (sliding window of 3) ===
//   (1, 2, 3)
//   (2, 3, 4)
//   (3, 4, 5)
//   (4, 5, 6)
//
// === Quadruple adjacent (sliding window of 4) ===
//   (1, 2, 3, 4)
//   (2, 3, 4, 5)
//   (3, 4, 5, 6)
//
// === Ascending consecutive pairs ===
//   1 -> 4 (increase of 3)
//   1 -> 5 (increase of 4)
//   5 -> 9 (increase of 4)
//   2 -> 6 (increase of 4)
//
// === Word pairs ===
//   "the quick"
//   "quick brown"
//   "brown fox"
//   "fox jumps"
