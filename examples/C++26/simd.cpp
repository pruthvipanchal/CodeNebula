// CodeNebula - C++26 Example: std::simd Vectorized Operations
// Compile: g++ -std=c++26 -Wall -Wextra -o example simd.cpp
// Note: Requires C++26 compiler support

#include <iostream>
#include <array>
#include <cstddef>

// C++26 introduces std::simd in <simd> for portable SIMD (Single Instruction,
// Multiple Data) programming. std::simd wraps a fixed-size vector of elements
// and maps arithmetic to hardware SIMD instructions (SSE, AVX, NEON, etc.).
//
// Key types:
//   std::simd<T, Abi>       - a SIMD vector of T
//   std::simd<T>::size()    - number of lanes (implementation-defined)
//   Arithmetic operators (+, -, *, /) work element-wise

// --- Simulation of std::simd for educational purposes ---
namespace simd_sim {
    template <typename T, std::size_t N = 4>
    struct simd {
        std::array<T, N> data{};
        static constexpr std::size_t size() { return N; }
        simd() = default;
        explicit simd(T val) { data.fill(val); }
        simd(std::initializer_list<T> il) {
            std::size_t i = 0;
            for (auto v : il) { if (i < N) data[i++] = v; }
        }
        T operator[](std::size_t i) const { return data[i]; }
        friend simd operator+(const simd& a, const simd& b) {
            simd r; for (std::size_t i = 0; i < N; ++i) r.data[i] = a.data[i] + b.data[i]; return r;
        }
        friend simd operator*(const simd& a, const simd& b) {
            simd r; for (std::size_t i = 0; i < N; ++i) r.data[i] = a.data[i] * b.data[i]; return r;
        }
    };
}

int main() {
    using Vec = simd_sim::simd<float, 4>;

    // Create SIMD vectors (in real C++26: std::simd<float> a{1,2,3,4})
    Vec a{1.0f, 2.0f, 3.0f, 4.0f};
    Vec b{5.0f, 6.0f, 7.0f, 8.0f};

    // Element-wise addition
    Vec sum = a + b;
    std::cout << "a + b = [";
    for (std::size_t i = 0; i < Vec::size(); ++i)
        std::cout << (i ? ", " : "") << sum[i];
    std::cout << "]\n";

    // Element-wise multiplication
    Vec prod = a * b;
    std::cout << "a * b = [";
    for (std::size_t i = 0; i < Vec::size(); ++i)
        std::cout << (i ? ", " : "") << prod[i];
    std::cout << "]\n";

    // Broadcast scalar to all lanes
    Vec scaled = a * Vec(10.0f);
    std::cout << "a * 10 = [";
    for (std::size_t i = 0; i < Vec::size(); ++i)
        std::cout << (i ? ", " : "") << scaled[i];
    std::cout << "]\n";

    std::cout << "SIMD lanes: " << Vec::size() << "\n";
    return 0;
}

// Expected output:
// a + b = [6, 8, 10, 12]
// a * b = [5, 12, 21, 32]
// a * 10 = [10, 20, 30, 40]
// SIMD lanes: 4
