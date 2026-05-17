// CodeNebula - C++23 Example: std::assume_aligned (C++23 Usage)
// Compile: g++ -std=c++23 -Wall -Wextra -o example assume_aligned.cpp
// Note: Requires GCC 13+ / Clang 17+

#include <cstdlib>
#include <iostream>
#include <memory>
#include <numeric>
#include <new>

// std::assume_aligned was introduced in C++20. In C++23 it can be combined
// with other C++23 features like constexpr improvements and deducing this.
// This example shows idiomatic C++23 usage patterns.

// SIMD-style processing with assume_aligned in a constexpr-friendly wrapper
template <std::size_t Align, typename T>
struct AlignedSpan {
    T* data_;
    std::size_t size_;

    // Deducing this (C++23) for const/non-const access
    template <typename Self>
    auto aligned_data(this Self&& self) {
        return std::assume_aligned<Align>(self.data_);
    }

    T& operator[](std::size_t i) {
        return aligned_data()[i];
    }

    void fill(T value) {
        auto* p = std::assume_aligned<Align>(data_);
        for (std::size_t i = 0; i < size_; ++i)
            p[i] = value;
    }

    T sum() const {
        const auto* p = std::assume_aligned<Align>(data_);
        T total{};
        for (std::size_t i = 0; i < size_; ++i)
            total += p[i];
        return total;
    }
};

int main() {
    std::cout << "=== std::assume_aligned (C++23 usage) ===\n\n";

    constexpr std::size_t N = 8;
    constexpr std::size_t ALIGN = 64;

    // Allocate aligned memory
    float* raw = static_cast<float*>(
        std::aligned_alloc(ALIGN, N * sizeof(float)));

    if (!raw) {
        std::cerr << "Allocation failed\n";
        return 1;
    }

    AlignedSpan<ALIGN, float> span{raw, N};

    // Fill with alignment hint active
    span.fill(2.5f);
    std::cout << "After fill(2.5): sum = " << span.sum() << "\n";

    // Direct element access
    span[0] = 10.0f;
    span[7] = 20.0f;
    std::cout << "After modification: [0]=" << span[0]
              << ", [7]=" << span[7] << "\n";
    std::cout << "Sum = " << span.sum() << "\n";

    // Verify alignment
    auto addr = reinterpret_cast<std::uintptr_t>(raw);
    std::cout << "\nPointer aligned to " << ALIGN << " bytes: "
              << (addr % ALIGN == 0 ? "yes" : "no") << "\n";

    std::cout << "\nassume_aligned combined with deducing this\n";
    std::cout << "enables cleaner API design in C++23.\n";

    std::free(raw);
    return 0;
}

// Expected output:
// === std::assume_aligned (C++23 usage) ===
//
// After fill(2.5): sum = 20
// After modification: [0]=10, [7]=20
// Sum = 45
//
// Pointer aligned to 64 bytes: yes
//
// assume_aligned combined with deducing this
// enables cleaner API design in C++23.
