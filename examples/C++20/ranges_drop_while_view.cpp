// CodeNebula - C++20 Example: std::ranges::drop_while_view
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_drop_while_view.cpp

#include <ranges>
#include <vector>
#include <string>
#include <iostream>

// std::ranges::drop_while_view / std::views::drop_while skips
// leading elements that satisfy a predicate, then yields all
// remaining elements (even if they match the predicate later).

int main() {
    std::vector<int> nums = {2, 4, 6, 7, 8, 10, 3, 12};

    // Drop while even - stops at first odd
    auto after_evens = nums | std::views::drop_while([](int n) {
        return n % 2 == 0;
    });
    std::cout << "After leading evens: ";
    for (int n : after_evens) std::cout << n << " ";
    std::cout << "\n";  // Output: 7 8 10 3 12 (note: 8,10,12 included)

    // Drop while less than threshold
    std::vector<int> sorted = {1, 3, 5, 7, 9, 11, 13};
    auto from10 = sorted | std::views::drop_while([](int n) { return n < 10; });
    std::cout << "From >= 10: ";
    for (int n : from10) std::cout << n << " ";
    std::cout << "\n";

    // Skip whitespace prefix in a string
    std::string text = "   Hello, World!";
    auto trimmed = text | std::views::drop_while([](char c) {
        return std::isspace(static_cast<unsigned char>(c));
    });
    std::cout << "Trimmed: '";
    for (char c : trimmed) std::cout << c;
    std::cout << "'\n";

    // Skip negative values to find first non-negative
    std::vector<int> mixed = {-5, -3, -1, 0, 2, -4, 6};
    auto from_nonneg = mixed | std::views::drop_while([](int n) {
        return n < 0;
    });
    std::cout << "From non-negative: ";
    for (int n : from_nonneg) std::cout << n << " ";
    std::cout << "\n";  // Output: 0 2 -4 6

    // Combine with take_while for extracting a segment
    auto segment = nums
        | std::views::drop_while([](int n) { return n < 6; })
        | std::views::take_while([](int n) { return n <= 10; });
    std::cout << "Segment [6..10]: ";
    for (int n : segment) std::cout << n << " ";
    std::cout << "\n";

    // All elements dropped if all match predicate
    auto all_dropped = nums | std::views::drop_while([](int) { return true; });
    std::cout << "All dropped empty: " << std::boolalpha
              << std::ranges::empty(all_dropped) << "\n";

    // None dropped if first element fails predicate
    auto none_dropped = nums | std::views::drop_while([](int) { return false; });
    std::cout << "None dropped size matches: "
              << (std::ranges::distance(none_dropped)
                  == static_cast<long long>(nums.size())) << "\n";

    return 0;
}
