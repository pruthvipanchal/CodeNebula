// CodeNebula - C++98 Example: merge
// Compile: g++ -std=c++98 -Wall -Wextra -o example merge.cpp

// std::merge combines two sorted ranges into a single sorted
// destination range. Both input ranges must already be sorted.

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

void print_vec(const std::vector<int>& v, const char* label) {
    std::cout << label << ": ";
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Two sorted ranges
    int a[] = {1, 3, 5, 7, 9};
    int b[] = {2, 4, 6, 8, 10};
    std::vector<int> v1(a, a + 5);
    std::vector<int> v2(b, b + 5);

    print_vec(v1, "Range A");
    print_vec(v2, "Range B");

    // Merge into a destination vector
    std::vector<int> result;
    std::merge(v1.begin(), v1.end(),
               v2.begin(), v2.end(),
               std::back_inserter(result));
    print_vec(result, "Merged");

    // Merge with overlapping values
    int c[] = {1, 2, 5};
    int d[] = {2, 3, 5, 8};
    std::vector<int> v3(c, c + 3);
    std::vector<int> v4(d, d + 4);

    std::vector<int> result2;
    std::merge(v3.begin(), v3.end(),
               v4.begin(), v4.end(),
               std::back_inserter(result2));
    print_vec(result2, "Merged (overlapping)");

    return 0;
}

// Expected output:
// Range A: 1 3 5 7 9
// Range B: 2 4 6 8 10
// Merged: 1 2 3 4 5 6 7 8 9 10
// Merged (overlapping): 1 2 2 3 5 5 8
