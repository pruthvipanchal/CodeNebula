// CodeNebula - C++20 Example: std::ranges::range Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_range.cpp

#include <ranges>
#include <vector>
#include <list>
#include <string>
#include <array>
#include <iostream>

// The std::ranges::range concept checks whether a type provides
// begin() and end() iterators, making it iterable.

// Function constrained to accept only range types
template <std::ranges::range R>
void print_range(const R& r) {
    for (const auto& elem : r) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

// Custom type that satisfies ranges::range
struct Countdown {
    int start;
    auto begin() const { return std::views::iota(0, start).begin(); }
    auto end() const { return std::views::iota(0, start).end(); }
};

int main() {
    // Standard containers satisfy ranges::range
    static_assert(std::ranges::range<std::vector<int>>);
    static_assert(std::ranges::range<std::list<double>>);
    static_assert(std::ranges::range<std::string>);
    static_assert(std::ranges::range<std::array<int, 5>>);
    static_assert(std::ranges::range<int[10]>);

    // Non-range types
    static_assert(!std::ranges::range<int>);
    static_assert(!std::ranges::range<double>);

    std::vector<int> vec = {10, 20, 30, 40, 50};
    std::string text = "hello";
    int arr[] = {1, 2, 3, 4};

    std::cout << "Vector: ";
    print_range(vec);

    std::cout << "String: ";
    print_range(text);

    std::cout << "C-array: ";
    print_range(arr);

    // Views are also ranges
    auto evens = vec | std::views::filter([](int x) { return x % 20 == 0; });
    static_assert(std::ranges::range<decltype(evens)>);
    std::cout << "Filtered: ";
    print_range(evens);

    // Custom range type
    Countdown cd{5};
    std::cout << "Countdown: ";
    print_range(cd);

    return 0;
}
