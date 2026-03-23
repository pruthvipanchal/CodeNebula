// CodeNebula - C++11 Example: vector (C++11 Features)
// Compile: g++ -std=c++11 -Wall -Wextra -o example vector.cpp

// Demonstrates C++11-specific std::vector features: initializer list
// construction, emplace_back, shrink_to_fit, data(), and move semantics.

#include <iostream>
#include <vector>
#include <string>

struct Widget {
    std::string name;
    int value;
    Widget(std::string n, int v) : name(std::move(n)), value(v) {
        std::cout << "  Constructed: " << name << "\n";
    }
};

int main() {
    // Initializer list construction (C++11)
    std::vector<int> nums = {10, 20, 30, 40, 50};
    std::cout << "=== Initializer list ===\n";
    for (const auto& n : nums) std::cout << n << " ";
    std::cout << "\n\n";

    // emplace_back: construct in-place (avoids copy/move)
    std::cout << "=== emplace_back vs push_back ===\n";
    std::vector<Widget> widgets;
    widgets.reserve(3);
    std::cout << "emplace_back:\n";
    widgets.emplace_back("Alpha", 1);   // constructs directly in vector
    widgets.emplace_back("Beta", 2);

    std::cout << "push_back (move):\n";
    widgets.push_back(Widget("Gamma", 3));  // construct + move
    std::cout << "\n";

    // data(): direct pointer access to underlying array
    std::cout << "=== data() pointer ===\n";
    int* ptr = nums.data();
    std::cout << "First element via data(): " << ptr[0] << "\n";
    std::cout << "Third element via data(): " << ptr[2] << "\n\n";

    // shrink_to_fit: request to reduce capacity to size
    std::cout << "=== shrink_to_fit ===\n";
    std::vector<int> v;
    v.reserve(100);
    v = {1, 2, 3};
    std::cout << "Before: size=" << v.size()
              << " capacity=" << v.capacity() << "\n";
    v.shrink_to_fit();
    std::cout << "After:  size=" << v.size()
              << " capacity=" << v.capacity() << "\n\n";

    // Move semantics: steal contents from another vector
    std::cout << "=== Move semantics ===\n";
    std::vector<int> src = {100, 200, 300};
    std::cout << "src size before move: " << src.size() << "\n";
    std::vector<int> dst = std::move(src);
    std::cout << "dst size after move:  " << dst.size() << "\n";
    std::cout << "src size after move:  " << src.size() << "\n";

    return 0;
}

// Expected output:
// === Initializer list ===
// 10 20 30 40 50
//
// === emplace_back vs push_back ===
// emplace_back:
//   Constructed: Alpha
//   Constructed: Beta
// push_back (move):
//   Constructed: Gamma
//
// === data() pointer ===
// First element via data(): 10
// Third element via data(): 30
//
// === shrink_to_fit ===
// Before: size=3 capacity=100
// After:  size=3 capacity=3
//
// === Move semantics ===
// src size before move: 3
// dst size after move:  3
// src size after move:  0
