// CodeNebula - C++98 Example: sort_heap
// Compile: g++ -std=c++98 -Wall -Wextra -o example sort_heap.cpp

// std::sort_heap sorts a range that is already a valid heap into
// ascending order. After sort_heap, the range is sorted but is
// no longer a heap.

#include <iostream>
#include <vector>
#include <algorithm>

void print_vec(const std::vector<int>& v, const char* label) {
    std::cout << label << ": ";
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    int arr[] = {7, 2, 9, 4, 1, 5, 8, 3, 6};
    const int n = sizeof(arr) / sizeof(arr[0]);
    std::vector<int> v(arr, arr + n);

    print_vec(v, "Original");

    // Step 1: make a heap
    std::make_heap(v.begin(), v.end());
    print_vec(v, "After make_heap");
    std::cout << "Front (max): " << v.front() << std::endl;

    // Step 2: sort the heap
    std::sort_heap(v.begin(), v.end());
    print_vec(v, "After sort_heap");

    // The two-step pattern (make_heap + sort_heap) is equivalent
    // to heapsort, giving O(n log n) sorting.
    std::cout << "This is heapsort!" << std::endl;

    return 0;
}

// Expected output:
// Original: 7 2 9 4 1 5 8 3 6
// After make_heap: 9 7 8 6 1 5 2 3 4
// Front (max): 9
// After sort_heap: 1 2 3 4 5 6 7 8 9
// This is heapsort!
