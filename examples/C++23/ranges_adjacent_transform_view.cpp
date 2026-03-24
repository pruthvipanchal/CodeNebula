// CodeNebula - C++23 Example: std::ranges::adjacent_transform_view
// Compile: g++ -std=c++23 -Wall -Wextra -o example ranges_adjacent_transform_view.cpp
// Note: Requires GCC 13+ / Clang 17+

// std::ranges::adjacent_transform_view<N> applies a function to each group of
// N adjacent elements. It combines adjacent_view with transform_view.
// views::pairwise_transform is an alias for adjacent_transform<2>.

#include <iostream>
#include <ranges>
#include <vector>
#include <cmath>

int main() {
    std::vector<int> nums = {1, 4, 9, 16, 25, 36};

    // Compute differences between consecutive elements
    std::cout << "=== Consecutive differences ===" << std::endl;
    auto diffs = std::views::adjacent_transform<2>(nums, [](int a, int b) {
        return b - a;
    });
    for (auto d : diffs) {
        std::cout << "  " << d;
    }
    std::cout << std::endl;

    // Compute running averages of pairs
    std::vector<double> temps = {20.5, 22.1, 19.8, 23.4, 21.0};
    std::cout << "\n=== Pairwise averages ===" << std::endl;
    auto avgs = std::views::adjacent_transform<2>(temps, [](double a, double b) {
        return (a + b) / 2.0;
    });
    for (auto avg : avgs) {
        std::cout << "  " << avg << std::endl;
    }

    // Three-element moving average
    std::cout << "\n=== 3-element moving average ===" << std::endl;
    auto moving_avg = std::views::adjacent_transform<3>(temps,
        [](double a, double b, double c) { return (a + b + c) / 3.0; }
    );
    for (auto avg : moving_avg) {
        std::cout << "  " << avg << std::endl;
    }

    // Detect local maxima using triple adjacency
    std::vector<int> signal = {1, 3, 2, 5, 4, 6, 1};
    std::cout << "\n=== Local maxima detection ===" << std::endl;
    auto is_peak = std::views::adjacent_transform<3>(signal,
        [](int left, int mid, int right) { return mid > left && mid > right; }
    );
    int idx = 1;
    for (auto peak : is_peak) {
        if (peak) std::cout << "  Peak at index " << idx << std::endl;
        ++idx;
    }

    // Euclidean distances between consecutive 1D points
    std::vector<double> points = {0.0, 3.0, 7.0, 8.0, 15.0};
    std::cout << "\n=== Distances between consecutive points ===" << std::endl;
    auto distances = std::views::adjacent_transform<2>(points,
        [](double a, double b) { return std::abs(b - a); }
    );
    for (auto d : distances) {
        std::cout << "  " << d << std::endl;
    }

    return 0;
}

// Expected output:
// === Consecutive differences ===
//   3  5  7  9  11
//
// === Pairwise averages ===
//   21.3
//   20.95
//   21.6
//   22.2
//
// === 3-element moving average ===
//   20.8
//   21.7667
//   21.4
//
// === Local maxima detection ===
//   Peak at index 1
//   Peak at index 3
//   Peak at index 5
//
// === Distances between consecutive points ===
//   3
//   4
//   1
//   7
