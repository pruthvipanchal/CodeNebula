// CodeNebula - C++98 Example: set_difference
// Compile: g++ -std=c++98 -Wall -Wextra -o example set_difference.cpp

// std::set_difference computes elements present in the first sorted
// range but not in the second sorted range.

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
    int a[] = {1, 2, 3, 4, 5, 6, 7};
    int b[] = {2, 4, 6, 8};
    std::vector<int> v1(a, a + 7);
    std::vector<int> v2(b, b + 4);

    print_vec(v1, "Set A");
    print_vec(v2, "Set B");

    // A - B: elements in A not in B
    std::vector<int> diff_ab;
    std::set_difference(v1.begin(), v1.end(),
                        v2.begin(), v2.end(),
                        std::back_inserter(diff_ab));
    print_vec(diff_ab, "A - B");

    // B - A: elements in B not in A
    std::vector<int> diff_ba;
    std::set_difference(v2.begin(), v2.end(),
                        v1.begin(), v1.end(),
                        std::back_inserter(diff_ba));
    print_vec(diff_ba, "B - A");

    return 0;
}

// Expected output:
// Set A: 1 2 3 4 5 6 7
// Set B: 2 4 6 8
// A - B: 1 3 5 7
// B - A: 8
