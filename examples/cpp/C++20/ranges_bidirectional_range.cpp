// CodeNebula - C++20 Example: std::ranges::bidirectional_range Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_bidirectional_range.cpp

#include <ranges>
#include <vector>
#include <list>
#include <forward_list>
#include <iostream>

// std::ranges::bidirectional_range requires that iterators support
// both increment (++) and decrement (--) operations.

// Print a range in reverse using bidirectional iterators
template <std::ranges::bidirectional_range R>
void print_reversed(const R& r) {
    auto it = std::ranges::end(r);
    auto begin = std::ranges::begin(r);
    while (it != begin) {
        --it;
        std::cout << *it << " ";
    }
    std::cout << "\n";
}

// Check if a bidirectional range is a palindrome efficiently
template <std::ranges::bidirectional_range R>
    requires std::equality_comparable<std::ranges::range_value_t<R>>
bool is_palindrome(const R& r) {
    auto front = std::ranges::begin(r);
    auto back = std::ranges::end(r);
    if (front == back) return true;
    --back;
    while (front != back) {
        if (*front != *back) return false;
        ++front;
        if (front == back) break;
        --back;
    }
    return true;
}

int main() {
    // Bidirectional containers
    static_assert(std::ranges::bidirectional_range<std::vector<int>>);
    static_assert(std::ranges::bidirectional_range<std::list<int>>);

    // forward_list is NOT bidirectional
    static_assert(!std::ranges::bidirectional_range<std::forward_list<int>>);

    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::cout << "Original: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << "\nReversed: ";
    print_reversed(nums);

    std::list<char> chars = {'r', 'a', 'c', 'e', 'c', 'a', 'r'};
    std::cout << "racecar is palindrome: " << std::boolalpha
              << is_palindrome(chars) << "\n";

    std::list<int> not_palin = {1, 2, 3, 4};
    std::cout << "{1,2,3,4} is palindrome: "
              << is_palindrome(not_palin) << "\n";

    // reverse_view requires bidirectional_range
    auto rev = nums | std::views::reverse;
    std::cout << "Reverse view: ";
    for (int n : rev) std::cout << n << " ";
    std::cout << "\n";
    return 0;
}
