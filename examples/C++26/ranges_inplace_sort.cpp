// CodeNebula - C++26 Example: ranges::inplace_sort (Proposed)
// Compile: g++ -std=c++26 -Wall -Wextra -o example ranges_inplace_sort.cpp
// Note: Requires C++26 compiler support

#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <string>

// C++26 proposes improved in-place sorting with ranges::inplace_sort.
// While std::ranges::sort already sorts in-place, the proposed enhancement
// adds explicit guarantees about no additional memory allocation and
// improved integration with projection and constrained ranges.
//
// Key improvements:
//   - No temporary buffer allocation (pure in-place guarantee)
//   - Better integration with range adaptors and projections
//   - Clearer naming to distinguish from out-of-place algorithms

// --- Demonstration using std::ranges::sort (available today) with
//     educational notes about C++26 improvements ---

template <typename T>
void print_vec(const std::string& label, const std::vector<T>& v) {
    std::cout << label << ": [";
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (i) std::cout << ", ";
        std::cout << v[i];
    }
    std::cout << "]\n";
}

int main() {
    std::cout << "--- ranges::inplace_sort Demo ---\n\n";

    // Basic in-place sort
    std::vector<int> nums = {5, 3, 8, 1, 9, 2, 7};
    print_vec("Before sort      ", nums);
    std::ranges::sort(nums);  // C++26: ranges::inplace_sort(nums)
    print_vec("After sort       ", nums);

    // Sort with custom comparator (descending)
    std::vector<int> desc = {5, 3, 8, 1, 9, 2, 7};
    std::ranges::sort(desc, std::greater{});
    print_vec("Descending sort  ", desc);

    // Sort with projection: sort strings by length
    std::vector<std::string> words = {"banana", "fig", "apple", "kiwi", "elderberry"};
    std::cout << "\nBefore sort by length: [";
    for (std::size_t i = 0; i < words.size(); ++i)
        std::cout << (i?", ":"") << words[i];
    std::cout << "]\n";

    std::ranges::sort(words, {}, &std::string::size);  // projection: sort by size
    std::cout << "After sort by length:  [";
    for (std::size_t i = 0; i < words.size(); ++i)
        std::cout << (i?", ":"") << words[i];
    std::cout << "]\n";

    // Sort a subrange
    std::vector<int> partial = {9, 7, 5, 3, 1, 2, 4, 6, 8};
    print_vec("\nBefore partial sort", partial);
    std::ranges::sort(partial.begin() + 2, partial.begin() + 7);
    print_vec("Sort indices [2,7)", partial);

    std::cout << "\nNote: C++26 ranges::inplace_sort guarantees zero allocations.\n";
    return 0;
}

// Expected output:
// --- ranges::inplace_sort Demo ---
//
// Before sort      : [5, 3, 8, 1, 9, 2, 7]
// After sort       : [1, 2, 3, 5, 7, 8, 9]
// Descending sort  : [9, 8, 7, 5, 3, 2, 1]
//
// Before sort by length: [banana, fig, apple, kiwi, elderberry]
// After sort by length:  [fig, kiwi, apple, banana, elderberry]
//
// Before partial sort: [9, 7, 5, 3, 1, 2, 4, 6, 8]
// Sort indices [2,7): [9, 7, 1, 2, 3, 4, 5, 6, 8]
//
// Note: C++26 ranges::inplace_sort guarantees zero allocations.
