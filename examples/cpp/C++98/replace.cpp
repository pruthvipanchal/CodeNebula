// CodeNebula - C++98 Example: replace
// Compile: g++ -std=c++98 -Wall -Wextra -o example replace.cpp

// std::replace replaces all elements equal to old_value with new_value
// in [first, last). Modifies the range in place.

#include <iostream>
#include <vector>
#include <algorithm>

void print_vec(const char* label, const std::vector<int>& v) {
    std::cout << label;
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    int arr[] = {1, 2, 3, 2, 4, 2, 5};
    std::vector<int> v(arr, arr + 7);
    print_vec("Original:        ", v);

    // Replace all 2s with 99
    std::replace(v.begin(), v.end(), 2, 99);
    print_vec("Replace 2->99:   ", v);

    // Replace a value not present (no change)
    std::replace(v.begin(), v.end(), 42, 0);
    print_vec("Replace 42->0:   ", v);

    // Replace in a sub-range only
    int arr2[] = {5, 5, 5, 5, 5};
    std::vector<int> v2(arr2, arr2 + 5);
    std::replace(v2.begin() + 1, v2.begin() + 4, 5, 0);
    print_vec("Sub-range 5->0:  ", v2);

    return 0;
}

// Expected output:
// Original:        1 2 3 2 4 2 5
// Replace 2->99:   1 99 3 99 4 99 5
// Replace 42->0:   1 99 3 99 4 99 5
// Sub-range 5->0:  5 0 0 0 5
