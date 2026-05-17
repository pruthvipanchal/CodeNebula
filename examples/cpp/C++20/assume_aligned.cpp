// CodeNebula - C++20 Example: std::assume_aligned
// Compile: g++ -std=c++20 -Wall -Wextra -o example assume_aligned.cpp

#include <cstdlib>
#include <iostream>
#include <memory>
#include <numeric>

// std::assume_aligned<N>(ptr) returns ptr with a compiler hint
// that it is aligned to N bytes, enabling SIMD optimizations

// Process array with alignment hint for vectorization
void process_aligned(float* data, std::size_t n) {
    // Tell the compiler this pointer is 64-byte aligned
    float* aligned_data = std::assume_aligned<64>(data);
    for (std::size_t i = 0; i < n; ++i) {
        aligned_data[i] *= 2.0f;
    }
}

// Sum with alignment hint
float sum_aligned(const float* data, std::size_t n) {
    const float* aligned_data = std::assume_aligned<32>(data);
    float total = 0.0f;
    for (std::size_t i = 0; i < n; ++i) {
        total += aligned_data[i];
    }
    return total;
}

int main() {
    constexpr std::size_t N = 16;
    constexpr std::size_t alignment = 64;

    std::cout << "=== std::assume_aligned optimization hint ===\n";

    // Allocate aligned memory
    float* data = static_cast<float*>(
        std::aligned_alloc(alignment, N * sizeof(float)));

    if (!data) {
        std::cerr << "Allocation failed\n";
        return 1;
    }

    // Verify alignment
    auto addr = reinterpret_cast<std::uintptr_t>(data);
    std::cout << "Pointer address: " << data << "\n";
    std::cout << "Aligned to " << alignment << " bytes: "
              << (addr % alignment == 0 ? "yes" : "no") << "\n";

    // Initialize
    std::iota(data, data + N, 1.0f);  // 1, 2, 3, ..., 16

    std::cout << "\nBefore processing: ";
    for (std::size_t i = 0; i < N; ++i) std::cout << data[i] << " ";
    std::cout << "\n";

    // Process with alignment hint
    process_aligned(data, N);

    std::cout << "After processing:  ";
    for (std::size_t i = 0; i < N; ++i) std::cout << data[i] << " ";
    std::cout << "\n";

    float total = sum_aligned(data, N);
    std::cout << "Sum of processed:  " << total << "\n";
    std::cout << "Expected:          " << N * (N + 1) << "\n";

    std::free(data);

    std::cout << "\n=== Note ===\n";
    std::cout << "assume_aligned is a compiler hint only.\n";
    std::cout << "Using it on unaligned memory is undefined behavior.\n";

    return 0;
}
