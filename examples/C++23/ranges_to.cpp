// CodeNebula - C++23 Example: ranges::to<Container>() Materialization
// Compile: g++ -std=c++23 -Wall -Wextra -o example ranges_to.cpp
// Note: Requires GCC 13+ / Clang 17+

// std::ranges::to<Container>() materializes a lazy view into a concrete
// container. This is the long-awaited feature that allows converting any
// range pipeline result directly into a vector, set, map, string, etc.

#include <iostream>
#include <algorithm>
#include <ranges>
#include <vector>
#include <set>
#include <deque>
#include <map>
#include <string>

int main() {
    // Basic: materialize a view into a vector
    std::cout << "=== View to vector ===" << std::endl;
    auto squares = std::views::iota(1, 6)
                 | std::views::transform([](int n) { return n * n; })
                 | std::ranges::to<std::vector>();
    for (auto v : squares) std::cout << "  " << v;
    std::cout << std::endl;

    // Materialize filtered data into a set (auto-sorted, unique)
    std::vector<int> data = {5, 3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    std::cout << "\n=== Filtered to set (unique, sorted) ===" << std::endl;
    auto unique_evens = data
        | std::views::filter([](int n) { return n % 2 != 0; })
        | std::ranges::to<std::set>();
    for (auto v : unique_evens) std::cout << "  " << v;
    std::cout << std::endl;

    // Materialize into a deque
    std::cout << "\n=== Transform to deque ===" << std::endl;
    auto doubled = data
        | std::views::take(5)
        | std::views::transform([](int n) { return n * 2; })
        | std::ranges::to<std::deque>();
    for (auto v : doubled) std::cout << "  " << v;
    std::cout << std::endl;

    // Build a map from a range of pairs
    std::cout << "\n=== Enumerate to map ===" << std::endl;
    std::vector<std::string> names = {"Alice", "Bob", "Charlie"};
    auto name_map = std::views::enumerate(names)
        | std::views::transform([](auto pair) {
            auto [idx, name] = pair;
            return std::pair<int, std::string>(static_cast<int>(idx), name);
          })
        | std::ranges::to<std::map>();
    for (const auto& [key, val] : name_map) {
        std::cout << "  " << key << " -> " << val << std::endl;
    }

    // Chain multiple operations and collect
    std::cout << "\n=== Complex pipeline to vector ===" << std::endl;
    auto result = std::views::iota(1, 20)
        | std::views::filter([](int n) { return n % 3 == 0; })
        | std::views::transform([](int n) { return n * n; })
        | std::views::take(4)
        | std::ranges::to<std::vector>();
    for (auto v : result) std::cout << "  " << v;
    std::cout << std::endl;

    // Nested: vector of vectors
    std::cout << "\n=== Chunks to vector<vector<int>> ===" << std::endl;
    auto chunks = std::views::iota(1, 10)
        | std::views::chunk(3)
        | std::views::transform([](auto chunk) {
            return chunk | std::ranges::to<std::vector>();
          })
        | std::ranges::to<std::vector>();
    for (const auto& c : chunks) {
        std::cout << "  [";
        for (size_t i = 0; i < c.size(); ++i) {
            if (i > 0) std::cout << ",";
            std::cout << c[i];
        }
        std::cout << "]" << std::endl;
    }

    return 0;
}

// Expected output:
// === View to vector ===
//   1  4  9  16  25
//
// === Filtered to set (unique, sorted) ===
//   1  3  5  9
//
// === Transform to deque ===
//   10  6  2  8  2
//
// === Enumerate to map ===
//   0 -> Alice
//   1 -> Bob
//   2 -> Charlie
//
// === Complex pipeline to vector ===
//   9  36  81  144
//
// === Chunks to vector<vector<int>> ===
//   [1,2,3]
//   [4,5,6]
//   [7,8,9]
