// CodeNebula - C++98 Example: std::multiplies
// Compile: g++ -std=c++98 -Wall -Wextra -o example multiplies.cpp

#include <iostream>
#include <functional>
#include <algorithm>
#include <numeric>

int main() {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {2, 3, 4, 5, 6};
    int result[5];

    // Element-wise multiplication
    std::transform(a, a + 5, b, result, std::multiplies<int>());

    std::cout << "Element-wise product: ";
    for (int i = 0; i < 5; ++i) std::cout << result[i] << " ";
    std::cout << std::endl;

    // Compute factorial using accumulate with multiplies
    // 5! = 1 * 2 * 3 * 4 * 5 = 120
    int factorial = std::accumulate(a, a + 5, 1, std::multiplies<int>());
    std::cout << "5! (accumulate): " << factorial << std::endl;

    // Triple each element using bind2nd
    std::transform(a, a + 5, result, std::bind2nd(std::multiplies<int>(), 3));

    std::cout << "Tripled: ";
    for (int i = 0; i < 5; ++i) std::cout << result[i] << " ";
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Element-wise product: 2 6 12 20 30
// 5! (accumulate): 120
// Tripled: 3 6 9 12 15
