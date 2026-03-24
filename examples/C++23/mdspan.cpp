// CodeNebula - C++23 Example: std::mdspan
// Compile: g++ -std=c++23 -Wall -Wextra -o example mdspan.cpp
// Note: Requires GCC 14+ / Clang 18+ / MSVC 19.36+

// std::mdspan is a non-owning multidimensional view over contiguous memory.
// It provides multidimensional indexing without copying data.
// Think of it as std::span but for N-dimensional arrays.

#include <iostream>
#include <mdspan>
#include <vector>
#include <numeric>

void print_matrix(std::mdspan<int, std::extents<std::size_t, std::dynamic_extent,
                  std::dynamic_extent>> mat) {
    for (std::size_t i = 0; i < mat.extent(0); ++i) {
        for (std::size_t j = 0; j < mat.extent(1); ++j) {
            std::cout << mat[i, j] << "\t";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::cout << "=== std::mdspan - 2D View ===" << std::endl;

    // Flat storage, viewed as a 3x4 matrix
    std::vector<int> data(12);
    std::iota(data.begin(), data.end(), 1);  // 1..12

    // Create a 3x4 mdspan over the flat data
    std::mdspan mat(data.data(), 3, 4);

    std::cout << "3x4 matrix:" << std::endl;
    print_matrix(mat);

    std::cout << "Extents: " << mat.extent(0) << " x " << mat.extent(1) << std::endl;
    std::cout << "Total size: " << mat.size() << std::endl;
    std::cout << "Element [1,2] = " << mat[1, 2] << std::endl;

    // Modify through mdspan (it's a view, not a copy)
    mat[0, 0] = 99;
    std::cout << "\nAfter mat[0,0] = 99:" << std::endl;
    std::cout << "data[0] = " << data[0] << " (underlying data changed)" << std::endl;

    // Static extents: compile-time known dimensions
    std::cout << "\n=== Static Extents ===" << std::endl;
    int arr[6] = {10, 20, 30, 40, 50, 60};
    std::mdspan<int, std::extents<std::size_t, 2, 3>> fixed(arr);
    std::cout << "2x3 static matrix:" << std::endl;
    for (std::size_t i = 0; i < 2; ++i) {
        for (std::size_t j = 0; j < 3; ++j)
            std::cout << fixed[i, j] << "\t";
        std::cout << std::endl;
    }

    // 3D mdspan
    std::cout << "\n=== 3D mdspan ===" << std::endl;
    std::vector<int> cube_data(24);
    std::iota(cube_data.begin(), cube_data.end(), 0);
    std::mdspan cube(cube_data.data(), 2, 3, 4);

    std::cout << "Shape: " << cube.extent(0) << "x"
              << cube.extent(1) << "x" << cube.extent(2) << std::endl;
    std::cout << "cube[1,2,3] = " << cube[1, 2, 3] << std::endl;
    std::cout << "cube[0,0,0] = " << cube[0, 0, 0] << std::endl;
    std::cout << "Rank: " << decltype(cube)::rank() << std::endl;

    return 0;
}

/*
Expected output:
=== std::mdspan - 2D View ===
3x4 matrix:
1	2	3	4
5	6	7	8
9	10	11	12
Extents: 3 x 4
Total size: 12
Element [1,2] = 7

After mat[0,0] = 99:
data[0] = 99 (underlying data changed)

=== Static Extents ===
2x3 static matrix:
10	20	30
40	50	60

=== 3D mdspan ===
Shape: 2x3x4
cube[1,2,3] = 23
cube[0,0,0] = 0
Rank: 3
*/
