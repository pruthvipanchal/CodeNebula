// CodeNebula - C++98 Example: copy
// Compile: g++ -std=c++98 -Wall -Wextra -o example copy.cpp

// std::copy copies elements from [first, last) to a destination range starting
// at d_first. Returns an iterator past the last copied element in destination.

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    std::vector<int> src(arr, arr + 5);

    // Copy into a pre-sized vector
    std::vector<int> dst(5);
    std::copy(src.begin(), src.end(), dst.begin());

    std::cout << "Source:      ";
    for (std::vector<int>::iterator it = src.begin(); it != src.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Destination: ";
    for (std::vector<int>::iterator it = dst.begin(); it != dst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Copy a sub-range (first 3 elements)
    std::vector<int> partial(3);
    std::copy(src.begin(), src.begin() + 3, partial.begin());

    std::cout << "Partial:     ";
    for (std::vector<int>::iterator it = partial.begin(); it != partial.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Copy from array to vector
    int data[] = {100, 200, 300};
    std::vector<int> from_arr(3);
    std::copy(data, data + 3, from_arr.begin());

    std::cout << "From array:  ";
    for (std::vector<int>::iterator it = from_arr.begin(); it != from_arr.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Source:      10 20 30 40 50
// Destination: 10 20 30 40 50
// Partial:     10 20 30
// From array:  100 200 300
