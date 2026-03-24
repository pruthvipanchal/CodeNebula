// CodeNebula - C++20 Example: std::constructible_from Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example constructible_from.cpp

// std::constructible_from<T, Args...> checks whether T can be constructed
// from the given argument types. It combines destructible with
// is_constructible_v.

#include <concepts>
#include <iostream>
#include <string>
#include <vector>

struct Point {
    double x, y;
    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}
};

struct OnlyExplicit {
    int value;
    explicit OnlyExplicit(int v) : value(v) {}
    OnlyExplicit() = delete;  // No default construction
};

// Factory function constrained by constructible_from
template <typename T, typename... Args>
    requires std::constructible_from<T, Args...>
T make(Args&&... args) {
    return T(std::forward<Args>(args)...);
}

// Check constructibility
template <typename T, typename... Args>
void check_constructible(const char* desc) {
    std::cout << desc << ": "
              << std::constructible_from<T, Args...> << "\n";
}

int main() {
    // Make various types using the factory
    auto p1 = make<Point>();
    std::cout << "Point(): (" << p1.x << ", " << p1.y << ")\n";

    auto p2 = make<Point>(3.0, 4.0);
    std::cout << "Point(3,4): (" << p2.x << ", " << p2.y << ")\n";

    auto s = make<std::string>("hello");
    std::cout << "string(\"hello\"): " << s << "\n";

    auto s2 = make<std::string>(5, 'x');
    std::cout << "string(5,'x'): " << s2 << "\n";

    auto e = make<OnlyExplicit>(42);
    std::cout << "OnlyExplicit(42): " << e.value << "\n";

    // Constructibility checks
    std::cout << "\nConstructibility checks:\n";
    check_constructible<int>("int from nothing");
    check_constructible<int, int>("int from int");
    check_constructible<Point>("Point from nothing");
    check_constructible<Point, double, double>("Point from double,double");
    check_constructible<std::string, const char*>("string from const char*");
    check_constructible<std::string, int>("string from int");
    check_constructible<OnlyExplicit>("OnlyExplicit from nothing");
    check_constructible<OnlyExplicit, int>("OnlyExplicit from int");

    return 0;
}

// Expected output:
// Point(): (0, 0)
// Point(3,4): (3, 4)
// string("hello"): hello
// string(5,'x'): xxxxx
// OnlyExplicit(42): 42
//
// Constructibility checks:
// int from nothing: 1
// int from int: 1
// Point from nothing: 1
// Point from double,double: 1
// string from const char*: 1
// string from int: 0
// OnlyExplicit from nothing: 0
// OnlyExplicit from int: 1
