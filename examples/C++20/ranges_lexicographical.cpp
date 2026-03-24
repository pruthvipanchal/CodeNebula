// CodeNebula - C++20 Example: Ranges Lexicographical Compare
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_lexicographical.cpp

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>

int main() {
    // ranges::lexicographical_compare - compare two sequences element by element
    std::vector<int> a = {1, 2, 3, 4};
    std::vector<int> b = {1, 2, 4, 0};

    std::cout << "A: ";
    for (int x : a) std::cout << x << ' ';
    std::cout << "\nB: ";
    for (int x : b) std::cout << x << ' ';
    std::cout << '\n';

    bool a_less = std::ranges::lexicographical_compare(a, b);
    std::cout << "A < B? " << (a_less ? "yes" : "no") << '\n';

    bool b_less = std::ranges::lexicographical_compare(b, a);
    std::cout << "B < A? " << (b_less ? "yes" : "no") << '\n';

    // Shorter prefix is less than longer sequence
    std::vector<int> prefix = {1, 2, 3};
    std::vector<int> longer = {1, 2, 3, 4};
    bool prefix_less = std::ranges::lexicographical_compare(prefix, longer);
    std::cout << "\n{1,2,3} < {1,2,3,4}? " << (prefix_less ? "yes" : "no") << '\n';

    // Equal sequences are not less
    bool eq = std::ranges::lexicographical_compare(a, a);
    std::cout << "A < A? " << (eq ? "yes" : "no") << '\n';

    // Case-insensitive string comparison
    std::string s1 = "Hello";
    std::string s2 = "hello";
    bool ci_less = std::ranges::lexicographical_compare(s1, s2,
        [](char c1, char c2) {
            return std::tolower(c1) < std::tolower(c2);
        });
    std::cout << "\n\"Hello\" < \"hello\" (case-insensitive)? "
              << (ci_less ? "yes" : "no") << '\n';

    // Sorting strings using lexicographical comparison
    std::vector<std::string> words = {"banana", "apple", "cherry", "apricot"};
    std::ranges::sort(words, [](const auto& x, const auto& y) {
        return std::ranges::lexicographical_compare(x, y);
    });
    std::cout << "\nLexicographically sorted: ";
    for (const auto& w : words) std::cout << w << ' ';
    std::cout << '\n';

    // Compare character arrays
    std::vector<char> ca = {'a', 'b', 'c'};
    std::vector<char> cb = {'a', 'b', 'd'};
    std::cout << "\n{'a','b','c'} < {'a','b','d'}? "
              << (std::ranges::lexicographical_compare(ca, cb) ? "yes" : "no")
              << '\n';

    return 0;
}
