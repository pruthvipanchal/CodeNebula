// CodeNebula - C++11 Example: std::is_heap Check
// Compile: g++ -std=c++11 -Wall -Wextra -o example is_heap.cpp

// std::is_heap checks whether a range satisfies the max-heap property:
// every parent element is greater than or equal to its children.
// A custom comparator can be used for min-heap or other orderings.

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // A valid max-heap
    std::vector<int> heap = {9, 5, 8, 1, 3, 6, 7};
    std::cout << "Max-heap {9,5,8,1,3,6,7}: " << std::boolalpha
              << std::is_heap(heap.begin(), heap.end()) << std::endl;

    // Not a heap (parent 5 < child 6 violates max-heap property)
    std::vector<int> not_heap = {9, 5, 8, 1, 3, 10, 7};
    std::cout << "Not heap {9,5,8,1,3,10,7}: "
              << std::is_heap(not_heap.begin(), not_heap.end()) << std::endl;

    // Build a heap from unsorted data
    std::vector<int> data = {3, 1, 4, 1, 5, 9, 2, 6};
    std::cout << "Before make_heap: "
              << std::is_heap(data.begin(), data.end()) << std::endl;

    std::make_heap(data.begin(), data.end());
    std::cout << "After make_heap: "
              << std::is_heap(data.begin(), data.end()) << std::endl;

    std::cout << "Heap contents: ";
    for (const auto& n : data) std::cout << n << " ";
    std::cout << std::endl;

    // Check min-heap with custom comparator
    std::vector<int> min_heap = {1, 3, 2, 5, 4, 8, 7};
    std::cout << "Min-heap with greater<>: "
              << std::is_heap(min_heap.begin(), min_heap.end(),
                              std::greater<int>()) << std::endl;

    // Push and pop maintain heap property
    data.push_back(15);
    std::push_heap(data.begin(), data.end());
    std::cout << "After push_heap(15): "
              << std::is_heap(data.begin(), data.end()) << std::endl;

    std::pop_heap(data.begin(), data.end());
    data.pop_back();
    std::cout << "After pop_heap: "
              << std::is_heap(data.begin(), data.end()) << std::endl;

    // Empty and single-element ranges are heaps
    std::vector<int> empty;
    std::vector<int> single = {42};
    std::cout << "Empty: " << std::is_heap(empty.begin(), empty.end()) << std::endl;
    std::cout << "Single: " << std::is_heap(single.begin(), single.end()) << std::endl;

    return 0;
}

// Expected output:
// Max-heap {9,5,8,1,3,6,7}: true
// Not heap {9,5,8,1,3,10,7}: false
// Before make_heap: false
// After make_heap: true
// Heap contents: 9 6 4 3 5 1 2 1 (order may vary by implementation)
// Min-heap with greater<>: true
// After push_heap(15): true
// After pop_heap: true
// Empty: true
// Single: true
