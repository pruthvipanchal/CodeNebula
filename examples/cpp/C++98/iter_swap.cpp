// CodeNebula - C++98 Example: iter_swap
// Compile: g++ -std=c++98 -Wall -Wextra -o example iter_swap.cpp

// std::iter_swap swaps the values pointed to by two iterators.
// It is equivalent to std::swap(*a, *b) but works generically with iterators.

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

void print_vec(const char* label, const std::vector<int>& v) {
    std::cout << label;
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    std::vector<int> v(arr, arr + 5);
    print_vec("Original:        ", v);

    // Swap first and last elements via iterators
    std::iter_swap(v.begin(), v.end() - 1);
    print_vec("Swap first/last: ", v);

    // Swap elements at index 1 and 3
    std::iter_swap(v.begin() + 1, v.begin() + 3);
    print_vec("Swap [1] & [3]:  ", v);

    // iter_swap works across different container types
    std::list<int> lst;
    lst.push_back(100);
    lst.push_back(200);

    std::cout << "\nVector[0]=" << v[0] << ", List front=" << lst.front() << std::endl;
    std::iter_swap(v.begin(), lst.begin());
    std::cout << "After iter_swap: Vector[0]=" << v[0]
              << ", List front=" << lst.front() << std::endl;

    return 0;
}

// Expected output:
// Original:        10 20 30 40 50
// Swap first/last: 50 20 30 40 10
// Swap [1] & [3]:  50 40 30 20 10
//
// Vector[0]=50, List front=100
// After iter_swap: Vector[0]=100, List front=50
