// CodeNebula - C++11 Example: is_array
// Compile: g++ -std=c++11 -Wall -Wextra -o example is_array.cpp

// Demonstrates std::is_array to check if a type is a C-style array.
// Note: std::array and std::vector are NOT detected as arrays.

#include <iostream>
#include <type_traits>
#include <array>
#include <vector>

int main() {
    std::cout << "=== std::is_array ===" << std::endl;

    std::cout << "int[5]:          " << std::is_array<int[5]>::value << std::endl;
    std::cout << "int[]:           " << std::is_array<int[]>::value << std::endl;
    std::cout << "char[10]:        " << std::is_array<char[10]>::value << std::endl;
    std::cout << "int[3][4]:       " << std::is_array<int[3][4]>::value << std::endl;
    std::cout << "int:             " << std::is_array<int>::value << std::endl;
    std::cout << "int*:            " << std::is_array<int*>::value << std::endl;

    // Standard containers are NOT C-style arrays
    std::cout << "\nstd::array<int,5>: "
              << std::is_array<std::array<int,5>>::value << std::endl;
    std::cout << "std::vector<int>:  "
              << std::is_array<std::vector<int>>::value << std::endl;

    static_assert(std::is_array<int[5]>::value, "int[5] is an array");
    static_assert(std::is_array<int[]>::value, "int[] is an array");
    static_assert(!std::is_array<int*>::value, "int* is not an array");

    // Rank and extent provide more detail
    std::cout << "\nRank of int[3][4]: " << std::rank<int[3][4]>::value << std::endl;
    std::cout << "Extent of int[5]:  " << std::extent<int[5]>::value << std::endl;

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::is_array ===
// int[5]:          1
// int[]:           1
// char[10]:        1
// int[3][4]:       1
// int:             0
// int*:            0
//
// std::array<int,5>: 0
// std::vector<int>:  0
//
// Rank of int[3][4]: 2
// Extent of int[5]:  5
//
// All checks passed!
