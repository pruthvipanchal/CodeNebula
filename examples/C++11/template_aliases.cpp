// CodeNebula - C++11 Example: Template Aliases (using =)
// Compile: g++ -std=c++11 -Wall -Wextra -o example template_aliases.cpp

// Demonstrates 'using' for template aliases, replacing verbose typedef syntax.
// Template aliases can be partially specialized (unlike typedef), making them
// essential for simplifying complex type expressions in generic code.

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <functional>

// ------------------------------------------------------------------
// 1. Simple type alias (replaces typedef)
// ------------------------------------------------------------------
// Old: typedef unsigned long ulong;
using ulong = unsigned long;
using StringVec = std::vector<std::string>;

// ------------------------------------------------------------------
// 2. Template alias (impossible with typedef!)
// ------------------------------------------------------------------
template <typename T>
using Vec = std::vector<T>;

template <typename V>
using StringMap = std::map<std::string, V>;

template <typename T>
using Ptr = std::shared_ptr<T>;

// ------------------------------------------------------------------
// 3. Function type aliases
// ------------------------------------------------------------------
using Predicate = std::function<bool(int)>;
using Transformer = std::function<int(int)>;

// ------------------------------------------------------------------
// 4. Real-world scenario: simplifying nested templates
// ------------------------------------------------------------------
template <typename T>
using Matrix = std::vector<std::vector<T>>;

template <typename T>
Matrix<T> createMatrix(int rows, int cols, T defaultVal)
{
    return Matrix<T>(rows, Vec<T>(cols, defaultVal));
}

int main()
{
    // ------------------------------------------------------------------
    // Simple type aliases
    // ------------------------------------------------------------------
    ulong big = 4000000000UL;
    StringVec names = {"Alice", "Bob", "Charlie"};

    std::cout << "=== Simple aliases ===" << std::endl;
    std::cout << "  ulong value: " << big << std::endl;
    std::cout << "  Names: ";
    for (const auto& n : names) std::cout << n << " ";
    std::cout << std::endl << std::endl;

    // ------------------------------------------------------------------
    // Template aliases
    // ------------------------------------------------------------------
    Vec<int> numbers = {10, 20, 30, 40};
    StringMap<int> ages = {{"Alice", 30}, {"Bob", 25}};
    Ptr<std::string> greeting = std::make_shared<std::string>("Hello!");

    std::cout << "=== Template aliases ===" << std::endl;
    std::cout << "  Vec<int>: ";
    for (auto n : numbers) std::cout << n << " ";
    std::cout << std::endl;

    std::cout << "  StringMap<int>:" << std::endl;
    for (const auto& p : ages) {
        std::cout << "    " << p.first << " -> " << p.second << std::endl;
    }

    std::cout << "  Ptr<string>: " << *greeting << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Function aliases
    // ------------------------------------------------------------------
    Predicate isEven = [](int n) { return n % 2 == 0; };
    Transformer doubleIt = [](int n) { return n * 2; };

    std::cout << "=== Function aliases ===" << std::endl;
    std::cout << "  isEven(4)   : " << (isEven(4) ? "true" : "false") << std::endl;
    std::cout << "  isEven(7)   : " << (isEven(7) ? "true" : "false") << std::endl;
    std::cout << "  doubleIt(5) : " << doubleIt(5) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Matrix alias (nested template simplification)
    // ------------------------------------------------------------------
    auto mat = createMatrix(3, 4, 0);
    mat[1][2] = 42;

    std::cout << "=== Matrix<int> (3x4) ===" << std::endl;
    for (int r = 0; r < 3; ++r) {
        std::cout << "  ";
        for (int c = 0; c < 4; ++c) {
            std::cout << mat[r][c] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

/*
Expected output:

=== Simple aliases ===
  ulong value: 4000000000
  Names: Alice Bob Charlie

=== Template aliases ===
  Vec<int>: 10 20 30 40
  StringMap<int>:
    Alice -> 30
    Bob -> 25
  Ptr<string>: Hello!

=== Function aliases ===
  isEven(4)   : true
  isEven(7)   : false
  doubleIt(5) : 10

=== Matrix<int> (3x4) ===
  0 0 0 0
  0 0 42 0
  0 0 0 0
*/
