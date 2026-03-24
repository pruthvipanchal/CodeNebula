// CodeNebula - C++20 Example: std::ranges::common_range Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_common_range.cpp

#include <ranges>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <iostream>

// std::ranges::common_range requires that begin() and end() return
// the same type. This is important for compatibility with legacy
// algorithms that expect matching iterator types.

// Works only with common ranges (same begin/end type)
template <std::ranges::common_range R>
auto legacy_accumulate(const R& r) {
    using T = std::ranges::range_value_t<R>;
    return std::accumulate(std::ranges::begin(r), std::ranges::end(r), T{});
}

int main() {
    // Standard containers are common ranges
    static_assert(std::ranges::common_range<std::vector<int>>);
    static_assert(std::ranges::common_range<std::list<int>>);

    // Some views are NOT common (begin and end have different types)
    auto take5 = std::views::iota(1) | std::views::take(5);
    static_assert(!std::ranges::common_range<decltype(take5)>);

    // Bounded iota IS common
    auto bounded = std::views::iota(1, 6);
    static_assert(std::ranges::common_range<decltype(bounded)>);

    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::cout << "Sum (vector): " << legacy_accumulate(nums) << "\n";
    std::cout << "Sum (iota 1..5): " << legacy_accumulate(bounded) << "\n";

    // Use common_view to adapt non-common ranges for legacy algorithms
    auto non_common = std::views::iota(1) | std::views::take(5);
    auto made_common = non_common | std::views::common;
    static_assert(std::ranges::common_range<decltype(made_common)>);

    // Now we can use legacy algorithms
    int sum = std::accumulate(made_common.begin(), made_common.end(), 0);
    std::cout << "Sum (made common): " << sum << "\n";

    // filter_view on a common range is still common
    auto evens = nums | std::views::filter([](int x) { return x % 2 == 0; });
    static_assert(std::ranges::common_range<decltype(evens)>);
    std::cout << "Sum (evens): " << legacy_accumulate(evens) << "\n";

    // Constructing a container from common range iterators
    auto transformed = nums
        | std::views::transform([](int x) { return x * 10; })
        | std::views::common;
    std::vector<int> result(transformed.begin(), transformed.end());
    std::cout << "Transformed: ";
    for (int v : result) std::cout << v << " ";
    std::cout << "\n";

    return 0;
}
