// CodeNebula - C++23 Example: Multidimensional Subscript Operator
// Compile: g++ -std=c++23 -Wall -Wextra -o example multidim_subscript.cpp
// Note: Requires GCC 12+ / Clang 15+ / MSVC 19.34+

// C++23 allows operator[] to accept multiple arguments: obj[i, j, k].
// This replaces awkward workarounds like obj[{i,j}] or obj(i,j).

#include <iostream>
#include <vector>

class Matrix {
    std::vector<double> data_;
    int rows_, cols_;
public:
    Matrix(int rows, int cols)
        : data_(rows * cols, 0.0), rows_(rows), cols_(cols) {}

    // C++23 multidimensional subscript operator
    double& operator[](int i, int j) {
        return data_[i * cols_ + j];
    }

    const double& operator[](int i, int j) const {
        return data_[i * cols_ + j];
    }

    int rows() const { return rows_; }
    int cols() const { return cols_; }

    void print() const {
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                std::cout << (*this)[i, j] << "\t";
            }
            std::cout << std::endl;
        }
    }
};

// 3D array example
class Tensor3D {
    std::vector<int> data_;
    int d1_, d2_, d3_;
public:
    Tensor3D(int d1, int d2, int d3)
        : data_(d1 * d2 * d3, 0), d1_(d1), d2_(d2), d3_(d3) {}

    int& operator[](int i, int j, int k) {
        return data_[(i * d2_ + j) * d3_ + k];
    }
};

int main() {
    std::cout << "=== 2D Matrix with operator[i, j] ===" << std::endl;
    Matrix m(3, 3);

    // Natural multidimensional indexing
    m[0, 0] = 1; m[0, 1] = 2; m[0, 2] = 3;
    m[1, 0] = 4; m[1, 1] = 5; m[1, 2] = 6;
    m[2, 0] = 7; m[2, 1] = 8; m[2, 2] = 9;
    m.print();

    std::cout << "\nDiagonal: " << m[0,0] << " " << m[1,1] << " " << m[2,2] << std::endl;

    std::cout << "\n=== 3D Tensor with operator[i, j, k] ===" << std::endl;
    Tensor3D t(2, 2, 2);
    t[0, 0, 0] = 1;
    t[0, 1, 1] = 42;
    t[1, 0, 1] = 99;
    std::cout << "t[0,0,0] = " << t[0,0,0] << std::endl;
    std::cout << "t[0,1,1] = " << t[0,1,1] << std::endl;
    std::cout << "t[1,0,1] = " << t[1,0,1] << std::endl;

    return 0;
}

/*
Expected output:
=== 2D Matrix with operator[i, j] ===
1	2	3
4	5	6
7	8	9

Diagonal: 1 5 9

=== 3D Tensor with operator[i, j, k] ===
t[0,0,0] = 1
t[0,1,1] = 42
t[1,0,1] = 99
*/
