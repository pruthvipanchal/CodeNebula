// CodeNebula - C++98 Example: pointer_to_binary_function / ptr_fun (binary)
// Compile: g++ -std=c++98 -Wall -Wextra -o example pointer_to_binary_function.cpp

#include <iostream>
#include <functional>
#include <algorithm>
#include <cmath>

int int_pow(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; ++i) result *= base;
    return result;
}

int int_max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int bases[] = {2, 3, 4, 5};
    int result[4];

    // ptr_fun wraps a binary function pointer to work with bind1st/bind2nd
    // Compute x^3 for each element using bind2nd
    std::transform(bases, bases + 4, result,
                   std::bind2nd(std::ptr_fun(int_pow), 3));

    std::cout << "Cubed: ";
    for (int i = 0; i < 4; ++i) std::cout << result[i] << " ";
    std::cout << std::endl;

    // Compute 10^x using bind1st
    int exps[] = {0, 1, 2, 3};
    std::transform(exps, exps + 4, result,
                   std::bind1st(std::ptr_fun(int_pow), 10));

    std::cout << "Powers of 10: ";
    for (int i = 0; i < 4; ++i) std::cout << result[i] << " ";
    std::cout << std::endl;

    // Element-wise max of two arrays
    int a[] = {3, 7, 2, 9};
    int b[] = {5, 1, 8, 4};
    std::transform(a, a + 4, b, result, std::ptr_fun(int_max));

    std::cout << "Element-wise max: ";
    for (int i = 0; i < 4; ++i) std::cout << result[i] << " ";
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Cubed: 8 27 64 125
// Powers of 10: 1 10 100 1000
// Element-wise max: 5 7 8 9
