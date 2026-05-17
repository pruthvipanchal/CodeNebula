// CodeNebula - C++11 Example: std::minmax Pair Result
// Compile: g++ -std=c++11 -Wall -Wextra -o example minmax.cpp

// std::minmax returns a std::pair containing the smaller and larger of two
// values (or the min and max of an initializer_list). It performs at most
// one and a half comparisons per element, which is more efficient than
// calling std::min and std::max separately.

#include <iostream>
#include <algorithm>
#include <string>
#include <utility>

int main() {
    // Basic minmax of two values
    auto result = std::minmax(3, 7);
    std::cout << "minmax(3, 7): min=" << result.first
              << ", max=" << result.second << std::endl;

    // Works with reversed arguments
    auto result2 = std::minmax(10, 2);
    std::cout << "minmax(10, 2): min=" << result2.first
              << ", max=" << result2.second << std::endl;

    // Equal values
    auto result3 = std::minmax(5, 5);
    std::cout << "minmax(5, 5): min=" << result3.first
              << ", max=" << result3.second << std::endl;

    // With strings (lexicographic comparison)
    auto str_result = std::minmax(std::string("banana"), std::string("apple"));
    std::cout << "minmax(banana, apple): min=" << str_result.first
              << ", max=" << str_result.second << std::endl;

    // With initializer_list - find min and max in one pass
    auto list_result = std::minmax({5, 2, 8, 1, 9, 3});
    std::cout << "minmax({5,2,8,1,9,3}): min=" << list_result.first
              << ", max=" << list_result.second << std::endl;

    // Custom comparator (by absolute value)
    auto abs_result = std::minmax(-7, 3, [](int a, int b) {
        return std::abs(a) < std::abs(b);
    });
    std::cout << "minmax(-7, 3) by abs: min=" << abs_result.first
              << ", max=" << abs_result.second << std::endl;

    // Initializer list with custom comparator
    auto custom = std::minmax({-5, 2, -8, 1, 9, -3}, [](int a, int b) {
        return std::abs(a) < std::abs(b);
    });
    std::cout << "minmax by abs value: min=" << custom.first
              << ", max=" << custom.second << std::endl;

    // Practical: clamp a value to a range
    int value = 15;
    auto bounds = std::minmax(0, 10);
    int clamped = std::max(bounds.first, std::min(value, bounds.second));
    std::cout << "Clamp " << value << " to [0,10]: " << clamped << std::endl;

    return 0;
}

// Expected output:
// minmax(3, 7): min=3, max=7
// minmax(10, 2): min=2, max=10
// minmax(5, 5): min=5, max=5
// minmax(banana, apple): min=apple, max=banana
// minmax({5,2,8,1,9,3}): min=1, max=9
// minmax(-7, 3) by abs: min=3, max=-7
// minmax by abs value: min=1, max=9
// Clamp 15 to [0,10]: 10
