// CodeNebula - C++98 Example: std::not_equal_to
// Compile: g++ -std=c++98 -Wall -Wextra -o example not_equal_to.cpp

#include <iostream>
#include <functional>
#include <algorithm>

int main() {
    int arr[] = {5, 3, 5, 5, 2, 5, 1};
    int n = 7;

    // Count elements not equal to 5
    int count = std::count_if(arr, arr + n,
                              std::bind2nd(std::not_equal_to<int>(), 5));
    std::cout << "Elements != 5: " << count << std::endl;

    // Find first element not equal to 5
    int* pos = std::find_if(arr, arr + n,
                            std::bind2nd(std::not_equal_to<int>(), 5));
    if (pos != arr + n) {
        std::cout << "First non-5 value: " << *pos
                  << " at index " << (pos - arr) << std::endl;
    }

    // Use mismatch with not_equal_to to find first matching pair
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {9, 8, 3, 7, 6};
    std::pair<int*, int*> m = std::mismatch(a, a + 5, b,
                                            std::not_equal_to<int>());
    std::cout << "First equal pair at index " << (m.first - a)
              << ": " << *m.first << std::endl;

    return 0;
}

// Expected output:
// Elements != 5: 3
// First non-5 value: 3 at index 1
// First equal pair at index 2: 3
