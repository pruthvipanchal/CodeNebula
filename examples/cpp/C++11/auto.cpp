// CodeNebula - C++11 Example: Auto Type Deduction
// Compile: g++ -std=c++11 -Wall -Wextra -o example auto.cpp

// Demonstrates the 'auto' keyword for automatic type deduction. The compiler
// infers the type from the initializer, reducing verbosity while preserving
// full type safety. Useful with complex iterator types and template returns.

#include <iostream>
#include <vector>
#include <map>
#include <string>

// Real-world scenario: a function whose return type is complex
auto computeRatio(double numerator, double denominator) -> double
{
    return numerator / denominator;
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic type deduction
    // ------------------------------------------------------------------
    auto intVal    = 42;          // int
    auto doubleVal = 3.14;        // double
    auto charVal   = 'A';         // char
    auto boolVal   = true;        // bool
    auto strVal    = std::string("hello");  // std::string (not const char*)

    std::cout << "=== Basic auto deduction ===" << std::endl;
    std::cout << "  intVal    : " << intVal    << std::endl;
    std::cout << "  doubleVal : " << doubleVal << std::endl;
    std::cout << "  charVal   : " << charVal   << std::endl;
    std::cout << "  boolVal   : " << boolVal   << std::endl;
    std::cout << "  strVal    : " << strVal    << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. auto with references and const
    // ------------------------------------------------------------------
    int x = 100;
    auto& refX       = x;         // int&
    const auto& crefX = x;        // const int&
    auto* ptrX        = &x;       // int*

    refX = 200;
    std::cout << "=== References and pointers ===" << std::endl;
    std::cout << "  x after refX = 200 : " << x << std::endl;
    std::cout << "  crefX              : " << crefX << std::endl;
    std::cout << "  *ptrX              : " << *ptrX << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. auto with iterators (eliminates verbose iterator types)
    // ------------------------------------------------------------------
    std::vector<int> nums = {10, 20, 30, 40, 50};

    std::cout << "=== Auto with iterators ===" << std::endl;
    std::cout << "  Vector: ";
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. auto with maps (avoids std::pair<const Key, Value>)
    // ------------------------------------------------------------------
    std::map<std::string, int> ages = {{"Alice", 30}, {"Bob", 25}};

    std::cout << "=== Auto with maps ===" << std::endl;
    for (auto it = ages.begin(); it != ages.end(); ++it) {
        std::cout << "  " << it->first << " -> " << it->second << std::endl;
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Trailing return type with auto
    // ------------------------------------------------------------------
    auto ratio = computeRatio(22.0, 7.0);
    std::cout << "=== Trailing return type ===" << std::endl;
    std::cout << "  22/7 = " << ratio << std::endl;

    return 0;
}

/*
Expected output:

=== Basic auto deduction ===
  intVal    : 42
  doubleVal : 3.14
  charVal   : A
  boolVal   : 1
  strVal    : hello

=== References and pointers ===
  x after refX = 200 : 200
  crefX              : 200
  *ptrX              : 200

=== Auto with iterators ===
  Vector: 10 20 30 40 50

=== Auto with maps ===
  Alice -> 30
  Bob -> 25

=== Trailing return type ===
  22/7 = 3.14286
*/
