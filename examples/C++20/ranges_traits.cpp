// CodeNebula - C++20 Example: Range Traits (range_value_t, range_reference_t, etc.)
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_traits.cpp

#include <ranges>
#include <vector>
#include <string>
#include <type_traits>
#include <iostream>

// Range traits extract type information from ranges:
// range_value_t, range_reference_t, range_difference_t, range_size_t, etc.

// Generic function using range traits
template <std::ranges::input_range R>
void describe_range(const R& r) {
    using value_t = std::ranges::range_value_t<R>;
    using ref_t = std::ranges::range_reference_t<R>;
    using diff_t = std::ranges::range_difference_t<R>;

    std::cout << "  value_type is integral: " << std::is_integral_v<value_t> << "\n";
    std::cout << "  reference is lvalue ref: " << std::is_lvalue_reference_v<ref_t> << "\n";
    std::cout << "  difference_type is signed: " << std::is_signed_v<diff_t> << "\n";

    // Use the traits to create a matching accumulator
    value_t sum{};
    for (const auto& elem : r) {
        sum = sum + elem;
    }
    std::cout << "  sum: " << sum << "\n";
}

// Return a new vector with elements doubled, using range_value_t
template <std::ranges::input_range R>
auto doubled(const R& r) {
    using T = std::ranges::range_value_t<R>;
    std::vector<T> result;
    for (const auto& elem : r) {
        result.push_back(elem + elem);
    }
    return result;
}

int main() {
    // Verify traits for vector<int>
    static_assert(std::same_as<std::ranges::range_value_t<std::vector<int>>, int>);
    static_assert(std::same_as<std::ranges::range_reference_t<std::vector<int>>, int&>);

    // Verify traits for string
    static_assert(std::same_as<std::ranges::range_value_t<std::string>, char>);

    std::vector<int> ints = {1, 2, 3, 4, 5};
    std::cout << "vector<int>:\n";
    describe_range(ints);

    std::vector<double> dbls = {1.5, 2.5, 3.5};
    std::cout << "vector<double>:\n";
    describe_range(dbls);

    // doubled() uses range_value_t to deduce return element type
    auto d = doubled(ints);
    std::cout << "Doubled ints: ";
    for (int v : d) std::cout << v << " ";
    std::cout << "\n";

    // Traits work with views too
    auto view = ints | std::views::transform([](int x) { return x * 0.5; });
    static_assert(std::same_as<std::ranges::range_value_t<decltype(view)>, double>);
    std::cout << "Transform view value_type is double: true\n";
    return 0;
}
