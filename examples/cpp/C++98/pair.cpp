// CodeNebula - C++98 Example: pair
// Compile: g++ -std=c++98 -Wall -Wextra -o example pair.cpp

// std::pair holds two values of potentially different types.
// It is heavily used with associative containers (map, multimap)
// and as a general-purpose two-element tuple.

#include <iostream>
#include <utility> // for std::pair, std::make_pair
#include <string>
#include <vector>
#include <algorithm>

int main() {
    // --- Construction ---
    std::cout << "=== Construction ===" << std::endl;

    // Direct construction
    std::pair<std::string, int> p1("Alice", 30);
    std::cout << "p1: (" << p1.first << ", " << p1.second << ")" << std::endl;

    // Default construction (value-initialized)
    std::pair<int, double> p2;
    std::cout << "p2 (default): (" << p2.first << ", " << p2.second << ")" << std::endl;

    // Copy construction
    std::pair<std::string, int> p3(p1);
    std::cout << "p3 (copy of p1): (" << p3.first << ", " << p3.second << ")" << std::endl;

    // --- make_pair ---
    std::cout << "\n=== make_pair ===" << std::endl;
    std::pair<int, double> p4 = std::make_pair(42, 3.14);
    std::cout << "make_pair(42, 3.14): (" << p4.first << ", " << p4.second << ")" << std::endl;

    std::pair<std::string, std::string> p5 =
        std::make_pair(std::string("hello"), std::string("world"));
    std::cout << "make_pair strings: (" << p5.first << ", " << p5.second << ")" << std::endl;

    // --- first and second access ---
    std::cout << "\n=== first and second ===" << std::endl;
    std::pair<int, std::string> p6(1, "one");
    std::cout << "first: " << p6.first << std::endl;
    std::cout << "second: " << p6.second << std::endl;

    // Modify through first/second
    p6.first = 2;
    p6.second = "two";
    std::cout << "After modification: (" << p6.first << ", " << p6.second << ")" << std::endl;

    // --- Assignment ---
    std::cout << "\n=== Assignment ===" << std::endl;
    std::pair<int, int> a(1, 2);
    std::pair<int, int> b(3, 4);
    std::cout << "a: (" << a.first << ", " << a.second << ")" << std::endl;
    std::cout << "b: (" << b.first << ", " << b.second << ")" << std::endl;
    a = b;
    std::cout << "After a = b: a=(" << a.first << ", " << a.second << ")" << std::endl;

    // --- Comparison operators ---
    std::cout << "\n=== Comparison operators ===" << std::endl;
    // Pairs compare lexicographically: first by .first, then by .second

    std::pair<int, int> c1(1, 2);
    std::pair<int, int> c2(1, 2);
    std::pair<int, int> c3(1, 3);
    std::pair<int, int> c4(2, 1);

    std::cout << "(1,2) == (1,2): " << (c1 == c2 ? "true" : "false") << std::endl;
    std::cout << "(1,2) != (1,3): " << (c1 != c3 ? "true" : "false") << std::endl;
    std::cout << "(1,2) < (1,3):  " << (c1 < c3 ? "true" : "false") << std::endl;
    std::cout << "(1,2) < (2,1):  " << (c1 < c4 ? "true" : "false") << std::endl;
    std::cout << "(2,1) > (1,3):  " << (c4 > c3 ? "true" : "false") << std::endl;
    std::cout << "(1,2) <= (1,2): " << (c1 <= c2 ? "true" : "false") << std::endl;
    std::cout << "(1,3) >= (1,2): " << (c3 >= c1 ? "true" : "false") << std::endl;

    // --- Nested pairs ---
    std::cout << "\n=== Nested pairs ===" << std::endl;
    std::pair<int, std::pair<int, int> > nested;
    nested.first = 1;
    nested.second.first = 2;
    nested.second.second = 3;
    std::cout << "Nested: (" << nested.first
              << ", (" << nested.second.first
              << ", " << nested.second.second << "))" << std::endl;

    // --- Pairs in a vector ---
    std::cout << "\n=== Vector of pairs ===" << std::endl;
    std::vector<std::pair<std::string, int> > scores;
    scores.push_back(std::make_pair(std::string("Charlie"), 85));
    scores.push_back(std::make_pair(std::string("Alice"), 95));
    scores.push_back(std::make_pair(std::string("Bob"), 90));

    std::cout << "Unsorted:" << std::endl;
    for (std::vector<std::pair<std::string, int> >::iterator it = scores.begin();
         it != scores.end(); ++it) {
        std::cout << "  " << it->first << ": " << it->second << std::endl;
    }

    // Sorting pairs (lexicographic by default: by name then by score)
    std::sort(scores.begin(), scores.end());
    std::cout << "Sorted (by name):" << std::endl;
    for (std::vector<std::pair<std::string, int> >::iterator it = scores.begin();
         it != scores.end(); ++it) {
        std::cout << "  " << it->first << ": " << it->second << std::endl;
    }

    // --- Pair as return value ---
    std::cout << "\n=== Pair as function return pattern ===" << std::endl;
    // Common pattern: returning (success, value) or (min, max)
    std::pair<int, int> minmax = std::make_pair(10, 50);
    std::cout << "Min: " << minmax.first << ", Max: " << minmax.second << std::endl;

    return 0;
}

/*
Expected output:
=== Construction ===
p1: (Alice, 30)
p2 (default): (0, 0)
p3 (copy of p1): (Alice, 30)

=== make_pair ===
make_pair(42, 3.14): (42, 3.14)
make_pair strings: (hello, world)

=== first and second ===
first: 1
second: one
After modification: (2, two)

=== Assignment ===
a: (1, 2)
b: (3, 4)
After a = b: a=(3, 4)

=== Comparison operators ===
(1,2) == (1,2): true
(1,2) != (1,3): true
(1,2) < (1,3):  true
(1,2) < (2,1):  true
(2,1) > (1,3):  true
(1,2) <= (1,2): true
(1,3) >= (1,2): true

=== Nested pairs ===
Nested: (1, (2, 3))

=== Vector of pairs ===
Unsorted:
  Charlie: 85
  Alice: 95
  Bob: 90
Sorted (by name):
  Alice: 95
  Bob: 90
  Charlie: 85

=== Pair as function return pattern ===
Min: 10, Max: 50
*/
