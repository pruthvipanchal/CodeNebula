// CodeNebula - C++98 Example: std::modulus
// Compile: g++ -std=c++98 -Wall -Wextra -o example modulus.cpp

#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

int main() {
    int a[] = {10, 23, 37, 44, 55};
    int b[] = {3, 5, 7, 9, 11};
    int result[5];

    // Element-wise modulus: a[i] % b[i]
    std::transform(a, a + 5, b, result, std::modulus<int>());

    std::cout << "Element-wise modulus: ";
    for (int i = 0; i < 5; ++i) std::cout << result[i] << " ";
    std::cout << std::endl;

    // Find elements divisible by 3 using bind2nd(modulus, 3) == 0
    // We check modulus result, then filter
    std::vector<int> v;
    for (int i = 1; i <= 12; ++i) v.push_back(i);

    std::cout << "Mod 3 results: ";
    std::vector<int> mods(v.size());
    std::transform(v.begin(), v.end(), mods.begin(),
                   std::bind2nd(std::modulus<int>(), 3));
    for (std::vector<int>::iterator it = mods.begin(); it != mods.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Element-wise modulus: 1 3 2 8 0
// Mod 3 results: 1 2 0 1 2 0 1 2 0 1 2 0
