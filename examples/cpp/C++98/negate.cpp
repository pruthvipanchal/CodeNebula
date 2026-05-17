// CodeNebula - C++98 Example: std::negate
// Compile: g++ -std=c++98 -Wall -Wextra -o example negate.cpp

#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

int main() {
    int arr[] = {1, -2, 3, -4, 5};
    int result[5];

    // Negate each element
    std::transform(arr, arr + 5, result, std::negate<int>());

    std::cout << "Negated: ";
    for (int i = 0; i < 5; ++i) std::cout << result[i] << " ";
    std::cout << std::endl;

    // Use negate to get absolute values (negate negatives)
    std::vector<int> v(arr, arr + 5);
    std::cout << "Original: ";
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Double negate returns original
    std::vector<int> doubled(v.size());
    std::transform(v.begin(), v.end(), doubled.begin(), std::negate<int>());
    std::transform(doubled.begin(), doubled.end(), doubled.begin(), std::negate<int>());

    std::cout << "Double negated (original): ";
    for (std::vector<int>::iterator it = doubled.begin(); it != doubled.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Negated: -1 2 -3 4 -5
// Original: 1 -2 3 -4 5
// Double negated (original): 1 -2 3 -4 5
