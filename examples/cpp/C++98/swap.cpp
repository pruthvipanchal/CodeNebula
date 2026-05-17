// CodeNebula - C++98 Example: swap
// Compile: g++ -std=c++98 -Wall -Wextra -o example swap.cpp

// std::swap exchanges the values of two objects. It works with any assignable
// and copy-constructible type. Containers also provide a member swap() which
// is typically more efficient (constant time for most containers).

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

void print_vec(const char* label, const std::vector<int>& v) {
    std::cout << label;
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Swap two integers
    int a = 10, b = 20;
    std::cout << "Before swap: a=" << a << " b=" << b << std::endl;
    std::swap(a, b);
    std::cout << "After swap:  a=" << a << " b=" << b << std::endl;

    // Swap two strings
    std::string s1 = "hello";
    std::string s2 = "world";
    std::cout << "\nBefore swap: s1=\"" << s1 << "\" s2=\"" << s2 << "\"" << std::endl;
    std::swap(s1, s2);
    std::cout << "After swap:  s1=\"" << s1 << "\" s2=\"" << s2 << "\"" << std::endl;

    // Swap two vectors (efficient, constant time)
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6, 7};
    std::vector<int> v1(arr1, arr1 + 3);
    std::vector<int> v2(arr2, arr2 + 4);

    std::cout << std::endl;
    print_vec("Before: v1 = ", v1);
    print_vec("Before: v2 = ", v2);
    std::swap(v1, v2);
    print_vec("After:  v1 = ", v1);
    print_vec("After:  v2 = ", v2);

    return 0;
}

// Expected output:
// Before swap: a=10 b=20
// After swap:  a=20 b=10
//
// Before swap: s1="hello" s2="world"
// After swap:  s1="world" s2="hello"
//
// Before: v1 = 1 2 3
// Before: v2 = 4 5 6 7
// After:  v1 = 4 5 6 7
// After:  v2 = 1 2 3
