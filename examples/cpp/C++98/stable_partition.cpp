// CodeNebula - C++98 Example: stable_partition
// Compile: g++ -std=c++98 -Wall -Wextra -o example stable_partition.cpp

// std::stable_partition reorders elements so that those satisfying
// a predicate come first, while preserving the relative order
// within each group (unlike std::partition).

#include <iostream>
#include <vector>
#include <algorithm>

bool is_even(int x) {
    return x % 2 == 0;
}

void print_vec(const std::vector<int>& v, const char* label) {
    std::cout << label << ": ";
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> v(arr, arr + 10);
    print_vec(v, "Original");

    // Stable partition: evens first, odds second
    // Relative order within each group is preserved
    std::vector<int>::iterator mid =
        std::stable_partition(v.begin(), v.end(), is_even);

    print_vec(v, "After stable_partition");

    std::cout << "Evens: ";
    for (std::vector<int>::iterator it = v.begin(); it != mid; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Odds:  ";
    for (std::vector<int>::iterator it = mid; it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Original: 1 2 3 4 5 6 7 8 9 10
// After stable_partition: 2 4 6 8 10 1 3 5 7 9
// Evens: 2 4 6 8 10
// Odds:  1 3 5 7 9
