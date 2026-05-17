// CodeNebula - C++98 Example: std::plus
// Compile: g++ -std=c++98 -Wall -Wextra -o example plus.cpp

#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {10, 20, 30, 40, 50};
    int result[5];

    // std::plus adds two values; use with transform for element-wise addition
    std::transform(a, a + 5, b, result, std::plus<int>());

    std::cout << "Element-wise sum: ";
    for (int i = 0; i < 5; ++i) std::cout << result[i] << " ";
    std::cout << std::endl;

    // Use plus with accumulate to sum a vector
    std::vector<int> v(a, a + 5);
    int total = std::accumulate(v.begin(), v.end(), 0, std::plus<int>());
    std::cout << "Accumulate sum: " << total << std::endl;

    // Add constant 100 to each element using bind2nd
    std::vector<int> out(5);
    std::transform(v.begin(), v.end(), out.begin(),
                   std::bind2nd(std::plus<int>(), 100));
    std::cout << "Each + 100: ";
    for (std::vector<int>::iterator it = out.begin(); it != out.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Element-wise sum: 11 22 33 44 55
// Accumulate sum: 15
// Each + 100: 101 102 103 104 105
