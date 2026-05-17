// CodeNebula - C++20 Example: ranges::find_end, find_first_of, adjacent_find
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_find_advanced.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    // ranges::find_end - find last occurrence of a subsequence
    std::vector<int> data = {1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5};
    std::vector<int> pattern = {1, 2, 3};

    auto [first, last] = std::ranges::find_end(data, pattern);
    if (first != data.end())
        std::cout << "Last {1,2,3} at index " << (first - data.begin()) << "\n";

    // Pattern not found
    std::vector<int> missing = {9, 9};
    auto [f2, l2] = std::ranges::find_end(data, missing);
    std::cout << "Found {9,9}: " << std::boolalpha << (f2 != data.end()) << "\n";

    // ranges::find_first_of - find first element from a set
    std::vector<int> numbers = {5, 7, 3, 9, 1, 4, 8, 2};
    std::vector<int> targets = {4, 8, 9};
    auto it = std::ranges::find_first_of(numbers, targets);
    if (it != numbers.end())
        std::cout << "\nFirst of {4,8,9}: " << *it
                  << " at index " << (it - numbers.begin()) << "\n";

    // find_first_of with strings
    std::string text = "hello world programming";
    std::string vowels = "aeiou";
    auto vit = std::ranges::find_first_of(text, vowels);
    if (vit != text.end())
        std::cout << "First vowel: '" << *vit
                  << "' at index " << (vit - text.begin()) << "\n";

    // ranges::adjacent_find - find consecutive equal elements
    std::vector<int> seq = {1, 2, 3, 3, 4, 5, 5, 5, 6};
    auto adj = std::ranges::adjacent_find(seq);
    if (adj != seq.end())
        std::cout << "\nFirst adjacent pair: " << *adj
                  << " at index " << (adj - seq.begin()) << "\n";

    // adjacent_find with custom predicate (gap > 2)
    std::vector<int> gaps = {1, 2, 3, 8, 9, 10, 20};
    auto gap = std::ranges::adjacent_find(gaps,
        [](int a, int b) { return (b - a) > 2; });
    if (gap != gaps.end())
        std::cout << "First big gap: " << *gap << " -> " << *(gap + 1) << "\n";

    // adjacent_find for detecting sorted order violation
    std::vector<int> sorted = {1, 3, 5, 4, 7, 9};
    auto unsorted_at = std::ranges::adjacent_find(sorted, std::ranges::greater{});
    if (unsorted_at != sorted.end())
        std::cout << "Sort violation: " << *unsorted_at
                  << " > " << *(unsorted_at + 1) << "\n";

    // adjacent_find with projection
    std::vector<std::string> words = {"cat", "car", "dog", "dot", "den"};
    auto same_start = std::ranges::adjacent_find(words,
        [](char a, char b) { return a == b; },
        [](const std::string& s) { return s.front(); });
    if (same_start != words.end())
        std::cout << "\nSame first letter: " << *same_start
                  << ", " << *(same_start + 1) << "\n";
    return 0;
}
