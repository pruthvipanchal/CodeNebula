// CodeNebula - C++20 Example: std::ranges::single_view
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_single_view.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    // single_view contains exactly one element
    std::ranges::single_view<int> sv(42);

    std::cout << "Single view value: " << *sv.begin() << "\n";
    std::cout << "Size: " << std::ranges::size(sv) << "\n";
    std::cout << "Data: " << *sv.data() << "\n";

    // Using views::single
    auto single_str = std::views::single(std::string("hello"));
    std::cout << "\nSingle string: " << *single_str.begin() << "\n";

    // Iteration over single_view
    std::cout << "Iterating: ";
    for (int n : std::views::single(99))
        std::cout << n << " ";
    std::cout << "\n";

    // single_view satisfies range concepts
    static_assert(std::ranges::range<std::ranges::single_view<int>>);
    static_assert(std::ranges::sized_range<std::ranges::single_view<int>>);
    static_assert(std::ranges::contiguous_range<std::ranges::single_view<int>>);
    std::cout << "\nSatisfies range: true\n";
    std::cout << "Satisfies contiguous_range: true\n";

    // Using single_view in algorithms
    auto sv2 = std::views::single(7);
    auto it = std::ranges::find(sv2, 7);
    std::cout << "\nFound 7: " << std::boolalpha << (it != sv2.end()) << "\n";

    it = std::ranges::find(sv2, 5);
    std::cout << "Found 5: " << (it != sv2.end()) << "\n";

    // Useful for providing a default single-element range
    auto make_range = [](bool use_single) {
        static std::vector<int> data = {10, 20, 30};
        if (use_single)
            return std::ranges::subrange(data.begin(), data.begin() + 1);
        return std::ranges::subrange(data.begin(), data.end());
    };

    std::cout << "\nSingle mode: ";
    for (int n : make_range(true)) std::cout << n << " ";
    std::cout << "\nFull mode: ";
    for (int n : make_range(false)) std::cout << n << " ";
    std::cout << "\n";

    // Combine with other views
    std::cout << "\nSingle + transform: ";
    for (int n : std::views::single(5)
                 | std::views::transform([](int x) { return x * x; }))
        std::cout << n << " ";
    std::cout << "\n";

    return 0;
}
