// CodeNebula - C++23 Example: ranges::find_last, find_last_if, find_last_if_not
// Compile: g++ -std=c++23 -Wall -Wextra -o example ranges_find_last.cpp
// Note: Requires GCC 13+ / Clang 17+

// C++23 adds find_last family algorithms that search for elements from the end
// of a range. They return a subrange from the found element to the end, or an
// empty subrange at the end if not found.

#include <iostream>
#include <algorithm>
#include <ranges>
#include <vector>
#include <string>

int main() {
    std::vector<int> nums = {1, 3, 5, 3, 7, 3, 9, 2};

    // ranges::find_last - find last occurrence of a value
    std::cout << "=== find_last ===" << std::endl;
    auto result = std::ranges::find_last(nums, 3);
    if (!result.empty()) {
        auto idx = result.begin() - nums.begin();
        std::cout << "  Last 3 found at index: " << idx << std::endl;
    }

    // Find last occurrence of a value not present
    auto not_found = std::ranges::find_last(nums, 42);
    std::cout << "  42 found: " << std::boolalpha << !not_found.empty() << std::endl;

    // ranges::find_last_if - find last element matching a predicate
    std::cout << "\n=== find_last_if ===" << std::endl;
    auto last_even = std::ranges::find_last_if(nums, [](int n) { return n % 2 == 0; });
    if (!last_even.empty()) {
        auto idx = last_even.begin() - nums.begin();
        std::cout << "  Last even number: " << *last_even.begin()
                  << " at index " << idx << std::endl;
    }

    auto last_gt5 = std::ranges::find_last_if(nums, [](int n) { return n > 5; });
    if (!last_gt5.empty()) {
        std::cout << "  Last number > 5: " << *last_gt5.begin() << std::endl;
    }

    // ranges::find_last_if_not - find last element NOT matching a predicate
    std::cout << "\n=== find_last_if_not ===" << std::endl;
    auto last_not_odd = std::ranges::find_last_if_not(nums, [](int n) { return n % 2 != 0; });
    if (!last_not_odd.empty()) {
        auto idx = last_not_odd.begin() - nums.begin();
        std::cout << "  Last non-odd: " << *last_not_odd.begin()
                  << " at index " << idx << std::endl;
    }

    // Practical: find last error in a log
    std::vector<std::string> log = {
        "INFO: start", "ERROR: disk full", "INFO: retry",
        "ERROR: timeout", "INFO: recovered", "INFO: done"
    };
    std::cout << "\n=== Find last error in log ===" << std::endl;
    auto last_error = std::ranges::find_last_if(log,
        [](const std::string& s) { return s.starts_with("ERROR"); });
    if (!last_error.empty()) {
        auto idx = last_error.begin() - log.begin();
        std::cout << "  Last error at entry " << idx << ": "
                  << *last_error.begin() << std::endl;
    }

    // Find last non-zero in data
    std::vector<int> data = {5, 0, 3, 0, 0, 7, 0, 0};
    auto last_nonzero = std::ranges::find_last_if(data, [](int n) { return n != 0; });
    if (!last_nonzero.empty()) {
        auto idx = last_nonzero.begin() - data.begin();
        std::cout << "\n=== Last non-zero ===" << std::endl;
        std::cout << "  Value " << *last_nonzero.begin()
                  << " at index " << idx << std::endl;
    }

    return 0;
}

// Expected output:
// === find_last ===
//   Last 3 found at index: 5
//   42 found: false
//
// === find_last_if ===
//   Last even number: 2 at index 7
//   Last number > 5: 9
//
// === find_last_if_not ===
//   Last non-odd: 2 at index 7
//
// === Find last error in log ===
//   Last error at entry 3: ERROR: timeout
//
// === Last non-zero ===
//   Value 7 at index 5
