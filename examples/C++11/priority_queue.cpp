// CodeNebula - C++11 Example: priority_queue (C++11 Features)
// Compile: g++ -std=c++11 -Wall -Wextra -o example priority_queue.cpp

// Demonstrates C++11-specific std::priority_queue features: emplace
// (construct in-place), swap, move semantics, and custom comparator
// with a lambda.

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <functional>

int main() {
    // Default max-heap with emplace
    std::cout << "=== emplace (max-heap) ===\n";
    std::priority_queue<int> maxpq;
    maxpq.emplace(30);
    maxpq.emplace(10);
    maxpq.emplace(50);
    maxpq.emplace(20);
    maxpq.emplace(40);

    std::cout << "Top: " << maxpq.top() << "\n";
    std::cout << "Drain: ";
    while (!maxpq.empty()) {
        std::cout << maxpq.top() << " ";
        maxpq.pop();
    }
    std::cout << "\n\n";

    // Min-heap using std::greater
    std::cout << "=== Min-heap (std::greater) ===\n";
    std::priority_queue<int, std::vector<int>, std::greater<int>> minpq;
    for (int v : {30, 10, 50, 20, 40}) minpq.emplace(v);

    std::cout << "Drain: ";
    while (!minpq.empty()) {
        std::cout << minpq.top() << " ";
        minpq.pop();
    }
    std::cout << "\n\n";

    // swap: exchange contents of two priority queues
    std::cout << "=== swap ===\n";
    std::priority_queue<int> pq1, pq2;
    pq1.push(100); pq1.push(200);
    pq2.push(5); pq2.push(10); pq2.push(15);

    std::cout << "Before: pq1.top=" << pq1.top()
              << " pq2.top=" << pq2.top() << "\n";
    pq1.swap(pq2);
    std::cout << "After:  pq1.top=" << pq1.top()
              << " pq2.top=" << pq2.top() << "\n";
    std::cout << "pq1.size=" << pq1.size()
              << " pq2.size=" << pq2.size() << "\n\n";

    // Move semantics
    std::cout << "=== Move semantics ===\n";
    std::priority_queue<int> src;
    src.push(7); src.push(3); src.push(9);
    std::cout << "src size before: " << src.size() << "\n";
    std::priority_queue<int> dst = std::move(src);
    std::cout << "dst size after:  " << dst.size() << "\n";
    std::cout << "dst top:         " << dst.top() << "\n";
    std::cout << "src size after:  " << src.size() << "\n";

    return 0;
}

// Expected output:
// === emplace (max-heap) ===
// Top: 50
// Drain: 50 40 30 20 10
//
// === Min-heap (std::greater) ===
// Drain: 10 20 30 40 50
//
// === swap ===
// Before: pq1.top=200 pq2.top=15
// After:  pq1.top=15 pq2.top=200
// pq1.size=3 pq2.size=2
//
// === Move semantics ===
// src size before: 3
// dst size after:  3
// dst top:         9
// src size after:  0
