// CodeNebula - C++20 Example: Ranges Is Permutation
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_is_permutation.cpp

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

int main() {
    // ranges::is_permutation - check if one range is a rearrangement of another
    std::vector<int> a = {1, 2, 3, 4, 5};
    std::vector<int> b = {3, 5, 1, 4, 2};
    std::vector<int> c = {1, 2, 3, 4, 6};

    std::cout << "A: ";
    for (int x : a) std::cout << x << ' ';
    std::cout << "\nB: ";
    for (int x : b) std::cout << x << ' ';
    std::cout << "\nC: ";
    for (int x : c) std::cout << x << ' ';
    std::cout << '\n';

    std::cout << "\nA is permutation of B? "
              << (std::ranges::is_permutation(a, b) ? "yes" : "no") << '\n';
    std::cout << "A is permutation of C? "
              << (std::ranges::is_permutation(a, c) ? "yes" : "no") << '\n';

    // With duplicate elements
    std::vector<int> d1 = {1, 1, 2, 3};
    std::vector<int> d2 = {3, 1, 2, 1};
    std::vector<int> d3 = {1, 2, 2, 3};
    std::cout << "\n{1,1,2,3} perm of {3,1,2,1}? "
              << (std::ranges::is_permutation(d1, d2) ? "yes" : "no") << '\n';
    std::cout << "{1,1,2,3} perm of {1,2,2,3}? "
              << (std::ranges::is_permutation(d1, d3) ? "yes" : "no") << '\n';

    // Different sizes are never permutations
    std::vector<int> short_v = {1, 2, 3};
    std::cout << "\n{1,2,3,4,5} perm of {1,2,3}? "
              << (std::ranges::is_permutation(a, short_v) ? "yes" : "no") << '\n';

    // Strings - check if anagrams
    std::string s1 = "listen";
    std::string s2 = "silent";
    std::string s3 = "hello";
    std::cout << "\n\"listen\" anagram of \"silent\"? "
              << (std::ranges::is_permutation(s1, s2) ? "yes" : "no") << '\n';
    std::cout << "\"listen\" anagram of \"hello\"? "
              << (std::ranges::is_permutation(s1, s3) ? "yes" : "no") << '\n';

    // With custom predicate (case-insensitive anagram check)
    std::string upper = "LISTEN";
    bool ci_perm = std::ranges::is_permutation(s1, upper,
        [](char a, char b) { return std::tolower(a) == std::tolower(b); });
    std::cout << "\"listen\" anagram of \"LISTEN\" (case-insensitive)? "
              << (ci_perm ? "yes" : "no") << '\n';

    // Empty ranges are permutations of each other
    std::vector<int> e1, e2;
    std::cout << "\nEmpty perm of empty? "
              << (std::ranges::is_permutation(e1, e2) ? "yes" : "no") << '\n';

    return 0;
}
