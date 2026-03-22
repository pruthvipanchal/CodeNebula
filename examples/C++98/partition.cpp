// CodeNebula - C++98 Example: partition
// Compile: g++ -std=c++98 -Wall -Wextra -o example partition.cpp

// std::partition reorders elements so that those satisfying a
// predicate come before those that do not. The relative order
// within each group is NOT guaranteed.

#include <iostream>
#include <vector>
#include <algorithm>

bool is_even(int x) {
    return x % 2 == 0;
}

bool is_negative(int x) {
    return x < 0;
}

void print_vec(const std::vector<int>& v, const char* label) {
    std::cout << label << ": ";
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Example 1: partition even / odd
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> v(arr, arr + 8);
    print_vec(v, "Original");

    std::vector<int>::iterator boundary =
        std::partition(v.begin(), v.end(), is_even);

    std::cout << "After partition (evens first):" << std::endl;
    std::cout << "  Evens: ";
    for (std::vector<int>::iterator it = v.begin(); it != boundary; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "  Odds:  ";
    for (std::vector<int>::iterator it = boundary; it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Example 2: partition negatives / non-negatives
    int arr2[] = {3, -1, 4, -5, 2, -3, 0};
    std::vector<int> w(arr2, arr2 + 7);
    print_vec(w, "Original");

    boundary = std::partition(w.begin(), w.end(), is_negative);
    std::cout << "Negative count: "
              << (boundary - w.begin()) << std::endl;

    return 0;
}

// Expected output (element order within groups may vary):
// Original: 1 2 3 4 5 6 7 8
// After partition (evens first):
//   Evens: 8 2 6 4
//   Odds:  5 3 7 1
// Original: 3 -1 4 -5 2 -3 0
// Negative count: 3
