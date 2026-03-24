// CodeNebula - C++20 Example: views::join, views::split, views::common, views::reverse
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_adaptor_structural.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <string>

int main() {
    // views::join - flatten a range of ranges
    std::vector<std::vector<int>> nested = {{1, 2, 3}, {4, 5}, {6, 7, 8, 9}};
    std::cout << "Joined (flattened): ";
    for (int n : nested | std::views::join) std::cout << n << " ";
    std::cout << "\n";

    // views::split - split a range by a delimiter
    std::string csv = "apple,banana,cherry,date,elderberry";
    std::cout << "Split by comma:\n";
    for (auto word : csv | std::views::split(',')) {
        std::cout << "  ";
        for (char c : word) std::cout << c;
        std::cout << "\n";
    }

    // Split with a string delimiter
    std::string text = "one--two--three--four";
    std::cout << "\nSplit by '--':\n";
    for (auto part : text | std::views::split(std::string_view("--"))) {
        std::cout << "  ";
        for (char c : part) std::cout << c;
        std::cout << "\n";
    }

    // views::common - convert to common range (begin/end same type)
    auto uncommon = std::views::iota(1) | std::views::take(5);
    auto common_rng = uncommon | std::views::common;
    std::vector<int> result(common_rng.begin(), common_rng.end());
    std::cout << "Common range to vector: ";
    for (int n : result) std::cout << n << " ";
    std::cout << "\n";

    // views::reverse - reverse a bidirectional range
    std::vector<int> nums = {10, 20, 30, 40, 50};
    std::cout << "\nReversed: ";
    for (int n : nums | std::views::reverse) std::cout << n << " ";
    std::cout << "\n";

    // Split and count words
    std::string sentence = "the quick brown fox jumps over the lazy dog";
    int word_count = 0;
    for ([[maybe_unused]] auto word : sentence | std::views::split(' '))
        ++word_count;
    std::cout << "Word count: " << word_count << "\n";

    // Reverse with filter
    std::cout << "Reversed evens: ";
    std::vector<int> all = {1, 2, 3, 4, 5, 6, 7, 8};
    for (int n : all | std::views::reverse
                     | std::views::filter([](int x) { return x % 2 == 0; }))
        std::cout << n << " ";
    std::cout << "\n";

    return 0;
}
