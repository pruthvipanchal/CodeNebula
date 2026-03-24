// CodeNebula - C++20 Example: std::ranges::sized_range Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_sized_range.cpp

#include <ranges>
#include <vector>
#include <list>
#include <forward_list>
#include <set>
#include <iostream>

// std::ranges::sized_range requires O(1) size via std::ranges::size().
// This means the range knows its element count without iterating.

// Reserve and copy - efficient only when we know the size upfront
template <std::ranges::sized_range R>
auto to_vector(R&& r) {
    using T = std::ranges::range_value_t<R>;
    std::vector<T> result;
    result.reserve(std::ranges::size(r));
    for (auto&& elem : r) {
        result.push_back(std::forward<decltype(elem)>(elem));
    }
    return result;
}

// Print range info including size
template <std::ranges::sized_range R>
void print_info(const R& r) {
    std::cout << "Size: " << std::ranges::size(r) << " | Elements: ";
    for (const auto& elem : r) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

int main() {
    // Most containers are sized ranges
    static_assert(std::ranges::sized_range<std::vector<int>>);
    static_assert(std::ranges::sized_range<std::list<int>>);
    static_assert(std::ranges::sized_range<std::set<int>>);
    static_assert(std::ranges::sized_range<int[5]>);

    // forward_list does NOT have O(1) size
    static_assert(!std::ranges::sized_range<std::forward_list<int>>);

    std::vector<int> vec = {10, 20, 30, 40, 50};
    print_info(vec);

    std::list<int> lst = {1, 2, 3};
    print_info(lst);

    // iota_view with bounds is sized
    auto iota = std::views::iota(1, 11);
    static_assert(std::ranges::sized_range<decltype(iota)>);
    std::cout << "iota size: " << std::ranges::size(iota) << "\n";

    // Convert a view to vector efficiently
    auto squares = iota | std::views::transform([](int x) { return x * x; });
    auto sq_vec = to_vector(squares);
    std::cout << "Squares: ";
    for (int v : sq_vec) std::cout << v << " ";
    std::cout << "\n";

    // take_view produces a sized_range from a sized source
    auto first3 = vec | std::views::take(3);
    static_assert(std::ranges::sized_range<decltype(first3)>);
    std::cout << "Take(3) size: " << std::ranges::size(first3) << "\n";

    return 0;
}
