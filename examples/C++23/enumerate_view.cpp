// CodeNebula - C++23 Example: std::ranges::enumerate_view
// Compile: g++ -std=c++23 -Wall -Wextra -o example enumerate_view.cpp
// Note: Requires GCC 13+ / Clang 17+

// std::ranges::enumerate_view pairs each element with its zero-based index,
// similar to Python's enumerate(). Each element becomes a tuple of (index, value).
// The index type is the range's difference_type.

#include <iostream>
#include <ranges>
#include <vector>
#include <string>
#include <array>

int main() {
    // Basic enumeration of a vector
    std::vector<std::string> fruits = {"Apple", "Banana", "Cherry", "Date", "Elderberry"};

    std::cout << "=== Enumerate fruits ===" << std::endl;
    for (auto [idx, fruit] : std::views::enumerate(fruits)) {
        std::cout << "  [" << idx << "] " << fruit << std::endl;
    }

    // Enumerate with modification
    std::vector<int> scores = {85, 92, 78, 95, 88};
    std::cout << "\n=== Add bonus based on position ===" << std::endl;
    for (auto [idx, score] : std::views::enumerate(scores)) {
        score += static_cast<int>(idx);  // Position-based bonus
    }
    for (auto [idx, score] : std::views::enumerate(scores)) {
        std::cout << "  Student " << idx << ": " << score << std::endl;
    }

    // Enumerate combined with filter
    std::vector<int> data = {10, -5, 30, -2, 15, -8, 25};
    std::cout << "\n=== Positive values with original indices ===" << std::endl;
    for (auto [idx, val] : std::views::enumerate(data)) {
        if (val > 0) {
            std::cout << "  Index " << idx << ": " << val << std::endl;
        }
    }

    // Enumerate an array
    std::array<char, 5> vowels = {'a', 'e', 'i', 'o', 'u'};
    std::cout << "\n=== Enumerate vowels ===" << std::endl;
    for (auto [i, v] : std::views::enumerate(vowels)) {
        std::cout << "  Vowel #" << i + 1 << ": '" << v << "'" << std::endl;
    }

    // Find index of maximum element
    std::vector<double> temps = {20.5, 23.1, 19.8, 25.4, 22.0};
    double max_temp = temps[0];
    std::size_t max_idx = 0;
    for (auto [idx, temp] : std::views::enumerate(temps)) {
        if (temp > max_temp) {
            max_temp = temp;
            max_idx = static_cast<std::size_t>(idx);
        }
    }
    std::cout << "\n=== Maximum temperature ===" << std::endl;
    std::cout << "  Max: " << max_temp << " at index " << max_idx << std::endl;

    return 0;
}

// Expected output:
// === Enumerate fruits ===
//   [0] Apple
//   [1] Banana
//   [2] Cherry
//   [3] Date
//   [4] Elderberry
//
// === Add bonus based on position ===
//   Student 0: 85
//   Student 1: 93
//   Student 2: 80
//   Student 3: 98
//   Student 4: 92
//
// === Positive values with original indices ===
//   Index 0: 10
//   Index 2: 30
//   Index 4: 15
//   Index 6: 25
//
// === Enumerate vowels ===
//   Vowel #1: 'a'
//   Vowel #2: 'e'
//   Vowel #3: 'i'
//   Vowel #4: 'o'
//   Vowel #5: 'u'
//
// === Maximum temperature ===
//   Max: 25.4 at index 3
