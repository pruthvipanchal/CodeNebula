// CodeNebula - C++98 Example: push_heap
// Compile: g++ -std=c++98 -Wall -Wextra -o example push_heap.cpp

// std::push_heap inserts the element at the end of a heap range
// into the correct position to maintain the heap property.
// The range [first, last-1) must already be a valid heap.

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
    std::vector<int> heap;

    // Build a max-heap by pushing elements one at a time
    int values[] = {30, 10, 50, 20, 40};
    const int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; ++i) {
        heap.push_back(values[i]);
        std::push_heap(heap.begin(), heap.end());

        std::cout << "Pushed " << values[i] << " -> heap top: "
                  << heap.front() << std::endl;
    }

    print_vec(heap, "Final heap");
    std::cout << "Max element (front): " << heap.front() << std::endl;

    // Push one more
    heap.push_back(60);
    std::push_heap(heap.begin(), heap.end());
    std::cout << "After pushing 60, top: " << heap.front() << std::endl;

    return 0;
}

// Expected output:
// Pushed 30 -> heap top: 30
// Pushed 10 -> heap top: 30
// Pushed 50 -> heap top: 50
// Pushed 20 -> heap top: 50
// Pushed 40 -> heap top: 50
// Final heap: 50 40 30 10 20
// Max element (front): 50
// After pushing 60, top: 60
