// CodeNebula - C++23 Example: std::ranges::stride_view
// Compile: g++ -std=c++23 -Wall -Wextra -o example ranges_stride_view.cpp
// Note: Requires GCC 13+ / Clang 17+

// std::ranges::stride_view takes every Nth element from a range. It advances
// through the underlying range by the given stride, producing a view that
// includes elements at positions 0, N, 2N, 3N, etc.

#include <iostream>
#include <ranges>
#include <vector>
#include <string>

int main() {
    std::vector<int> data = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Take every 2nd element
    std::cout << "=== Every 2nd element (stride 2) ===" << std::endl;
    for (auto val : data | std::views::stride(2)) {
        std::cout << "  " << val;
    }
    std::cout << std::endl;

    // Take every 3rd element
    std::cout << "\n=== Every 3rd element (stride 3) ===" << std::endl;
    for (auto val : data | std::views::stride(3)) {
        std::cout << "  " << val;
    }
    std::cout << std::endl;

    // Practical: downsample a signal
    std::vector<double> signal = {1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5};
    std::cout << "\n=== Downsampled signal (every 3rd sample) ===" << std::endl;
    for (auto val : signal | std::views::stride(3)) {
        std::cout << "  " << val << std::endl;
    }

    // Combine stride with other views
    std::cout << "\n=== Even-indexed elements, squared ===" << std::endl;
    for (auto val : data | std::views::stride(2)
                        | std::views::transform([](int x) { return x * x; })) {
        std::cout << "  " << val;
    }
    std::cout << std::endl;

    // Interleave columns: get column 0 and column 1 from flat 2D data
    // Data represents a 4x3 matrix stored row-major
    std::vector<int> matrix = {10, 20, 30,
                               40, 50, 60,
                               70, 80, 90,
                               100, 110, 120};
    int cols = 3;
    std::cout << "\n=== Extract column 0 from 4x3 matrix ===" << std::endl;
    for (auto val : matrix | std::views::drop(0) | std::views::stride(cols)) {
        std::cout << "  " << val;
    }
    std::cout << std::endl;

    std::cout << "\n=== Extract column 1 from 4x3 matrix ===" << std::endl;
    for (auto val : matrix | std::views::drop(1) | std::views::stride(cols)) {
        std::cout << "  " << val;
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// === Every 2nd element (stride 2) ===
//   0  2  4  6  8
//
// === Every 3rd element (stride 3) ===
//   0  3  6  9
//
// === Downsampled signal (every 3rd sample) ===
//   1
//   2.5
//   4
//
// === Even-indexed elements, squared ===
//   0  4  16  36  64
//
// === Extract column 0 from 4x3 matrix ===
//   10  40  70  100
//
// === Extract column 1 from 4x3 matrix ===
//   20  50  80  110
