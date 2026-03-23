// CodeNebula - C++11 Example: map (C++11 Features)
// Compile: g++ -std=c++11 -Wall -Wextra -o example map.cpp

// Demonstrates C++11-specific std::map features: initializer list,
// emplace, at() with bounds checking, and move semantics.

#include <iostream>
#include <map>
#include <string>
#include <stdexcept>

int main() {
    // Initializer list construction (C++11)
    std::map<std::string, int> scores = {
        {"Alice", 95}, {"Bob", 87}, {"Charlie", 92}
    };

    std::cout << "=== Initializer list ===\n";
    for (const auto& p : scores)
        std::cout << "  " << p.first << ": " << p.second << "\n";
    std::cout << "\n";

    // emplace: construct key-value pair in-place
    std::cout << "=== emplace ===\n";
    auto r1 = scores.emplace("Diana", 88);
    std::cout << "emplace Diana: inserted=" << std::boolalpha
              << r1.second << "\n";

    auto r2 = scores.emplace("Alice", 100);  // key exists, not inserted
    std::cout << "emplace Alice: inserted=" << r2.second
              << " (value stays " << r2.first->second << ")\n\n";

    // emplace_hint
    std::cout << "=== emplace_hint ===\n";
    auto hint = scores.find("Charlie");
    scores.emplace_hint(hint, "Calvin", 79);
    for (const auto& p : scores)
        std::cout << "  " << p.first << ": " << p.second << "\n";
    std::cout << "\n";

    // at(): bounds-checked access (throws std::out_of_range)
    std::cout << "=== at() ===\n";
    std::cout << "Bob's score: " << scores.at("Bob") << "\n";
    try {
        scores.at("Eve");
    } catch (const std::out_of_range& e) {
        std::cout << "at(\"Eve\"): out_of_range caught\n";
    }
    std::cout << "\n";

    // Move semantics
    std::cout << "=== Move semantics ===\n";
    std::map<std::string, int> src = {{"x", 1}, {"y", 2}};
    std::cout << "src size before: " << src.size() << "\n";
    std::map<std::string, int> dst = std::move(src);
    std::cout << "dst size after:  " << dst.size() << "\n";
    std::cout << "src size after:  " << src.size() << "\n";

    return 0;
}

// Expected output:
// === Initializer list ===
//   Alice: 95
//   Bob: 87
//   Charlie: 92
//
// === emplace ===
// emplace Diana: inserted=true
// emplace Alice: inserted=false (value stays 95)
//
// === emplace_hint ===
//   Alice: 95
//   Bob: 87
//   Calvin: 79
//   Charlie: 92
//   Diana: 88
//
// === at() ===
// Bob's score: 87
// at("Eve"): out_of_range caught
//
// === Move semantics ===
// src size before: 2
// dst size after:  2
// src size after:  0
