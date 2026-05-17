// CodeNebula - C++20 Example: std::ranges::input_range Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_input_range.cpp

#include <ranges>
#include <vector>
#include <list>
#include <sstream>
#include <iterator>
#include <iostream>

// std::ranges::input_range requires that iterators support at least
// single-pass reading (input iterator category).

// Accept any input range and compute its sum
template <std::ranges::input_range R>
    requires std::integral<std::ranges::range_value_t<R>>
auto sum_range(R&& r) {
    long long total = 0;
    for (auto&& val : r) {
        total += val;
    }
    return total;
}

// Count elements in any input range
template <std::ranges::input_range R>
std::size_t count_elements(R&& r) {
    std::size_t count = 0;
    for ([[maybe_unused]] auto&& val : r) {
        ++count;
    }
    return count;
}

int main() {
    // All standard containers model input_range
    static_assert(std::ranges::input_range<std::vector<int>>);
    static_assert(std::ranges::input_range<std::list<int>>);

    // istream_view is a classic single-pass input range
    std::istringstream iss("10 20 30 40 50");
    auto stream_range = std::ranges::istream_view<int>(iss);
    static_assert(std::ranges::input_range<decltype(stream_range)>);

    std::cout << "Stream values: ";
    for (int val : stream_range) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    // Using sum_range with a vector
    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::cout << "Sum of vector: " << sum_range(nums) << "\n";

    // Using with a view pipeline
    auto squares = nums | std::views::transform([](int x) { return x * x; });
    static_assert(std::ranges::input_range<decltype(squares)>);
    std::cout << "Sum of squares: " << sum_range(squares) << "\n";

    // Using count_elements with a filtered range
    auto evens = nums | std::views::filter([](int x) { return x % 2 == 0; });
    std::cout << "Even count: " << count_elements(evens) << "\n";

    return 0;
}
