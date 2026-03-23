// CodeNebula - C++11 Example: std::cbegin and std::cend Const Iterators
// Compile: g++ -std=c++11 -Wall -Wextra -o example cbegin_cend.cpp

// Container member functions cbegin() and cend() return const_iterators,
// guaranteeing read-only access to elements. This is useful when you want
// to express intent that elements should not be modified.
// Note: Free functions std::cbegin/std::cend were added in C++14.

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>

int main() {
    // Vector with const iterators
    std::vector<int> numbers = {10, 20, 30, 40, 50};

    std::cout << "Vector via cbegin/cend: ";
    for (auto it = numbers.cbegin(); it != numbers.cend(); ++it) {
        // *it = 99;  // ERROR: cannot modify through const_iterator
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Set already has const iterators (elements are immutable)
    std::set<std::string> names = {"Alice", "Bob", "Charlie"};

    std::cout << "Set via cbegin/cend: ";
    for (auto it = names.cbegin(); it != names.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Using const_iterator with auto type deduction
    auto cit = numbers.cbegin();
    std::cout << "First element (const): " << *cit << std::endl;

    // Useful with algorithms for read-only operations
    auto found = std::find(numbers.cbegin(), numbers.cend(), 30);
    if (found != numbers.cend()) {
        std::cout << "Found 30 at position: "
                  << std::distance(numbers.cbegin(), found) << std::endl;
    }

    // Count elements greater than 25 using const iterators
    int count = std::count_if(numbers.cbegin(), numbers.cend(),
                              [](int n) { return n > 25; });
    std::cout << "Elements > 25: " << count << std::endl;

    // Const iterators prevent accidental modification
    std::cout << "Type safety: const_iterator prevents writes" << std::endl;

    return 0;
}

// Expected output:
// Vector via cbegin/cend: 10 20 30 40 50
// Set via cbegin/cend: Alice Bob Charlie
// First element (const): 10
// Found 30 at position: 2
// Elements > 25: 3
// Type safety: const_iterator prevents writes
