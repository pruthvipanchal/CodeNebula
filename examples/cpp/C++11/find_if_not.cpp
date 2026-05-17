// CodeNebula - C++11 Example: std::find_if_not
// Compile: g++ -std=c++11 -Wall -Wextra -o example find_if_not.cpp

// std::find_if_not returns an iterator to the first element for which the
// predicate returns false. It is the complement of std::find_if, making
// code more readable when searching for the first non-matching element.

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main() {
    // Find the first odd number
    std::vector<int> nums = {2, 4, 6, 7, 8, 10};
    auto it = std::find_if_not(nums.begin(), nums.end(),
                               [](int n) { return n % 2 == 0; });
    if (it != nums.end()) {
        std::cout << "First non-even: " << *it << std::endl;
    }

    // Find the first non-positive number
    std::vector<int> data = {5, 3, 8, -1, 4, -2};
    auto neg = std::find_if_not(data.begin(), data.end(),
                                [](int n) { return n > 0; });
    if (neg != data.end()) {
        std::cout << "First non-positive: " << *neg << std::endl;
    }

    // Find the first short string
    std::vector<std::string> words = {"elephant", "giraffe", "cat", "hippopotamus"};
    auto short_word = std::find_if_not(words.begin(), words.end(),
                                       [](const std::string& s) { return s.size() > 4; });
    if (short_word != words.end()) {
        std::cout << "First short word (<= 4 chars): " << *short_word << std::endl;
    }

    // Skip leading whitespace characters
    std::string text = "   Hello World";
    auto non_space = std::find_if_not(text.begin(), text.end(),
                                      [](char c) { return c == ' '; });
    std::string trimmed(non_space, text.end());
    std::cout << "Trimmed: '" << trimmed << "'" << std::endl;

    // When all elements match, returns end()
    std::vector<int> all_positive = {1, 2, 3, 4, 5};
    auto result = std::find_if_not(all_positive.begin(), all_positive.end(),
                                   [](int n) { return n > 0; });
    std::cout << "Found non-positive in {1..5}: "
              << std::boolalpha << (result != all_positive.end()) << std::endl;

    // Partition point: find where sorted order breaks
    std::vector<int> sorted_ish = {1, 2, 3, 5, 4, 6};
    int prev = sorted_ish[0];
    auto break_pt = std::find_if_not(sorted_ish.begin() + 1, sorted_ish.end(),
                                     [&prev](int n) { bool ok = n >= prev; prev = n; return ok; });
    if (break_pt != sorted_ish.end()) {
        std::cout << "Sort breaks at value: " << *break_pt << std::endl;
    }

    return 0;
}

// Expected output:
// First non-even: 7
// First non-positive: -1
// First short word (<= 4 chars): cat
// Trimmed: 'Hello World'
// Found non-positive in {1..5}: false
// Sort breaks at value: 4
