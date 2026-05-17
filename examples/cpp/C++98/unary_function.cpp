// CodeNebula - C++98 Example: unary_function
// Compile: g++ -std=c++98 -Wall -Wextra -o example unary_function.cpp

#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

// Inherit from unary_function to define argument_type and result_type
// This enables use with not1(), bind adapters, etc.
struct IsEven : std::unary_function<int, bool> {
    bool operator()(int x) const {
        return x % 2 == 0;
    }
};

struct Square : std::unary_function<int, int> {
    int operator()(int x) const {
        return x * x;
    }
};

int main() {
    std::vector<int> v;
    for (int i = 1; i <= 6; ++i) v.push_back(i);

    // Count even numbers using our unary functor
    int evens = std::count_if(v.begin(), v.end(), IsEven());
    std::cout << "Even count (1-6): " << evens << std::endl;

    // Use not1 with our unary_function-derived functor
    int odds = std::count_if(v.begin(), v.end(), std::not1(IsEven()));
    std::cout << "Odd count (1-6): " << odds << std::endl;

    // Transform using Square functor
    std::vector<int> result(v.size());
    std::transform(v.begin(), v.end(), result.begin(), Square());
    std::cout << "Squares: ";
    for (std::vector<int>::iterator it = result.begin(); it != result.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Even count (1-6): 3
// Odd count (1-6): 3
// Squares: 1 4 9 16 25 36
