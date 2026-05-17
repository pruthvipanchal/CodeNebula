// CodeNebula - C++98 Example: set_intersection
// Compile: g++ -std=c++98 -Wall -Wextra -o example set_intersection.cpp

// std::set_intersection computes the intersection of two sorted
// ranges -- elements that appear in both ranges.

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
    int a[] = {1, 2, 3, 4, 5, 6};
    int b[] = {2, 4, 6, 8, 10};
    std::vector<int> v1(a, a + 6);
    std::vector<int> v2(b, b + 5);

    print_vec(v1, "Set A");
    print_vec(v2, "Set B");

    std::vector<int> result;
    std::set_intersection(v1.begin(), v1.end(),
                          v2.begin(), v2.end(),
                          std::back_inserter(result));
    print_vec(result, "A intersect B");

    // No overlap
    int c[] = {1, 3, 5};
    int d[] = {2, 4, 6};
    std::vector<int> v3(c, c + 3);
    std::vector<int> v4(d, d + 3);

    std::vector<int> result2;
    std::set_intersection(v3.begin(), v3.end(),
                          v4.begin(), v4.end(),
                          std::back_inserter(result2));
    std::cout << "Disjoint intersection size: "
              << result2.size() << std::endl;

    return 0;
}

// Expected output:
// Set A: 1 2 3 4 5 6
// Set B: 2 4 6 8 10
// A intersect B: 2 4 6
// Disjoint intersection size: 0
