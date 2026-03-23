// CodeNebula - C++11 Example: is_pointer
// Compile: g++ -std=c++11 -Wall -Wextra -o example is_pointer.cpp

// Demonstrates std::is_pointer to check if a type is a pointer type.
// Note: std::is_pointer does NOT match smart pointers or member pointers.

#include <iostream>
#include <type_traits>
#include <memory>

struct MyClass { int x; };

int main() {
    std::cout << "=== std::is_pointer ===" << std::endl;

    std::cout << "int*:             " << std::is_pointer<int*>::value << std::endl;
    std::cout << "const int*:       " << std::is_pointer<const int*>::value << std::endl;
    std::cout << "void*:            " << std::is_pointer<void*>::value << std::endl;
    std::cout << "char*:            " << std::is_pointer<char*>::value << std::endl;
    std::cout << "int:              " << std::is_pointer<int>::value << std::endl;
    std::cout << "int&:             " << std::is_pointer<int&>::value << std::endl;
    std::cout << "int**:            " << std::is_pointer<int**>::value << std::endl;

    // Smart pointers are NOT raw pointers
    std::cout << "\nshared_ptr<int>:  "
              << std::is_pointer<std::shared_ptr<int>>::value << std::endl;

    // Member pointers are NOT detected by is_pointer
    std::cout << "int MyClass::*:   "
              << std::is_pointer<int MyClass::*>::value << std::endl;

    static_assert(std::is_pointer<int*>::value, "int* is a pointer");
    static_assert(std::is_pointer<int**>::value, "int** is a pointer");
    static_assert(!std::is_pointer<int>::value, "int is not a pointer");
    static_assert(!std::is_pointer<int&>::value, "int& is not a pointer");

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::is_pointer ===
// int*:             1
// const int*:       1
// void*:            1
// char*:            1
// int:              0
// int&:             0
// int**:            1
//
// shared_ptr<int>:  0
// int MyClass::*:   0
//
// All checks passed!
