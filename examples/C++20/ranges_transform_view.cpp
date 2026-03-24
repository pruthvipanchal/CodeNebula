// CodeNebula - C++20 Example: std::ranges::transform_view
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_transform_view.cpp

#include <ranges>
#include <vector>
#include <string>
#include <cmath>
#include <iostream>

// std::ranges::transform_view / std::views::transform applies a
// function to each element lazily, producing a new view of results.

struct Point {
    double x, y;
};

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Simple transformation: square each element
    auto squares = numbers | std::views::transform([](int n) { return n * n; });
    std::cout << "Squares: ";
    for (int n : squares) std::cout << n << " ";
    std::cout << "\n";

    // Transform to a different type
    auto as_strings = numbers | std::views::transform([](int n) {
        return "val:" + std::to_string(n);
    });
    std::cout << "As strings: ";
    for (const auto& s : as_strings) std::cout << s << " ";
    std::cout << "\n";

    // Transform struct members
    std::vector<Point> points = {{1, 2}, {3, 4}, {5, 12}, {8, 15}};
    auto distances = points | std::views::transform([](const Point& p) {
        return std::sqrt(p.x * p.x + p.y * p.y);
    });
    std::cout << "Distances: ";
    for (double d : distances) std::cout << d << " ";
    std::cout << "\n";

    // Chain transforms
    auto pipeline = numbers
        | std::views::transform([](int n) { return n * 2; })
        | std::views::transform([](int n) { return n + 1; });
    std::cout << "2n+1: ";
    for (int n : pipeline) std::cout << n << " ";
    std::cout << "\n";

    // Transform preserves range category
    static_assert(std::ranges::random_access_range<decltype(squares)>);
    std::cout << "squares[2]: " << squares[2] << "\n";
    std::cout << "squares size: " << std::ranges::size(squares) << "\n";

    // Combine with filter
    auto even_cubes = numbers
        | std::views::filter([](int n) { return n % 2 == 0; })
        | std::views::transform([](int n) { return n * n * n; });
    std::cout << "Even cubes: ";
    for (int n : even_cubes) std::cout << n << " ";
    std::cout << "\n";

    // Transform preserves sized_range
    std::cout << "squares size: " << std::ranges::size(squares) << "\n";
    return 0;
}
