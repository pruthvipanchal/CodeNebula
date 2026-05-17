// CodeNebula - C++20 Example: ranges::search, search_n
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_search.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    // ranges::search - find first occurrence of a subsequence
    std::vector<int> data = {1, 2, 3, 4, 5, 1, 2, 3, 6, 7};
    std::vector<int> pattern = {1, 2, 3};

    auto [first, last] = std::ranges::search(data, pattern);
    if (first != data.end())
        std::cout << "Pattern {1,2,3} found at index "
                  << (first - data.begin()) << "\n";

    // Search for missing pattern
    std::vector<int> missing = {8, 9};
    auto [f2, l2] = std::ranges::search(data, missing);
    std::cout << "Pattern {8,9} found: " << std::boolalpha
              << (f2 != data.end()) << "\n";

    // Search in strings
    std::string text = "the quick brown fox jumps over the lazy dog";
    auto [sf, sl] = std::ranges::search(text, std::string("fox"));
    if (sf != text.end())
        std::cout << "\n\"fox\" found at index " << (sf - text.begin()) << "\n";

    // Case-insensitive search
    std::string haystack = "Hello World HELLO World";
    auto [ci_f, ci_l] = std::ranges::search(haystack, std::string("hello"),
        [](char a, char b) { return std::tolower(a) == std::tolower(b); });
    if (ci_f != haystack.end())
        std::cout << "Case-insensitive \"hello\" at index "
                  << (ci_f - haystack.begin()) << "\n";

    // ranges::search_n - find N consecutive occurrences of a value
    std::vector<int> seq = {1, 2, 2, 2, 3, 4, 4, 5, 5, 5, 5};

    auto [sn_f, sn_l] = std::ranges::search_n(seq, 3, 2);
    if (sn_f != seq.end())
        std::cout << "\n3 consecutive 2s at index " << (sn_f - seq.begin()) << "\n";

    auto [sn_f2, sn_l2] = std::ranges::search_n(seq, 4, 5);
    if (sn_f2 != seq.end())
        std::cout << "4 consecutive 5s at index " << (sn_f2 - seq.begin()) << "\n";

    // search_n not found
    auto [sn_f3, sn_l3] = std::ranges::search_n(seq, 5, 5);
    std::cout << "5 consecutive 5s found: " << (sn_f3 != seq.end()) << "\n";

    // search_n with predicate (consecutive even numbers)
    std::vector<int> nums = {1, 4, 6, 8, 3, 2, 4, 7};
    auto [ep_f, ep_l] = std::ranges::search_n(nums, 3, 0,
        [](int a, [[maybe_unused]] int b) { return a % 2 == 0; });
    if (ep_f != nums.end())
        std::cout << "\n3 consecutive evens at index "
                  << (ep_f - nums.begin()) << "\n";

    // search_n with projection
    std::vector<std::string> words = {"cat", "car", "cup", "dog", "dot"};
    auto [wp_f, wp_l] = std::ranges::search_n(words, 2, 'd', std::equal_to{},
        [](const std::string& s) { return s.front(); });
    if (wp_f != words.end())
        std::cout << "2 'd'-words at index " << (wp_f - words.begin()) << "\n";
    return 0;
}
