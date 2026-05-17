// CodeNebula - C++20 Example: std::ranges::output_range Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_output_range.cpp

#include <ranges>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

// std::ranges::output_range<R, T> checks that a range's iterator
// can be used to write values of type T into the range.

// Fill an output range with a repeated value
template <typename T, std::ranges::output_range<T> R>
void fill_range(R&& r, const T& value) {
    for (auto it = std::ranges::begin(r); it != std::ranges::end(r); ++it) {
        *it = value;
    }
}

// Generate values into an output range using a function
template <typename R, typename Gen>
    requires std::ranges::output_range<R, std::invoke_result_t<Gen>>
void generate_into(R&& r, Gen gen) {
    for (auto it = std::ranges::begin(r); it != std::ranges::end(r); ++it) {
        *it = gen();
    }
}

int main() {
    // Vectors and lists are output ranges for their value type
    static_assert(std::ranges::output_range<std::vector<int>, int>);
    static_assert(std::ranges::output_range<std::list<double>, double>);

    // Fill a vector with a value
    std::vector<int> vec(5);
    fill_range(vec, 42);
    std::cout << "Filled vector: ";
    for (int v : vec) std::cout << v << " ";
    std::cout << "\n";

    // Generate sequential values
    std::vector<int> seq(8);
    int counter = 1;
    generate_into(seq, [&counter]() { return counter++; });
    std::cout << "Generated sequence: ";
    for (int v : seq) std::cout << v << " ";
    std::cout << "\n";

    // Using ranges::fill from the standard library
    std::list<std::string> words(4);
    std::ranges::fill(words, "hello");
    std::cout << "Filled list: ";
    for (const auto& w : words) std::cout << w << " ";
    std::cout << "\n";

    // A span is also an output range
    int arr[5] = {};
    auto sp = std::span(arr);
    static_assert(std::ranges::output_range<decltype(sp), int>);
    fill_range(sp, 99);
    std::cout << "Filled span: ";
    for (int v : arr) std::cout << v << " ";
    std::cout << "\n";

    return 0;
}
