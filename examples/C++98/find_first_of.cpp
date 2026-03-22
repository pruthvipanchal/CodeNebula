// CodeNebula - C++98 Example: find_first_of
// Compile: g++ -std=c++98 -Wall -Wextra -o example find_first_of.cpp

// std::find_first_of searches [first1, last1) for the first element that matches
// ANY element in [first2, last2). Like searching for any character in a set.

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int arr[] = {1, 5, 3, 7, 9, 2, 8};
    std::vector<int> v(arr, arr + 7);

    // Search for the first occurrence of any value in {7, 2, 10}
    int targets[] = {7, 2, 10};
    std::vector<int> search_set(targets, targets + 3);

    std::vector<int>::iterator it =
        std::find_first_of(v.begin(), v.end(),
                           search_set.begin(), search_set.end());

    if (it != v.end()) {
        std::cout << "First match: " << *it
                  << " at index " << (it - v.begin()) << std::endl;
    }

    // Search for values not present
    int missing[] = {100, 200};
    std::vector<int> bad(missing, missing + 2);
    it = std::find_first_of(v.begin(), v.end(), bad.begin(), bad.end());
    if (it == v.end()) {
        std::cout << "No element from {100, 200} found" << std::endl;
    }

    // Works with plain arrays too
    int data[] = {10, 20, 30, 40, 50};
    int keys[] = {30, 50};
    int* p = std::find_first_of(data, data + 5, keys, keys + 2);
    if (p != data + 5) {
        std::cout << "In array, first match: " << *p
                  << " at index " << (p - data) << std::endl;
    }

    return 0;
}

// Expected output:
// First match: 7 at index 3
// No element from {100, 200} found
// In array, first match: 30 at index 2
