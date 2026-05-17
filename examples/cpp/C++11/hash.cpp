// CodeNebula - C++11 Example: hash
// Compile: g++ -std=c++11 -Wall -Wextra -o example hash.cpp

// Demonstrates std::hash specializations for standard types.
// std::hash is used by unordered containers (unordered_map, unordered_set).

#include <iostream>
#include <functional>
#include <string>
#include <typeinfo>

// Custom type with hash specialization
struct Point {
    int x, y;
};

namespace std {
    template<>
    struct hash<Point> {
        size_t operator()(const Point& p) const {
            // Combine hashes using a common technique
            size_t h1 = std::hash<int>{}(p.x);
            size_t h2 = std::hash<int>{}(p.y);
            return h1 ^ (h2 << 1);
        }
    };
}

int main() {
    std::cout << "=== std::hash ===" << std::endl;

    // Hash integers
    std::hash<int> int_hash;
    std::cout << "hash(42):      " << int_hash(42) << std::endl;
    std::cout << "hash(0):       " << int_hash(0) << std::endl;

    // Hash strings
    std::hash<std::string> str_hash;
    std::cout << "hash(\"hello\"): " << str_hash("hello") << std::endl;
    std::cout << "hash(\"world\"): " << str_hash("world") << std::endl;

    // Same value always produces same hash
    std::cout << "\nConsistency check:" << std::endl;
    std::cout << "hash(\"test\") == hash(\"test\"): "
              << (str_hash("test") == str_hash("test")) << std::endl;

    // Hash other types
    std::hash<double> dbl_hash;
    std::hash<bool> bool_hash;
    std::hash<char> char_hash;
    std::cout << "\nhash(3.14):    " << dbl_hash(3.14) << std::endl;
    std::cout << "hash(true):    " << bool_hash(true) << std::endl;
    std::cout << "hash('A'):     " << char_hash('A') << std::endl;

    // Custom type hash
    Point p1{10, 20};
    Point p2{20, 10};
    std::hash<Point> point_hash;
    std::cout << "\nhash(Point{10,20}): " << point_hash(p1) << std::endl;
    std::cout << "hash(Point{20,10}): " << point_hash(p2) << std::endl;

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output (hash values are implementation-defined):
// === std::hash ===
// hash(42):      42
// hash(0):       0
// hash("hello"): <some hash value>
// hash("world"): <some hash value>
//
// Consistency check:
// hash("test") == hash("test"): 1
//
// hash(3.14):    <some hash value>
// hash(true):    1
// hash('A'):     65
//
// hash(Point{10,20}): <some hash value>
// hash(Point{20,10}): <some hash value>
//
// All checks passed!
