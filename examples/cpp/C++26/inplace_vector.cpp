// CodeNebula - C++26 Example: std::inplace_vector
// Compile: g++ -std=c++26 -Wall -Wextra -o example inplace_vector.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// std::inplace_vector<T, N> is a fixed-capacity, variable-size container
// stored entirely on the stack (no heap allocation). It behaves like
// std::vector but with a compile-time maximum capacity N.

#include <iostream>
#include <array>
#include <algorithm>
#include <stdexcept>
#include <cstddef>

// --- C++26 std::inplace_vector Syntax ---
//
// #include <inplace_vector>
//
// std::inplace_vector<int, 10> v;    // capacity=10, size=0, stack-allocated
// v.push_back(1);                     // size=1
// v.push_back(2);                     // size=2
// v[0];                               // 1
// v.size();                           // 2
// v.capacity();                       // 10 (always)
// // v.push_back() throws if size == capacity

// --- Simulation using C++20 features ---

template<typename T, std::size_t N>
class inplace_vector_sim {
    std::array<T, N> storage_{};
    std::size_t size_ = 0;

public:
    constexpr void push_back(const T& val) {
        if (size_ >= N) throw std::bad_alloc();
        storage_[size_++] = val;
    }
    constexpr T& operator[](std::size_t i) { return storage_[i]; }
    constexpr const T& operator[](std::size_t i) const { return storage_[i]; }
    constexpr std::size_t size() const { return size_; }
    constexpr std::size_t capacity() const { return N; }
    constexpr bool empty() const { return size_ == 0; }
    constexpr void pop_back() { if (size_ > 0) --size_; }
    constexpr T* begin() { return storage_.data(); }
    constexpr T* end() { return storage_.data() + size_; }
    constexpr const T* begin() const { return storage_.data(); }
    constexpr const T* end() const { return storage_.data() + size_; }
};

int main() {
    std::cout << "=== C++26 std::inplace_vector (Simulated) ===" << std::endl;

    inplace_vector_sim<int, 8> v;
    std::cout << "Capacity: " << v.capacity() << ", Size: " << v.size() << std::endl;

    // Add elements
    for (int i : {10, 30, 20, 50, 40})
        v.push_back(i);
    std::cout << "After push_back x5, size: " << v.size() << std::endl;

    // Iterate
    std::cout << "Elements: ";
    for (auto x : v) std::cout << x << " ";
    std::cout << std::endl;

    // Sort (works with random-access iterators)
    std::sort(v.begin(), v.end());
    std::cout << "Sorted:   ";
    for (auto x : v) std::cout << x << " ";
    std::cout << std::endl;

    // Overflow check
    try {
        for (int i = 0; i < 10; ++i) v.push_back(99);
    } catch (const std::bad_alloc&) {
        std::cout << "Overflow caught at size " << v.size() << std::endl;
    }

    std::cout << "inplace_vector: stack-allocated, fixed-capacity vector." << std::endl;
    return 0;
}

// Expected output:
// === C++26 std::inplace_vector (Simulated) ===
// Capacity: 8, Size: 0
// After push_back x5, size: 5
// Elements: 10 30 20 50 40
// Sorted:   10 20 30 40 50
// Overflow caught at size 8
// inplace_vector: stack-allocated, fixed-capacity vector.
