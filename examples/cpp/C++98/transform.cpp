// CodeNebula - C++98 Example: transform
// Compile: g++ -std=c++98 -Wall -Wextra -o example transform.cpp

// std::transform applies a function to each element in a range and stores the
// result in a destination range. It has two forms: unary (one input range)
// and binary (two input ranges combined with a binary operation).

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int square(int x) {
    return x * x;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    std::vector<int> v(arr, arr + 5);

    // Unary transform: square each element
    std::vector<int> squared(5);
    std::transform(v.begin(), v.end(), squared.begin(), square);

    std::cout << "Original: ";
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Squared:  ";
    for (std::vector<int>::iterator it = squared.begin(); it != squared.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Unary transform: negate using std::negate
    std::vector<int> negated(5);
    std::transform(v.begin(), v.end(), negated.begin(), std::negate<int>());

    std::cout << "Negated:  ";
    for (std::vector<int>::iterator it = negated.begin(); it != negated.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Binary transform: add two ranges element-wise
    int arr2[] = {10, 20, 30, 40, 50};
    std::vector<int> v2(arr2, arr2 + 5);
    std::vector<int> sums(5);
    std::transform(v.begin(), v.end(), v2.begin(), sums.begin(),
                   std::plus<int>());

    std::cout << "Sums:     ";
    for (std::vector<int>::iterator it = sums.begin(); it != sums.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Original: 1 2 3 4 5
// Squared:  1 4 9 16 25
// Negated:  -1 -2 -3 -4 -5
// Sums:     11 22 33 44 55
