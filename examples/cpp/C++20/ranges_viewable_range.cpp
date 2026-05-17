// CodeNebula - C++20 Example: std::ranges::viewable_range Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_viewable_range.cpp

#include <ranges>
#include <vector>
#include <string>
#include <iostream>

// std::ranges::viewable_range is a range that can be converted to a view
// using std::views::all(). Includes views and lvalue container references.

// Accept any viewable_range and adapt it to a view
template <std::ranges::viewable_range R>
auto make_view(R&& r) {
    return std::views::all(std::forward<R>(r));
}

// Process pipeline - requires viewable_range input
template <std::ranges::viewable_range R>
void process_and_print(R&& r) {
    auto view = std::views::all(std::forward<R>(r))
        | std::views::transform([](auto x) { return x * 2; });
    std::cout << "Doubled: ";
    for (auto v : view) std::cout << v << " ";
    std::cout << "\n";
}

int main() {
    // Lvalue containers are viewable (converted via ref_view)
    std::vector<int> vec = {1, 2, 3, 4, 5};
    static_assert(std::ranges::viewable_range<decltype(vec)&>);

    // Views themselves are viewable
    auto iota = std::views::iota(1, 6);
    static_assert(std::ranges::viewable_range<decltype(iota)>);

    // Create views from different sources
    auto v1 = make_view(vec);
    std::cout << "From vector: ";
    for (int n : v1) std::cout << n << " ";
    std::cout << "\n";

    auto v2 = make_view(std::views::iota(10, 15));
    std::cout << "From iota: ";
    for (int n : v2) std::cout << n << " ";
    std::cout << "\n";

    // Process with pipeline
    process_and_print(vec);

    // Rvalue containers are viewable (converted via owning_view)
    auto v3 = make_view(std::vector{10, 20, 30});
    std::cout << "From rvalue vector: ";
    for (int n : v3) std::cout << n << " ";
    std::cout << "\n";

    // Pipe operator requires viewable_range
    auto filtered = vec | std::views::filter([](int x) { return x > 2; });
    std::cout << "Filtered: ";
    for (int n : filtered) std::cout << n << " ";
    std::cout << "\n";

    // String is viewable as lvalue
    std::string text = "Hello";
    auto chars = make_view(text);
    std::cout << "Chars: ";
    for (char c : chars) std::cout << c << " ";
    std::cout << "\n";
    return 0;
}
