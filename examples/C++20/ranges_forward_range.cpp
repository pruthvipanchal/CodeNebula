// CodeNebula - C++20 Example: std::ranges::forward_range Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_forward_range.cpp

#include <ranges>
#include <vector>
#include <forward_list>
#include <list>
#include <algorithm>
#include <iostream>

// std::ranges::forward_range requires multi-pass iteration,
// meaning you can iterate over the range multiple times and
// save/restore iterator positions.

// Find duplicates - requires multi-pass (forward_range)
template <std::ranges::forward_range R>
bool has_duplicates(R&& r) {
    for (auto it = std::ranges::begin(r); it != std::ranges::end(r); ++it) {
        for (auto jt = std::next(it); jt != std::ranges::end(r); ++jt) {
            if (*it == *jt) return true;
        }
    }
    return false;
}

// Check if range is palindrome - requires forward_range
template <std::ranges::forward_range R>
    requires std::equality_comparable<std::ranges::range_value_t<R>>
bool is_palindrome(R&& r) {
    auto collected = std::vector(std::ranges::begin(r), std::ranges::end(r));
    auto sz = collected.size();
    for (std::size_t i = 0; i < sz / 2; ++i) {
        if (collected[i] != collected[sz - 1 - i]) return false;
    }
    return true;
}

int main() {
    // Forward-iterable containers
    static_assert(std::ranges::forward_range<std::vector<int>>);
    static_assert(std::ranges::forward_range<std::forward_list<int>>);
    static_assert(std::ranges::forward_range<std::list<int>>);

    std::vector<int> nums = {3, 1, 4, 1, 5};
    std::cout << "nums has duplicates: " << std::boolalpha
              << has_duplicates(nums) << "\n";

    std::vector<int> unique_nums = {1, 2, 3, 4, 5};
    std::cout << "unique_nums has duplicates: "
              << has_duplicates(unique_nums) << "\n";

    // forward_list is a forward_range but NOT bidirectional
    std::forward_list<int> flist = {1, 2, 3, 2, 1};
    std::cout << "flist is palindrome: " << is_palindrome(flist) << "\n";

    // Views can also be forward ranges
    auto filtered = nums | std::views::filter([](int x) { return x > 2; });
    static_assert(std::ranges::forward_range<decltype(filtered)>);
    std::cout << "Filtered has duplicates: "
              << has_duplicates(filtered) << "\n";

    // Using ranges::search (requires forward_range)
    std::vector<int> pattern = {4, 1};
    auto result = std::ranges::search(nums, pattern);
    std::cout << "Pattern found at position: "
              << std::ranges::distance(nums.begin(), result.begin()) << "\n";

    return 0;
}
