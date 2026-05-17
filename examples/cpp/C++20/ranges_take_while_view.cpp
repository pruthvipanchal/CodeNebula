// CodeNebula - C++20 Example: std::ranges::take_while_view
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_take_while_view.cpp

#include <ranges>
#include <vector>
#include <string>
#include <iostream>

// std::ranges::take_while_view / std::views::take_while produces a
// view of leading elements that satisfy a predicate. Iteration stops
// at the first element that does NOT satisfy the condition.

int main() {
    std::vector<int> nums = {2, 4, 6, 7, 8, 10, 12};

    // Take while elements are even
    auto leading_evens = nums | std::views::take_while([](int n) {
        return n % 2 == 0;
    });
    std::cout << "Leading evens: ";
    for (int n : leading_evens) std::cout << n << " ";
    std::cout << "\n";  // Output: 2 4 6 (stops at 7)

    // Take while elements are less than a threshold
    auto small = nums | std::views::take_while([](int n) { return n < 8; });
    std::cout << "While < 8: ";
    for (int n : small) std::cout << n << " ";
    std::cout << "\n";

    // Take while on sorted data - efficient prefix extraction
    std::vector<int> sorted = {1, 3, 5, 7, 9, 11, 13, 15};
    auto below10 = sorted | std::views::take_while([](int n) { return n < 10; });
    std::cout << "Below 10: ";
    for (int n : below10) std::cout << n << " ";
    std::cout << "\n";

    // With strings - take while alphabetic
    std::string input = "hello123world";
    auto alpha_prefix = input | std::views::take_while([](char c) {
        return std::isalpha(static_cast<unsigned char>(c));
    });
    std::cout << "Alpha prefix: ";
    for (char c : alpha_prefix) std::cout << c;
    std::cout << "\n";  // Output: hello

    // Combine with transform
    auto processed = nums
        | std::views::take_while([](int n) { return n < 10; })
        | std::views::transform([](int n) { return n * n; });
    std::cout << "Squared while < 10: ";
    for (int n : processed) std::cout << n << " ";
    std::cout << "\n";

    // Difference from take: take_while uses a predicate, take uses count
    auto take3 = nums | std::views::take(3);
    std::cout << "take(3):       ";
    for (int n : take3) std::cout << n << " ";
    std::cout << "\n";

    // take_while is NOT a sized_range (size unknown until iteration)
    static_assert(!std::ranges::sized_range<decltype(leading_evens)>);

    // Empty result if first element fails predicate
    auto none = nums | std::views::take_while([](int n) { return n > 100; });
    std::cout << "None match: " << std::boolalpha
              << std::ranges::empty(none) << "\n";

    return 0;
}
