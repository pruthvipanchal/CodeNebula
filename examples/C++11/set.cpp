// CodeNebula - C++11 Example: set (C++11 Features)
// Compile: g++ -std=c++11 -Wall -Wextra -o example set.cpp

// Demonstrates C++11-specific std::set features: initializer list,
// emplace, emplace_hint, and move semantics.

#include <iostream>
#include <set>
#include <string>

int main() {
    // Initializer list construction (C++11)
    std::set<int> nums = {50, 10, 30, 20, 40, 30};  // duplicates ignored
    std::cout << "=== Initializer list ===\n";
    for (const auto& n : nums) std::cout << n << " ";
    std::cout << "\n(size: " << nums.size() << ")\n\n";

    // emplace: construct element in-place, returns pair<iterator, bool>
    std::cout << "=== emplace ===\n";
    auto result1 = nums.emplace(25);
    std::cout << "emplace(25): inserted=" << std::boolalpha
              << result1.second << ", value=" << *result1.first << "\n";

    auto result2 = nums.emplace(30);  // already exists
    std::cout << "emplace(30): inserted=" << result2.second
              << ", value=" << *result2.first << "\n\n";

    // emplace_hint: provide a hint iterator for faster insertion
    std::cout << "=== emplace_hint ===\n";
    auto hint = nums.find(40);
    nums.emplace_hint(hint, 35);  // hint near correct position
    for (const auto& n : nums) std::cout << n << " ";
    std::cout << "\n\n";

    // emplace with complex types (string set)
    std::cout << "=== String set with emplace ===\n";
    std::set<std::string> words = {"hello", "world"};
    words.emplace("foo");
    words.emplace("bar");
    words.emplace("hello");  // duplicate, not inserted
    for (const auto& w : words) std::cout << w << " ";
    std::cout << "\n\n";

    // Move semantics
    std::cout << "=== Move semantics ===\n";
    std::set<int> src = {1, 2, 3, 4, 5};
    std::cout << "src size before: " << src.size() << "\n";
    std::set<int> dst = std::move(src);
    std::cout << "dst size after:  " << dst.size() << "\n";
    std::cout << "src size after:  " << src.size() << "\n";

    // count and find with auto (C++11 style)
    std::cout << "\n=== find / count ===\n";
    auto it = dst.find(3);
    if (it != dst.end())
        std::cout << "Found: " << *it << "\n";
    std::cout << "count(3): " << dst.count(3) << "\n";
    std::cout << "count(9): " << dst.count(9) << "\n";

    return 0;
}

// Expected output:
// === Initializer list ===
// 10 20 30 40 50
// (size: 5)
//
// === emplace ===
// emplace(25): inserted=true, value=25
// emplace(30): inserted=false, value=30
//
// === emplace_hint ===
// 10 20 25 30 35 40 50
//
// === String set with emplace ===
// bar foo hello world
//
// === Move semantics ===
// src size before: 5
// dst size after:  5
// src size after:  0
//
// === find / count ===
// Found: 3
// count(3): 1
// count(9): 0
