// CodeNebula - C++26 Example: std::simd::reduce Horizontal Operations
// Compile: g++ -std=c++26 -Wall -Wextra -o example simd_reduce.cpp
// Note: Requires C++26 compiler support

#include <iostream>
#include <array>
#include <cstddef>
#include <algorithm>
#include <numeric>

// Horizontal (reduce) operations collapse all lanes of a SIMD vector into
// a single scalar. C++26's std::simd provides:
//   reduce(simd_vec)              - sum all lanes
//   reduce(simd_vec, std::plus)   - sum (explicit)
//   reduce(simd_vec, std::multiplies) - product
//   hmin(simd_vec), hmax(simd_vec)    - horizontal min/max

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
    };

    // Horizontal sum (default reduce)
    template <typename T, std::size_t N>
    T reduce(const simd<T,N>& v) {
        return std::accumulate(v.data.begin(), v.data.end(), T{0});
    }

    // Horizontal product
    template <typename T, std::size_t N>
    T reduce_mul(const simd<T,N>& v) {
        return std::accumulate(v.data.begin(), v.data.end(), T{1}, std::multiplies<T>{});
    }

    // Horizontal min and max
    template <typename T, std::size_t N>
    T hmin(const simd<T,N>& v) { return *std::min_element(v.data.begin(), v.data.end()); }

    template <typename T, std::size_t N>
    T hmax(const simd<T,N>& v) { return *std::max_element(v.data.begin(), v.data.end()); }
}

int main() {
    using Vec = simd_sim::simd<float, 4>;

    Vec v{3.0f, 1.0f, 4.0f, 1.5f};

    std::cout << "Vector: [3, 1, 4, 1.5]\n";
    std::cout << "reduce (sum):     " << simd_sim::reduce(v)     << "\n";
    std::cout << "reduce (product): " << simd_sim::reduce_mul(v) << "\n";
    std::cout << "hmin:             " << simd_sim::hmin(v)       << "\n";
    std::cout << "hmax:             " << simd_sim::hmax(v)       << "\n";

    // Practical use: dot product via multiply + reduce
    Vec a{1.0f, 2.0f, 3.0f, 4.0f};
    Vec b{5.0f, 6.0f, 7.0f, 8.0f};
    // In real C++26: auto dot = std::reduce(a * b);
    simd_sim::simd<float, 4> prod;
    for (std::size_t i = 0; i < 4; ++i)
        prod.data[i] = a[i] * b[i];
    float dot = simd_sim::reduce(prod);
    std::cout << "dot(a, b):        " << dot << "\n";

    return 0;
}

// Expected output:
// Vector: [3, 1, 4, 1.5]
// reduce (sum):     9.5
// reduce (product): 18
// hmin:             1
// hmax:             4
// dot(a, b):        70
