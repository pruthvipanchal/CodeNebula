// CodeNebula - C++17 Example: std::for_each_n
// Compile: g++ -std=c++17 -Wall -Wextra -o example for_each_n.cpp

// Demonstrates std::for_each_n, which applies a function to the first N
// elements of a range. Unlike std::for_each, you specify a count instead
// of an end iterator -- useful when you only want to process a prefix.

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic usage: print first N elements
    // ------------------------------------------------------------------
    std::cout << "=== print first N elements ===" << std::endl;
    std::vector<int> nums = {10, 20, 30, 40, 50, 60, 70, 80};

    std::cout << "  All: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << std::endl;

    std::cout << "  First 4: ";
    std::for_each_n(nums.begin(), 4, [](int n) {
        std::cout << n << " ";
    });
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Modify first N elements
    // ------------------------------------------------------------------
    std::cout << "\n=== modify first N ===" << std::endl;
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8};
    std::cout << "  Before: ";
    for (int x : data) std::cout << x << " ";
    std::cout << std::endl;

    // Double the first 3 elements
    std::for_each_n(data.begin(), 3, [](int& x) { x *= 2; });
    std::cout << "  After (first 3 doubled): ";
    for (int x : data) std::cout << x << " ";
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Return value: iterator past the last processed element
    // ------------------------------------------------------------------
    std::cout << "\n=== return value ===" << std::endl;
    std::vector<int> v = {100, 200, 300, 400, 500};
    auto it = std::for_each_n(v.begin(), 3, [](int n) {
        std::cout << "  processed: " << n << std::endl;
    });
    std::cout << "  Next element after processed range: " << *it << std::endl;

    // ------------------------------------------------------------------
    // 4. With strings
    // ------------------------------------------------------------------
    std::cout << "\n=== string processing ===" << std::endl;
    std::vector<std::string> words = {"alpha", "beta", "gamma", "delta", "epsilon"};

    std::cout << "  First 3 uppercased:" << std::endl;
    std::for_each_n(words.begin(), 3, [](std::string& w) {
        for (char& c : w) c = static_cast<char>(std::toupper(c));
    });
    for (const auto& w : words) std::cout << "    " << w << std::endl;

    // ------------------------------------------------------------------
    // 5. Accumulate using for_each_n (stateful lambda)
    // ------------------------------------------------------------------
    std::cout << "\n=== stateful lambda (sum first N) ===" << std::endl;
    std::vector<int> scores = {95, 87, 92, 78, 85, 91, 88};
    int sum = 0;
    int count = 5;
    std::for_each_n(scores.begin(), count, [&sum](int s) { sum += s; });
    std::cout << "  Sum of first " << count << " scores: " << sum << std::endl;
    std::cout << "  Average: " << static_cast<double>(sum) / count << std::endl;

    // ------------------------------------------------------------------
    // 6. N = 0 is safe (no-op)
    // ------------------------------------------------------------------
    std::cout << "\n=== N=0 (no-op) ===" << std::endl;
    std::for_each_n(nums.begin(), 0, [](int) {
        std::cout << "  This should never print" << std::endl;
    });
    std::cout << "  for_each_n with N=0 did nothing (as expected)" << std::endl;

    return 0;
}

/*
Expected output:

=== print first N elements ===
  All: 10 20 30 40 50 60 70 80
  First 4: 10 20 30 40

=== modify first N ===
  Before: 1 2 3 4 5 6 7 8
  After (first 3 doubled): 2 4 6 4 5 6 7 8

=== return value ===
  processed: 100
  processed: 200
  processed: 300
  Next element after processed range: 400

=== string processing ===
  First 3 uppercased:
    ALPHA
    BETA
    GAMMA
    delta
    epsilon

=== stateful lambda (sum first N) ===
  Sum of first 5 scores: 437
  Average: 87.4

=== N=0 (no-op) ===
  for_each_n with N=0 did nothing (as expected)
*/
