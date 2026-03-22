// CodeNebula - C++98 Example: partial_sort_copy
// Compile: g++ -std=c++98 -Wall -Wextra -o example partial_sort_copy.cpp

// std::partial_sort_copy copies the smallest N elements from a
// source range into a destination range in sorted order, without
// modifying the source.

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
    int arr[] = {50, 20, 80, 10, 40, 90, 30, 70, 60};
    const int n = sizeof(arr) / sizeof(arr[0]);
    std::vector<int> src(arr, arr + n);

    print_vec(src, "Source");

    // Copy 4 smallest elements, sorted, into dest
    std::vector<int> dest(4);
    std::partial_sort_copy(src.begin(), src.end(),
                           dest.begin(), dest.end());
    print_vec(dest, "4 smallest sorted");

    // Source is unchanged
    print_vec(src, "Source after");

    // Copy 3 largest using greater<int> comparator
    std::vector<int> top3(3);
    std::partial_sort_copy(src.begin(), src.end(),
                           top3.begin(), top3.end(),
                           std::greater<int>());
    print_vec(top3, "3 largest sorted desc");

    return 0;
}

// Expected output:
// Source: 50 20 80 10 40 90 30 70 60
// 4 smallest sorted: 10 20 30 40
// Source after: 50 20 80 10 40 90 30 70 60
// 3 largest sorted desc: 90 80 70
