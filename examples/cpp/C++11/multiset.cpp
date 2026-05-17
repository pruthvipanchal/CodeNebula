// CodeNebula - C++11 Example: multiset (C++11 Features)
// Compile: g++ -std=c++11 -Wall -Wextra -o example multiset.cpp

// Demonstrates C++11-specific std::multiset features: initializer list,
// emplace, emplace_hint, and move semantics. Unlike set, multiset
// allows duplicate elements.

#include <iostream>
#include <set>
#include <string>

int main() {
    // Initializer list with duplicates (C++11)
    std::multiset<int> ms = {30, 10, 20, 30, 10, 40, 30};
    std::cout << "=== Initializer list (duplicates allowed) ===\n";
    for (const auto& v : ms) std::cout << v << " ";
    std::cout << "\n(size: " << ms.size() << ")\n\n";

    // emplace: always inserts (duplicates OK), returns iterator
    std::cout << "=== emplace ===\n";
    auto it1 = ms.emplace(25);
    std::cout << "emplace(25): *it = " << *it1 << "\n";
    auto it2 = ms.emplace(30);  // fourth 30
    std::cout << "emplace(30): *it = " << *it2 << "\n";
    std::cout << "count(30): " << ms.count(30) << "\n\n";

    // emplace_hint: hint for insertion position
    std::cout << "=== emplace_hint ===\n";
    auto hint = ms.lower_bound(35);
    ms.emplace_hint(hint, 35);
    ms.emplace_hint(hint, 35);  // second 35
    for (const auto& v : ms) std::cout << v << " ";
    std::cout << "\n\n";

    // equal_range: find all elements with a given value
    std::cout << "=== equal_range for 30 ===\n";
    auto range = ms.equal_range(30);
    std::cout << "Elements equal to 30: ";
    for (auto it = range.first; it != range.second; ++it)
        std::cout << *it << " ";
    std::cout << "(count: " << ms.count(30) << ")\n\n";

    // String multiset with emplace
    std::cout << "=== String multiset ===\n";
    std::multiset<std::string> words;
    words.emplace("apple");
    words.emplace("banana");
    words.emplace("apple");   // duplicate OK
    words.emplace("cherry");
    words.emplace("banana");  // duplicate OK
    for (const auto& w : words) std::cout << w << " ";
    std::cout << "\n\n";

    // Move semantics
    std::cout << "=== Move semantics ===\n";
    std::multiset<int> src = {1, 1, 2, 3, 3};
    std::cout << "src size before: " << src.size() << "\n";
    std::multiset<int> dst = std::move(src);
    std::cout << "dst size after:  " << dst.size() << "\n";
    std::cout << "src size after:  " << src.size() << "\n";

    return 0;
}

// Expected output:
// === Initializer list (duplicates allowed) ===
// 10 10 20 30 30 30 40
// (size: 7)
//
// === emplace ===
// emplace(25): *it = 25
// emplace(30): *it = 30
// count(30): 4
//
// === emplace_hint ===
// 10 10 20 25 30 30 30 30 35 35 40
//
// === equal_range for 30 ===
// Elements equal to 30: 30 30 30 30 (count: 4)
//
// === String multiset ===
// apple apple banana banana cherry
//
// === Move semantics ===
// src size before: 5
// dst size after:  5
// src size after:  0
