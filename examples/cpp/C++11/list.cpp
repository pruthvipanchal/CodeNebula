// CodeNebula - C++11 Example: list (C++11 Features)
// Compile: g++ -std=c++11 -Wall -Wextra -o example list.cpp

// Demonstrates C++11-specific std::list features: initializer list,
// emplace, emplace_front/back, sort with lambda, and move semantics.

#include <iostream>
#include <list>
#include <string>

struct Task {
    std::string name;
    int priority;
    Task(std::string n, int p) : name(std::move(n)), priority(p) {}
};

void print_tasks(const std::list<Task>& tasks) {
    for (const auto& t : tasks)
        std::cout << "  [" << t.priority << "] " << t.name << "\n";
}

int main() {
    // Initializer list construction (C++11)
    std::list<int> nums = {5, 3, 1, 4, 2};
    std::cout << "=== Initializer list ===\n";
    for (const auto& n : nums) std::cout << n << " ";
    std::cout << "\n\n";

    // emplace_front / emplace_back: construct in-place
    std::cout << "=== emplace_front / emplace_back ===\n";
    std::list<Task> tasks;
    tasks.emplace_back("Write code", 2);
    tasks.emplace_back("Run tests", 3);
    tasks.emplace_front("Plan design", 1);
    print_tasks(tasks);
    std::cout << "\n";

    // emplace: insert in-place at a position
    std::cout << "=== emplace at position ===\n";
    auto it = tasks.begin();
    std::advance(it, 2);  // point to "Run tests"
    tasks.emplace(it, "Code review", 2);
    print_tasks(tasks);
    std::cout << "\n";

    // sort with lambda (C++11 lambda)
    std::cout << "=== Sort by priority (lambda) ===\n";
    tasks.sort([](const Task& a, const Task& b) {
        return a.priority < b.priority;
    });
    print_tasks(tasks);
    std::cout << "\n";

    // Sort descending
    std::cout << "=== Sort descending ===\n";
    tasks.sort([](const Task& a, const Task& b) {
        return a.priority > b.priority;
    });
    print_tasks(tasks);
    std::cout << "\n";

    // Move semantics
    std::cout << "=== Move semantics ===\n";
    std::list<Task> moved = std::move(tasks);
    std::cout << "Original size: " << tasks.size() << "\n";
    std::cout << "Moved size:    " << moved.size() << "\n";

    return 0;
}

// Expected output:
// === Initializer list ===
// 5 3 1 4 2
//
// === emplace_front / emplace_back ===
//   [1] Plan design
//   [2] Write code
//   [3] Run tests
//
// === emplace at position ===
//   [1] Plan design
//   [2] Write code
//   [2] Code review
//   [3] Run tests
//
// === Sort by priority (lambda) ===
//   [1] Plan design
//   [2] Write code
//   [2] Code review
//   [3] Run tests
//
// === Sort descending ===
//   [3] Run tests
//   [2] Write code
//   [2] Code review
//   [1] Plan design
//
// === Move semantics ===
// Original size: 0
// Moved size:    4
