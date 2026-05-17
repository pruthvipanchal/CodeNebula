// CodeNebula - C++11 Example: aligned_union
// Compile: g++ -std=c++11 -Wall -Wextra -o example aligned_union.cpp

// Demonstrates std::aligned_union to create storage large enough and
// properly aligned for any of the specified types. Useful for type-safe
// unions and variant implementations.

#include <iostream>
#include <type_traits>
#include <new>
#include <string>
#include <cstring>

struct Point { double x, y, z; };

int main() {
    std::cout << "=== std::aligned_union ===" << std::endl;

    // aligned_union provides storage for the largest of the given types
    using Storage = std::aligned_union<0, int, double, Point>::type;

    std::cout << "sizeof(int):     " << sizeof(int) << std::endl;
    std::cout << "sizeof(double):  " << sizeof(double) << std::endl;
    std::cout << "sizeof(Point):   " << sizeof(Point) << std::endl;
    std::cout << "sizeof(Storage): " << sizeof(Storage) << std::endl;
    std::cout << "alignof(Storage):" << alignof(Storage) << std::endl;

    // Storage is large enough for any of the types
    static_assert(sizeof(Storage) >= sizeof(int), "fits int");
    static_assert(sizeof(Storage) >= sizeof(double), "fits double");
    static_assert(sizeof(Storage) >= sizeof(Point), "fits Point");

    // Use the storage to hold different types
    Storage store;

    // Store an int
    new (&store) int(42);
    std::cout << "\nStored int:    " << *reinterpret_cast<int*>(&store) << std::endl;

    // Store a double (reuse same storage)
    new (&store) double(3.14159);
    std::cout << "Stored double: " << *reinterpret_cast<double*>(&store) << std::endl;

    // Store a Point
    new (&store) Point{1.0, 2.0, 3.0};
    Point* p = reinterpret_cast<Point*>(&store);
    std::cout << "Stored Point:  (" << p->x << ", " << p->y << ", " << p->z << ")"
              << std::endl;

    // The first template parameter is minimum size (0 means auto)
    using Big = std::aligned_union<128, int, double>::type;
    std::cout << "\naligned_union<128,...> size: " << sizeof(Big)
              << " (at least 128)" << std::endl;
    static_assert(sizeof(Big) >= 128, "respects minimum size");

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::aligned_union ===
// sizeof(int):     4
// sizeof(double):  8
// sizeof(Point):   24
// sizeof(Storage): 24
// alignof(Storage):8
//
// Stored int:    42
// Stored double: 3.14159
// Stored Point:  (1, 2, 3)
//
// aligned_union<128,...> size: 128 (at least 128)
//
// All checks passed!
