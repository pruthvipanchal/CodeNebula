// CodeNebula - C++98 Example: adjacent_find
// Compile: g++ -std=c++98 -Wall -Wextra -o example adjacent_find.cpp

// std::adjacent_find searches for the first pair of consecutive equal elements
// in [first, last). An optional binary predicate can customize the comparison.

#include <iostream>
#include <vector>
#include <algorithm>

bool both_odd(int a, int b) {
    return (a % 2 != 0) && (b % 2 != 0);
}

int main() {
    int arr[] = {1, 2, 3, 3, 4, 5, 5, 6};
    std::vector<int> v(arr, arr + 8);

    std::cout << "Sequence: ";
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Find first pair of equal adjacent elements
    std::vector<int>::iterator it = std::adjacent_find(v.begin(), v.end());
    if (it != v.end()) {
        std::cout << "First adjacent pair: " << *it
                  << " at index " << (it - v.begin()) << std::endl;
    }

    // Find next pair after the first
    it = std::adjacent_find(it + 1, v.end());
    if (it != v.end()) {
        std::cout << "Next adjacent pair: " << *it
                  << " at index " << (it - v.begin()) << std::endl;
    }

    // Use a custom predicate: find adjacent odd numbers
    int arr2[] = {2, 4, 3, 7, 6, 8};
    std::vector<int> v2(arr2, arr2 + 6);
    it = std::adjacent_find(v2.begin(), v2.end(), both_odd);
    if (it != v2.end()) {
        std::cout << "Adjacent odds: " << *it << " and " << *(it + 1)
                  << " at index " << (it - v2.begin()) << std::endl;
    }

    return 0;
}

// Expected output:
// Sequence: 1 2 3 3 4 5 5 6
// First adjacent pair: 3 at index 2
// Next adjacent pair: 5 at index 5
// Adjacent odds: 3 and 7 at index 2
