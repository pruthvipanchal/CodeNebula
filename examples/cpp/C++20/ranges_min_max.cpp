// CodeNebula - C++20 Example: Ranges Min Max
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_min_max.cpp

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

int main() {
    // ranges::min - return the smaller of two values
    std::cout << "min(3, 7): " << std::ranges::min(3, 7) << '\n';
    std::cout << "min(5, 5): " << std::ranges::min(5, 5) << '\n';

    // ranges::max - return the larger of two values
    std::cout << "max(3, 7): " << std::ranges::max(3, 7) << '\n';

    // ranges::min / max with initializer list
    int smallest = std::ranges::min({5, 2, 8, 1, 9, 3});
    int largest  = std::ranges::max({5, 2, 8, 1, 9, 3});
    std::cout << "\nmin({5,2,8,1,9,3}): " << smallest << '\n';
    std::cout << "max({5,2,8,1,9,3}): " << largest << '\n';

    // ranges::min / max over a range
    std::vector<int> nums = {42, 17, 93, 5, 68};
    std::cout << "\nVector min: " << std::ranges::min(nums) << '\n';
    std::cout << "Vector max: " << std::ranges::max(nums) << '\n';

    // ranges::minmax - get both min and max at once
    auto [lo, hi] = std::ranges::minmax(nums);
    std::cout << "\nminmax: [" << lo << ", " << hi << "]\n";

    auto [lo2, hi2] = std::ranges::minmax({10, 30, 20, 50, 40});
    std::cout << "minmax({10,30,20,50,40}): [" << lo2 << ", " << hi2 << "]\n";

    // With custom comparator
    std::cout << "\nmin by abs: "
              << std::ranges::min(-5, 3, [](int a, int b) {
                     return std::abs(a) < std::abs(b);
                 }) << '\n';

    // With projection
    std::vector<std::string> words = {"banana", "fig", "cherry", "apple"};
    auto shortest = std::ranges::min(words, {}, &std::string::size);
    auto longest  = std::ranges::max(words, {}, &std::string::size);
    std::cout << "\nShortest word: " << shortest << '\n';
    std::cout << "Longest word:  " << longest << '\n';

    auto [s, l] = std::ranges::minmax(words, {}, &std::string::size);
    std::cout << "minmax by length: [" << s << ", " << l << "]\n";

    return 0;
}
