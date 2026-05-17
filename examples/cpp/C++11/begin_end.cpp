// CodeNebula - C++11 Example: std::begin and std::end Free Functions
// Compile: g++ -std=c++11 -Wall -Wextra -o example begin_end.cpp

// std::begin() and std::end() are free functions that return iterators for
// any container or C-style array. They provide a uniform interface that
// works with both STL containers and raw arrays in generic code.

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

// Generic function that works with any container or array
template <typename Container>
void print_all(const Container& c, const char* label) {
    std::cout << label << ": ";
    for (auto it = std::begin(c); it != std::end(c); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template <typename Container>
bool contains(const Container& c, int value) {
    return std::find(std::begin(c), std::end(c), value) != std::end(c);
}

int main() {
    // Works with C-style arrays
    int arr[] = {5, 3, 8, 1, 9, 2};
    print_all(arr, "C-array");

    // Works with std::vector
    std::vector<int> vec = {10, 20, 30, 40, 50};
    print_all(vec, "Vector");

    // Use with algorithms on C-arrays (no need to calculate size)
    std::sort(std::begin(arr), std::end(arr));
    print_all(arr, "Sorted array");

    // Generic contains works for both types
    std::cout << "Array contains 8: " << std::boolalpha
              << contains(arr, 8) << std::endl;
    std::cout << "Vector contains 25: " << std::boolalpha
              << contains(vec, 25) << std::endl;

    // Use with std::distance to get size generically
    std::cout << "Array size: "
              << std::distance(std::begin(arr), std::end(arr)) << std::endl;
    std::cout << "Vector size: "
              << std::distance(std::begin(vec), std::end(vec)) << std::endl;

    // Copy array to vector using free functions
    std::vector<int> copy(std::begin(arr), std::end(arr));
    print_all(copy, "Copied");

    return 0;
}

// Expected output:
// C-array: 5 3 8 1 9 2
// Vector: 10 20 30 40 50
// Sorted array: 1 2 3 5 8 9
// Array contains 8: true
// Vector contains 25: false
// Array size: 6
// Vector size: 5
// Copied: 1 2 3 5 8 9
