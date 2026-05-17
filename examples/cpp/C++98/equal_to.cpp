// CodeNebula - C++98 Example: std::equal_to
// Compile: g++ -std=c++98 -Wall -Wextra -o example equal_to.cpp

#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

int main() {
    int arr[] = {1, 5, 3, 5, 2, 5, 4};
    int n = 7;

    // Count elements equal to 5 using bind2nd + equal_to
    int count = std::count_if(arr, arr + n,
                              std::bind2nd(std::equal_to<int>(), 5));
    std::cout << "Count of 5s: " << count << std::endl;

    // Find first element equal to 3
    int* pos = std::find_if(arr, arr + n,
                            std::bind2nd(std::equal_to<int>(), 3));
    if (pos != arr + n) {
        std::cout << "First 3 at index: " << (pos - arr) << std::endl;
    }

    // Check if two ranges are equal element-wise
    int a[] = {1, 2, 3};
    int b[] = {1, 2, 3};
    bool eq = std::equal(a, a + 3, b, std::equal_to<int>());
    std::cout << "Arrays equal: " << (eq ? "yes" : "no") << std::endl;

    int c[] = {1, 2, 4};
    eq = std::equal(a, a + 3, c, std::equal_to<int>());
    std::cout << "a == c: " << (eq ? "yes" : "no") << std::endl;

    return 0;
}

// Expected output:
// Count of 5s: 3
// First 3 at index: 2
// Arrays equal: yes
// a == c: no
