// CodeNebula - C++23 Example: std::ranges::repeat_view
// Compile: g++ -std=c++23 -Wall -Wextra -o example repeat_view.cpp
// Note: Requires GCC 13+ / Clang 17+

// std::ranges::repeat_view generates a view that repeats a value a specified
// number of times, or infinitely if no bound is given. Useful for generating
// fill values or combining with zip to pad ranges.

#include <iostream>
#include <ranges>
#include <vector>
#include <string>

int main() {
    // Bounded repeat: repeat a value N times
    std::cout << "=== Repeat 42 five times ===" << std::endl;
    for (auto val : std::views::repeat(42, 5)) {
        std::cout << "  " << val;
    }
    std::cout << std::endl;

    // Repeat a string
    std::cout << "\n=== Repeat \"Hello\" 3 times ===" << std::endl;
    for (const auto& s : std::views::repeat(std::string("Hello"), 3)) {
        std::cout << "  " << s;
    }
    std::cout << std::endl;

    // Unbounded repeat with take (infinite repeat, limited)
    std::cout << "\n=== Infinite repeat of 0, take 6 ===" << std::endl;
    for (auto val : std::views::repeat(0) | std::views::take(6)) {
        std::cout << "  " << val;
    }
    std::cout << std::endl;

    // Combine with zip: pad a short range with default values
    std::vector<std::string> names = {"Alice", "Bob", "Charlie"};
    std::cout << "\n=== Names with default scores (zip + repeat) ===" << std::endl;
    for (auto [name, score] : std::views::zip(names, std::views::repeat(0))) {
        std::cout << "  " << name << ": " << score << std::endl;
    }

    // Generate indexed default values
    std::cout << "\n=== Indices with default value ===" << std::endl;
    for (auto [idx, val] : std::views::zip(std::views::iota(0, 5),
                                            std::views::repeat(-1))) {
        std::cout << "  [" << idx << "] = " << val << std::endl;
    }

    // Repeat for separator generation
    std::cout << "\n=== Repeated separator ===" << std::endl;
    for (const auto& sep : std::views::repeat(std::string("---"), 4)) {
        std::cout << sep;
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// === Repeat 42 five times ===
//   42  42  42  42  42
//
// === Repeat "Hello" 3 times ===
//   Hello  Hello  Hello
//
// === Infinite repeat of 0, take 6 ===
//   0  0  0  0  0  0
//
// === Names with default scores (zip + repeat) ===
//   Alice: 0
//   Bob: 0
//   Charlie: 0
//
// === Indices with default value ===
//   [0] = -1
//   [1] = -1
//   [2] = -1
//   [3] = -1
//   [4] = -1
//
// === Repeated separator ===
// ------------
