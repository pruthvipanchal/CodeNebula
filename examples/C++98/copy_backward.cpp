// CodeNebula - C++98 Example: copy_backward
// Compile: g++ -std=c++98 -Wall -Wextra -o example copy_backward.cpp

// std::copy_backward copies elements from [first, last) into a destination
// range ending at d_last, copying from back to front. This is useful when
// source and destination ranges overlap and the destination starts after source.

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
    // Basic copy_backward into another vector
    int arr[] = {1, 2, 3, 4, 5};
    std::vector<int> src(arr, arr + 5);
    std::vector<int> dst(5, 0);

    std::copy_backward(src.begin(), src.end(), dst.end());
    print_vec("Source:      ", src);
    print_vec("Destination: ", dst);

    // Shift elements right within the same vector (overlapping ranges)
    // Move elements [0..2] to positions [2..4], preserving order
    int arr2[] = {10, 20, 30, 0, 0};
    std::vector<int> v(arr2, arr2 + 5);
    print_vec("Before shift: ", v);

    std::copy_backward(v.begin(), v.begin() + 3, v.begin() + 5);
    print_vec("After shift:  ", v);

    return 0;
}

// Expected output:
// Source:      1 2 3 4 5
// Destination: 1 2 3 4 5
// Before shift: 10 20 30 0 0
// After shift:  10 20 10 20 30
