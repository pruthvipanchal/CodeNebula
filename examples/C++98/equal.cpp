// CodeNebula - C++98 Example: equal
// Compile: g++ -std=c++98 -Wall -Wextra -o example equal.cpp

// std::equal checks whether two ranges are element-wise equal.
// Returns true if all corresponding elements match, false otherwise.

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

bool abs_equal(int a, int b) {
    return std::abs(a) == std::abs(b);
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3, 4, 5};
    int arr3[] = {1, 2, 9, 4, 5};
    std::vector<int> v1(arr1, arr1 + 5);
    std::vector<int> v2(arr2, arr2 + 5);
    std::vector<int> v3(arr3, arr3 + 5);

    // Compare equal ranges
    bool result = std::equal(v1.begin(), v1.end(), v2.begin());
    std::cout << "v1 == v2: " << (result ? "true" : "false") << std::endl;

    // Compare different ranges
    result = std::equal(v1.begin(), v1.end(), v3.begin());
    std::cout << "v1 == v3: " << (result ? "true" : "false") << std::endl;

    // Compare with custom predicate (absolute value equality)
    int arr4[] = {-1, 2, -3, 4, -5};
    std::vector<int> v4(arr4, arr4 + 5);
    result = std::equal(v1.begin(), v1.end(), v4.begin(), abs_equal);
    std::cout << "v1 abs-equals v4: " << (result ? "true" : "false") << std::endl;

    // Compare a sub-range
    result = std::equal(v1.begin(), v1.begin() + 2, v3.begin());
    std::cout << "First 2 elements equal: " << (result ? "true" : "false") << std::endl;

    return 0;
}

// Expected output:
// v1 == v2: true
// v1 == v3: false
// v1 abs-equals v4: true
// First 2 elements equal: true
