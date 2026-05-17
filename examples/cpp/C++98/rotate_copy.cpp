// CodeNebula - C++98 Example: rotate_copy
// Compile: g++ -std=c++98 -Wall -Wextra -o example rotate_copy.cpp

// std::rotate_copy copies a rotated version of a range into a
// destination without modifying the source.

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
    int arr[] = {10, 20, 30, 40, 50};
    const int n = sizeof(arr) / sizeof(arr[0]);

    std::vector<int> src(arr, arr + n);
    std::vector<int> dest(n);

    print_vec(src, "Source");

    // Copy with rotation: element at index 2 (30) becomes first
    std::rotate_copy(src.begin(), src.begin() + 2, src.end(),
                     dest.begin());
    print_vec(dest, "Rotated copy (pivot=2)");
    print_vec(src, "Source unchanged");

    // Another rotation: pivot at index 4
    std::rotate_copy(src.begin(), src.begin() + 4, src.end(),
                     dest.begin());
    print_vec(dest, "Rotated copy (pivot=4)");

    return 0;
}

// Expected output:
// Source: 10 20 30 40 50
// Rotated copy (pivot=2): 30 40 50 10 20
// Source unchanged: 10 20 30 40 50
// Rotated copy (pivot=4): 50 10 20 30 40
