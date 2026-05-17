// CodeNebula - C++98 Example: prev_permutation
// Compile: g++ -std=c++98 -Wall -Wextra -o example prev_permutation.cpp

// std::prev_permutation rearranges elements into the previous
// lexicographically smaller permutation. Returns false when it
// wraps around from the smallest to the largest permutation.

#include <iostream>
#include <vector>
#include <algorithm>

void print_vec(const std::vector<int>& v) {
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Generate all permutations in reverse order
    std::vector<int> v;
    v.push_back(3);
    v.push_back(2);
    v.push_back(1);

    std::cout << "All permutations in reverse order:" << std::endl;
    int count = 0;
    do {
        std::cout << "  ";
        print_vec(v);
        ++count;
    } while (std::prev_permutation(v.begin(), v.end()));
    std::cout << "Total: " << count << " permutations" << std::endl;

    // Single step: get the previous permutation
    int arr[] = {2, 1, 3};
    std::vector<int> w(arr, arr + 3);
    std::cout << "Current: ";
    print_vec(w);
    std::prev_permutation(w.begin(), w.end());
    std::cout << "Prev:    ";
    print_vec(w);

    // When already at smallest, it wraps to largest
    int arr2[] = {1, 2, 3};
    std::vector<int> smallest(arr2, arr2 + 3);
    std::cout << "Smallest: ";
    print_vec(smallest);
    bool wrapped = !std::prev_permutation(smallest.begin(), smallest.end());
    std::cout << "After prev (wrapped): ";
    print_vec(smallest);
    std::cout << "Wrapped? " << (wrapped ? "yes" : "no") << std::endl;

    return 0;
}

// Expected output:
// All permutations in reverse order:
//   3 2 1
//   3 1 2
//   2 3 1
//   2 1 3
//   1 3 2
//   1 2 3
// Total: 6 permutations
// Current: 2 1 3
// Prev:    1 3 2
// Smallest: 1 2 3
// After prev (wrapped): 3 2 1
// Wrapped? yes
