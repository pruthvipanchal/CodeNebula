// CodeNebula - C++98 Example: partial_sort
// Compile: g++ -std=c++98 -Wall -Wextra -o example partial_sort.cpp

// std::partial_sort rearranges elements so that the first N
// elements are the smallest N in sorted order. The remaining
// elements are in unspecified order. Useful when you only need
// the top-N results.

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
    int arr[] = {9, 3, 7, 1, 5, 8, 2, 6, 4};
    const int n = sizeof(arr) / sizeof(arr[0]);
    std::vector<int> v(arr, arr + n);

    print_vec(v, "Original");

    // Sort only the first 3 smallest elements into position
    std::partial_sort(v.begin(), v.begin() + 3, v.end());
    std::cout << "After partial_sort (first 3): ";
    for (int i = 0; i < 3; ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << "(rest unspecified)" << std::endl;

    // Sort the first 5 smallest with descending comparator
    std::vector<int> v2(arr, arr + n);
    std::partial_sort(v2.begin(), v2.begin() + 5, v2.end(),
                      std::greater<int>());
    std::cout << "Top 5 descending: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << v2[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Original: 9 3 7 1 5 8 2 6 4
// After partial_sort (first 3): 1 2 3 (rest unspecified)
// Top 5 descending: 9 8 7 6 5
