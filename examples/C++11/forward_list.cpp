// CodeNebula - C++11 Example: std::forward_list Singly-Linked List
// Compile: g++ -std=c++11 -Wall -Wextra -o example forward_list.cpp

// std::forward_list is a singly-linked list that supports only forward
// iteration. It uses less memory than std::list and provides O(1)
// insertion/removal at the front. It has no size() member for efficiency.

#include <iostream>
#include <forward_list>
#include <algorithm>

int main() {
    // Create a forward_list with initializer list
    std::forward_list<int> flist = {5, 3, 8, 1, 9};

    std::cout << "Original: ";
    for (const auto& val : flist) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Insert at the front (O(1) operation)
    flist.push_front(42);
    std::cout << "After push_front(42): ";
    for (const auto& val : flist) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Insert after a specific position
    auto it = flist.begin();
    flist.insert_after(it, 99);
    std::cout << "After insert_after begin (99): ";
    for (const auto& val : flist) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Sort the list (member function, not std::sort)
    flist.sort();
    std::cout << "Sorted: ";
    for (const auto& val : flist) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Remove specific values
    flist.remove(99);
    std::cout << "After remove(99): ";
    for (const auto& val : flist) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Remove elements matching a predicate
    flist.remove_if([](int n) { return n > 10; });
    std::cout << "After removing > 10: ";
    for (const auto& val : flist) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Check if empty (no size() member exists)
    std::cout << "Is empty: " << std::boolalpha << flist.empty() << std::endl;

    return 0;
}

// Expected output:
// Original: 5 3 8 1 9
// After push_front(42): 42 5 3 8 1 9
// After insert_after begin (99): 42 99 5 3 8 1 9
// Sorted: 1 3 5 8 9 42 99
// After remove(99): 1 3 5 8 9 42
// After removing > 10: 1 3 5 8 9
// Is empty: false
