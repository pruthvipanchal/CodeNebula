// CodeNebula - C++98 Example: search
// Compile: g++ -std=c++98 -Wall -Wextra -o example search.cpp

// std::search finds the FIRST occurrence of a subsequence within a range.
// (Compare with std::find_end which finds the LAST occurrence.)

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int arr[] = {1, 2, 3, 4, 1, 2, 3, 4, 5};
    std::vector<int> v(arr, arr + 9);

    int pat[] = {1, 2, 3};
    std::vector<int> pattern(pat, pat + 3);

    std::cout << "Sequence: ";
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Find first occurrence of {1, 2, 3}
    std::vector<int>::iterator it =
        std::search(v.begin(), v.end(), pattern.begin(), pattern.end());

    if (it != v.end()) {
        std::cout << "First {1,2,3} at index " << (it - v.begin()) << std::endl;
    }

    // Find second occurrence by starting after the first
    it = std::search(it + 1, v.end(), pattern.begin(), pattern.end());
    if (it != v.end()) {
        std::cout << "Second {1,2,3} at index " << (it - v.begin()) << std::endl;
    }

    // Search for a subsequence not present
    int bad[] = {9, 9};
    it = std::search(v.begin(), v.end(), bad, bad + 2);
    if (it == v.end()) {
        std::cout << "Pattern {9,9} not found" << std::endl;
    }

    return 0;
}

// Expected output:
// Sequence: 1 2 3 4 1 2 3 4 5
// First {1,2,3} at index 0
// Second {1,2,3} at index 4
// Pattern {9,9} not found
