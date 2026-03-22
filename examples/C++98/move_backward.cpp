// CodeNebula - C++98 Example: move_backward
// Compile: g++ -std=c++98 -Wall -Wextra -o example move_backward.cpp

// NOTE: std::move_backward was introduced in C++11.
// In C++98, the equivalent is std::copy_backward. This example demonstrates
// the copy_backward pattern that C++11's move_backward replaces with move
// semantics for better performance on move-aware types.

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
    // C++98: use copy_backward to shift elements right in overlapping ranges
    // C++11: std::move_backward would do this with move semantics

    std::string words[] = {"alpha", "beta", "gamma", "", ""};
    std::vector<std::string> v(words, words + 5);

    print_vec("Before: ", v);

    // Shift first 3 elements to the right by 2 positions
    std::copy_backward(v.begin(), v.begin() + 3, v.end());

    print_vec("After:  ", v);

    // Another example: copy_backward between separate containers
    std::string src_arr[] = {"one", "two", "three"};
    std::vector<std::string> src(src_arr, src_arr + 3);
    std::vector<std::string> dst(3);

    std::copy_backward(src.begin(), src.end(), dst.end());
    print_vec("Src: ", src);
    print_vec("Dst: ", dst);

    std::cout << "\nNote: C++11 std::move_backward would use move semantics." << std::endl;

    return 0;
}

// Expected output:
// Before: "alpha" "beta" "gamma" "" ""
// After:  "alpha" "beta" "alpha" "beta" "gamma"
// Src: "one" "two" "three"
// Dst: "one" "two" "three"
//
// Note: C++11 std::move_backward would use move semantics.
