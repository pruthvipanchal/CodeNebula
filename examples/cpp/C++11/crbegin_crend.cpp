// CodeNebula - C++11 Example: crbegin and crend Const Reverse Iterators
// Compile: g++ -std=c++11 -Wall -Wextra -o example crbegin_crend.cpp

// crbegin() and crend() return const reverse iterators that traverse a
// container from back to front with read-only access. They combine the
// guarantees of const_iterator with reverse traversal.

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

int main() {
    // Const reverse iteration over a vector
    std::vector<int> nums = {10, 20, 30, 40, 50};

    std::cout << "Const reverse vector: ";
    for (auto it = nums.crbegin(); it != nums.crend(); ++it) {
        // *it = 99;  // ERROR: cannot modify through const_reverse_iterator
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Const reverse iteration over a list
    std::list<std::string> words = {"alpha", "beta", "gamma", "delta"};

    std::cout << "Const reverse list: ";
    for (auto it = words.crbegin(); it != words.crend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Use with algorithms for read-only reverse searches
    auto found = std::find(nums.crbegin(), nums.crend(), 30);
    if (found != nums.crend()) {
        auto pos = std::distance(nums.crbegin(), found);
        std::cout << "Found 30 at reverse position: " << pos << std::endl;
    }

    // Count elements in reverse range
    int count = std::count_if(nums.crbegin(), nums.crend(),
                              [](int n) { return n >= 30; });
    std::cout << "Elements >= 30: " << count << std::endl;

    // Const reverse iterators express intent clearly
    std::cout << "Last 3 elements (reversed): ";
    auto it = nums.crbegin();
    for (int i = 0; i < 3 && it != nums.crend(); ++i, ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Compare iterator types
    std::cout << "Type guarantees:" << std::endl;
    std::cout << "  rbegin  -> reverse_iterator (mutable, reverse)" << std::endl;
    std::cout << "  crbegin -> const_reverse_iterator (read-only, reverse)" << std::endl;

    return 0;
}

// Expected output:
// Const reverse vector: 50 40 30 20 10
// Const reverse list: delta gamma beta alpha
// Found 30 at reverse position: 2
// Elements >= 30: 3
// Last 3 elements (reversed): 50 40 30
// Type guarantees:
//   rbegin  -> reverse_iterator (mutable, reverse)
//   crbegin -> const_reverse_iterator (read-only, reverse)
