// CodeNebula - C++98 Example: front_insert_iterator
// Compile: g++ -std=c++98 -Wall -Wextra -o example front_insert_iterator.cpp

#include <iostream>
#include <deque>
#include <algorithm>
#include <iterator>

int main() {
    int src[] = {1, 2, 3, 4, 5};
    std::deque<int> d;

    // front_inserter creates a front_insert_iterator
    // Each element is pushed to the front, reversing order
    std::copy(src, src + 5, std::front_inserter(d));

    std::cout << "Deque after front_insert (reversed): ";
    for (std::deque<int>::iterator it = d.begin(); it != d.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Add more elements to the front
    int more[] = {10, 20};
    std::copy(more, more + 2, std::front_inserter(d));

    std::cout << "After inserting 10,20 at front: ";
    for (std::deque<int>::iterator it = d.begin(); it != d.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Deque after front_insert (reversed): 5 4 3 2 1
// After inserting 10,20 at front: 20 10 5 4 3 2 1
