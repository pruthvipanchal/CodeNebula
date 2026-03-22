// CodeNebula - C++98 Example: std::minus
// Compile: g++ -std=c++98 -Wall -Wextra -o example minus.cpp

#include <iostream>
#include <functional>
#include <algorithm>

int main() {
    int a[] = {50, 40, 30, 20, 10};
    int b[] = {5, 10, 15, 20, 25};
    int result[5];

    // Element-wise subtraction: a[i] - b[i]
    std::transform(a, a + 5, b, result, std::minus<int>());

    std::cout << "Element-wise difference: ";
    for (int i = 0; i < 5; ++i) std::cout << result[i] << " ";
    std::cout << std::endl;

    // Subtract constant from each element using bind2nd
    int out[5];
    std::transform(a, a + 5, out, std::bind2nd(std::minus<int>(), 5));

    std::cout << "Each - 5: ";
    for (int i = 0; i < 5; ++i) std::cout << out[i] << " ";
    std::cout << std::endl;

    // Subtract each element from constant using bind1st
    std::transform(a, a + 5, out, std::bind1st(std::minus<int>(), 100));

    std::cout << "100 - each: ";
    for (int i = 0; i < 5; ++i) std::cout << out[i] << " ";
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Element-wise difference: 45 30 15 0 -15
// Each - 5: 45 35 25 15 5
// 100 - each: 50 60 70 80 90
