// CodeNebula - C++98 Example: set_symmetric_difference
// Compile: g++ -std=c++98 -Wall -Wextra -o example set_symmetric_difference.cpp

// std::set_symmetric_difference computes elements that are in
// either sorted range but not in both (the XOR of two sets).

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

    std::vector<int> result;
    std::set_symmetric_difference(v1.begin(), v1.end(),
                                  v2.begin(), v2.end(),
                                  std::back_inserter(result));
    print_vec(result, "A sym_diff B");

    // Identical sets have empty symmetric difference
    std::vector<int> result2;
    std::set_symmetric_difference(v1.begin(), v1.end(),
                                  v1.begin(), v1.end(),
                                  std::back_inserter(result2));
    std::cout << "Same set sym_diff size: "
              << result2.size() << std::endl;

    return 0;
}

// Expected output:
// Set A: 1 2 3 4 5
// Set B: 3 4 5 6 7
// A sym_diff B: 1 2 6 7
// Same set sym_diff size: 0
