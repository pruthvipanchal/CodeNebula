// CodeNebula - C++98 Example: move_algorithm
// Compile: g++ -std=c++98 -Wall -Wextra -o example move_algorithm.cpp

// NOTE: std::move (the algorithm version) was introduced in C++11.
// In C++98, the equivalent operation is std::copy. This example demonstrates
// using std::copy as the C++98 counterpart.
// In C++11+, std::move(first, last, d_first) moves elements using move
// semantics, which can be more efficient for types with move constructors.

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

void print_vec(const char* label, const std::vector<std::string>& v) {
    std::cout << label;
    for (std::vector<std::string>::const_iterator it = v.begin();
         it != v.end(); ++it) {
        std::cout << "\"" << *it << "\" ";
    }
    std::cout << std::endl;
}

int main() {
    // In C++98, we use std::copy to transfer elements between containers.
    // C++11's std::move algorithm would leave source in a moved-from state.

    std::string words[] = {"hello", "world", "from", "C++98"};
    std::vector<std::string> src(words, words + 4);
    std::vector<std::string> dst(4);

    print_vec("Source before copy: ", src);

    // C++98 copy (C++11 would use std::move for efficiency)
    std::copy(src.begin(), src.end(), dst.begin());

    print_vec("Source after copy:  ", src);
    print_vec("Destination:        ", dst);

    std::cout << "\nNote: In C++98, std::copy makes full copies." << std::endl;
    std::cout << "C++11 std::move would transfer ownership efficiently." << std::endl;

    return 0;
}

// Expected output:
// Source before copy: "hello" "world" "from" "C++98"
// Source after copy:  "hello" "world" "from" "C++98"
// Destination:        "hello" "world" "from" "C++98"
//
// Note: In C++98, std::copy makes full copies.
// C++11 std::move would transfer ownership efficiently.
