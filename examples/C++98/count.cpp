// CodeNebula - C++98 Example: count
// Compile: g++ -std=c++98 -Wall -Wextra -o example count.cpp

// std::count returns the number of elements in [first, last) that are equal
// to a given value.

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int arr[] = {1, 3, 2, 3, 5, 3, 2, 1, 3};
    std::vector<int> v(arr, arr + 9);

    std::cout << "Sequence: ";
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Count occurrences of 3
    int c = std::count(v.begin(), v.end(), 3);
    std::cout << "Count of 3: " << c << std::endl;

    // Count occurrences of 2
    c = std::count(v.begin(), v.end(), 2);
    std::cout << "Count of 2: " << c << std::endl;

    // Count a value not present
    c = std::count(v.begin(), v.end(), 99);
    std::cout << "Count of 99: " << c << std::endl;

    // Count in a plain array
    c = std::count(arr, arr + 9, 1);
    std::cout << "Count of 1 in array: " << c << std::endl;

    return 0;
}

// Expected output:
// Sequence: 1 3 2 3 5 3 2 1 3
// Count of 3: 4
// Count of 2: 2
// Count of 99: 0
// Count of 1 in array: 2
