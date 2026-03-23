// CodeNebula - C++11 Example: std::is_permutation
// Compile: g++ -std=c++11 -Wall -Wextra -o example is_permutation.cpp

// std::is_permutation checks whether one range is a rearrangement of another.
// Two ranges are permutations of each other if they contain the same elements
// with the same multiplicities, regardless of order.

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main() {
    // Basic permutation check
    std::vector<int> a = {1, 2, 3, 4, 5};
    std::vector<int> b = {3, 5, 1, 4, 2};

    std::cout << "{1,2,3,4,5} is permutation of {3,5,1,4,2}: "
              << std::boolalpha
              << std::is_permutation(a.begin(), a.end(), b.begin()) << std::endl;

    // Different elements - not a permutation
    std::vector<int> c = {1, 2, 3, 4, 6};
    std::cout << "{1,2,3,4,5} is permutation of {1,2,3,4,6}: "
              << std::is_permutation(a.begin(), a.end(), c.begin()) << std::endl;

    // Duplicate elements matter
    std::vector<int> d = {1, 1, 2, 3};
    std::vector<int> e = {3, 1, 2, 1};
    std::vector<int> f = {1, 2, 2, 3};

    std::cout << "{1,1,2,3} is permutation of {3,1,2,1}: "
              << std::is_permutation(d.begin(), d.end(), e.begin()) << std::endl;
    std::cout << "{1,1,2,3} is permutation of {1,2,2,3}: "
              << std::is_permutation(d.begin(), d.end(), f.begin()) << std::endl;

    // Check if two strings are anagrams
    std::string s1 = "listen";
    std::string s2 = "silent";
    std::string s3 = "hello";

    std::cout << "'listen' is anagram of 'silent': "
              << std::is_permutation(s1.begin(), s1.end(), s2.begin()) << std::endl;
    std::cout << "'listen' is anagram of 'hello': "
              << std::is_permutation(s1.begin(), s1.end(), s3.begin()) << std::endl;

    // With custom comparator (case-insensitive)
    std::string upper = "ABC";
    std::string lower = "cab";
    std::cout << "'ABC' is permutation of 'cab' (case-insensitive): "
              << std::is_permutation(upper.begin(), upper.end(), lower.begin(),
                                     [](char a, char b) {
                                         return std::tolower(a) == std::tolower(b);
                                     }) << std::endl;

    // Empty ranges are permutations of each other
    std::vector<int> empty1, empty2;
    std::cout << "Empty ranges: "
              << std::is_permutation(empty1.begin(), empty1.end(),
                                     empty2.begin()) << std::endl;

    return 0;
}

// Expected output:
// {1,2,3,4,5} is permutation of {3,5,1,4,2}: true
// {1,2,3,4,5} is permutation of {1,2,3,4,6}: false
// {1,1,2,3} is permutation of {3,1,2,1}: true
// {1,1,2,3} is permutation of {1,2,2,3}: false
// 'listen' is anagram of 'silent': true
// 'listen' is anagram of 'hello': false
// 'ABC' is permutation of 'cab' (case-insensitive): true
// Empty ranges: true
