// CodeNebula - C++17 Example: std::not_fn
// Compile: g++ -std=c++17 -Wall -Wextra -o example not_fn.cpp

// Demonstrates std::not_fn, which creates a wrapper that negates the result
// of any callable. It replaces the deprecated std::not1/std::not2 and works
// with any callable (lambdas, function objects, free functions, etc.).

#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <string>

bool is_even(int n) { return n % 2 == 0; }
bool is_positive(int n) { return n > 0; }

struct LengthChecker {
    std::size_t max_len;
    bool operator()(const std::string& s) const { return s.size() <= max_len; }
};

int main()
{
    // ------------------------------------------------------------------
    // 1. Negate a free function
    // ------------------------------------------------------------------
    auto is_odd = std::not_fn(is_even);

    std::cout << "=== Negate Free Function ===" << std::endl;
    std::cout << "  is_even(4) = " << is_even(4) << std::endl;
    std::cout << "  is_odd(4)  = " << is_odd(4) << std::endl;
    std::cout << "  is_odd(7)  = " << is_odd(7) << std::endl;

    // ------------------------------------------------------------------
    // 2. Use with algorithms -- partition odd/even
    // ------------------------------------------------------------------
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto count_odd = std::count_if(nums.begin(), nums.end(), std::not_fn(is_even));
    auto count_neg = std::count_if(nums.begin(), nums.end(), std::not_fn(is_positive));

    std::cout << "\n=== With Algorithms ===" << std::endl;
    std::cout << "  Odd numbers in [1..10] : " << count_odd << std::endl;
    std::cout << "  Non-positive in [1..10]: " << count_neg << std::endl;

    // ------------------------------------------------------------------
    // 3. Negate a lambda
    // ------------------------------------------------------------------
    auto is_short = [](const std::string& s) { return s.size() < 4; };
    auto is_long  = std::not_fn(is_short);

    std::vector<std::string> words = {"hi", "hello", "ok", "wonderful", "no"};
    auto long_count = std::count_if(words.begin(), words.end(), is_long);

    std::cout << "\n=== Negate Lambda ===" << std::endl;
    std::cout << "  Words: ";
    for (const auto& w : words) std::cout << w << " ";
    std::cout << std::endl;
    std::cout << "  Long words (>=4 chars): " << long_count << std::endl;

    // ------------------------------------------------------------------
    // 4. Negate a function object
    // ------------------------------------------------------------------
    LengthChecker fits_in_5{5};
    auto too_long = std::not_fn(fits_in_5);

    std::cout << "\n=== Negate Function Object ===" << std::endl;
    for (const auto& w : words) {
        std::cout << "  \"" << w << "\" too long for 5? " << too_long(w) << std::endl;
    }

    // ------------------------------------------------------------------
    // 5. Composing with remove_if
    // ------------------------------------------------------------------
    std::vector<int> data = {-3, -1, 0, 2, 5, -7, 8};
    // Remove non-positive elements (keep only positive)
    data.erase(
        std::remove_if(data.begin(), data.end(), std::not_fn(is_positive)),
        data.end()
    );

    std::cout << "\n=== remove_if with not_fn ===" << std::endl;
    std::cout << "  After keeping positives: ";
    for (int v : data) std::cout << v << " ";
    std::cout << std::endl;

    return 0;
}

/*
Expected output:

=== Negate Free Function ===
  is_even(4) = 1
  is_odd(4)  = 0
  is_odd(7)  = 1

=== With Algorithms ===
  Odd numbers in [1..10] : 5
  Non-positive in [1..10]: 0

=== Negate Lambda ===
  Words: hi hello ok wonderful no
  Long words (>=4 chars): 2

=== Negate Function Object ===
  "hi" too long for 5? 0
  "hello" too long for 5? 0
  "ok" too long for 5? 0
  "wonderful" too long for 5? 1
  "no" too long for 5? 0

=== remove_if with not_fn ===
  After keeping positives: 2 5 8
*/
