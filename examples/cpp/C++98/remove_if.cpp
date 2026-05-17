// CodeNebula - C++98 Example: remove_if
// Compile: g++ -std=c++98 -Wall -Wextra -o example remove_if.cpp

// std::remove_if "removes" elements for which a predicate returns true.
// Like std::remove, it shifts elements and returns a new logical end.
// Use erase-remove_if idiom to actually shrink the container.

#include <iostream>
#include <vector>
#include <algorithm>

bool is_odd(int x) {
    return x % 2 != 0;
}

struct LessThan {
    int threshold;
    LessThan(int t) : threshold(t) {}
    bool operator()(int x) const { return x < threshold; }
};

void print_vec(const char* label, const std::vector<int>& v) {
    std::cout << label;
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> v(arr, arr + 10);
    print_vec("Original:          ", v);

    // Remove odd numbers using erase-remove_if
    std::vector<int> evens(v);
    evens.erase(std::remove_if(evens.begin(), evens.end(), is_odd),
                evens.end());
    print_vec("After remove odds: ", evens);

    // Remove elements less than 5 using a functor
    std::vector<int> big(v);
    big.erase(std::remove_if(big.begin(), big.end(), LessThan(5)),
              big.end());
    print_vec("After remove < 5:  ", big);

    return 0;
}

// Expected output:
// Original:          1 2 3 4 5 6 7 8 9 10
// After remove odds: 2 4 6 8 10
// After remove < 5:  5 6 7 8 9 10
