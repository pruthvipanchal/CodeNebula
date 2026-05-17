// CodeNebula - C++98 Example: count_if
// Compile: g++ -std=c++98 -Wall -Wextra -o example count_if.cpp

// std::count_if counts elements in [first, last) for which a predicate
// returns true.

#include <iostream>
#include <vector>
#include <algorithm>

bool is_even(int x) {
    return x % 2 == 0;
}

bool is_negative(int x) {
    return x < 0;
}

struct InRange {
    int lo, hi;
    InRange(int l, int h) : lo(l), hi(h) {}
    bool operator()(int x) const { return x >= lo && x <= hi; }
};

int main() {
    int arr[] = {-3, 1, 4, -1, 5, 9, -2, 6, 5, 3};
    std::vector<int> v(arr, arr + 10);

    std::cout << "Sequence: ";
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Count even numbers
    int c = std::count_if(v.begin(), v.end(), is_even);
    std::cout << "Even numbers: " << c << std::endl;

    // Count negative numbers
    c = std::count_if(v.begin(), v.end(), is_negative);
    std::cout << "Negative numbers: " << c << std::endl;

    // Count numbers in range [1, 5] using functor
    c = std::count_if(v.begin(), v.end(), InRange(1, 5));
    std::cout << "Numbers in [1,5]: " << c << std::endl;

    return 0;
}

// Expected output:
// Sequence: -3 1 4 -1 5 9 -2 6 5 3
// Even numbers: 3
// Negative numbers: 3
// Numbers in [1,5]: 5
