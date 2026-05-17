// CodeNebula - C++23 Example: std::flat_set
// Compile: g++ -std=c++23 -Wall -Wextra -o example flat_set.cpp
// Note: Requires GCC 14+ / Clang 18+ / MSVC 19.37+

// std::flat_set is a sorted associative container adaptor backed by a
// contiguous container (vector by default). It has O(log n) lookup and
// cache-friendly iteration, but O(n) insertion (due to shifting elements).

#include <iostream>
#include <flat_set>
#include <string>
#include <vector>

int main() {
    std::cout << "=== std::flat_set ===" << std::endl;

    // Construction: duplicates are removed, elements are sorted
    std::flat_set<int> nums = {5, 3, 8, 1, 3, 7, 5, 2};
    std::cout << "Elements (sorted, unique): ";
    for (int n : nums) std::cout << n << " ";
    std::cout << std::endl;
    std::cout << "Size: " << nums.size() << std::endl;

    // Insert
    auto [it1, inserted1] = nums.insert(4);
    auto [it2, inserted2] = nums.insert(3);  // duplicate
    std::cout << "\nInsert 4: " << (inserted1 ? "success" : "duplicate") << std::endl;
    std::cout << "Insert 3: " << (inserted2 ? "success" : "duplicate") << std::endl;

    // Lookup operations
    std::cout << "\n=== Lookup ===" << std::endl;
    std::cout << "Contains 7: " << nums.contains(7) << std::endl;
    std::cout << "Contains 9: " << nums.contains(9) << std::endl;
    std::cout << "Count of 5: " << nums.count(5) << std::endl;

    // Lower/upper bound
    auto lb = nums.lower_bound(4);
    auto ub = nums.upper_bound(4);
    std::cout << "lower_bound(4) -> " << *lb << std::endl;
    std::cout << "upper_bound(4) -> " << *ub << std::endl;

    // Erase
    nums.erase(3);
    std::cout << "\nAfter erasing 3: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << std::endl;

    // String flat_set
    std::cout << "\n=== String flat_set ===" << std::endl;
    std::flat_set<std::string> words = {"banana", "apple", "cherry", "apple", "date"};
    for (const auto& w : words) std::cout << "  " << w << std::endl;

    // Construct from sorted_unique (skip sorting, assert uniqueness)
    std::cout << "\n=== From sorted_unique vector ===" << std::endl;
    std::vector<int> sorted_data = {10, 20, 30, 40, 50};
    std::flat_set<int> fast_set(std::sorted_unique, std::move(sorted_data));
    std::cout << "Fast set: ";
    for (int n : fast_set) std::cout << n << " ";
    std::cout << std::endl;

    // Extract underlying container
    auto extracted = std::move(fast_set).extract();
    std::cout << "Extracted container size: " << extracted.size() << std::endl;

    return 0;
}

/*
Expected output:
=== std::flat_set ===
Elements (sorted, unique): 1 2 3 5 7 8
Size: 6

Insert 4: success
Insert 3: duplicate

=== Lookup ===
Contains 7: 1
Contains 9: 0
Count of 5: 1
lower_bound(4) -> 4
upper_bound(4) -> 5

After erasing 3: 1 2 4 5 7 8

=== String flat_set ===
  apple
  banana
  cherry
  date

=== From sorted_unique vector ===
Fast set: 10 20 30 40 50
Extracted container size: 5
*/
