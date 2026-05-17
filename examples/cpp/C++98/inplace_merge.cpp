// CodeNebula - C++98 Example: inplace_merge
// Compile: g++ -std=c++98 -Wall -Wextra -o example inplace_merge.cpp

// std::inplace_merge merges two consecutive sorted subranges
// within the same container into a single sorted range, in-place.

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
    // Two sorted halves in one vector: [1,3,5,7] and [2,4,6,8]
    int arr[] = {1, 3, 5, 7, 2, 4, 6, 8};
    std::vector<int> v(arr, arr + 8);

    print_vec(v, "Before inplace_merge");

    // The midpoint separating the two sorted halves
    std::inplace_merge(v.begin(), v.begin() + 4, v.end());
    print_vec(v, "After inplace_merge");

    // Another example: three sorted runs merged in two steps
    int arr2[] = {10, 30, 50, 20, 40, 60};
    std::vector<int> w(arr2, arr2 + 6);
    print_vec(w, "Before (two runs)");

    std::inplace_merge(w.begin(), w.begin() + 3, w.end());
    print_vec(w, "After inplace_merge");

    return 0;
}

// Expected output:
// Before inplace_merge: 1 3 5 7 2 4 6 8
// After inplace_merge: 1 2 3 4 5 6 7 8
// Before (two runs): 10 30 50 20 40 60
// After inplace_merge: 10 20 30 40 50 60
