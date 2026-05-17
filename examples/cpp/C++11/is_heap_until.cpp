// CodeNebula - C++11 Example: std::is_heap_until
// Compile: g++ -std=c++11 -Wall -Wextra -o example is_heap_until.cpp

// std::is_heap_until returns an iterator to the first element that violates
// the heap property. All elements before the returned iterator form a valid
// heap. Returns end() if the entire range is a valid heap.

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
    // Partially valid heap
    std::vector<int> data = {9, 5, 7, 1, 3, 10, 2};

    std::cout << "Data: ";
    for (const auto& n : data) std::cout << n << " ";
    std::cout << std::endl;

    auto it = std::is_heap_until(data.begin(), data.end());
    if (it != data.end()) {
        std::cout << "Heap property broken at value: " << *it << std::endl;
        std::cout << "Valid heap prefix length: "
                  << std::distance(data.begin(), it) << std::endl;
    }

    // Print the valid heap prefix
    std::cout << "Valid heap prefix: ";
    for (auto i = data.begin(); i != it; ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    // Fully valid heap
    std::vector<int> heap = {9, 5, 8, 1, 3, 6, 7};
    auto heap_it = std::is_heap_until(heap.begin(), heap.end());
    std::cout << "\nFull heap {9,5,8,1,3,6,7} - returned end: "
              << std::boolalpha << (heap_it == heap.end()) << std::endl;

    // Build heap and verify
    std::vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6};
    std::make_heap(nums.begin(), nums.end());
    auto check = std::is_heap_until(nums.begin(), nums.end());
    std::cout << "After make_heap, valid until end: "
              << (check == nums.end()) << std::endl;

    // Corrupt the heap and find where it breaks
    nums[3] = 100;  // violate heap property
    auto broken = std::is_heap_until(nums.begin(), nums.end());
    if (broken != nums.end()) {
        std::cout << "After corruption, heap breaks at index: "
                  << std::distance(nums.begin(), broken) << std::endl;
    }

    // Min-heap with custom comparator
    std::vector<int> min_data = {1, 3, 2, 5, 4, 10, 7};
    auto min_it = std::is_heap_until(min_data.begin(), min_data.end(),
                                     std::greater<int>());
    std::cout << "Min-heap valid prefix length: "
              << std::distance(min_data.begin(), min_it) << std::endl;

    return 0;
}

// Expected output:
// Data: 9 5 7 1 3 10 2
// Heap property broken at value: 10
// Valid heap prefix length: 5
// Valid heap prefix: 9 5 7 1 3
// Full heap {9,5,8,1,3,6,7} - returned end: true
// After make_heap, valid until end: true
// After corruption, heap breaks at index: <depends on heap layout>
// Min-heap valid prefix length: <depends on validity>
