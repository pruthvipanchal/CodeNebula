// CodeNebula - C++98 Example: valarray
// Compile: g++ -std=c++98 -Wall -Wextra -o example valarray.cpp

#include <iostream>
#include <valarray>
#include <cmath>

int main() {
    // valarray supports element-wise arithmetic
    double a_data[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double b_data[] = {10.0, 20.0, 30.0, 40.0, 50.0};

    std::valarray<double> a(a_data, 5);
    std::valarray<double> b(b_data, 5);

    // Element-wise operations
    std::valarray<double> sum = a + b;
    std::valarray<double> prod = a * b;
    std::valarray<double> scaled = a * 3.0;

    std::cout << "a + b:   ";
    for (std::size_t i = 0; i < sum.size(); ++i) std::cout << sum[i] << " ";
    std::cout << std::endl;

    std::cout << "a * b:   ";
    for (std::size_t i = 0; i < prod.size(); ++i) std::cout << prod[i] << " ";
    std::cout << std::endl;

    std::cout << "a * 3:   ";
    for (std::size_t i = 0; i < scaled.size(); ++i) std::cout << scaled[i] << " ";
    std::cout << std::endl;

    // Aggregate functions
    std::cout << "sum(a):  " << a.sum() << std::endl;
    std::cout << "min(a):  " << a.min() << std::endl;
    std::cout << "max(a):  " << a.max() << std::endl;

    // Apply math functions
    std::valarray<double> sq = std::sqrt(a);
    std::cout << "sqrt(a): ";
    for (std::size_t i = 0; i < sq.size(); ++i) std::cout << sq[i] << " ";
    std::cout << std::endl;

    return 0;
}

// Expected output:
// a + b:   11 22 33 44 55
// a * b:   10 40 90 160 250
// a * 3:   3 6 9 12 15
// sum(a):  15
// min(a):  1
// max(a):  5
// sqrt(a): 1 1.41421 1.73205 2 2.23607
