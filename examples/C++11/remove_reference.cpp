// CodeNebula - C++11 Example: remove_reference
// Compile: g++ -std=c++11 -Wall -Wextra -o example remove_reference.cpp

// Demonstrates std::remove_reference to strip lvalue and rvalue references
// from types. Essential for implementing perfect forwarding and move semantics.

#include <iostream>
#include <type_traits>

template<typename T>
void show_type_info() {
    using NoRef = typename std::remove_reference<T>::type;
    std::cout << "  is_reference:         " << std::is_reference<T>::value << std::endl;
    std::cout << "  is_lvalue_reference:  " << std::is_lvalue_reference<T>::value << std::endl;
    std::cout << "  is_rvalue_reference:  " << std::is_rvalue_reference<T>::value << std::endl;
    std::cout << "  after remove_ref same as int: "
              << std::is_same<NoRef, int>::value << std::endl;
}

int main() {
    std::cout << "=== std::remove_reference ===" << std::endl;

    // Basic removal
    static_assert(std::is_same<std::remove_reference<int>::type, int>::value,
                  "int unchanged");
    static_assert(std::is_same<std::remove_reference<int&>::type, int>::value,
                  "int& -> int");
    static_assert(std::is_same<std::remove_reference<int&&>::type, int>::value,
                  "int&& -> int");

    std::cout << "int:" << std::endl;
    show_type_info<int>();
    std::cout << "int&:" << std::endl;
    show_type_info<int&>();
    std::cout << "int&&:" << std::endl;
    show_type_info<int&&>();

    // const is preserved, only reference is removed
    static_assert(std::is_same<std::remove_reference<const int&>::type,
                  const int>::value, "const int& -> const int");

    std::cout << "\nconst int& -> const int: "
              << std::is_same<std::remove_reference<const int&>::type,
                              const int>::value << std::endl;

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::remove_reference ===
// int:
//   is_reference:         0
//   is_lvalue_reference:  0
//   is_rvalue_reference:  0
//   after remove_ref same as int: 1
// int&:
//   is_reference:         1
//   is_lvalue_reference:  1
//   is_rvalue_reference:  0
//   after remove_ref same as int: 1
// int&&:
//   is_reference:         1
//   is_lvalue_reference:  0
//   is_rvalue_reference:  1
//   after remove_ref same as int: 1
//
// const int& -> const int: 1
//
// All checks passed!
