// CodeNebula - C++98 Example: rotate
// Compile: g++ -std=c++98 -Wall -Wextra -o example rotate.cpp

// std::rotate rotates elements in a range so that a chosen middle
// element becomes the first element. Elements before it wrap around
// to the end.

#include <iostream>
#include <vector>
#include <algorithm>

void print_vec(const std::vector<int>& v, const char* label) {
    std::cout << label << ": ";
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Build vector: 1 2 3 4 5 6 7
    std::vector<int> v;
    for (int i = 1; i <= 7; ++i) {
        v.push_back(i);
    }
    print_vec(v, "Original");

    // Rotate so that element at index 3 (value 4) becomes the first
    std::rotate(v.begin(), v.begin() + 3, v.end());
    print_vec(v, "After rotate by 3");

    // Rotate back by 4 positions to restore original order
    std::rotate(v.begin(), v.begin() + 4, v.end());
    print_vec(v, "After rotate by 4 (restored)");

    // Rotate by 1 -- a common "shift left by one" pattern
    std::vector<int> w;
    for (int i = 10; i <= 14; ++i) {
        w.push_back(i);
    }
    print_vec(w, "Before shift-left");
    std::rotate(w.begin(), w.begin() + 1, w.end());
    print_vec(w, "After shift-left by 1");

    return 0;
}

// Expected output:
// Original: 1 2 3 4 5 6 7
// After rotate by 3: 4 5 6 7 1 2 3
// After rotate by 4 (restored): 1 2 3 4 5 6 7
// After shift-left by 1: 11 12 13 14 10
