// CodeNebula - C++11 Example: std::is_sorted Check
// Compile: g++ -std=c++11 -Wall -Wextra -o example is_sorted.cpp

// std::is_sorted checks whether a range is sorted in non-decreasing order
// (or according to a custom comparator). It returns true for empty ranges
// and single-element ranges.

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main() {
    // Check ascending order
    std::vector<int> sorted_asc = {1, 2, 3, 4, 5};
    std::cout << "Ascending {1,2,3,4,5}: " << std::boolalpha
              << std::is_sorted(sorted_asc.begin(), sorted_asc.end()) << std::endl;

    // Unsorted vector
    std::vector<int> unsorted = {3, 1, 4, 1, 5};
    std::cout << "Unsorted {3,1,4,1,5}: "
              << std::is_sorted(unsorted.begin(), unsorted.end()) << std::endl;

    // Equal elements are considered sorted
    std::vector<int> equal = {5, 5, 5, 5};
    std::cout << "Equal {5,5,5,5}: "
              << std::is_sorted(equal.begin(), equal.end()) << std::endl;

    // Descending order with custom comparator
    std::vector<int> sorted_desc = {5, 4, 3, 2, 1};
    std::cout << "Descending with greater<>: "
              << std::is_sorted(sorted_desc.begin(), sorted_desc.end(),
                                std::greater<int>()) << std::endl;

    // Check strings (lexicographic order)
    std::vector<std::string> words = {"apple", "banana", "cherry"};
    std::cout << "Strings sorted: "
              << std::is_sorted(words.begin(), words.end()) << std::endl;

    // Sort by string length
    std::vector<std::string> by_len = {"hi", "hey", "hello", "greetings"};
    std::cout << "Sorted by length: "
              << std::is_sorted(by_len.begin(), by_len.end(),
                                [](const std::string& a, const std::string& b) {
                                    return a.size() < b.size();
                                }) << std::endl;

    // Empty and single-element ranges
    std::vector<int> empty;
    std::vector<int> single = {42};
    std::cout << "Empty range: "
              << std::is_sorted(empty.begin(), empty.end()) << std::endl;
    std::cout << "Single element: "
              << std::is_sorted(single.begin(), single.end()) << std::endl;

    return 0;
}

// Expected output:
// Ascending {1,2,3,4,5}: true
// Unsorted {3,1,4,1,5}: false
// Equal {5,5,5,5}: true
// Descending with greater<>: true
// Strings sorted: true
// Sorted by length: true
// Empty range: true
// Single element: true
