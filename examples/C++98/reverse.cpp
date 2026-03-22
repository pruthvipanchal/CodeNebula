// CodeNebula - C++98 Example: reverse
// Compile: g++ -std=c++98 -Wall -Wextra -o example reverse.cpp

// std::reverse reverses the order of elements in [first, last) in place.
// It requires bidirectional iterators.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void print_vec(const char* label, const std::vector<int>& v) {
    std::cout << label;
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    std::vector<int> v(arr, arr + 5);
    print_vec("Original:     ", v);

    // Reverse the entire vector
    std::reverse(v.begin(), v.end());
    print_vec("Reversed:     ", v);

    // Reverse back to original
    std::reverse(v.begin(), v.end());
    print_vec("Reversed again:", v);

    // Reverse a sub-range (middle 3 elements)
    int arr2[] = {10, 20, 30, 40, 50};
    std::vector<int> v2(arr2, arr2 + 5);
    print_vec("Before:       ", v2);
    std::reverse(v2.begin() + 1, v2.begin() + 4);
    print_vec("Mid reversed: ", v2);

    // Reverse a string
    std::string s = "Hello, World!";
    std::cout << "\nString: " << s << std::endl;
    std::reverse(s.begin(), s.end());
    std::cout << "Reversed: " << s << std::endl;

    return 0;
}

// Expected output:
// Original:     1 2 3 4 5
// Reversed:     5 4 3 2 1
// Reversed again:1 2 3 4 5
// Before:       10 20 30 40 50
// Mid reversed: 10 40 30 20 50
//
// String: Hello, World!
// Reversed: !dlroW ,olleH
