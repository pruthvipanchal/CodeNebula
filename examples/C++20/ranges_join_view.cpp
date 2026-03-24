// CodeNebula - C++20 Example: std::ranges::join_view
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_join_view.cpp

#include <ranges>
#include <vector>
#include <string>
#include <array>
#include <iostream>

// std::ranges::join_view / std::views::join flattens a range of
// ranges into a single contiguous view of elements.

int main() {
    // Flatten a vector of vectors
    std::vector<std::vector<int>> nested = {
        {1, 2, 3}, {4, 5}, {6, 7, 8, 9}
    };
    auto flat = nested | std::views::join;
    std::cout << "Flattened: ";
    for (int n : flat) std::cout << n << " ";
    std::cout << "\n";

    // Flatten array of arrays
    std::array<std::array<int, 3>, 3> matrix = {{
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9}
    }};
    auto flat_matrix = matrix | std::views::join;
    std::cout << "Flat matrix: ";
    for (int n : flat_matrix) std::cout << n << " ";
    std::cout << "\n";

    // Join strings (vector of strings -> view of chars)
    std::vector<std::string> words = {"Hello", " ", "World", "!"};
    auto joined_chars = words | std::views::join;
    std::cout << "Joined chars: ";
    for (char c : joined_chars) std::cout << c;
    std::cout << "\n";

    // Join with filter - flatten then filter
    auto flat_evens = nested
        | std::views::join
        | std::views::filter([](int n) { return n % 2 == 0; });
    std::cout << "Flat evens: ";
    for (int n : flat_evens) std::cout << n << " ";
    std::cout << "\n";

    // Join with transform - transform inner ranges then flatten
    auto doubled_flat = nested
        | std::views::transform([](const auto& inner) {
            return inner | std::views::transform([](int n) { return n * 2; });
        })
        | std::views::join;
    std::cout << "Doubled flat: ";
    for (int n : doubled_flat) std::cout << n << " ";
    std::cout << "\n";

    // Empty inner ranges are handled gracefully
    std::vector<std::vector<int>> sparse = {{1}, {}, {2, 3}, {}, {4}};
    std::cout << "Sparse joined: ";
    for (int n : sparse | std::views::join) std::cout << n << " ";
    std::cout << "\n";
    return 0;
}
