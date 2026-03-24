// CodeNebula - C++23 Example: C++23 Range Adaptors
// Compile: g++ -std=c++23 -Wall -Wextra -o example ranges_adaptors.cpp
// Note: Requires GCC 13+ / Clang 17+

// C++23 adds many new range adaptors accessible via the views:: namespace.
// This example demonstrates piping with views::zip, views::zip_transform,
// views::adjacent, views::chunk, views::slide, views::stride, and others.

#include <iostream>
#include <ranges>
#include <vector>
#include <string>

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<std::string> labels = {"one", "two", "three", "four", "five"};

    // views::zip as a pipe adaptor
    std::cout << "=== views::zip (labels + nums) ===" << std::endl;
    for (auto [lbl, n] : std::views::zip(labels, nums)) {
        std::cout << "  " << lbl << " = " << n << std::endl;
    }

    // views::zip_transform as adaptor
    std::vector<int> a = {10, 20, 30};
    std::vector<int> b = {1, 2, 3};
    std::cout << "\n=== views::zip_transform (subtract) ===" << std::endl;
    for (auto val : std::views::zip_transform(std::minus{}, a, b)) {
        std::cout << "  " << val;
    }
    std::cout << std::endl;

    // views::adjacent<2> piped
    std::cout << "\n=== views::adjacent<2> piped ===" << std::endl;
    for (auto [x, y] : nums | std::views::adjacent<2>) {
        std::cout << "  " << x << "+" << y << "=" << x + y;
    }
    std::cout << std::endl;

    // views::chunk piped
    std::cout << "\n=== views::chunk(4) piped ===" << std::endl;
    for (auto chunk : nums | std::views::chunk(4)) {
        std::cout << "  [";
        bool first = true;
        for (auto v : chunk) { if (!first) std::cout << ","; std::cout << v; first = false; }
        std::cout << "]";
    }
    std::cout << std::endl;

    // views::slide piped
    std::cout << "\n=== views::slide(3) piped ===" << std::endl;
    for (auto win : nums | std::views::take(6) | std::views::slide(3)) {
        std::cout << "  [";
        bool first = true;
        for (auto v : win) { if (!first) std::cout << ","; std::cout << v; first = false; }
        std::cout << "]";
    }
    std::cout << std::endl;

    // views::stride piped
    std::cout << "\n=== views::stride(3) piped ===" << std::endl;
    for (auto val : nums | std::views::stride(3)) {
        std::cout << "  " << val;
    }
    std::cout << std::endl;

    // Chaining multiple new adaptors together
    std::cout << "\n=== Combined: stride(2) | chunk(3) ===" << std::endl;
    for (auto chunk : nums | std::views::stride(2) | std::views::chunk(3)) {
        std::cout << "  [";
        bool first = true;
        for (auto v : chunk) { if (!first) std::cout << ","; std::cout << v; first = false; }
        std::cout << "]";
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// === views::zip (labels + nums) ===
//   one = 1
//   two = 2
//   three = 3
//   four = 4
//   five = 5
//
// === views::zip_transform (subtract) ===
//   9  18  27
//
// === views::adjacent<2> piped ===
//   1+2=3  2+3=5  3+4=7  4+5=9  5+6=11  6+7=13  7+8=15  8+9=17  9+10=19
//
// === views::chunk(4) piped ===
//   [1,2,3,4]  [5,6,7,8]  [9,10]
//
// === views::slide(3) piped ===
//   [1,2,3]  [2,3,4]  [3,4,5]  [4,5,6]
//
// === views::stride(3) piped ===
//   1  4  7  10
//
// === Combined: stride(2) | chunk(3) ===
//   [1,3,5]  [7,9]
