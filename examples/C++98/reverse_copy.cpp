// CodeNebula - C++98 Example: reverse_copy
// Compile: g++ -std=c++98 -Wall -Wextra -o example reverse_copy.cpp

// std::reverse_copy copies elements from [first, last) into a destination
// in reverse order. The source range is NOT modified.

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
    std::vector<int> src(arr, arr + 5);
    std::vector<int> dst(5);

    // Reverse copy into another vector
    std::reverse_copy(src.begin(), src.end(), dst.begin());
    print_vec("Source:       ", src);
    print_vec("Reverse copy: ", dst);

    // Reverse copy a sub-range
    std::vector<int> partial(3);
    std::reverse_copy(src.begin() + 1, src.begin() + 4, partial.begin());
    print_vec("Sub-range rev:", partial);

    // Reverse copy a string
    std::string original = "abcdef";
    std::string reversed(original.size(), ' ');
    std::reverse_copy(original.begin(), original.end(), reversed.begin());
    std::cout << "\nOriginal string: " << original << std::endl;
    std::cout << "Reversed copy:   " << reversed << std::endl;

    // Source remains unchanged
    print_vec("\nSource after:  ", src);

    return 0;
}

// Expected output:
// Source:       1 2 3 4 5
// Reverse copy: 5 4 3 2 1
// Sub-range rev:4 3 2
//
// Original string: abcdef
// Reversed copy:   fedcba
//
// Source after:  1 2 3 4 5
