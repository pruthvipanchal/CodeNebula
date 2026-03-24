// CodeNebula - C++20 Example: Ranges Swap Ranges
// Compile: g++ -std=c++20 -Wall -Wextra -o example shift.cpp

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

void print(const char* label, const std::vector<int>& v) {
    std::cout << label;
    for (int x : v) std::cout << x << ' ';
    std::cout << '\n';
}

int main() {
    // ranges::swap_ranges - swap elements between two ranges
    std::vector<int> a = {1, 2, 3, 4, 5};
    std::vector<int> b = {10, 20, 30, 40, 50};

    print("A before: ", a);
    print("B before: ", b);

    std::ranges::swap_ranges(a, b);
    print("A after:  ", a);
    print("B after:  ", b);

    // Swap partial ranges (first 3 elements)
    std::vector<int> x = {1, 2, 3, 4, 5};
    std::vector<int> y = {90, 80, 70, 60, 50};

    std::ranges::swap_ranges(
        std::ranges::subrange(x.begin(), x.begin() + 3),
        std::ranges::subrange(y.begin(), y.begin() + 3));
    print("\nPartial swap X: ", x);
    print("Partial swap Y: ", y);

    // Swap non-overlapping sections within the same container
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8};
    print("\nBefore internal swap: ", data);
    std::ranges::swap_ranges(
        std::ranges::subrange(data.begin(), data.begin() + 4),
        std::ranges::subrange(data.begin() + 4, data.end()));
    print("After internal swap:  ", data);

    // Swap ranges of different sizes (swaps up to the shorter)
    std::vector<int> short_v = {100, 200};
    std::vector<int> long_v = {1, 2, 3, 4, 5};
    std::ranges::swap_ranges(short_v, long_v);
    print("\nShort after: ", short_v);
    print("Long after:  ", long_v);

    // Swap with strings
    std::vector<std::string> names1 = {"Alice", "Bob", "Carol"};
    std::vector<std::string> names2 = {"Xena", "Yuri", "Zara"};

    std::ranges::swap_ranges(names1, names2);
    std::cout << "\nNames1: ";
    for (const auto& n : names1) std::cout << n << ' ';
    std::cout << "\nNames2: ";
    for (const auto& n : names2) std::cout << n << ' ';
    std::cout << '\n';

    return 0;
}
