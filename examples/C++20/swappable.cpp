// CodeNebula - C++20 Example: std::swappable Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example swappable.cpp

// std::swappable<T> checks that lvalues of type T can be swapped.
// std::swappable_with<T, U> checks that values of types T and U
// can be swapped with each other.

#include <concepts>
#include <iostream>
#include <string>
#include <vector>

// Generic swap-and-report function
template <std::swappable T>
void swap_and_show(T& a, T& b) {
    std::cout << "  Before: a=" << a << ", b=" << b << "\n";
    std::ranges::swap(a, b);
    std::cout << "  After:  a=" << a << ", b=" << b << "\n";
}

// Sort two elements using swap
template <std::swappable T>
void sort_pair(T& a, T& b) {
    if (b < a) {
        std::ranges::swap(a, b);
    }
    std::cout << "  Sorted: " << a << ", " << b << "\n";
}

// Custom non-swappable type (deleted swap)
struct NoSwap {
    int value;
    NoSwap(int v) : value(v) {}
    NoSwap(const NoSwap&) = delete;
    NoSwap& operator=(const NoSwap&) = delete;
};

int main() {
    // Swap integers
    std::cout << "Swapping ints:\n";
    int x = 10, y = 20;
    swap_and_show(x, y);

    // Swap strings
    std::cout << "Swapping strings:\n";
    std::string s1 = "hello", s2 = "world";
    swap_and_show(s1, s2);

    // Swap doubles
    std::cout << "Swapping doubles:\n";
    double d1 = 1.5, d2 = 9.9;
    swap_and_show(d1, d2);

    // Sort pairs
    std::cout << "Sorting pairs:\n";
    int a = 50, b = 10;
    sort_pair(a, b);

    // Concept checks
    std::cout << "\nSwappable checks:\n";
    std::cout << "int: " << std::swappable<int> << "\n";
    std::cout << "string: " << std::swappable<std::string> << "\n";
    std::cout << "vector<int>: " << std::swappable<std::vector<int>> << "\n";
    std::cout << "NoSwap: " << std::swappable<NoSwap> << "\n";

    return 0;
}

// Expected output:
// Swapping ints:
//   Before: a=10, b=20
//   After:  a=20, b=10
// Swapping strings:
//   Before: a=hello, b=world
//   After:  a=world, b=hello
// Swapping doubles:
//   Before: a=1.5, b=9.9
//   After:  a=9.9, b=1.5
// Sorting pairs:
//   Sorted: 10, 50
//
// Swappable checks:
// int: 1
// string: 1
// vector<int>: 1
// NoSwap: 0
