// CodeNebula - C++98 Example: replace_if
// Compile: g++ -std=c++98 -Wall -Wextra -o example replace_if.cpp

// std::replace_if replaces all elements for which a predicate returns true
// with a specified new value. Modifies the range in place.

#include <iostream>
#include <vector>
#include <algorithm>

bool is_negative(int x) {
    return x < 0;
}

struct IsMultipleOf {
    int divisor;
    IsMultipleOf(int d) : divisor(d) {}
    bool operator()(int x) const { return x % divisor == 0; }
};

void print_vec(const char* label, const std::vector<int>& v) {
    std::cout << label;
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    int arr[] = {-3, 1, -4, 1, -5, 9, -2, 6};
    std::vector<int> v(arr, arr + 8);
    print_vec("Original:             ", v);

    // Replace all negative values with 0
    std::replace_if(v.begin(), v.end(), is_negative, 0);
    print_vec("Negatives -> 0:       ", v);

    // Replace multiples of 3 with -1 using a functor
    int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> v2(arr2, arr2 + 10);
    print_vec("Original:             ", v2);

    std::replace_if(v2.begin(), v2.end(), IsMultipleOf(3), -1);
    print_vec("Multiples of 3 -> -1: ", v2);

    return 0;
}

// Expected output:
// Original:             -3 1 -4 1 -5 9 -2 6
// Negatives -> 0:       0 1 0 1 0 9 0 6
// Original:             1 2 3 4 5 6 7 8 9 10
// Multiples of 3 -> -1: 1 2 -1 4 5 -1 7 8 -1 10
