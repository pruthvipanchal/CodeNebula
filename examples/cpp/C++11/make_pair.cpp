// CodeNebula - C++11 Example: std::make_pair (move-aware)
// Compile: g++ -std=c++11 -Wall -Wextra -o example make_pair.cpp

// In C++11, std::make_pair deduces types and supports move semantics.
// It no longer requires explicit template arguments and handles
// rvalue references efficiently, avoiding unnecessary copies.

#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <memory>

int main() {
    // Basic type deduction
    auto p1 = std::make_pair(42, 3.14);
    std::cout << "p1: {" << p1.first << ", " << p1.second << "}" << std::endl;

    // String type deduction
    auto p2 = std::make_pair(std::string("hello"), std::string("world"));
    std::cout << "p2: {" << p2.first << ", " << p2.second << "}" << std::endl;

    // Move semantics: move a string into the pair
    std::string name = "Alice";
    auto p3 = std::make_pair(1, std::move(name));
    std::cout << "p3: {" << p3.first << ", " << p3.second << "}" << std::endl;
    std::cout << "name after move: \"" << name << "\" (empty)" << std::endl;

    // Move-only types (unique_ptr)
    auto p4 = std::make_pair(
        std::make_unique<int>(100),
        std::make_unique<int>(200)
    );
    std::cout << "p4: {" << *p4.first << ", " << *p4.second << "}" << std::endl;

    // Pairs of different types
    auto p5 = std::make_pair('A', std::vector<int>{1, 2, 3});
    std::cout << "p5: {" << p5.first << ", [";
    for (size_t i = 0; i < p5.second.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << p5.second[i];
    }
    std::cout << "]}" << std::endl;

    // Nested pairs
    auto nested = std::make_pair(
        std::make_pair(1, 2),
        std::make_pair(3, 4)
    );
    std::cout << "nested: {{" << nested.first.first << ", "
              << nested.first.second << "}, {"
              << nested.second.first << ", "
              << nested.second.second << "}}" << std::endl;

    // Comparison operators work automatically
    auto a = std::make_pair(1, 10);
    auto b = std::make_pair(1, 20);
    auto c = std::make_pair(2, 5);
    std::cout << "\nComparisons:" << std::endl;
    std::cout << "(1,10) < (1,20): " << (a < b ? "true" : "false") << std::endl;
    std::cout << "(1,20) < (2,5):  " << (b < c ? "true" : "false") << std::endl;
    std::cout << "(1,10) == (1,10): " << (a == a ? "true" : "false") << std::endl;

    // Swap pairs
    auto s1 = std::make_pair(1, std::string("first"));
    auto s2 = std::make_pair(2, std::string("second"));
    s1.swap(s2);
    std::cout << "\nAfter swap: s1={" << s1.first << ", " << s1.second
              << "} s2={" << s2.first << ", " << s2.second << "}" << std::endl;

    return 0;
}

// Expected output:
// p1: {42, 3.14}
// p2: {hello, world}
// p3: {1, Alice}
// name after move: "" (empty)
// p4: {100, 200}
// p5: {A, [1, 2, 3]}
// nested: {{1, 2}, {3, 4}}
//
// Comparisons:
// (1,10) < (1,20): true
// (1,20) < (2,5):  true
// (1,10) == (1,10): true
//
// After swap: s1={2, second} s2={1, first}
