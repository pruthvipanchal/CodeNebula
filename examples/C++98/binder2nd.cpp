// CodeNebula - C++98 Example: binder2nd / bind2nd()
// Compile: g++ -std=c++98 -Wall -Wextra -o example binder2nd.cpp

#include <iostream>
#include <functional>
#include <algorithm>

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = 8;

    // bind2nd(less, 5) creates: x < 5
    int count = std::count_if(arr, arr + n,
                              std::bind2nd(std::less<int>(), 5));
    std::cout << "Elements < 5: " << count << std::endl;

    // bind2nd(plus, 100) creates: x + 100
    int result[8];
    std::transform(arr, arr + n, result,
                   std::bind2nd(std::plus<int>(), 100));

    std::cout << "Each + 100: ";
    for (int i = 0; i < n; ++i) std::cout << result[i] << " ";
    std::cout << std::endl;

    // bind2nd(modulus, 2) creates: x % 2  (to check odd/even)
    // Then bind2nd(equal_to, 0) checks if result is 0
    int evens = std::count_if(arr, arr + n,
                              std::not1(std::bind2nd(std::modulus<int>(), 2)));
    std::cout << "Even numbers: " << evens << std::endl;

    return 0;
}

// Expected output:
// Elements < 5: 4
// Each + 100: 101 102 103 104 105 106 107 108
// Even numbers: 4
