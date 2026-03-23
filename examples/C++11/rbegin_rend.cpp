// CodeNebula - C++11 Example: std::rbegin and std::rend Reverse Iterators
// Compile: g++ -std=c++11 -Wall -Wextra -o example rbegin_rend.cpp

// rbegin() and rend() return reverse iterators that traverse a container
// from back to front. In C++11 these are member functions; the free
// function versions std::rbegin/std::rend were added in C++14.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    // Reverse iterate a vector
    std::vector<int> nums = {1, 2, 3, 4, 5};

    std::cout << "Forward: ";
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Reverse: ";
    for (auto it = nums.rbegin(); it != nums.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Reverse iterate a string
    std::string word = "Hello";
    std::cout << "String reversed: ";
    for (auto it = word.rbegin(); it != word.rend(); ++it) {
        std::cout << *it;
    }
    std::cout << std::endl;

    // Check if a string is a palindrome
    auto is_palindrome = [](const std::string& s) {
        return std::equal(s.begin(), s.begin() + s.size() / 2, s.rbegin());
    };

    std::cout << "'racecar' is palindrome: " << std::boolalpha
              << is_palindrome("racecar") << std::endl;
    std::cout << "'hello' is palindrome: " << std::boolalpha
              << is_palindrome("hello") << std::endl;

    // Find last even number using reverse iterators
    std::vector<int> data = {3, 8, 5, 12, 7, 6, 1};
    auto rit = std::find_if(data.rbegin(), data.rend(),
                            [](int n) { return n % 2 == 0; });
    if (rit != data.rend()) {
        std::cout << "Last even number: " << *rit << std::endl;
    }

    // Reverse sort using reverse iterators
    std::sort(nums.rbegin(), nums.rend());
    std::cout << "Reverse sorted: ";
    for (const auto& n : nums) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Forward: 1 2 3 4 5
// Reverse: 5 4 3 2 1
// String reversed: olleH
// 'racecar' is palindrome: true
// 'hello' is palindrome: false
// Last even number: 6
// Reverse sorted: 5 4 3 2 1
