// CodeNebula - C++23 Example: ranges::fold_left, fold_right, fold_left_first, fold_right_last
// Compile: g++ -std=c++23 -Wall -Wextra -o example ranges_fold.cpp
// Note: Requires GCC 13+ / Clang 17+

// C++23 introduces fold algorithms for ranges. fold_left processes left-to-right
// with an initial value. fold_right processes right-to-left. fold_left_first and
// fold_right_last use the first/last element as the initial value.

#include <iostream>
#include <algorithm>
#include <ranges>
#include <vector>
#include <string>
#include <functional>

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};

    // fold_left: left-to-right reduction with initial value
    std::cout << "=== fold_left ===" << std::endl;
    auto sum = std::ranges::fold_left(nums, 0, std::plus{});
    std::cout << "  Sum: " << sum << std::endl;

    auto product = std::ranges::fold_left(nums, 1, std::multiplies{});
    std::cout << "  Product: " << product << std::endl;

    // fold_left with string concatenation (shows left-to-right order)
    std::vector<std::string> words = {"A", "B", "C", "D"};
    auto concat_left = std::ranges::fold_left(words, std::string("("),
        [](std::string acc, const std::string& w) { return acc + w + " "; });
    std::cout << "  Left concat: " << concat_left << ")" << std::endl;

    // fold_right: right-to-left reduction with initial value
    std::cout << "\n=== fold_right ===" << std::endl;
    auto concat_right = std::ranges::fold_right(words, std::string(")"),
        [](const std::string& w, std::string acc) { return " " + w + acc; });
    std::cout << "  Right concat: (" << concat_right << std::endl;

    auto right_sub = std::ranges::fold_right(nums, 0,
        [](int val, int acc) { return val - acc; });
    std::cout << "  Right subtraction (1-(2-(3-(4-(5-0))))): " << right_sub << std::endl;

    // fold_left_first: uses first element as initial value
    std::cout << "\n=== fold_left_first ===" << std::endl;
    auto max_val = std::ranges::fold_left_first(nums,
        [](int a, int b) { return a > b ? a : b; });
    if (max_val) std::cout << "  Max: " << *max_val << std::endl;

    auto min_val = std::ranges::fold_left_first(nums,
        [](int a, int b) { return a < b ? a : b; });
    if (min_val) std::cout << "  Min: " << *min_val << std::endl;

    // fold_left_first on empty range returns std::optional with no value
    std::vector<int> empty;
    auto empty_result = std::ranges::fold_left_first(empty, std::plus{});
    std::cout << "  Empty fold has value: " << std::boolalpha
              << empty_result.has_value() << std::endl;

    // fold_right_last: uses last element as initial value
    std::cout << "\n=== fold_right_last ===" << std::endl;
    auto right_max = std::ranges::fold_right_last(nums,
        [](int val, int acc) { return val > acc ? val : acc; });
    if (right_max) std::cout << "  Max (right): " << *right_max << std::endl;

    // Practical: build a sentence
    std::vector<std::string> parts = {"The", "quick", "brown", "fox"};
    auto sentence = std::ranges::fold_left(parts, std::string{},
        [](std::string acc, const std::string& w) {
            return acc.empty() ? w : acc + " " + w;
        });
    std::cout << "\n=== Practical: build sentence ===" << std::endl;
    std::cout << "  " << sentence << std::endl;

    return 0;
}

// Expected output:
// === fold_left ===
//   Sum: 15
//   Product: 120
//   Left concat: (A B C D )
//
// === fold_right ===
//   Right concat: ( A B C D)
//   Right subtraction (1-(2-(3-(4-(5-0))))): 3
//
// === fold_left_first ===
//   Max: 5
//   Min: 1
//   Empty fold has value: false
//
// === fold_right_last ===
//   Max (right): 5
//
// === Practical: build sentence ===
//   The quick brown fox
