// CodeNebula - C++98 Example: find_if
// Compile: g++ -std=c++98 -Wall -Wextra -o example find_if.cpp

// std::find_if searches for the first element in [first, last) for which a
// predicate returns true. Returns an iterator to that element, or last.

#include <iostream>
#include <vector>
#include <algorithm>

bool is_even(int x) {
    return x % 2 == 0;
}

struct GreaterThan {
    int threshold;
    GreaterThan(int t) : threshold(t) {}
    bool operator()(int x) const { return x > threshold; }
};

int main() {
    int arr[] = {3, 7, 2, 9, 4, 1, 8};
    std::vector<int> v(arr, arr + 7);

    // Find the first even number
    std::vector<int>::iterator it = std::find_if(v.begin(), v.end(), is_even);
    if (it != v.end()) {
        std::cout << "First even: " << *it
                  << " at index " << (it - v.begin()) << std::endl;
    }

    // Find the first element greater than 5 using a functor
    it = std::find_if(v.begin(), v.end(), GreaterThan(5));
    if (it != v.end()) {
        std::cout << "First > 5: " << *it
                  << " at index " << (it - v.begin()) << std::endl;
    }

    // Find the first element greater than 100 (not found)
    it = std::find_if(v.begin(), v.end(), GreaterThan(100));
    if (it == v.end()) {
        std::cout << "No element > 100" << std::endl;
    }

    return 0;
}

// Expected output:
// First even: 2 at index 2
// First > 5: 7 at index 1
// No element > 100
