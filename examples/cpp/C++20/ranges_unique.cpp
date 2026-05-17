// CodeNebula - C++20 Example: Ranges Unique
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_unique.cpp

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

int main() {
    // ranges::unique - remove consecutive duplicates in place
    std::vector<int> nums = {1, 1, 2, 2, 2, 3, 3, 4, 5, 5};
    std::cout << "Original: ";
    for (int n : nums) std::cout << n << ' ';
    std::cout << '\n';

    auto [first, last] = std::ranges::unique(nums);
    nums.erase(first, last);
    std::cout << "After unique + erase: ";
    for (int n : nums) std::cout << n << ' ';
    std::cout << '\n';

    // unique with custom comparator (case-insensitive dedup)
    std::vector<std::string> words = {"Hello", "hello", "HELLO", "World", "world"};
    std::cout << "\nBefore: ";
    for (const auto& w : words) std::cout << w << ' ';
    std::cout << '\n';

    auto cmp = [](const std::string& a, const std::string& b) {
        return std::ranges::equal(a, b, [](char c1, char c2) {
            return std::tolower(c1) == std::tolower(c2);
        });
    };
    auto [f2, l2] = std::ranges::unique(words, cmp);
    words.erase(f2, l2);
    std::cout << "Case-insensitive unique: ";
    for (const auto& w : words) std::cout << w << ' ';
    std::cout << '\n';

    // ranges::unique_copy - copy without consecutive duplicates
    std::vector<int> src = {5, 5, 3, 3, 3, 7, 7, 1};
    std::vector<int> dst;

    std::ranges::unique_copy(src, std::back_inserter(dst));
    std::cout << "\nSource:      ";
    for (int s : src) std::cout << s << ' ';
    std::cout << '\n';
    std::cout << "Unique copy: ";
    for (int d : dst) std::cout << d << ' ';
    std::cout << '\n';

    // Sort first then unique to remove all duplicates
    std::vector<int> data = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    std::ranges::sort(data);
    auto [ef, el] = std::ranges::unique(data);
    data.erase(ef, el);
    std::cout << "\nSorted unique: ";
    for (int d : data) std::cout << d << ' ';
    std::cout << '\n';

    return 0;
}
