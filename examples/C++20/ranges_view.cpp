// CodeNebula - C++20 Example: std::ranges::view Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_view.cpp

#include <ranges>
#include <vector>
#include <string>
#include <iostream>

// std::ranges::view is a concept for lightweight, non-owning range
// adaptors. Views are cheap to copy/move and provide lazy evaluation.
// A view must be default-constructible, movable, and O(1) to copy.

int main() {
    // Views are ranges that are cheap to copy
    static_assert(std::ranges::view<std::ranges::empty_view<int>>);
    static_assert(std::ranges::view<std::ranges::single_view<int>>);

    // Containers are NOT views (they own their elements)
    static_assert(!std::ranges::view<std::vector<int>>);
    static_assert(!std::ranges::view<std::string>);

    // Creating views
    auto empty = std::views::empty<int>;
    static_assert(std::ranges::view<decltype(empty)>);
    std::cout << "Empty view size: 0\n";

    auto single = std::views::single(42);
    static_assert(std::ranges::view<decltype(single)>);
    std::cout << "Single view: " << *single.begin() << "\n";

    auto iota = std::views::iota(1, 6);
    static_assert(std::ranges::view<decltype(iota)>);
    std::cout << "Iota view: ";
    for (int n : iota) std::cout << n << " ";
    std::cout << "\n";

    // Composing views - all results are views
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto pipeline = data
        | std::views::filter([](int x) { return x % 2 == 0; })
        | std::views::transform([](int x) { return x * x; });

    static_assert(std::ranges::view<decltype(pipeline)>);
    std::cout << "Pipeline (even squares): ";
    for (int n : pipeline) std::cout << n << " ";
    std::cout << "\n";

    // Views are lazy - nothing computed until iterated
    auto large = std::views::iota(0)
        | std::views::filter([](int x) { return x % 7 == 0; })
        | std::views::take(5);
    std::cout << "First 5 multiples of 7: ";
    for (int n : large) std::cout << n << " ";
    std::cout << "\n";
    return 0;
}
