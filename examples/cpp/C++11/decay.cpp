// CodeNebula - C++11 Example: decay
// Compile: g++ -std=c++11 -Wall -Wextra -o example decay.cpp

// Demonstrates std::decay which applies the type transformations that
// occur when passing by value: removes references, cv-qualifiers,
// converts arrays to pointers, and functions to function pointers.

#include <iostream>
#include <type_traits>

void func(int) {}

int main() {
    std::cout << "=== std::decay ===" << std::endl;

    // Removes references and cv-qualifiers
    static_assert(std::is_same<std::decay<int&>::type, int>::value, "int& -> int");
    static_assert(std::is_same<std::decay<int&&>::type, int>::value, "int&& -> int");
    static_assert(std::is_same<std::decay<const int&>::type, int>::value,
                  "const int& -> int");

    std::cout << "decay<int&> is int:        "
              << std::is_same<std::decay<int&>::type, int>::value << std::endl;
    std::cout << "decay<const int&> is int:  "
              << std::is_same<std::decay<const int&>::type, int>::value << std::endl;
    std::cout << "decay<int&&> is int:       "
              << std::is_same<std::decay<int&&>::type, int>::value << std::endl;
    std::cout << "decay<volatile int> is int:"
              << std::is_same<std::decay<volatile int>::type, int>::value << std::endl;

    // Arrays decay to pointers
    static_assert(std::is_same<std::decay<int[5]>::type, int*>::value,
                  "int[5] -> int*");
    std::cout << "\ndecay<int[5]> is int*:     "
              << std::is_same<std::decay<int[5]>::type, int*>::value << std::endl;
    std::cout << "decay<int[]> is int*:      "
              << std::is_same<std::decay<int[]>::type, int*>::value << std::endl;

    // Functions decay to function pointers
    using FuncType = decltype(func);
    using DecayedFunc = std::decay<FuncType>::type;
    static_assert(std::is_same<DecayedFunc, void(*)(int)>::value,
                  "function -> function pointer");
    std::cout << "\ndecay<void(int)> is void(*)(int): "
              << std::is_same<DecayedFunc, void(*)(int)>::value << std::endl;

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::decay ===
// decay<int&> is int:        1
// decay<const int&> is int:  1
// decay<int&&> is int:       1
// decay<volatile int> is int:1
//
// decay<int[5]> is int*:     1
// decay<int[]> is int*:      1
//
// decay<void(int)> is void(*)(int): 1
//
// All checks passed!
