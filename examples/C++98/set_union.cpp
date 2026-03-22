// CodeNebula - C++98 Example: set_union
// Compile: g++ -std=c++98 -Wall -Wextra -o example set_union.cpp

// std::set_union computes the union of two sorted ranges.
// Elements that appear in both ranges appear once in the output
// (or the maximum count from either range for duplicates).

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
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {3, 4, 5, 6, 7};
    std::vector<int> v1(a, a + 5);
    std::vector<int> v2(b, b + 5);

    print_vec(v1, "Set A");
    print_vec(v2, "Set B");

    // Compute union
    std::vector<int> result;
    std::set_union(v1.begin(), v1.end(),
                   v2.begin(), v2.end(),
                   std::back_inserter(result));
    print_vec(result, "A union B");

    // Union with duplicates in input
    int c[] = {1, 1, 2, 3, 3};
    int d[] = {1, 2, 2, 3};
    std::vector<int> v3(c, c + 5);
    std::vector<int> v4(d, d + 4);

    print_vec(v3, "Set C");
    print_vec(v4, "Set D");

    std::vector<int> result2;
    std::set_union(v3.begin(), v3.end(),
                   v4.begin(), v4.end(),
                   std::back_inserter(result2));
    print_vec(result2, "C union D");

    return 0;
}

// Expected output:
// Set A: 1 2 3 4 5
// Set B: 3 4 5 6 7
// A union B: 1 2 3 4 5 6 7
// Set C: 1 1 2 3 3
// Set D: 1 2 2 3
// C union D: 1 1 2 2 3 3
