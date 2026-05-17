// CodeNebula - C++20 Example: Ranges Heap Operations
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_heap.cpp

#include <algorithm>
#include <iostream>
#include <vector>

void print(const char* label, const std::vector<int>& v) {
    std::cout << label;
    for (int x : v) std::cout << x << ' ';
    std::cout << '\n';
}

int main() {
    // ranges::make_heap - build a max-heap from unsorted data
    std::vector<int> heap = {3, 1, 4, 1, 5, 9, 2, 6};
    print("Original:   ", heap);

    std::ranges::make_heap(heap);
    print("Make heap:  ", heap);

    // ranges::push_heap - add an element to the heap
    heap.push_back(8);
    std::ranges::push_heap(heap);
    print("Push 8:     ", heap);

    heap.push_back(7);
    std::ranges::push_heap(heap);
    print("Push 7:     ", heap);

    // ranges::pop_heap - move the largest element to the end
    std::ranges::pop_heap(heap);
    std::cout << "Popped max: " << heap.back() << '\n';
    heap.pop_back();
    print("After pop:  ", heap);

    // Pop another
    std::ranges::pop_heap(heap);
    std::cout << "Popped max: " << heap.back() << '\n';
    heap.pop_back();
    print("After pop:  ", heap);

    // ranges::sort_heap - sort a heap into ascending order
    std::vector<int> to_sort = {5, 3, 8, 1, 7, 2, 9, 4};
    std::ranges::make_heap(to_sort);
    print("\nHeap:       ", to_sort);

    std::ranges::sort_heap(to_sort);
    print("Sort heap:  ", to_sort);

    // Min-heap using greater comparator
    std::vector<int> min_heap = {6, 2, 8, 1, 4};
    std::ranges::make_heap(min_heap, std::ranges::greater{});
    print("\nMin heap:   ", min_heap);
    std::cout << "Min element at front: " << min_heap.front() << '\n';

    std::ranges::pop_heap(min_heap, std::ranges::greater{});
    std::cout << "Popped min: " << min_heap.back() << '\n';
    min_heap.pop_back();

    return 0;
}
