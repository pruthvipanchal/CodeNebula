// CodeNebula - C++98 Example: includes
// Compile: g++ -std=c++98 -Wall -Wextra -o example includes.cpp

// std::includes checks whether every element in one sorted range
// is contained in another sorted range (i.e., sorted subset test).

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
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[] = {2, 4, 6, 8};
    int c[] = {2, 4, 11};

    std::vector<int> full(a, a + 10);
    std::vector<int> sub1(b, b + 4);
    std::vector<int> sub2(c, c + 3);

    print_vec(full, "Full set");
    print_vec(sub1, "Subset 1");
    print_vec(sub2, "Subset 2");

    // Both ranges must be sorted for std::includes to work
    bool result1 = std::includes(full.begin(), full.end(),
                                 sub1.begin(), sub1.end());
    std::cout << "Full includes Subset 1? "
              << (result1 ? "yes" : "no") << std::endl;

    bool result2 = std::includes(full.begin(), full.end(),
                                 sub2.begin(), sub2.end());
    std::cout << "Full includes Subset 2? "
              << (result2 ? "yes" : "no") << std::endl;

    // Empty set is always a subset
    std::vector<int> empty;
    bool result3 = std::includes(full.begin(), full.end(),
                                 empty.begin(), empty.end());
    std::cout << "Full includes empty? "
              << (result3 ? "yes" : "no") << std::endl;

    return 0;
}

// Expected output:
// Full set: 1 2 3 4 5 6 7 8 9 10
// Subset 1: 2 4 6 8
// Subset 2: 2 4 11
// Full includes Subset 1? yes
// Full includes Subset 2? no
// Full includes empty? yes
