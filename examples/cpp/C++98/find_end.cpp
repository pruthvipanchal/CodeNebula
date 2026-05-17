// CodeNebula - C++98 Example: find_end
// Compile: g++ -std=c++98 -Wall -Wextra -o example find_end.cpp

// std::find_end searches for the LAST occurrence of a subsequence within a range.
// Returns an iterator to the beginning of the last match, or last1 if not found.

#include <iostream>
#include <vector>
#include <algorithm>

void print_vec(const std::vector<int>& v) {
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    int arr[] = {1, 2, 3, 1, 2, 3, 1, 2, 3, 4};
    std::vector<int> v(arr, arr + 10);

    int sub[] = {1, 2, 3};
    std::vector<int> pattern(sub, sub + 3);

    std::cout << "Sequence:    ";
    print_vec(v);
    std::cout << "Subsequence: ";
    print_vec(pattern);

    // Find the last occurrence of {1, 2, 3}
    std::vector<int>::iterator it =
        std::find_end(v.begin(), v.end(), pattern.begin(), pattern.end());

    if (it != v.end()) {
        std::cout << "Last occurrence at index " << (it - v.begin()) << std::endl;
    }

    // Search for a pattern that does not exist
    int missing[] = {5, 6};
    std::vector<int> bad(missing, missing + 2);
    it = std::find_end(v.begin(), v.end(), bad.begin(), bad.end());
    if (it == v.end()) {
        std::cout << "Pattern {5,6} not found" << std::endl;
    }

    return 0;
}

// Expected output:
// Sequence:    1 2 3 1 2 3 1 2 3 4
// Subsequence: 1 2 3
// Last occurrence at index 6
// Pattern {5,6} not found
