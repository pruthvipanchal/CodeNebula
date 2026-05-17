// CodeNebula - C++20 Example: Constant Evaluation for Non-Type Template Parameters
// Compile: g++ -std=c++20 -Wall -Wextra -o example consteval_nttp.cpp

// C++20 expands non-type template parameters (NTTPs) significantly.
// consteval ensures values used as NTTPs are truly compile-time constants.

#include <iostream>
#include <array>

// Basic NTTP with consteval to guarantee compile-time value
consteval int compute_size(int rows, int cols) {
    return rows * cols;
}

// Template using an int NTTP
template <int N>
struct FixedBuffer {
    std::array<int, N> data{};
    constexpr int size() const { return N; }
};

// consteval function producing a value for NTTP use
consteval int next_power_of_two(int n) {
    int result = 1;
    while (result < n) result *= 2;
    return result;
}

// Template that uses a consteval-produced NTTP
template <int N>
struct AlignedBuffer {
    static constexpr int aligned_size = next_power_of_two(N);
    std::array<char, aligned_size> storage{};

    void print_info() const {
        std::cout << "Requested: " << N
                  << ", Aligned to: " << aligned_size << "\n";
    }
};

// Floating-point NTTPs are new in C++20
template <double Factor>
double scale(double value) {
    return value * Factor;
}

// consteval to validate NTTP values at compile time
consteval int validated_positive(int n) {
    if (n <= 0) throw "Value must be positive";  // compile error if n <= 0
    return n;
}

template <int N>
void print_n_stars() {
    for (int i = 0; i < N; ++i) std::cout << '*';
    std::cout << "\n";
}

int main() {
    // consteval result used as NTTP
    FixedBuffer<compute_size(3, 4)> buf;
    std::cout << "FixedBuffer size: " << buf.size() << "\n";

    // Power-of-two alignment via consteval
    AlignedBuffer<10> a10;
    AlignedBuffer<50> a50;
    AlignedBuffer<100> a100;
    a10.print_info();
    a50.print_info();
    a100.print_info();

    // Floating-point NTTP (C++20)
    std::cout << "scale<2.5>(10.0) = " << scale<2.5>(10.0) << "\n";
    std::cout << "scale<0.1>(50.0) = " << scale<0.1>(50.0) << "\n";

    // Validated NTTP
    print_n_stars<validated_positive(5)>();

    // This would fail at compile time:
    // print_n_stars<validated_positive(-1)>();  // ERROR: "Value must be positive"

    return 0;
}

// Expected output:
// FixedBuffer size: 12
// Requested: 10, Aligned to: 16
// Requested: 50, Aligned to: 64
// Requested: 100, Aligned to: 128
// scale<2.5>(10.0) = 25
// scale<0.1>(50.0) = 5
// *****
