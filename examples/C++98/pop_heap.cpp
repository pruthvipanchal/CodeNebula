// CodeNebula - C++98 Example: pop_heap
// Compile: g++ -std=c++98 -Wall -Wextra -o example pop_heap.cpp

// std::pop_heap moves the largest element (front) to the end of
// the range and re-heapifies [first, last-1). You then call
// pop_back() on the container to actually remove it.

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
    int arr[] = {10, 20, 30, 40, 50};
    std::vector<int> heap(arr, arr + 5);

    // First, make a valid heap
    std::make_heap(heap.begin(), heap.end());
    print_vec(heap, "Heap");
    std::cout << "Max: " << heap.front() << std::endl;

    // Pop the max element
    std::pop_heap(heap.begin(), heap.end());
    int popped = heap.back();
    heap.pop_back();
    std::cout << "Popped: " << popped << std::endl;
    std::cout << "New max: " << heap.front() << std::endl;

    // Pop again
    std::pop_heap(heap.begin(), heap.end());
    popped = heap.back();
    heap.pop_back();
    std::cout << "Popped: " << popped << std::endl;
    std::cout << "New max: " << heap.front() << std::endl;

    print_vec(heap, "Remaining heap");

    return 0;
}

// Expected output:
// Heap: 50 40 30 10 20
// Max: 50
// Popped: 50
// New max: 40
// Popped: 40
// New max: 30
// Remaining heap: 30 10 20
