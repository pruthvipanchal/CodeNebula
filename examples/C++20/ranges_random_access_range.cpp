// CodeNebula - C++20 Example: std::ranges::random_access_range Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_random_access_range.cpp

#include <ranges>
#include <vector>
#include <deque>
#include <list>
#include <array>
#include <algorithm>
#include <iostream>

// std::ranges::random_access_range requires O(1) access to any
// element by index, supporting iterator arithmetic (+, -, []).

// Binary search using random access iterators
template <std::ranges::random_access_range R, typename T>
bool binary_search_range(R&& r, const T& target) {
    auto lo = std::ranges::begin(r);
    auto hi = std::ranges::end(r);
    while (lo < hi) {
        auto mid = lo + (hi - lo) / 2;
        if (*mid == target) return true;
        else if (*mid < target) lo = mid + 1;
        else hi = mid;
    }
    return false;
}

// Get the nth element from end
template <std::ranges::random_access_range R>
auto nth_from_end(R&& r, std::ranges::range_difference_t<R> n) {
    return *(std::ranges::end(r) - n - 1);
}

int main() {
    // Random access containers
    static_assert(std::ranges::random_access_range<std::vector<int>>);
    static_assert(std::ranges::random_access_range<std::deque<int>>);
    static_assert(std::ranges::random_access_range<std::array<int, 5>>);
    static_assert(std::ranges::random_access_range<int[5]>);

    // list is NOT random access
    static_assert(!std::ranges::random_access_range<std::list<int>>);

    std::vector<int> sorted = {2, 5, 8, 12, 16, 23, 38, 56, 72};

    std::cout << "Search for 23: " << std::boolalpha
              << binary_search_range(sorted, 23) << "\n";
    std::cout << "Search for 10: "
              << binary_search_range(sorted, 10) << "\n";

    std::cout << "2nd from end: " << nth_from_end(sorted, 2) << "\n";
    std::cout << "Last element: " << nth_from_end(sorted, 0) << "\n";

    // Direct subscript access via ranges
    std::cout << "Element at index 3: " << sorted[3] << "\n";

    // iota_view is random access
    auto iota = std::views::iota(0, 10);
    static_assert(std::ranges::random_access_range<decltype(iota)>);
    std::cout << "iota[7]: " << iota[7] << "\n";

    // ranges::sort requires random_access_range
    std::vector<int> unsorted = {5, 3, 8, 1, 9, 2};
    std::ranges::sort(unsorted);
    std::cout << "Sorted: ";
    for (int n : unsorted) std::cout << n << " ";
    std::cout << "\n";
    return 0;
}
