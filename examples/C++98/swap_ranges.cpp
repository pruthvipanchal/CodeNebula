// CodeNebula - C++98 Example: swap_ranges
// Compile: g++ -std=c++98 -Wall -Wextra -o example swap_ranges.cpp

// std::swap_ranges swaps elements between two ranges element by element.
// The ranges must not overlap. Returns an iterator to the element past
// the last swapped element in the second range.

#include <iostream>
#include <vector>
#include <algorithm>

void print_vec(const char* label, const std::vector<int>& v) {
    std::cout << label;
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {10, 20, 30, 40, 50};
    std::vector<int> v1(a, a + 5);
    std::vector<int> v2(b, b + 5);

    print_vec("v1 before: ", v1);
    print_vec("v2 before: ", v2);

    // Swap all elements between v1 and v2
    std::swap_ranges(v1.begin(), v1.end(), v2.begin());

    print_vec("v1 after:  ", v1);
    print_vec("v2 after:  ", v2);

    // Swap only a sub-range (first 2 elements)
    std::swap_ranges(v1.begin(), v1.begin() + 2, v2.begin());

    std::cout << std::endl;
    print_vec("After partial swap v1: ", v1);
    print_vec("After partial swap v2: ", v2);

    // Swap between two halves of the same vector (non-overlapping)
    int arr[] = {1, 2, 3, 4, 5, 6};
    std::vector<int> v(arr, arr + 6);
    print_vec("\nSingle vec before: ", v);

    std::swap_ranges(v.begin(), v.begin() + 3, v.begin() + 3);
    print_vec("Halves swapped:    ", v);

    return 0;
}

// Expected output:
// v1 before: 1 2 3 4 5
// v2 before: 10 20 30 40 50
// v1 after:  10 20 30 40 50
// v2 after:  1 2 3 4 5
//
// After partial swap v1: 1 2 30 40 50
// After partial swap v2: 10 20 3 4 5
//
// Single vec before: 1 2 3 4 5 6
// Halves swapped:    4 5 6 1 2 3
