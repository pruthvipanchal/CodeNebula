// CodeNebula - C++11 Example: stack (C++11 Features)
// Compile: g++ -std=c++11 -Wall -Wextra -o example stack.cpp

// Demonstrates C++11-specific std::stack features: emplace (construct
// in-place on top), swap, and move semantics.

#include <iostream>
#include <stack>
#include <string>
#include <utility>

int main() {
    // emplace: construct element directly on top of the stack
    std::cout << "=== emplace ===\n";
    std::stack<std::pair<std::string, int>> tasks;
    tasks.emplace("Write code", 1);
    tasks.emplace("Run tests", 2);
    tasks.emplace("Deploy", 3);

    std::cout << "Top: (" << tasks.top().first << ", "
              << tasks.top().second << ")\n";
    std::cout << "Size: " << tasks.size() << "\n\n";

    // Pop and display all elements (LIFO order)
    std::cout << "=== Pop all (LIFO) ===\n";
    while (!tasks.empty()) {
        auto& t = tasks.top();
        std::cout << "  (" << t.first << ", " << t.second << ")\n";
        tasks.pop();
    }
    std::cout << "\n";

    // swap: exchange contents of two stacks
    std::cout << "=== swap ===\n";
    std::stack<int> s1, s2;
    s1.push(10); s1.push(20); s1.push(30);
    s2.push(100); s2.push(200);

    std::cout << "Before swap: s1.top=" << s1.top()
              << " s2.top=" << s2.top() << "\n";
    s1.swap(s2);
    std::cout << "After swap:  s1.top=" << s1.top()
              << " s2.top=" << s2.top() << "\n";
    std::cout << "s1.size=" << s1.size()
              << " s2.size=" << s2.size() << "\n\n";

    // Move semantics
    std::cout << "=== Move semantics ===\n";
    std::stack<int> src;
    src.push(1); src.push(2); src.push(3);
    std::cout << "src size before: " << src.size() << "\n";
    std::stack<int> dst = std::move(src);
    std::cout << "dst size after:  " << dst.size() << "\n";
    std::cout << "dst top:         " << dst.top() << "\n";
    std::cout << "src size after:  " << src.size() << "\n";

    return 0;
}

// Expected output:
// === emplace ===
// Top: (Deploy, 3)
// Size: 3
//
// === Pop all (LIFO) ===
//   (Deploy, 3)
//   (Run tests, 2)
//   (Write code, 1)
//
// === swap ===
// Before swap: s1.top=30 s2.top=200
// After swap:  s1.top=200 s2.top=30
// s1.size=2 s2.size=3
//
// === Move semantics ===
// src size before: 3
// dst size after:  3
// dst top:         3
// src size after:  0
