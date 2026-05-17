// CodeNebula - C++11 Example: std::is_sorted_until
// Compile: g++ -std=c++11 -Wall -Wextra -o example is_sorted_until.cpp

// std::is_sorted_until returns an iterator to the first element that breaks
// the sorted order. All elements before the returned iterator form a sorted
// range. Returns end() if the entire range is sorted.

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
    // Partially sorted range
    std::vector<int> data = {1, 3, 5, 4, 7, 9};
    auto it = std::is_sorted_until(data.begin(), data.end());

    std::cout << "Data: ";
    for (const auto& n : data) std::cout << n << " ";
    std::cout << std::endl;

    if (it != data.end()) {
        std::cout << "Sorted until value: " << *it << std::endl;
        std::cout << "Sorted prefix length: "
                  << std::distance(data.begin(), it) << std::endl;
    }

    // Print the sorted prefix
    std::cout << "Sorted prefix: ";
    for (auto i = data.begin(); i != it; ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    // Fully sorted range returns end()
    std::vector<int> sorted = {1, 2, 3, 4, 5};
    auto end_it = std::is_sorted_until(sorted.begin(), sorted.end());
    std::cout << "Fully sorted - returned end: "
              << std::boolalpha << (end_it == sorted.end()) << std::endl;

    // With custom comparator (descending)
    std::vector<int> desc = {9, 7, 5, 8, 3, 1};
    auto desc_it = std::is_sorted_until(desc.begin(), desc.end(),
                                        std::greater<int>());
    std::cout << "Descending sorted until: " << *desc_it
              << " (prefix length: " << std::distance(desc.begin(), desc_it)
              << ")" << std::endl;

    // Find the longest sorted prefix in different data
    std::vector<int> mixed = {2, 4, 6, 8, 3, 5, 7};
    auto mix_it = std::is_sorted_until(mixed.begin(), mixed.end());
    std::cout << "Mixed: sorted prefix has "
              << std::distance(mixed.begin(), mix_it) << " elements" << std::endl;

    // Single element - trivially sorted
    std::vector<int> single = {42};
    auto s_it = std::is_sorted_until(single.begin(), single.end());
    std::cout << "Single element returns end: "
              << (s_it == single.end()) << std::endl;

    return 0;
}

// Expected output:
// Data: 1 3 5 4 7 9
// Sorted until value: 4
// Sorted prefix length: 3
// Sorted prefix: 1 3 5
// Fully sorted - returned end: true
// Descending sorted until: 8 (prefix length: 3)
// Mixed: sorted prefix has 4 elements
// Single element returns end: true
