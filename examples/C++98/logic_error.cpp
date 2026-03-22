// CodeNebula - C++98 Example: std::logic_error
// Compile: g++ -std=c++98 -Wall -Wextra -o example logic_error.cpp

#include <iostream>
#include <stdexcept>

class Matrix {
    int rows_, cols_;
public:
    Matrix(int r, int c) : rows_(r), cols_(c) {
        if (r <= 0 || c <= 0) {
            throw std::logic_error("matrix dimensions must be positive");
        }
    }
    int rows() const { return rows_; }
    int cols() const { return cols_; }
};

Matrix multiply(const Matrix& a, const Matrix& b) {
    if (a.cols() != b.rows()) {
        throw std::logic_error("incompatible matrix dimensions for multiplication");
    }
    return Matrix(a.rows(), b.cols());
}

int main() {
    // Invalid dimensions
    try {
        Matrix m(0, 5);
    } catch (const std::logic_error& e) {
        std::cout << "Logic error: " << e.what() << std::endl;
    }

    // Incompatible multiplication
    try {
        Matrix a(2, 3);
        Matrix b(4, 5);
        multiply(a, b);
    } catch (const std::logic_error& e) {
        std::cout << "Logic error: " << e.what() << std::endl;
    }

    // Valid multiplication
    try {
        Matrix a(2, 3);
        Matrix b(3, 4);
        Matrix c = multiply(a, b);
        std::cout << "Result: " << c.rows() << "x" << c.cols() << std::endl;
    } catch (const std::logic_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}

// Expected output:
// Logic error: matrix dimensions must be positive
// Logic error: incompatible matrix dimensions for multiplication
// Result: 2x4
