// CodeNebula - C++98 Example: std::greater_equal
// Compile: g++ -std=c++98 -Wall -Wextra -o example greater_equal.cpp

#include <iostream>
#include <functional>
#include <algorithm>

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = 8;

    // Count elements >= 5
    int count = std::count_if(arr, arr + n,
                              std::bind2nd(std::greater_equal<int>(), 5));
    std::cout << "Elements >= 5: " << count << std::endl;

    // Find first element >= 4
    int* pos = std::find_if(arr, arr + n,
                            std::bind2nd(std::greater_equal<int>(), 4));
    if (pos != arr + n) {
        std::cout << "First >= 4: " << *pos
                  << " at index " << (pos - arr) << std::endl;
    }

    // Sort descending using greater_equal (note: not a strict weak ordering
    // for sort, so we show it with other algorithms instead)
    // Use with lower_bound on sorted descending array
    int desc[] = {8, 7, 6, 5, 4, 3, 2, 1};
    int* lb = std::lower_bound(desc, desc + 8, 5, std::greater_equal<int>());
    std::cout << "lower_bound(5) in desc array at index: " << (lb - desc) << std::endl;

    return 0;
}

// Expected output:
// Elements >= 5: 4
// First >= 4: 4 at index 3
// lower_bound(5) in desc array at index: 3
