// CodeNebula - C++23 Example: std::flat_multiset
// Compile: g++ -std=c++23 -Wall -Wextra -o example flat_multiset.cpp
// Note: Requires GCC 14+ / Clang 18+ / MSVC 19.37+

// std::flat_multiset is a sorted container adaptor (backed by a vector)
// that allows duplicate elements. Cache-friendly with contiguous storage.

#include <iostream>
#include <flat_set>
#include <string>
#include <vector>

int main() {
    std::cout << "=== std::flat_multiset ===" << std::endl;

    // Construction: duplicates are kept, elements are sorted
    std::flat_multiset<int> nums = {5, 3, 8, 1, 3, 7, 5, 2, 3};
    std::cout << "Elements (sorted, with duplicates): ";
    for (int n : nums) std::cout << n << " ";
    std::cout << std::endl;
    std::cout << "Size: " << nums.size() << std::endl;

    // Insert (always succeeds, returns iterator)
    nums.insert(3);
    nums.insert(10);
    std::cout << "\nAfter inserting 3 and 10: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << std::endl;

    // Count duplicates
    std::cout << "\n=== Counting ===" << std::endl;
    std::cout << "Count of 3: " << nums.count(3) << std::endl;
    std::cout << "Count of 5: " << nums.count(5) << std::endl;
    std::cout << "Count of 9: " << nums.count(9) << std::endl;

    // equal_range: find all occurrences
    std::cout << "\n=== equal_range for 3 ===" << std::endl;
    auto [lo, hi] = nums.equal_range(3);
    std::cout << "All 3s: ";
    for (auto it = lo; it != hi; ++it) std::cout << *it << " ";
    std::cout << "(count: " << std::distance(lo, hi) << ")" << std::endl;

    // Lower/upper bound
    std::cout << "\n=== Bounds ===" << std::endl;
    std::cout << "lower_bound(5) -> " << *nums.lower_bound(5) << std::endl;
    std::cout << "upper_bound(5) -> " << *nums.upper_bound(5) << std::endl;

    // Erase: remove all occurrences of a value
    auto removed = nums.erase(3);
    std::cout << "\nErased " << removed << " occurrences of 3" << std::endl;
    std::cout << "After erase: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << std::endl;

    // String multiset: word frequency tracking
    std::cout << "\n=== String flat_multiset ===" << std::endl;
    std::flat_multiset<std::string> words = {
        "the", "cat", "sat", "on", "the", "mat", "the"
    };
    std::cout << "Words: ";
    for (const auto& w : words) std::cout << w << " ";
    std::cout << std::endl;
    std::cout << "Occurrences of 'the': " << words.count("the") << std::endl;

    // Extract underlying container
    auto data = std::move(words).extract();
    std::cout << "Extracted vector size: " << data.size() << std::endl;

    return 0;
}

/*
Expected output:
=== std::flat_multiset ===
Elements (sorted, with duplicates): 1 2 3 3 3 5 5 7 8
Size: 9

After inserting 3 and 10: 1 2 3 3 3 3 5 5 7 8 10

=== Counting ===
Count of 3: 4
Count of 5: 2
Count of 9: 0

=== equal_range for 3 ===
All 3s: 3 3 3 3 (count: 4)

=== Bounds ===
lower_bound(5) -> 5
upper_bound(5) -> 7

Erased 4 occurrences of 3
After erase: 1 2 5 5 7 8 10

=== String flat_multiset ===
Words: cat mat on sat the the the
Occurrences of 'the': 3
Extracted vector size: 7
*/
