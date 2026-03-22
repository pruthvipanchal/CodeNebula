// CodeNebula - C++98 Example: find
// Compile: g++ -std=c++98 -Wall -Wextra -o example find.cpp

// std::find searches for the first element equal to a given value in [first, last).
// Returns an iterator to the found element, or last if not found.

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int arr[] = {4, 7, 2, 9, 1, 5, 3};
    std::vector<int> v(arr, arr + 7);

    // Find an element that exists
    std::vector<int>::iterator it = std::find(v.begin(), v.end(), 9);
    if (it != v.end()) {
        std::cout << "Found 9 at index " << (it - v.begin()) << std::endl;
    }

    // Find an element that does not exist
    it = std::find(v.begin(), v.end(), 42);
    if (it == v.end()) {
        std::cout << "42 not found in the vector" << std::endl;
    }

    // Find in a plain array
    int* p = std::find(arr, arr + 7, 1);
    if (p != arr + 7) {
        std::cout << "Found 1 in array at index " << (p - arr) << std::endl;
    }

    // Find starting from a specific position
    it = std::find(v.begin() + 3, v.end(), 5);
    if (it != v.end()) {
        std::cout << "Found 5 at index " << (it - v.begin()) << std::endl;
    }

    return 0;
}

// Expected output:
// Found 9 at index 3
// 42 not found in the vector
// Found 1 in array at index 4
// Found 5 at index 5
