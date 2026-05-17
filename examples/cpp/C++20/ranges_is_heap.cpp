// CodeNebula - C++20 Example: Ranges Is Heap
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_is_heap.cpp

#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>

void print(const char* label, const std::vector<int>& v) {
    std::cout << label;
    for (int x : v) std::cout << x << ' ';
    std::cout << '\n';
}

int main() {
    // ranges::is_heap - check if range satisfies max-heap property
    std::vector<int> heap = {9, 7, 8, 3, 5, 6, 4, 1, 2};
    std::vector<int> not_heap = {1, 5, 3, 7, 2};

    print("Heap:     ", heap);
    print("Not heap: ", not_heap);

    std::cout << "is_heap(heap)?     "
              << (std::ranges::is_heap(heap) ? "yes" : "no") << '\n';
    std::cout << "is_heap(not_heap)? "
              << (std::ranges::is_heap(not_heap) ? "yes" : "no") << '\n';

    // Verify after make_heap
    std::ranges::make_heap(not_heap);
    print("\nAfter make_heap: ", not_heap);
    std::cout << "is_heap now? "
              << (std::ranges::is_heap(not_heap) ? "yes" : "no") << '\n';

    // ranges::is_heap_until - find where the heap property breaks
    std::vector<int> partial = {9, 7, 8, 3, 10, 6};
    print("\nPartial: ", partial);
    auto boundary = std::ranges::is_heap_until(partial);
    std::cout << "Heap until index " << (boundary - partial.begin())
              << " (value " << *boundary << ")\n";

    // Fully valid heap returns end
    auto end_it = std::ranges::is_heap_until(heap);
    std::cout << "Valid heap until end? "
              << (end_it == heap.end() ? "yes" : "no") << '\n';

    // Min-heap check using greater comparator
    std::vector<int> min_heap = {1, 3, 2, 7, 5, 8, 4};
    print("\nMin heap: ", min_heap);
    bool is_min = std::ranges::is_heap(min_heap, std::ranges::greater{});
    std::cout << "is_heap (min, greater)? " << (is_min ? "yes" : "no") << '\n';

    // Demonstrate heap corruption
    std::vector<int> good = {10, 8, 9, 4, 5, 6, 7};
    print("\nGood heap: ", good);
    std::cout << "is_heap? " << (std::ranges::is_heap(good) ? "yes" : "no") << '\n';

    good[3] = 99;  // corrupt the heap
    print("Corrupted: ", good);
    std::cout << "is_heap? " << (std::ranges::is_heap(good) ? "yes" : "no") << '\n';

    auto brk = std::ranges::is_heap_until(good);
    std::cout << "Heap breaks at index " << (brk - good.begin()) << '\n';

    return 0;
}
