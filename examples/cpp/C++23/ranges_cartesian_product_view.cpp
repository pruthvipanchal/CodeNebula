// CodeNebula - C++23 Example: std::ranges::cartesian_product_view
// Compile: g++ -std=c++23 -Wall -Wextra -o example ranges_cartesian_product_view.cpp
// Note: Requires GCC 13+ / Clang 17+

// std::ranges::cartesian_product_view produces the Cartesian product of
// multiple ranges. Each element is a tuple of one element from each input
// range. The last range varies fastest (like nested loops).

#include <iostream>
#include <ranges>
#include <vector>
#include <string>
#include <array>

int main() {
    // Basic Cartesian product of two ranges
    std::vector<int> rows = {1, 2, 3};
    std::vector<char> cols = {'A', 'B'};

    std::cout << "=== Grid coordinates (rows x cols) ===" << std::endl;
    for (auto [r, c] : std::views::cartesian_product(rows, cols)) {
        std::cout << "  (" << r << ", " << c << ")" << std::endl;
    }

    // Three-way product: clothing combinations
    std::array<std::string, 2> sizes = {"S", "L"};
    std::array<std::string, 3> colors = {"Red", "Blue", "Green"};
    std::array<std::string, 2> styles = {"V-Neck", "Crew"};

    std::cout << "\n=== Clothing combinations ===" << std::endl;
    int count = 0;
    for (auto [sz, col, st] : std::views::cartesian_product(sizes, colors, styles)) {
        std::cout << "  " << sz << " " << col << " " << st << std::endl;
        ++count;
    }
    std::cout << "  Total combinations: " << count << std::endl;

    // Practical: generate (x, y) pixel grid
    auto xs = std::views::iota(0, 3);
    auto ys = std::views::iota(0, 3);
    std::cout << "\n=== 3x3 pixel grid ===" << std::endl;
    for (auto [x, y] : std::views::cartesian_product(xs, ys)) {
        std::cout << "  pixel(" << x << "," << y << ")";
        if (y == 2) std::cout << std::endl;
    }

    // Dice roll combinations (2 dice, values 1-3 for brevity)
    auto die = std::views::iota(1, 4);
    std::cout << "\n=== Two-dice sums (1-3) ===" << std::endl;
    for (auto [d1, d2] : std::views::cartesian_product(die, die)) {
        std::cout << "  " << d1 << "+" << d2 << "=" << d1 + d2 << std::endl;
    }

    return 0;
}

// Expected output:
// === Grid coordinates (rows x cols) ===
//   (1, A)
//   (1, B)
//   (2, A)
//   (2, B)
//   (3, A)
//   (3, B)
//
// === Clothing combinations ===
//   S Red V-Neck
//   S Red Crew
//   S Blue V-Neck
//   S Blue Crew
//   S Green V-Neck
//   S Green Crew
//   L Red V-Neck
//   L Red Crew
//   L Blue V-Neck
//   L Blue Crew
//   L Green V-Neck
//   L Green Crew
//   Total combinations: 12
//
// === 3x3 pixel grid ===
//   pixel(0,0)  pixel(0,1)  pixel(0,2)
//   pixel(1,0)  pixel(1,1)  pixel(1,2)
//   pixel(2,0)  pixel(2,1)  pixel(2,2)
//
// === Two-dice sums (1-3) ===
//   1+1=2
//   1+2=3
//   1+3=4
//   2+1=3
//   2+2=4
//   2+3=5
//   3+1=4
//   3+2=5
//   3+3=6
