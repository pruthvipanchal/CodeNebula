// CodeNebula - C++11 Example: multimap (C++11 Features)
// Compile: g++ -std=c++11 -Wall -Wextra -o example multimap.cpp

// Demonstrates C++11-specific std::multimap features: initializer list,
// emplace, emplace_hint, and move semantics. Unlike map, multimap
// allows duplicate keys.

#include <iostream>
#include <map>
#include <string>

int main() {
    // Initializer list with duplicate keys (C++11)
    std::multimap<std::string, int> grades = {
        {"Alice", 90}, {"Bob", 85}, {"Alice", 95}, {"Bob", 78}
    };

    std::cout << "=== Initializer list ===\n";
    for (const auto& p : grades)
        std::cout << "  " << p.first << ": " << p.second << "\n";
    std::cout << "\n";

    // emplace: always inserts, returns iterator
    std::cout << "=== emplace ===\n";
    auto it = grades.emplace("Charlie", 88);
    std::cout << "emplace Charlie: " << it->first << "=" << it->second << "\n";
    grades.emplace("Alice", 92);  // third Alice entry
    std::cout << "count(Alice): " << grades.count("Alice") << "\n\n";

    // emplace_hint
    std::cout << "=== emplace_hint ===\n";
    auto hint = grades.lower_bound("Bob");
    grades.emplace_hint(hint, "Bob", 91);
    std::cout << "count(Bob): " << grades.count("Bob") << "\n\n";

    // equal_range: iterate all values for a key
    std::cout << "=== equal_range for Alice ===\n";
    auto range = grades.equal_range("Alice");
    for (auto ri = range.first; ri != range.second; ++ri)
        std::cout << "  " << ri->first << ": " << ri->second << "\n";
    std::cout << "\n";

    // Full contents after modifications
    std::cout << "=== All entries ===\n";
    for (const auto& p : grades)
        std::cout << "  " << p.first << ": " << p.second << "\n";
    std::cout << "\n";

    // Move semantics
    std::cout << "=== Move semantics ===\n";
    std::multimap<std::string, int> src = {{"x", 1}, {"x", 2}, {"y", 3}};
    std::cout << "src size before: " << src.size() << "\n";
    std::multimap<std::string, int> dst = std::move(src);
    std::cout << "dst size after:  " << dst.size() << "\n";
    std::cout << "src size after:  " << src.size() << "\n";

    return 0;
}

// Expected output:
// === Initializer list ===
//   Alice: 90
//   Alice: 95
//   Bob: 85
//   Bob: 78
//
// === emplace ===
// emplace Charlie: Charlie=88
// count(Alice): 3
//
// === emplace_hint ===
// count(Bob): 3
//
// === equal_range for Alice ===
//   Alice: 90
//   Alice: 95
//   Alice: 92
//
// === All entries ===
//   Alice: 90
//   Alice: 95
//   Alice: 92
//   Bob: 91
//   Bob: 85
//   Bob: 78
//   Charlie: 88
//
// === Move semantics ===
// src size before: 3
// dst size after:  3
// src size after:  0
