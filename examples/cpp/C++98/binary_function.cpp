// CodeNebula - C++98 Example: binary_function
// Compile: g++ -std=c++98 -Wall -Wextra -o example binary_function.cpp

#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <numeric>

// Inherit from binary_function to enable bind1st/bind2nd/not2
struct PowerOf : std::binary_function<int, int, int> {
    int operator()(int base, int exp) const {
        int result = 1;
        for (int i = 0; i < exp; ++i) result *= base;
        return result;
    }
};

struct SumGreaterThan : std::binary_function<int, int, bool> {
    bool operator()(int a, int b) const {
        return (a + b) > 10;
    }
};

int main() {
    // Use PowerOf with bind2nd to square each element
    std::vector<int> v;
    for (int i = 1; i <= 5; ++i) v.push_back(i);

    std::vector<int> result(v.size());
    std::transform(v.begin(), v.end(), result.begin(),
                   std::bind2nd(PowerOf(), 2));

    std::cout << "Squared: ";
    for (std::vector<int>::iterator it = result.begin(); it != result.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Use PowerOf with bind1st to compute powers of 2
    std::transform(v.begin(), v.end(), result.begin(),
                   std::bind1st(PowerOf(), 2));

    std::cout << "Powers of 2: ";
    for (std::vector<int>::iterator it = result.begin(); it != result.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Squared: 1 4 9 16 25
// Powers of 2: 2 4 8 16 32
