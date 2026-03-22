// CodeNebula - C++98 Example: make_heap
// Compile: g++ -std=c++98 -Wall -Wextra -o example make_heap.cpp

// std::make_heap rearranges elements in a range to form a max-heap
// (by default). The largest element will be at the front. This runs
// in O(n) time, which is faster than pushing elements one by one.

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

void print_vec(const std::vector<int>& v, const char* label) {
    std::cout << label << ": ";
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
    const int n = sizeof(arr) / sizeof(arr[0]);
    std::vector<int> v(arr, arr + n);

    print_vec(v, "Original");

    // Build a max-heap (default)
    std::make_heap(v.begin(), v.end());
    print_vec(v, "Max-heap");
    std::cout << "Largest (front): " << v.front() << std::endl;

    // Build a min-heap using greater<int>
    std::vector<int> v2(arr, arr + n);
    std::make_heap(v2.begin(), v2.end(), std::greater<int>());
    print_vec(v2, "Min-heap");
    std::cout << "Smallest (front): " << v2.front() << std::endl;

    // Verify heap property manually: parent >= children
    // For index i, children are at 2i+1 and 2i+2
    bool valid = true;
    for (std::vector<int>::size_type i = 0; i < v.size(); ++i) {
        std::vector<int>::size_type left = 2 * i + 1;
        std::vector<int>::size_type right = 2 * i + 2;
        if (left < v.size() && v[i] < v[left]) valid = false;
        if (right < v.size() && v[i] < v[right]) valid = false;
    }
    std::cout << "Is valid max-heap? " << (valid ? "yes" : "no")
              << std::endl;

    return 0;
}

// Expected output:
// Original: 3 1 4 1 5 9 2 6
// Max-heap: 9 6 4 1 5 3 2 1
// Largest (front): 9
// Min-heap: 1 1 2 3 5 9 4 6
// Smallest (front): 1
// Is valid max-heap? yes
