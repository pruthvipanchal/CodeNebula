// CodeNebula - C++26 Example: ranges::inplace_transform (Proposed)
// Compile: g++ -std=c++26 -Wall -Wextra -o example ranges_inplace_transform.cpp
// Note: Requires C++26 compiler support

#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

// C++26 proposes ranges::inplace_transform — a convenience algorithm that
// transforms elements of a range in-place without needing an output iterator.
//
// Current C++23 approach:
//   std::ranges::transform(vec, vec.begin(), func);  // output = input range
//
// Proposed C++26:
//   std::ranges::inplace_transform(vec, func);  // cleaner, intent is clear
//
// This avoids the redundant output iterator and makes the in-place intent
// explicit at the call site.

// --- Simulation of ranges::inplace_transform ---
namespace ranges_sim {
    // inplace_transform: applies f to each element, writing back in-place
    template <std::ranges::forward_range R, typename F>
    void inplace_transform(R&& range, F func) {
        for (auto& elem : range) {
            elem = func(std::move(elem));
        }
    }
}

void print_vec(const std::string& label, const std::vector<int>& v) {
    std::cout << label << ": [";
    for (std::size_t i = 0; i < v.size(); ++i)
        std::cout << (i ? ", " : "") << v[i];
    std::cout << "]\n";
}

int main() {
    std::cout << "--- ranges::inplace_transform Demo ---\n\n";

    // Double each element in-place
    std::vector<int> nums = {1, 2, 3, 4, 5};
    print_vec("Before doubling", nums);
    ranges_sim::inplace_transform(nums, [](int x) { return x * 2; });
    print_vec("After doubling ", nums);

    // Square each element in-place
    std::vector<int> squares = {1, 2, 3, 4, 5};
    print_vec("\nBefore squaring", squares);
    ranges_sim::inplace_transform(squares, [](int x) { return x * x; });
    print_vec("After squaring ", squares);

    // Clamp values in-place
    std::vector<int> vals = {-5, 3, 15, 7, -2, 20};
    print_vec("\nBefore clamping", vals);
    ranges_sim::inplace_transform(vals, [](int x) {
        return std::max(0, std::min(10, x));  // clamp to [0, 10]
    });
    print_vec("After clamping ", vals);

    // Compare with C++23 approach (works today)
    std::cout << "\nC++23 equivalent: ranges::transform(vec, vec.begin(), f)\n";
    std::cout << "C++26 proposed:   ranges::inplace_transform(vec, f)\n";

    return 0;
}

// Expected output:
// --- ranges::inplace_transform Demo ---
//
// Before doubling: [1, 2, 3, 4, 5]
// After doubling : [2, 4, 6, 8, 10]
//
// Before squaring: [1, 2, 3, 4, 5]
// After squaring : [1, 4, 9, 16, 25]
//
// Before clamping: [-5, 3, 15, 7, -2, 20]
// After clamping : [0, 3, 10, 7, 0, 10]
//
// C++23 equivalent: ranges::transform(vec, vec.begin(), f)
// C++26 proposed:   ranges::inplace_transform(vec, f)
