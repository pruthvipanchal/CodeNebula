// CodeNebula - C++11 Example: is_same
// Compile: g++ -std=c++11 -Wall -Wextra -o example is_same.cpp

// Demonstrates std::is_same to check if two types are identical.
// The comparison is exact: cv-qualifiers and references matter.

#include <iostream>
#include <type_traits>
#include <cstdint>

int main() {
    std::cout << "=== std::is_same ===" << std::endl;

    // Exact type matches
    std::cout << "int, int:           " << std::is_same<int, int>::value << std::endl;
    std::cout << "int, unsigned:      " << std::is_same<int, unsigned>::value << std::endl;
    std::cout << "int, int32_t:       " << std::is_same<int, int32_t>::value << std::endl;
    std::cout << "int, const int:     " << std::is_same<int, const int>::value << std::endl;
    std::cout << "int, int&:          " << std::is_same<int, int&>::value << std::endl;
    std::cout << "float, double:      " << std::is_same<float, double>::value << std::endl;

    static_assert(std::is_same<int, int>::value, "int is same as int");
    static_assert(!std::is_same<int, long>::value, "int differs from long");
    static_assert(!std::is_same<int, const int>::value, "cv matters");

    // Use with decltype
    auto x = 42;
    auto y = 42.0;
    std::cout << "\ndecltype(x) is int:    " << std::is_same<decltype(x), int>::value << std::endl;
    std::cout << "decltype(y) is double: " << std::is_same<decltype(y), double>::value << std::endl;

    // Removing qualifiers for comparison
    std::cout << "\nremove_const<const int>, int: "
              << std::is_same<std::remove_const<const int>::type, int>::value << std::endl;

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::is_same ===
// int, int:           1
// int, unsigned:      0
// int, int32_t:       1
// int, const int:     0
// int, int&:          0
// float, double:      0
//
// decltype(x) is int:    1
// decltype(y) is double: 1
//
// remove_const<const int>, int: 1
//
// All checks passed!
