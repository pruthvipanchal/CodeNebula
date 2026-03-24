// CodeNebula - C++20 Example: std::ranges::drop_view
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_drop_view.cpp

#include <ranges>
#include <vector>
#include <string>
#include <iostream>

// std::ranges::drop_view / std::views::drop skips the first N
// elements and produces a view of the remaining elements.

int main() {
    std::vector<int> nums = {10, 20, 30, 40, 50, 60, 70};

    // Drop first 3 elements
    auto after3 = nums | std::views::drop(3);
    std::cout << "After dropping 3: ";
    for (int n : after3) std::cout << n << " ";
    std::cout << "\n";  // Output: 40 50 60 70

    // Drop more than available - yields empty range
    auto drop_100 = nums | std::views::drop(100);
    std::cout << "Drop 100 empty: " << std::boolalpha
              << std::ranges::empty(drop_100) << "\n";

    // Drop 0 - yields all elements
    auto drop0 = nums | std::views::drop(0);
    std::cout << "Drop 0 size: " << std::ranges::size(drop0) << "\n";

    // Combine drop and take for slicing
    auto slice = nums | std::views::drop(2) | std::views::take(3);
    std::cout << "Slice [2..5): ";
    for (int n : slice) std::cout << n << " ";
    std::cout << "\n";  // Output: 30 40 50

    // Skip header rows in data
    std::vector<std::string> csv_lines = {
        "Name,Age,City",       // header
        "Alice,30,New York",
        "Bob,25,London",
        "Carol,35,Tokyo"
    };
    auto data_rows = csv_lines | std::views::drop(1);
    std::cout << "\nData rows (skipping header):\n";
    for (const auto& line : data_rows) {
        std::cout << "  " << line << "\n";
    }

    // drop preserves sized_range
    static_assert(std::ranges::sized_range<decltype(after3)>);
    std::cout << "\nDrop 3 size: " << std::ranges::size(after3) << "\n";

    // drop preserves random_access_range
    static_assert(std::ranges::random_access_range<decltype(after3)>);
    std::cout << "after3[0]: " << after3[0] << "\n";

    // Pagination using drop + take
    std::vector<int> all_items = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int page_size = 3;
    int page = 1;  // 0-indexed
    auto page_view = all_items | std::views::drop(page * page_size)
                                | std::views::take(page_size);
    std::cout << "\nPage 1 (size 3): ";
    for (int n : page_view) std::cout << n << " ";
    std::cout << "\n";

    return 0;
}
