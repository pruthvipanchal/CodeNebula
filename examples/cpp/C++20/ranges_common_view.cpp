// CodeNebula - C++20 Example: std::ranges::common_view
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_common_view.cpp

#include <ranges>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

// std::ranges::common_view / std::views::common converts a range
// into one where begin() and end() return the same type. This is
// needed for legacy algorithms that require matching iterator types.

int main() {
    // Unbounded iota piped through take produces non-common range
    auto non_common = std::views::iota(1) | std::views::take(5);
    static_assert(!std::ranges::common_range<decltype(non_common)>);

    // Convert to common_view for legacy algorithm compatibility
    auto common = non_common | std::views::common;
    static_assert(std::ranges::common_range<decltype(common)>);

    // Now we can use std::accumulate (requires same begin/end type)
    int sum = std::accumulate(common.begin(), common.end(), 0);
    std::cout << "Sum of 1..5: " << sum << "\n";

    // Construct a vector from a non-common view
    auto transformed = std::views::iota(1)
        | std::views::transform([](int n) { return n * n; })
        | std::views::take(6)
        | std::views::common;
    std::vector<int> squares(transformed.begin(), transformed.end());
    std::cout << "Squares: ";
    for (int n : squares) std::cout << n << " ";
    std::cout << "\n";

    // Already-common ranges pass through unchanged
    std::vector<int> vec = {5, 3, 8, 1, 9};
    auto already_common = vec | std::views::common;
    static_assert(std::ranges::common_range<decltype(already_common)>);

    // Use common_view with std::sort (legacy version)
    auto view = vec | std::views::common;
    // Note: std::ranges::sort works without common, but std::sort needs it
    std::cout << "Original: ";
    for (int n : vec) std::cout << n << " ";
    std::cout << "\n";

    // Use with std::distance (legacy)
    auto counted = std::views::iota(0) | std::views::take(10) | std::views::common;
    auto dist = std::distance(counted.begin(), counted.end());
    std::cout << "Distance: " << dist << "\n";

    // Practical: use string algorithm with non-common view
    auto chars = std::views::iota('a')
        | std::views::take(10)
        | std::views::common;
    std::string str(chars.begin(), chars.end());
    std::cout << "String: " << str << "\n";

    // Use with std::find (legacy)
    auto nums = std::views::iota(10)
        | std::views::take(20)
        | std::views::common;
    auto it = std::find(nums.begin(), nums.end(), 15);
    if (it != nums.end()) {
        std::cout << "Found: " << *it << "\n";
    }
    return 0;
}
