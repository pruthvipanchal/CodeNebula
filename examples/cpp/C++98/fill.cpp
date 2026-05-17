// CodeNebula - C++98 Example: fill
// Compile: g++ -std=c++98 -Wall -Wextra -o example fill.cpp

// std::fill assigns a given value to every element in [first, last).

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
    // Fill an entire vector with a value
    std::vector<int> v(8);
    std::fill(v.begin(), v.end(), 42);
    print_vec("Filled with 42: ", v);

    // Fill only a sub-range
    std::fill(v.begin() + 2, v.begin() + 6, 0);
    print_vec("Middle zeroed:  ", v);

    // Fill a plain array
    int arr[5];
    std::fill(arr, arr + 5, -1);
    std::cout << "Array filled:   ";
    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Filled with 42: 42 42 42 42 42 42 42 42
// Middle zeroed:  42 42 0 0 0 0 42 42
// Array filled:   -1 -1 -1 -1 -1
