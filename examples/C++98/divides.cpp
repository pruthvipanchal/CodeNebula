// CodeNebula - C++98 Example: std::divides
// Compile: g++ -std=c++98 -Wall -Wextra -o example divides.cpp

#include <iostream>
#include <functional>
#include <algorithm>

int main() {
    int a[] = {100, 200, 300, 400, 500};
    int b[] = {10, 20, 30, 40, 50};
    int result[5];

    // Element-wise integer division
    std::transform(a, a + 5, b, result, std::divides<int>());

    std::cout << "Element-wise division: ";
    for (int i = 0; i < 5; ++i) std::cout << result[i] << " ";
    std::cout << std::endl;

    // Divide each element by 10 using bind2nd
    std::transform(a, a + 5, result, std::bind2nd(std::divides<int>(), 10));

    std::cout << "Each / 10: ";
    for (int i = 0; i < 5; ++i) std::cout << result[i] << " ";
    std::cout << std::endl;

    // Floating-point division
    double nums[] = {1.0, 2.0, 3.0, 4.0};
    double dres[4];
    std::transform(nums, nums + 4, dres,
                   std::bind1st(std::divides<double>(), 12.0));

    std::cout << "12 / each: ";
    for (int i = 0; i < 4; ++i) std::cout << dres[i] << " ";
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Element-wise division: 10 10 10 10 10
// Each / 10: 10 20 30 40 50
// 12 / each: 12 6 4 3
