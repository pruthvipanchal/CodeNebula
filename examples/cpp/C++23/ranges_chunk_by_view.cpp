// CodeNebula - C++23 Example: std::ranges::chunk_by_view
// Compile: g++ -std=c++23 -Wall -Wextra -o example ranges_chunk_by_view.cpp
// Note: Requires GCC 13+ / Clang 17+

// std::ranges::chunk_by_view splits a range into subranges based on a binary
// predicate. A new chunk starts whenever the predicate returns false for
// two adjacent elements. Unlike chunk_view, chunks have variable sizes.

#include <iostream>
#include <ranges>
#include <vector>
#include <string>

int main() {
    // Group consecutive equal elements (like "group by")
    std::vector<int> data = {1, 1, 2, 2, 2, 3, 1, 1};
    std::cout << "=== Group equal consecutive elements ===" << std::endl;
    for (auto group : data | std::views::chunk_by(std::equal_to{})) {
        std::cout << "  [";
        bool first = true;
        for (auto val : group) {
            if (!first) std::cout << ", ";
            std::cout << val;
            first = false;
        }
        std::cout << "]" << std::endl;
    }

    // Group ascending runs
    std::vector<int> nums = {1, 3, 5, 2, 4, 8, 1, 7};
    std::cout << "\n=== Ascending runs ===" << std::endl;
    for (auto run : nums | std::views::chunk_by(std::less{})) {
        std::cout << "  [";
        bool first = true;
        for (auto val : run) {
            if (!first) std::cout << ", ";
            std::cout << val;
            first = false;
        }
        std::cout << "]" << std::endl;
    }

    // Split words by first letter change
    std::vector<std::string> words = {"apple", "ant", "bear", "bat", "bee", "cat"};
    std::cout << "\n=== Group by first letter ===" << std::endl;
    auto same_letter = [](const std::string& a, const std::string& b) {
        return a[0] == b[0];
    };
    for (auto group : words | std::views::chunk_by(same_letter)) {
        std::cout << "  Group: ";
        for (const auto& w : group) std::cout << w << " ";
        std::cout << std::endl;
    }

    // Group positive and negative runs
    std::vector<int> values = {3, 5, -1, -4, 2, 7, -3};
    std::cout << "\n=== Same-sign groups ===" << std::endl;
    auto same_sign = [](int a, int b) { return (a >= 0) == (b >= 0); };
    for (auto group : values | std::views::chunk_by(same_sign)) {
        std::cout << "  [";
        bool first = true;
        for (auto v : group) {
            if (!first) std::cout << ", ";
            std::cout << v;
            first = false;
        }
        std::cout << "]" << std::endl;
    }

    return 0;
}

// Expected output:
// === Group equal consecutive elements ===
//   [1, 1]
//   [2, 2, 2]
//   [3]
//   [1, 1]
//
// === Ascending runs ===
//   [1, 3, 5]
//   [2, 4, 8]
//   [1, 7]
//
// === Group by first letter ===
//   Group: apple ant
//   Group: bear bat bee
//   Group: cat
//
// === Same-sign groups ===
//   [3, 5]
//   [-1, -4]
//   [2, 7]
//   [-3]
