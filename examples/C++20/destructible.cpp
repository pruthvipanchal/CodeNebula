// CodeNebula - C++20 Example: std::destructible Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example destructible.cpp

// std::destructible<T> is satisfied when T has a non-throwing destructor.
// Most types are destructible; reference types and void are not, nor are
// types with deleted or throwing noexcept(false) destructors.

#include <concepts>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// A type with a custom destructor that logs
struct Tracked {
    int id;
    Tracked(int i) : id(i) {
        std::cout << "  Tracked(" << id << ") constructed\n";
    }
    ~Tracked() {
        std::cout << "  Tracked(" << id << ") destroyed\n";
    }
};

// A type with a deleted destructor (not destructible)
struct Immortal {
    ~Immortal() = delete;
};

// Factory that only creates destructible types
template <std::destructible T, typename... Args>
std::unique_ptr<T> safe_create(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

// Check destructibility
template <typename T>
void check_destructible(const char* name) {
    std::cout << name << " is destructible: " << std::destructible<T> << "\n";
}

int main() {
    // Create tracked objects via factory
    std::cout << "Creating tracked objects:\n";
    {
        auto t1 = safe_create<Tracked>(1);
        auto t2 = safe_create<Tracked>(2);
        std::cout << "  Leaving scope...\n";
    }
    std::cout << "  Objects destroyed\n";

    // Create standard types
    auto str = safe_create<std::string>("hello");
    std::cout << "\nCreated string: " << *str << "\n";

    // Destructibility checks
    std::cout << "\nDestructibility checks:\n";
    check_destructible<int>("int");
    check_destructible<std::string>("string");
    check_destructible<std::vector<int>>("vector<int>");
    check_destructible<Tracked>("Tracked");
    check_destructible<Immortal>("Immortal");
    check_destructible<void>("void");

    // safe_create<Immortal>();  // Compile error: not destructible

    return 0;
}

// Expected output:
// Creating tracked objects:
//   Tracked(1) constructed
//   Tracked(2) constructed
//   Leaving scope...
//   Tracked(2) destroyed
//   Tracked(1) destroyed
//   Objects destroyed
//
// Created string: hello
//
// Destructibility checks:
// int is destructible: 1
// string is destructible: 1
// vector<int> is destructible: 1
// Tracked is destructible: 1
// Immortal is destructible: 0
// void is destructible: 0
