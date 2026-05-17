// CodeNebula - C++98 Example: search_n
// Compile: g++ -std=c++98 -Wall -Wextra -o example search_n.cpp

// std::search_n searches for N consecutive copies of a given value in a range.
// Returns an iterator to the start of the run, or last if not found.

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    std::vector<int> v(arr, arr + 10);

    std::cout << "Sequence: ";
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Find 3 consecutive 3s
    std::vector<int>::iterator it = std::search_n(v.begin(), v.end(), 3, 3);
    if (it != v.end()) {
        std::cout << "Three 3s found at index " << (it - v.begin()) << std::endl;
    }

    // Find 4 consecutive 4s
    it = std::search_n(v.begin(), v.end(), 4, 4);
    if (it != v.end()) {
        std::cout << "Four 4s found at index " << (it - v.begin()) << std::endl;
    }

    // Find 2 consecutive 2s
    it = std::search_n(v.begin(), v.end(), 2, 2);
    if (it != v.end()) {
        std::cout << "Two 2s found at index " << (it - v.begin()) << std::endl;
    }

    // Search for a run that does not exist
    it = std::search_n(v.begin(), v.end(), 5, 4);
    if (it == v.end()) {
        std::cout << "Five 4s not found" << std::endl;
    }

    return 0;
}

// Expected output:
// Sequence: 1 2 2 3 3 3 4 4 4 4
// Three 3s found at index 3
// Four 4s found at index 6
// Two 2s found at index 1
// Five 4s not found
