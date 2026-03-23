// CodeNebula - C++11 Example: std::array Fixed-Size Container
// Compile: g++ -std=c++11 -Wall -Wextra -o example array.cpp

// std::array is a fixed-size container that wraps a C-style array.
// Unlike raw arrays, it knows its size, supports iterators, and
// can be passed by value. It has zero overhead over C arrays.

#include <iostream>
#include <array>
#include <algorithm>

int main() {
    // Create and initialize an array of 5 integers
    std::array<int, 5> nums = {10, 20, 30, 40, 50};

    // Access elements
    std::cout << "First element: " << nums.front() << std::endl;
    std::cout << "Last element: " << nums.back() << std::endl;
    std::cout << "Element at index 2: " << nums.at(2) << std::endl;

    // Size is always known at compile time
    std::cout << "Size: " << nums.size() << std::endl;
    std::cout << "Is empty: " << std::boolalpha << nums.empty() << std::endl;

    // Range-based for loop works naturally
    std::cout << "All elements: ";
    for (const auto& n : nums) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // Works with standard algorithms
    std::sort(nums.begin(), nums.end(), std::greater<int>());
    std::cout << "Sorted descending: ";
    for (const auto& n : nums) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // Fill entire array with a single value
    std::array<int, 4> filled;
    filled.fill(42);
    std::cout << "Filled array: ";
    for (const auto& n : filled) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // Direct access to underlying data
    int* raw = nums.data();
    std::cout << "Raw pointer access [0]: " << raw[0] << std::endl;

    return 0;
}

// Expected output:
// First element: 10
// Last element: 50
// Element at index 2: 30
// Size: 5
// Is empty: false
// All elements: 10 20 30 40 50
// Sorted descending: 50 40 30 20 10
// Filled array: 42 42 42 42
// Raw pointer access [0]: 50
