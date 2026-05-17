// CodeNebula - C++98 Example: insert_iterator
// Compile: g++ -std=c++98 -Wall -Wextra -o example insert_iterator.cpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(5);
    v.push_back(6);

    int to_insert[] = {3, 4};

    // inserter() inserts at a given position
    // Here we insert {3,4} before element '5' (index 2)
    std::copy(to_insert, to_insert + 2, std::inserter(v, v.begin() + 2));

    std::cout << "Vector after inserting 3,4 at position 2: ";
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Insert at the end using inserter
    int extras[] = {7, 8};
    std::copy(extras, extras + 2, std::inserter(v, v.end()));

    std::cout << "After inserting 7,8 at end: ";
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Vector after inserting 3,4 at position 2: 1 2 3 4 5 6
// After inserting 7,8 at end: 1 2 3 4 5 6 7 8
