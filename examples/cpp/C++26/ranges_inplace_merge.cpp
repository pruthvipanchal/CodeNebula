// CodeNebula - C++26 Example: ranges::inplace_merge Improvements
// Compile: g++ -std=c++26 -Wall -Wextra -o example ranges_inplace_merge.cpp
// Note: Requires C++26 compiler support

#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <string>

// C++26 improves std::ranges::inplace_merge with:
//   - Better constexpr support
//   - Enhanced projection support
//   - Improved performance guarantees for the in-place merge case
//
// inplace_merge merges two consecutive sorted subranges [first, mid) and
// [mid, last) into a single sorted range [first, last), all in-place.
// This is a key building block for merge sort and related algorithms.

template <typename T>
void print_vec(const std::string& label, const std::vector<T>& v) {
    std::cout << label << ": [";
    for (std::size_t i = 0; i < v.size(); ++i)
        std::cout << (i ? ", " : "") << v[i];
    std::cout << "]\n";
}

int main() {
    std::cout << "--- ranges::inplace_merge Demo ---\n\n";

    // Two sorted halves merged in-place
    std::vector<int> v1 = {1, 3, 5, 7,  2, 4, 6, 8};
    //                      ^sorted^     ^sorted^
    print_vec("Before merge", v1);
    std::ranges::inplace_merge(v1, v1.begin() + 4);
    print_vec("After merge ", v1);

    // Merge with custom comparator (descending)
    std::cout << "\n";
    std::vector<int> v2 = {8, 6, 4, 2,  7, 5, 3, 1};
    print_vec("Before desc merge", v2);
    std::ranges::inplace_merge(v2, v2.begin() + 4, std::greater{});
    print_vec("After desc merge ", v2);

    // Merge with projection: merge by absolute value
    std::cout << "\n";
    std::vector<int> v3 = {-1, 3, -5, 7,  -2, 4, -6, 8};
    // Sorted by abs:       1   3   5  7     2  4   6  8
    print_vec("Before abs merge", v3);
    std::ranges::inplace_merge(v3, v3.begin() + 4, std::less{},
                                [](int x) { return x < 0 ? -x : x; });
    print_vec("After abs merge ", v3);

    // Building a full merge sort using inplace_merge
    std::cout << "\n--- Merge sort using inplace_merge ---\n";
    std::vector<int> data = {9, 1, 5, 3, 7, 2, 8, 4, 6};
    print_vec("Unsorted", data);
    // Bottom-up merge sort
    for (std::size_t width = 1; width < data.size(); width *= 2) {
        for (std::size_t i = 0; i < data.size(); i += 2 * width) {
            auto mid = std::min(i + width, data.size());
            auto end = std::min(i + 2 * width, data.size());
            std::ranges::inplace_merge(
                data.begin() + i, data.begin() + mid, data.begin() + end);
        }
    }
    print_vec("Sorted  ", data);

    return 0;
}

// Expected output:
// --- ranges::inplace_merge Demo ---
//
// Before merge: [1, 3, 5, 7, 2, 4, 6, 8]
// After merge : [1, 2, 3, 4, 5, 6, 7, 8]
//
// Before desc merge: [8, 6, 4, 2, 7, 5, 3, 1]
// After desc merge : [8, 7, 6, 5, 4, 3, 2, 1]
//
// Before abs merge: [-1, 3, -5, 7, -2, 4, -6, 8]
// After abs merge : [-1, -2, 3, 4, -5, -6, 7, 8]
//
// --- Merge sort using inplace_merge ---
// Unsorted: [9, 1, 5, 3, 7, 2, 8, 4, 6]
// Sorted  : [1, 2, 3, 4, 5, 6, 7, 8, 9]
