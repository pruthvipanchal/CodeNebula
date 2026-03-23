// CodeNebula - C++11 Example: std::any_of Predicate Check
// Compile: g++ -std=c++11 -Wall -Wextra -o example any_of.cpp

// std::any_of returns true if a predicate holds for at least one element
// in a range. It short-circuits: evaluation stops at the first match.
// Returns false for empty ranges.

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main() {
    std::vector<int> numbers = {1, 3, 5, 8, 9};

    // Check if any element is even
    bool has_even = std::any_of(numbers.begin(), numbers.end(),
                                [](int n) { return n % 2 == 0; });
    std::cout << "Any even: " << std::boolalpha << has_even << std::endl;

    // Check if any element is negative
    bool has_negative = std::any_of(numbers.begin(), numbers.end(),
                                    [](int n) { return n < 0; });
    std::cout << "Any negative: " << has_negative << std::endl;

    // Check if any element exceeds a threshold
    bool has_large = std::any_of(numbers.begin(), numbers.end(),
                                 [](int n) { return n > 100; });
    std::cout << "Any > 100: " << has_large << std::endl;

    // Check strings for a specific property
    std::vector<std::string> words = {"cat", "dog", "elephant", "ant"};
    bool has_long_word = std::any_of(words.begin(), words.end(),
                                     [](const std::string& s) { return s.size() > 5; });
    std::cout << "Any word > 5 chars: " << has_long_word << std::endl;

    // Empty range returns false
    std::vector<int> empty;
    bool empty_result = std::any_of(empty.begin(), empty.end(),
                                    [](int n) { return n == 0; });
    std::cout << "Any of empty range: " << empty_result << std::endl;

    // Practical use: check if any student passed
    std::vector<int> scores = {45, 32, 58, 71, 29};
    int passing = 60;
    bool anyone_passed = std::any_of(scores.begin(), scores.end(),
                                     [passing](int s) { return s >= passing; });
    std::cout << "Anyone scored >= " << passing << ": " << anyone_passed << std::endl;

    return 0;
}

// Expected output:
// Any even: true
// Any negative: false
// Any > 100: false
// Any word > 5 chars: true
// Any of empty range: false
// Anyone scored >= 60: true
