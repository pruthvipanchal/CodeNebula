// CodeNebula - C++98 Example: binary_negate / not2()
// Compile: g++ -std=c++98 -Wall -Wextra -o example binary_negate.cpp

#include <iostream>
#include <functional>
#include <algorithm>

int main() {
    int arr[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    int n = 9;

    // Sort ascending using std::less
    std::sort(arr, arr + n, std::less<int>());
    std::cout << "Ascending (less):    ";
    for (int i = 0; i < n; ++i) std::cout << arr[i] << " ";
    std::cout << std::endl;

    // not2(less) negates less, giving >=  (not a strict weak order for sort,
    // but useful for other algorithms)
    // Use not2(less) with mismatch to find first pair where a[i] < b[i]
    int a[] = {5, 5, 3, 7};
    int b[] = {5, 4, 6, 7};

    std::pair<int*, int*> mm = std::mismatch(a, a + 4, b,
                                             std::not2(std::less<int>()));

    if (mm.first != a + 4) {
        std::cout << "First pair where a < b: a="
                  << *mm.first << " b=" << *mm.second
                  << " at index " << (mm.first - a) << std::endl;
    }

    // Count pairs where a[i] != b[i] using not2(equal_to)
    int eq_count = std::inner_product(a, a + 4, b, 0,
                                      std::plus<int>(),
                                      std::not2(std::equal_to<int>()));
    std::cout << "Unequal pairs: " << eq_count << std::endl;

    return 0;
}

// Expected output:
// Ascending (less):    1 2 3 4 5 6 7 8 9
// First pair where a < b: a=3 b=6 at index 2
// Unequal pairs: 2
