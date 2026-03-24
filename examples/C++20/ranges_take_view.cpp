// CodeNebula - C++20 Example: std::ranges::take_view
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_take_view.cpp

#include <ranges>
#include <vector>
#include <string>
#include <iostream>

// std::ranges::take_view / std::views::take produces a view of the
// first N elements from a range. If the range has fewer than N
// elements, all elements are included.

int main() {
    std::vector<int> nums = {10, 20, 30, 40, 50, 60, 70, 80};

    // Take first 3 elements
    auto first3 = nums | std::views::take(3);
    std::cout << "First 3: ";
    for (int n : first3) std::cout << n << " ";
    std::cout << "\n";

    // Take more than available - safely returns all
    auto take_100 = nums | std::views::take(100);
    std::cout << "Take 100 (only 8 exist): ";
    for (int n : take_100) std::cout << n << " ";
    std::cout << "\n";

    // Take zero elements
    auto take0 = nums | std::views::take(0);
    std::cout << "Take 0 empty: " << std::boolalpha
              << std::ranges::empty(take0) << "\n";

    // Combine with other views
    auto first_evens = nums
        | std::views::filter([](int n) { return n % 20 == 0; })
        | std::views::take(2);
    std::cout << "First 2 multiples of 20: ";
    for (int n : first_evens) std::cout << n << " ";
    std::cout << "\n";

    // Take from infinite range
    auto first_squares = std::views::iota(1)
        | std::views::transform([](int n) { return n * n; })
        | std::views::take(6);
    std::cout << "First 6 squares: ";
    for (int n : first_squares) std::cout << n << " ";
    std::cout << "\n";

    // take preserves sized_range when source is sized
    static_assert(std::ranges::sized_range<decltype(first3)>);
    std::cout << "first3 size: " << std::ranges::size(first3) << "\n";

    // Practical: paginated output
    std::vector<std::string> items = {
        "apple", "banana", "cherry", "date",
        "elderberry", "fig", "grape"
    };
    int page_size = 3;
    for (int page = 0; page * page_size < static_cast<int>(items.size()); ++page) {
        auto page_view = items | std::views::drop(page * page_size)
                               | std::views::take(page_size);
        std::cout << "Page " << page << ": ";
        for (const auto& s : page_view) std::cout << s << " ";
        std::cout << "\n";
    }

    return 0;
}
