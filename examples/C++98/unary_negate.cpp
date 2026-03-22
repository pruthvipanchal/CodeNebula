// CodeNebula - C++98 Example: unary_negate / not1()
// Compile: g++ -std=c++98 -Wall -Wextra -o example unary_negate.cpp

#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

// Custom predicate deriving from unary_function (required for not1)
struct IsPositive : std::unary_function<int, bool> {
    bool operator()(int x) const { return x > 0; }
};

int main() {
    int arr[] = {-3, -1, 0, 2, 5, -4, 7};
    int n = 7;

    // Count positive numbers
    int pos = std::count_if(arr, arr + n, IsPositive());
    std::cout << "Positive count: " << pos << std::endl;

    // not1() creates a unary_negate that inverts the predicate
    // Count non-positive numbers (zero or negative)
    int non_pos = std::count_if(arr, arr + n, std::not1(IsPositive()));
    std::cout << "Non-positive count: " << non_pos << std::endl;

    // Partition: non-positive first, positive last
    std::vector<int> v(arr, arr + n);
    std::partition(v.begin(), v.end(), std::not1(IsPositive()));

    std::cout << "Partitioned (non-pos first): ";
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Positive count: 3
// Non-positive count: 4
// Partitioned (non-pos first): -3 -1 0 -4 5 2 7
