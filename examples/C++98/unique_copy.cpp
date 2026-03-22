// CodeNebula - C++98 Example: unique_copy
// Compile: g++ -std=c++98 -Wall -Wextra -o example unique_copy.cpp

// std::unique_copy copies elements from a range, skipping
// consecutive duplicates, into a destination range.

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

void print_vec(const std::vector<int>& v, const char* label) {
    std::cout << label << ": ";
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    int arr[] = {1, 1, 2, 3, 3, 3, 4, 4, 5};
    const int n = sizeof(arr) / sizeof(arr[0]);

    std::vector<int> src(arr, arr + n);
    print_vec(src, "Source");

    // Copy unique elements into a new vector via back_inserter
    std::vector<int> dest;
    std::unique_copy(src.begin(), src.end(), std::back_inserter(dest));
    print_vec(dest, "Unique copy");

    // Source remains unchanged
    print_vec(src, "Source after");

    // Copy into a pre-sized vector
    std::vector<int> dest2(n, 0);
    std::vector<int>::iterator end_it =
        std::unique_copy(src.begin(), src.end(), dest2.begin());
    dest2.erase(end_it, dest2.end());
    print_vec(dest2, "Unique copy (pre-sized)");

    return 0;
}

// Expected output:
// Source: 1 1 2 3 3 3 4 4 5
// Unique copy: 1 2 3 4 5
// Source after: 1 1 2 3 3 3 4 4 5
// Unique copy (pre-sized): 1 2 3 4 5
