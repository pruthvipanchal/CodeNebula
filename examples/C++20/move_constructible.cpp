// CodeNebula - C++20 Example: std::move_constructible Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example move_constructible.cpp

// std::move_constructible<T> is satisfied when T can be constructed from
// an rvalue of type T. Most types satisfy this; types with deleted move
// and copy constructors do not.

#include <concepts>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// A move-only resource type
struct UniqueBuffer {
    std::unique_ptr<int[]> data;
    std::size_t size;

    UniqueBuffer(std::size_t n) : data(std::make_unique<int[]>(n)), size(n) {
        for (std::size_t i = 0; i < n; ++i) data[i] = static_cast<int>(i);
    }
    // Move constructor enabled, copy deleted (via unique_ptr)
};

// Not move constructible
struct Pinned {
    int value = 42;
    Pinned() = default;
    Pinned(Pinned&&) = delete;
    Pinned(const Pinned&) = delete;
};

// Transfer ownership of a move-constructible resource
template <std::move_constructible T>
T take_ownership(T&& resource) {
    std::cout << "  Ownership transferred\n";
    return std::move(resource);
}

// Collect items into a vector (requires move_constructible)
template <std::move_constructible T>
std::vector<T> collect(T&& first, T&& second) {
    std::vector<T> result;
    result.push_back(std::move(first));
    result.push_back(std::move(second));
    return result;
}

template <typename T>
void check_move(const char* name) {
    std::cout << name << ": " << std::move_constructible<T> << "\n";
}

int main() {
    // Transfer string ownership
    std::string s = "hello";
    std::cout << "Moving string:\n";
    auto s2 = take_ownership(std::move(s));
    std::cout << "  Result: " << s2 << "\n";

    // Transfer unique_ptr ownership
    std::cout << "Moving unique_ptr:\n";
    auto p = std::make_unique<int>(99);
    auto p2 = take_ownership(std::move(p));
    std::cout << "  Value: " << *p2 << "\n";

    // Collect items
    auto items = collect(std::string("foo"), std::string("bar"));
    std::cout << "Collected: " << items[0] << ", " << items[1] << "\n";

    // Concept checks
    std::cout << "\nMove constructible checks:\n";
    check_move<int>("int");
    check_move<std::string>("string");
    check_move<std::unique_ptr<int>>("unique_ptr<int>");
    check_move<UniqueBuffer>("UniqueBuffer");
    check_move<Pinned>("Pinned");

    return 0;
}

// Expected output:
// Moving string:
//   Ownership transferred
//   Result: hello
// Moving unique_ptr:
//   Ownership transferred
//   Value: 99
// Collected: foo, bar
//
// Move constructible checks:
// int: 1
// string: 1
// unique_ptr<int>: 1
// UniqueBuffer: 1
// Pinned: 0
