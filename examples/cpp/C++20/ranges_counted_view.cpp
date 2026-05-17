// CodeNebula - C++20 Example: std::views::counted
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_counted_view.cpp

#include <ranges>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <iostream>

// std::views::counted creates a view from an iterator and a count,
// producing a span-like subrange of exactly N elements starting
// from the given position.

int main() {
    std::vector<int> vec = {10, 20, 30, 40, 50, 60, 70, 80};

    // Create a counted view: 4 elements starting at index 2
    auto sub = std::views::counted(vec.begin() + 2, 4);
    std::cout << "Counted(begin+2, 4): ";
    for (int n : sub) std::cout << n << " ";
    std::cout << "\n";  // Output: 30 40 50 60

    // Counted from beginning
    auto first3 = std::views::counted(vec.begin(), 3);
    std::cout << "First 3: ";
    for (int n : first3) std::cout << n << " ";
    std::cout << "\n";

    // Works with raw pointers
    int arr[] = {1, 2, 3, 4, 5, 6};
    auto from_ptr = std::views::counted(arr + 1, 3);
    std::cout << "From pointer: ";
    for (int n : from_ptr) std::cout << n << " ";
    std::cout << "\n";  // Output: 2 3 4

    // Works with non-random-access iterators (e.g., list)
    std::list<int> lst = {100, 200, 300, 400, 500};
    auto lst_sub = std::views::counted(std::next(lst.begin()), 3);
    std::cout << "List counted: ";
    for (int n : lst_sub) std::cout << n << " ";
    std::cout << "\n";  // Output: 200 300 400

    // Counted view is sized
    std::cout << "Counted size: " << std::ranges::size(sub) << "\n";

    // Use with algorithms
    auto counted = std::views::counted(vec.begin(), 5);
    auto sum = std::ranges::fold_left(counted, 0, std::plus<>{});
    std::cout << "Sum of first 5: " << sum << "\n";

    // Combine with other views
    auto filtered = std::views::counted(vec.begin(), 6)
        | std::views::filter([](int n) { return n > 30; });
    std::cout << "Counted+filtered: ";
    for (int n : filtered) std::cout << n << " ";
    std::cout << "\n";

    // Useful for processing chunks of raw data
    std::vector<double> data = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
    for (std::size_t i = 0; i + 2 <= data.size(); i += 2) {
        auto chunk = std::views::counted(data.begin() + i, 2);
        std::cout << "Chunk: ";
        for (double d : chunk) std::cout << d << " ";
        std::cout << "\n";
    }

    return 0;
}
