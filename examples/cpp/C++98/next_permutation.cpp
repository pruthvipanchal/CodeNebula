// CodeNebula - C++98 Example: next_permutation
// Compile: g++ -std=c++98 -Wall -Wextra -o example next_permutation.cpp

// std::next_permutation rearranges elements into the next
// lexicographically greater permutation. Returns false when it
// wraps around to the smallest permutation (sorted order).

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
    // Generate all permutations of {1, 2, 3}
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    std::cout << "All permutations of {1, 2, 3}:" << std::endl;
    // Start from sorted order to get all permutations
    std::sort(v.begin(), v.end());
    int count = 0;
    do {
        std::cout << "  ";
        print_vec(v);
        ++count;
    } while (std::next_permutation(v.begin(), v.end()));
    std::cout << "Total: " << count << " permutations" << std::endl;

    // Single step: get the next permutation of a specific arrangement
    int arr[] = {1, 3, 2};
    std::vector<int> w(arr, arr + 3);
    std::cout << "Current: ";
    print_vec(w);
    std::next_permutation(w.begin(), w.end());
    std::cout << "Next:    ";
    print_vec(w);

    return 0;
}

// Expected output:
// All permutations of {1, 2, 3}:
//   1 2 3
//   1 3 2
//   2 1 3
//   2 3 1
//   3 1 2
//   3 2 1
// Total: 6 permutations
// Current: 1 3 2
// Next:    2 1 3
