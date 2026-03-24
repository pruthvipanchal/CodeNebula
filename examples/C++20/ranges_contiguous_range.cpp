// CodeNebula - C++20 Example: std::ranges::contiguous_range Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_contiguous_range.cpp

#include <ranges>
#include <vector>
#include <array>
#include <string>
#include <deque>
#include <span>
#include <iostream>
#include <cstring>

// std::ranges::contiguous_range guarantees that elements are stored
// in contiguous memory, allowing pointer arithmetic and direct memory access.

// Safely copy raw bytes from a contiguous range
template <std::ranges::contiguous_range R>
    requires std::is_trivially_copyable_v<std::ranges::range_value_t<R>>
void raw_copy(const R& src, std::ranges::range_value_t<R>* dest) {
    auto* ptr = std::ranges::data(src);
    auto count = std::ranges::size(src);
    std::memcpy(dest, ptr, count * sizeof(std::ranges::range_value_t<R>));
}

// Process contiguous data with pointer arithmetic
template <std::ranges::contiguous_range R>
void print_with_addresses(const R& r) {
    const auto* base = std::ranges::data(r);
    for (std::size_t i = 0; i < std::ranges::size(r); ++i) {
        std::cout << "  offset " << i << ": " << base[i] << "\n";
    }
}

int main() {
    // Contiguous containers
    static_assert(std::ranges::contiguous_range<std::vector<int>>);
    static_assert(std::ranges::contiguous_range<std::array<int, 5>>);
    static_assert(std::ranges::contiguous_range<std::string>);
    static_assert(std::ranges::contiguous_range<std::span<int>>);
    static_assert(std::ranges::contiguous_range<int[5]>);

    // Deque is random access but NOT contiguous
    static_assert(!std::ranges::contiguous_range<std::deque<int>>);

    std::vector<int> vec = {10, 20, 30, 40, 50};
    std::cout << "Vector elements:\n";
    print_with_addresses(vec);

    // Raw copy demonstration
    int buffer[5];
    raw_copy(vec, buffer);
    std::cout << "Copied buffer: ";
    for (int v : buffer) std::cout << v << " ";
    std::cout << "\n";

    // std::span wraps contiguous memory
    std::span<int> sp(vec);
    std::cout << "Span data pointer == vector data: " << std::boolalpha
              << (std::ranges::data(sp) == std::ranges::data(vec)) << "\n";

    // String is contiguous
    std::string str = "Hello";
    std::cout << "String elements:\n";
    print_with_addresses(str);

    return 0;
}
