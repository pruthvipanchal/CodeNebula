// CodeNebula - C++98 Example: unique
// Compile: g++ -std=c++98 -Wall -Wextra -o example unique.cpp

// std::unique removes consecutive duplicate elements in-place.
// It returns an iterator to the new logical end. Elements past
// that iterator are unspecified. Typically used after sorting.

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

bool same_tens(int a, int b) {
    return (a / 10) == (b / 10);
}

int main() {
    // Example 1: basic unique on sorted data
    int arr[] = {1, 1, 2, 2, 2, 3, 4, 4, 5};
    const int n = sizeof(arr) / sizeof(arr[0]);
    std::vector<int> v(arr, arr + n);

    print_vec(v, "Before unique");

    std::vector<int>::iterator new_end = std::unique(v.begin(), v.end());
    v.erase(new_end, v.end());  // erase the leftover tail
    print_vec(v, "After unique + erase");

    // Example 2: unique with custom predicate
    int arr2[] = {10, 12, 15, 21, 25, 30, 35};
    std::vector<int> w(arr2, arr2 + 7);
    print_vec(w, "Before unique (same tens)");

    new_end = std::unique(w.begin(), w.end(), same_tens);
    w.erase(new_end, w.end());
    print_vec(w, "After unique (same tens)");

    return 0;
}

// Expected output:
// Before unique: 1 1 2 2 2 3 4 4 5
// After unique + erase: 1 2 3 4 5
// Before unique (same tens): 10 12 15 21 25 30 35
// After unique (same tens): 10 21 30
