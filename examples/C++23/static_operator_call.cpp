// CodeNebula - C++23 Example: Static operator()
// Compile: g++ -std=c++23 -Wall -Wextra -o example static_operator_call.cpp
// Note: Requires GCC 13+ / Clang 16+ / MSVC 19.34+

// C++23 allows operator() to be declared static for stateless functors.
// This eliminates the implicit 'this' pointer, enabling better optimization.

#include <iostream>
#include <vector>
#include <algorithm>

// Stateless comparator: no 'this' pointer overhead
struct DescendingOrder {
    static bool operator()(int a, int b) {
        return a > b;
    }
};

// Stateless function object for transformations
struct Square {
    static int operator()(int x) {
        return x * x;
    }
};

// Can also be used with multiple parameters
struct Add {
    static int operator()(int a, int b) {
        return a + b;
    }
};

// Stateless predicate
struct IsEven {
    static bool operator()(int x) {
        return x % 2 == 0;
    }
};

// Lambdas can also be static in C++23
inline constexpr auto triple = [](int x) static { return x * 3; };

int main() {
    std::cout << "=== Static operator() ===" << std::endl;

    // Direct call on type (no object needed conceptually, but syntax requires one)
    std::cout << "Square(5) = " << Square{}(5) << std::endl;
    std::cout << "Add(3, 4) = " << Add{}(3, 4) << std::endl;

    std::cout << "\n=== Sorting with static comparator ===" << std::endl;
    std::vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6};
    std::sort(nums.begin(), nums.end(), DescendingOrder{});
    std::cout << "Descending: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << std::endl;

    std::cout << "\n=== Filtering with static predicate ===" << std::endl;
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8};
    auto it = std::partition(data.begin(), data.end(), IsEven{});
    std::cout << "Even elements: ";
    for (auto i = data.begin(); i != it; ++i) std::cout << *i << " ";
    std::cout << std::endl;

    std::cout << "\n=== Static lambda ===" << std::endl;
    std::cout << "triple(7) = " << triple(7) << std::endl;

    // Static lambdas cannot capture anything (enforced at compile time)
    // auto bad = [&x](int y) static { return x + y; }; // ERROR: captures

    std::cout << "\nBenefit: no 'this' pointer = smaller callable, better inlining" << std::endl;

    return 0;
}

/*
Expected output:
=== Static operator() ===
Square(5) = 25
Add(3, 4) = 7

=== Sorting with static comparator ===
Descending: 9 6 5 4 3 2 1 1

=== Filtering with static predicate ===
Even elements: 8 2 6 4
(Note: partition order of even elements may vary)

=== Static lambda ===
triple(7) = 21

Benefit: no 'this' pointer = smaller callable, better inlining
*/
