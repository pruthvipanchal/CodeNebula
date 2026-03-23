// CodeNebula - C++11 Example: is_void
// Compile: g++ -std=c++11 -Wall -Wextra -o example is_void.cpp

// Demonstrates std::is_void to check if a type is void.
// Only void (and cv-qualified variants) returns true.

#include <iostream>
#include <type_traits>

int main() {
    std::cout << "=== std::is_void ===" << std::endl;

    std::cout << "void:           " << std::is_void<void>::value << std::endl;
    std::cout << "const void:     " << std::is_void<const void>::value << std::endl;
    std::cout << "volatile void:  " << std::is_void<volatile void>::value << std::endl;
    std::cout << "cv void:        "
              << std::is_void<const volatile void>::value << std::endl;
    std::cout << "int:            " << std::is_void<int>::value << std::endl;
    std::cout << "void*:          " << std::is_void<void*>::value << std::endl;
    std::cout << "bool:           " << std::is_void<bool>::value << std::endl;

    static_assert(std::is_void<void>::value, "void is void");
    static_assert(std::is_void<const void>::value, "const void is void");
    static_assert(!std::is_void<void*>::value, "void* is not void");
    static_assert(!std::is_void<int>::value, "int is not void");

    // Practical use: check return type
    using ReturnType = void;
    std::cout << "\nReturnType is void: " << std::is_void<ReturnType>::value << std::endl;

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::is_void ===
// void:           1
// const void:     1
// volatile void:  1
// cv void:        1
// int:            0
// void*:          0
// bool:           0
//
// ReturnType is void: 1
//
// All checks passed!
