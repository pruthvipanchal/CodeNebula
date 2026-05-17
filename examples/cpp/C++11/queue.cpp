// CodeNebula - C++11 Example: queue (C++11 Features)
// Compile: g++ -std=c++11 -Wall -Wextra -o example queue.cpp

// Demonstrates C++11-specific std::queue features: emplace (construct
// in-place at back), swap, and move semantics.

#include <iostream>
#include <queue>
#include <string>
#include <utility>

int main() {
    // emplace: construct element directly at the back
    std::cout << "=== emplace ===\n";
    std::queue<std::pair<std::string, int>> jobs;
    jobs.emplace("Print report", 1);
    jobs.emplace("Send email", 2);
    jobs.emplace("Backup data", 3);

    std::cout << "Front: (" << jobs.front().first << ", "
              << jobs.front().second << ")\n";
    std::cout << "Back:  (" << jobs.back().first << ", "
              << jobs.back().second << ")\n";
    std::cout << "Size:  " << jobs.size() << "\n\n";

    // Process all elements (FIFO order)
    std::cout << "=== Process all (FIFO) ===\n";
    while (!jobs.empty()) {
        auto& j = jobs.front();
        std::cout << "  (" << j.first << ", " << j.second << ")\n";
        jobs.pop();
    }
    std::cout << "\n";

    // swap: exchange contents of two queues
    std::cout << "=== swap ===\n";
    std::queue<int> q1, q2;
    q1.push(10); q1.push(20); q1.push(30);
    q2.push(100); q2.push(200);

    std::cout << "Before: q1.front=" << q1.front()
              << " q2.front=" << q2.front() << "\n";
    q1.swap(q2);
    std::cout << "After:  q1.front=" << q1.front()
              << " q2.front=" << q2.front() << "\n";
    std::cout << "q1.size=" << q1.size()
              << " q2.size=" << q2.size() << "\n\n";

    // Move semantics
    std::cout << "=== Move semantics ===\n";
    std::queue<int> src;
    src.push(1); src.push(2); src.push(3);
    std::cout << "src size before: " << src.size() << "\n";
    std::queue<int> dst = std::move(src);
    std::cout << "dst size after:  " << dst.size() << "\n";
    std::cout << "dst front:       " << dst.front() << "\n";
    std::cout << "src size after:  " << src.size() << "\n";

    return 0;
}

// Expected output:
// === emplace ===
// Front: (Print report, 1)
// Back:  (Backup data, 3)
// Size:  3
//
// === Process all (FIFO) ===
//   (Print report, 1)
//   (Send email, 2)
//   (Backup data, 3)
//
// === swap ===
// Before: q1.front=10 q2.front=100
// After:  q1.front=100 q2.front=10
// q1.size=2 q2.size=3
//
// === Move semantics ===
// src size before: 3
// dst size after:  3
// dst front:       1
// src size after:  0
