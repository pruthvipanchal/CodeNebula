// CodeNebula - C++20 Example: std::ranges::empty_view
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_empty_view.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <string>
#include <algorithm>

// Function that returns a view - empty_view as default/sentinel
auto get_data(bool available) {
    static std::vector<int> data = {10, 20, 30, 40, 50};
    if (available)
        return std::ranges::subrange(data.begin(), data.end());
    else
        return std::ranges::subrange(data.end(), data.end());
}

int main() {
    // empty_view contains no elements of a given type
    std::ranges::empty_view<int> empty_ints;

    std::cout << "Empty view size: " << std::ranges::size(empty_ints) << "\n";
    std::cout << "Empty view is empty: " << std::boolalpha
              << std::ranges::empty(empty_ints) << "\n";
    std::cout << "Data pointer: " << empty_ints.data() << "\n";

    // Using views::empty
    auto ev = std::views::empty<double>;
    std::cout << "\nEmpty<double> size: " << std::ranges::size(ev) << "\n";

    // Iteration over empty view does nothing
    std::cout << "Iterating empty view: [";
    for (int n : std::views::empty<int>)
        std::cout << n;  // Never executes
    std::cout << "]\n";

    // empty_view satisfies range concepts
    static_assert(std::ranges::range<std::ranges::empty_view<int>>);
    static_assert(std::ranges::sized_range<std::ranges::empty_view<int>>);
    static_assert(std::ranges::contiguous_range<std::ranges::empty_view<int>>);
    std::cout << "\nSatisfies range: true\n";
    std::cout << "Satisfies sized_range: true\n";
    std::cout << "Satisfies contiguous_range: true\n";

    // Useful as a no-op in generic code
    auto process = [](auto&& rng) {
        int count = 0;
        for ([[maybe_unused]] auto&& elem : rng) ++count;
        return count;
    };

    std::vector<int> nums = {1, 2, 3};
    std::cout << "\nProcess vector: " << process(nums) << " elements\n";
    std::cout << "Process empty: " << process(std::views::empty<int>) << " elements\n";

    // Use in conditional data retrieval
    std::cout << "\nWith data: ";
    for (int n : get_data(true)) std::cout << n << " ";
    std::cout << "\nWithout data: ";
    for (int n : get_data(false)) std::cout << n << " ";
    std::cout << "(nothing)\n";

    return 0;
}
