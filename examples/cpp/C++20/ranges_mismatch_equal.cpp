// CodeNebula - C++20 Example: ranges::mismatch, equal
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_mismatch_equal.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::vector<int> a = {1, 2, 3, 4, 5};
    std::vector<int> b = {1, 2, 3, 4, 5};
    std::vector<int> c = {1, 2, 9, 4, 5};

    std::cout << std::boolalpha;
    std::cout << "a == b: " << std::ranges::equal(a, b) << "\n";
    std::cout << "a == c: " << std::ranges::equal(a, c) << "\n";

    // Equal with custom comparator (absolute value)
    std::vector<int> d = {-1, -2, -3, -4, -5};
    std::cout << "a abs-equal d: " << std::ranges::equal(a, d,
        [](int x, int y) { return std::abs(x) == std::abs(y); }) << "\n";

    // Equal with projection (case-insensitive strings)
    std::vector<std::string> words1 = {"Hello", "WORLD"};
    std::vector<std::string> words2 = {"hello", "world"};
    auto to_lower = [](const std::string& s) {
        std::string low = s;
        for (char& ch : low) ch = static_cast<char>(std::tolower(ch));
        return low;
    };
    std::cout << "Case-insensitive equal: "
              << std::ranges::equal(words1, words2, {}, to_lower, to_lower) << "\n";

    // ranges::mismatch - find first differing position
    auto [it1, it2] = std::ranges::mismatch(a, c);
    if (it1 != a.end())
        std::cout << "\nMismatch at index " << (it1 - a.begin())
                  << ": " << *it1 << " vs " << *it2 << "\n";

    // Mismatch when ranges are equal
    auto [m1, m2] = std::ranges::mismatch(a, b);
    std::cout << "a vs b mismatch at end: " << (m1 == a.end()) << "\n";

    // Mismatch with different-length ranges (prefix check)
    std::vector<int> shorter = {1, 2, 3};
    auto [s1, s2] = std::ranges::mismatch(a, shorter);
    if (s2 == shorter.end())
        std::cout << "Shorter is prefix of a (" << shorter.size() << " elements)\n";

    // Mismatch with strings
    std::string str1 = "abcdefgh", str2 = "abcXefgh";
    auto [c1, c2] = std::ranges::mismatch(str1, str2);
    if (c1 != str1.end())
        std::cout << "\nString mismatch at index " << (c1 - str1.begin())
                  << ": '" << *c1 << "' vs '" << *c2 << "'\n";

    // Equal on views
    std::cout << "\niota(1,6) == a: "
              << std::ranges::equal(std::views::iota(1, 6), a) << "\n";

    // Mismatch with predicate (x == 2*y)
    std::vector<int> e = {2, 4, 6, 8, 10};
    std::vector<int> f = {1, 2, 3, 5, 5};
    auto [p1, p2] = std::ranges::mismatch(e, f,
        [](int x, int y) { return x == y * 2; });
    if (p1 != e.end())
        std::cout << "Double mismatch at index " << (p1 - e.begin())
                  << ": " << *p1 << " != 2*" << *p2 << "\n";
    return 0;
}
