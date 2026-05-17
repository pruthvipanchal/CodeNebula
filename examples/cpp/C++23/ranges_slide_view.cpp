// CodeNebula - C++23 Example: std::ranges::slide_view
// Compile: g++ -std=c++23 -Wall -Wextra -o example ranges_slide_view.cpp
// Note: Requires GCC 13+ / Clang 17+

// std::ranges::slide_view produces a view of overlapping subranges (windows)
// of a given size. Each window is a subrange. Unlike adjacent_view, the window
// size is a runtime parameter and elements are accessed as subranges, not tuples.

#include <iostream>
#include <ranges>
#include <vector>
#include <numeric>

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7};

    // Sliding window of size 3
    std::cout << "=== Sliding window of size 3 ===" << std::endl;
    for (auto window : data | std::views::slide(3)) {
        std::cout << "  [";
        bool first = true;
        for (auto val : window) {
            if (!first) std::cout << ", ";
            std::cout << val;
            first = false;
        }
        std::cout << "]" << std::endl;
    }

    // Moving average with slide
    std::vector<double> prices = {100.0, 102.5, 98.0, 105.0, 110.0, 107.5, 112.0};
    std::cout << "\n=== 3-day moving average ===" << std::endl;
    for (auto window : prices | std::views::slide(3)) {
        double sum = 0.0;
        int count = 0;
        for (auto val : window) { sum += val; ++count; }
        std::cout << "  Average: " << sum / count << std::endl;
    }

    // Sliding window of size 2 for differences
    std::cout << "\n=== Consecutive differences ===" << std::endl;
    for (auto window : data | std::views::slide(2)) {
        auto it = window.begin();
        int first_val = *it++;
        int second_val = *it;
        std::cout << "  " << second_val << " - " << first_val
                  << " = " << second_val - first_val << std::endl;
    }

    // Detect pattern: three consecutive increasing values
    std::vector<int> seq = {5, 3, 4, 6, 2, 3, 5, 7};
    std::cout << "\n=== Windows with 3 consecutive increases ===" << std::endl;
    int pos = 0;
    for (auto window : seq | std::views::slide(3)) {
        auto it = window.begin();
        int a = *it++, b = *it++, c = *it;
        if (a < b && b < c) {
            std::cout << "  At index " << pos << ": [" << a << ", "
                      << b << ", " << c << "]" << std::endl;
        }
        ++pos;
    }

    return 0;
}

// Expected output:
// === Sliding window of size 3 ===
//   [1, 2, 3]
//   [2, 3, 4]
//   [3, 4, 5]
//   [4, 5, 6]
//   [5, 6, 7]
//
// === 3-day moving average ===
//   Average: 100.167
//   Average: 101.833
//   Average: 104.333
//   Average: 107.5
//   Average: 109.833
//
// === Consecutive differences ===
//   2 - 1 = 1
//   3 - 2 = 1
//   4 - 3 = 1
//   5 - 4 = 1
//   6 - 5 = 1
//   7 - 6 = 1
//
// === Windows with 3 consecutive increases ===
//   At index 1: [3, 4, 6]
//   At index 4: [2, 3, 5]
//   At index 5: [3, 5, 7]
