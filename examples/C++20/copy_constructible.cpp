// CodeNebula - C++20 Example: std::copy_constructible Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example copy_constructible.cpp

// std::copy_constructible<T> is satisfied when T can be constructed from
// both lvalue and rvalue references, and from const references. This is
// stronger than move_constructible: all copy_constructible types are also
// move_constructible.

#include <concepts>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// A copyable value type
struct Color {
    int r, g, b;
    Color(int r, int g, int b) : r(r), g(g), b(b) {}
};

std::ostream& operator<<(std::ostream& os, const Color& c) {
    return os << "(" << c.r << "," << c.g << "," << c.b << ")";
}

// Clone function: only works with copy_constructible types
template <std::copy_constructible T>
T clone(const T& original) {
    return T(original);  // explicit copy
}

// Broadcast: fill a vector with copies of a value
template <std::copy_constructible T>
std::vector<T> broadcast(const T& value, std::size_t count) {
    return std::vector<T>(count, value);
}

template <typename T>
void check_copy(const char* name) {
    std::cout << name << " - copy: " << std::copy_constructible<T>
              << ", move: " << std::move_constructible<T> << "\n";
}

int main() {
    // Clone values
    Color red(255, 0, 0);
    auto red_copy = clone(red);
    std::cout << "Original: " << red << "\n";
    std::cout << "Clone:    " << red_copy << "\n";

    auto s = clone(std::string("hello"));
    std::cout << "Cloned string: " << s << "\n";

    // Broadcast
    auto colors = broadcast(Color(0, 128, 255), 3);
    std::cout << "\nBroadcast colors: ";
    for (const auto& c : colors) std::cout << c << " ";
    std::cout << "\n";

    auto nums = broadcast(42, 4);
    std::cout << "Broadcast ints: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << "\n";

    // Concept checks: copy vs move constructible
    std::cout << "\nConstructibility checks:\n";
    check_copy<int>("int");
    check_copy<std::string>("string");
    check_copy<Color>("Color");
    check_copy<std::vector<int>>("vector<int>");
    check_copy<std::unique_ptr<int>>("unique_ptr<int>");

    return 0;
}

// Expected output:
// Original: (255,0,0)
// Clone:    (255,0,0)
// Cloned string: hello
//
// Broadcast colors: (0,128,255) (0,128,255) (0,128,255)
// Broadcast ints: 42 42 42 42
//
// Constructibility checks:
// int - copy: 1, move: 1
// string - copy: 1, move: 1
// Color - copy: 1, move: 1
// vector<int> - copy: 1, move: 1
// unique_ptr<int> - copy: 0, move: 1
