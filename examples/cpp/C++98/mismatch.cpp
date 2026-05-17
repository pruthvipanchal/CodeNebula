// CodeNebula - C++98 Example: mismatch
// Compile: g++ -std=c++98 -Wall -Wextra -o example mismatch.cpp

// std::mismatch compares two ranges element by element and returns a pair of
// iterators pointing to the first position where they differ.

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 9, 4, 5};
    std::vector<int> v1(arr1, arr1 + 5);
    std::vector<int> v2(arr2, arr2 + 5);

    std::cout << "Range 1: ";
    for (std::vector<int>::iterator it = v1.begin(); it != v1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Range 2: ";
    for (std::vector<int>::iterator it = v2.begin(); it != v2.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Find the first mismatch
    std::pair<std::vector<int>::iterator, std::vector<int>::iterator> result =
        std::mismatch(v1.begin(), v1.end(), v2.begin());

    if (result.first != v1.end()) {
        std::cout << "First mismatch at index "
                  << (result.first - v1.begin())
                  << ": " << *result.first << " vs " << *result.second
                  << std::endl;
    }

    // Compare identical ranges
    int arr3[] = {1, 2, 3, 4, 5};
    std::vector<int> v3(arr3, arr3 + 5);
    result = std::mismatch(v1.begin(), v1.end(), v3.begin());
    if (result.first == v1.end()) {
        std::cout << "v1 and v3 are identical" << std::endl;
    }

    return 0;
}

// Expected output:
// Range 1: 1 2 3 4 5
// Range 2: 1 2 9 4 5
// First mismatch at index 2: 3 vs 9
// v1 and v3 are identical
