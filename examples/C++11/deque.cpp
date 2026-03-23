// CodeNebula - C++11 Example: deque (C++11 Features)
// Compile: g++ -std=c++11 -Wall -Wextra -o example deque.cpp

// Demonstrates C++11-specific std::deque features: initializer list,
// emplace_front, emplace_back, shrink_to_fit, and move semantics.

#include <iostream>
#include <deque>
#include <string>

int main() {
    // Initializer list construction (C++11)
    std::deque<int> dq = {10, 20, 30, 40, 50};
    std::cout << "=== Initializer list ===\n";
    for (const auto& v : dq) std::cout << v << " ";
    std::cout << "\n\n";

    // emplace_front and emplace_back: construct in-place
    std::cout << "=== emplace_front / emplace_back ===\n";
    std::deque<std::string> names;
    names.emplace_back("Charlie");
    names.emplace_back("Diana");
    names.emplace_front("Bob");
    names.emplace_front("Alice");
    for (const auto& n : names) std::cout << n << " ";
    std::cout << "\n\n";

    // emplace: construct at arbitrary position
    std::cout << "=== emplace at position ===\n";
    auto it = names.begin() + 2;  // before "Charlie"
    names.emplace(it, "Brenda");
    for (const auto& n : names) std::cout << n << " ";
    std::cout << "\n\n";

    // shrink_to_fit: request to reduce memory usage
    std::cout << "=== shrink_to_fit ===\n";
    std::deque<int> big;
    for (int i = 0; i < 1000; ++i) big.push_back(i);
    big.clear();
    std::cout << "Size after clear: " << big.size() << "\n";
    big.shrink_to_fit();
    std::cout << "shrink_to_fit called\n\n";

    // Move semantics
    std::cout << "=== Move semantics ===\n";
    std::deque<int> src = {1, 2, 3, 4, 5};
    std::cout << "src size before: " << src.size() << "\n";
    std::deque<int> dst = std::move(src);
    std::cout << "dst size after:  " << dst.size() << "\n";
    std::cout << "src size after:  " << src.size() << "\n";

    // Range-based for with auto (C++11)
    std::cout << "\ndst contents: ";
    for (auto val : dst) std::cout << val << " ";
    std::cout << "\n";

    return 0;
}

// Expected output:
// === Initializer list ===
// 10 20 30 40 50
//
// === emplace_front / emplace_back ===
// Alice Bob Charlie Diana
//
// === emplace at position ===
// Alice Bob Brenda Charlie Diana
//
// === shrink_to_fit ===
// Size after clear: 0
// shrink_to_fit called
//
// === Move semantics ===
// src size before: 5
// dst size after:  5
// src size after:  0
//
// dst contents: 1 2 3 4 5
