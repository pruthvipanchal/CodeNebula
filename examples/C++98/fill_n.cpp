// CodeNebula - C++98 Example: fill_n
// Compile: g++ -std=c++98 -Wall -Wextra -o example fill_n.cpp

// std::fill_n assigns a value to the first N elements starting from an iterator.

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
    std::vector<int> v(10, 0);
    print_vec("Initial:      ", v);

    // Fill first 3 elements with 1
    std::fill_n(v.begin(), 3, 1);
    print_vec("First 3 = 1:  ", v);

    // Fill 4 elements starting at index 3 with 5
    std::fill_n(v.begin() + 3, 4, 5);
    print_vec("Mid 4 = 5:    ", v);

    // Fill last 3 elements with 9
    std::fill_n(v.begin() + 7, 3, 9);
    print_vec("Last 3 = 9:   ", v);

    // Fill zero elements (no-op)
    std::fill_n(v.begin(), 0, 999);
    print_vec("Fill 0 (noop):", v);

    return 0;
}

// Expected output:
// Initial:      0 0 0 0 0 0 0 0 0 0
// First 3 = 1:  1 1 1 0 0 0 0 0 0 0
// Mid 4 = 5:    1 1 1 5 5 5 5 0 0 0
// Last 3 = 9:   1 1 1 5 5 5 5 9 9 9
// Fill 0 (noop):1 1 1 5 5 5 5 9 9 9
