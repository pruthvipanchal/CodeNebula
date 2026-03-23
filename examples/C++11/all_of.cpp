// CodeNebula - C++11 Example: std::all_of Predicate Check
// Compile: g++ -std=c++11 -Wall -Wextra -o example all_of.cpp

// std::all_of returns true if a predicate holds for every element in a range.
// It short-circuits: evaluation stops at the first element that fails.
// Returns true for empty ranges.

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main() {
    std::vector<int> numbers = {2, 4, 6, 8, 10};

    // Check if all elements are even
    bool all_even = std::all_of(numbers.begin(), numbers.end(),
                                [](int n) { return n % 2 == 0; });
    std::cout << "All even: " << std::boolalpha << all_even << std::endl;

    // Check if all elements are positive
    bool all_positive = std::all_of(numbers.begin(), numbers.end(),
                                    [](int n) { return n > 0; });
    std::cout << "All positive: " << all_positive << std::endl;

    // Add an odd number and recheck
    numbers.push_back(7);
    all_even = std::all_of(numbers.begin(), numbers.end(),
                           [](int n) { return n % 2 == 0; });
    std::cout << "All even after adding 7: " << all_even << std::endl;

    // Check if all strings have minimum length
    std::vector<std::string> words = {"hello", "world", "test"};
    bool all_long = std::all_of(words.begin(), words.end(),
                                [](const std::string& s) { return s.size() >= 4; });
    std::cout << "All words >= 4 chars: " << all_long << std::endl;

    // Empty range returns true
    std::vector<int> empty;
    bool empty_result = std::all_of(empty.begin(), empty.end(),
                                    [](int n) { return n > 100; });
    std::cout << "All of empty range: " << empty_result << std::endl;

    // Check if all elements are less than a threshold
    std::vector<int> scores = {85, 92, 78, 95, 88};
    int threshold = 100;
    bool all_below = std::all_of(scores.begin(), scores.end(),
                                 [threshold](int s) { return s < threshold; });
    std::cout << "All scores < " << threshold << ": " << all_below << std::endl;

    return 0;
}

// Expected output:
// All even: true
// All positive: true
// All even after adding 7: false
// All words >= 4 chars: true
// All of empty range: true
// All scores < 100: true
