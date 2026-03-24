// CodeNebula - C++26 Example: std::mdspan Improvements
// Compile: g++ -std=c++26 -Wall -Wextra -o example mdspan_improvements.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// C++26 improves std::mdspan with better dynamic_extent handling,
// submdspan support, and layout improvements. mdspan provides a
// non-owning multidimensional view over contiguous memory.

#include <iostream>
#include <vector>
#include <array>
#include <numeric>
#include <cstddef>

// --- C++26 mdspan Improvements ---
//
// #include <mdspan>
//
// // Basic mdspan (C++23)
// std::vector<int> data(12);
// std::mdspan<int, std::extents<int, 3, 4>> mat(data.data());
//
// // C++26: submdspan -- extract a sub-view
// auto row = std::submdspan(mat, 1, std::full_extent);  // 2nd row
// auto col = std::submdspan(mat, std::full_extent, 2);  // 3rd column
//
// // C++26: improved dynamic_extent mixed with static
// std::mdspan<int, std::extents<int, std::dynamic_extent, 4>> dynRows(ptr, rows);

// --- Simulation using C++20 features ---

template<typename T, std::size_t Rows, std::size_t Cols>
class mdspan_sim {
    T* data_;
public:
    mdspan_sim(T* p) : data_(p) {}
    T& operator()(std::size_t r, std::size_t c) { return data_[r * Cols + c]; }
    const T& operator()(std::size_t r, std::size_t c) const { return data_[r * Cols + c]; }
    static constexpr std::size_t rows() { return Rows; }
    static constexpr std::size_t cols() { return Cols; }
    T* data() { return data_; }
};

int main() {
    std::cout << "=== C++26 std::mdspan Improvements (Simulated) ===" << std::endl;

    // Create a 3x4 matrix view over flat data
    std::vector<int> storage(12);
    std::iota(storage.begin(), storage.end(), 1); // 1..12

    mdspan_sim<int, 3, 4> mat(storage.data());

    // Display matrix
    std::cout << "3x4 Matrix:" << std::endl;
    for (std::size_t r = 0; r < mat.rows(); ++r) {
        std::cout << "  ";
        for (std::size_t c = 0; c < mat.cols(); ++c)
            std::cout << mat(r, c) << "\t";
        std::cout << std::endl;
    }

    // Simulate submdspan: extract row 1
    std::cout << "Row 1 (submdspan): ";
    for (std::size_t c = 0; c < mat.cols(); ++c)
        std::cout << mat(1, c) << " ";
    std::cout << std::endl;

    // Simulate submdspan: extract column 2
    std::cout << "Col 2 (submdspan): ";
    for (std::size_t r = 0; r < mat.rows(); ++r)
        std::cout << mat(r, 2) << " ";
    std::cout << std::endl;

    // Modify through the view
    mat(0, 0) = 99;
    std::cout << "After mat(0,0)=99, storage[0] = " << storage[0] << std::endl;

    std::cout << "mdspan gives multidimensional views with zero overhead." << std::endl;
    return 0;
}

// Expected output:
// === C++26 std::mdspan Improvements (Simulated) ===
// 3x4 Matrix:
//   1	2	3	4
//   5	6	7	8
//   9	10	11	12
// Row 1 (submdspan): 5 6 7 8
// Col 2 (submdspan): 3 7 11
// After mat(0,0)=99, storage[0] = 99
// mdspan gives multidimensional views with zero overhead.
