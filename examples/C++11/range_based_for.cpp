// CodeNebula - C++11 Example: Range-Based For Loop
// Compile: g++ -std=c++11 -Wall -Wextra -o example range_based_for.cpp

// Demonstrates range-based for loops with vectors, arrays, maps, and strings.
// This syntax eliminates manual iterator management, reducing bugs and
// improving readability in everyday container traversal.

#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <string>

int main()
{
    // ------------------------------------------------------------------
    // 1. Range-based for with std::vector
    // ------------------------------------------------------------------
    std::vector<int> nums = {10, 20, 30, 40, 50};

    std::cout << "=== Vector (by value) ===" << std::endl;
    std::cout << "  ";
    for (int n : nums) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // Modify elements using reference
    for (int& n : nums) {
        n *= 2;
    }
    std::cout << "  After doubling: ";
    for (const int& n : nums) {       // const ref avoids copies
        std::cout << n << " ";
    }
    std::cout << std::endl << std::endl;

    // ------------------------------------------------------------------
    // 2. Range-based for with C-style array
    // ------------------------------------------------------------------
    int arr[] = {1, 2, 3, 4, 5};

    std::cout << "=== C-style array ===" << std::endl;
    std::cout << "  ";
    for (auto val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl << std::endl;

    // ------------------------------------------------------------------
    // 3. Range-based for with std::array
    // ------------------------------------------------------------------
    std::array<double, 4> prices = {{9.99, 19.99, 29.99, 49.99}};

    std::cout << "=== std::array ===" << std::endl;
    double total = 0.0;
    for (const auto& p : prices) {
        total += p;
        std::cout << "  $" << p << std::endl;
    }
    std::cout << "  Total: $" << total << std::endl << std::endl;

    // ------------------------------------------------------------------
    // 4. Range-based for with std::map
    // ------------------------------------------------------------------
    std::map<std::string, int> scores = {
        {"Alice", 95}, {"Bob", 87}, {"Charlie", 92}
    };

    std::cout << "=== std::map ===" << std::endl;
    for (const auto& pair : scores) {
        std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Range-based for with std::string
    // ------------------------------------------------------------------
    std::string greeting = "Hello!";

    std::cout << "=== std::string ===" << std::endl;
    std::cout << "  Characters: ";
    for (char c : greeting) {
        std::cout << "[" << c << "] ";
    }
    std::cout << std::endl << std::endl;

    // ------------------------------------------------------------------
    // 6. Range-based for with initializer list
    // ------------------------------------------------------------------
    std::cout << "=== Initializer list ===" << std::endl;
    std::cout << "  Squares: ";
    for (auto x : {1, 4, 9, 16, 25}) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}

/*
Expected output:

=== Vector (by value) ===
  10 20 30 40 50
  After doubling: 20 40 60 80 100

=== C-style array ===
  1 2 3 4 5

=== std::array ===
  $9.99
  $19.99
  $29.99
  $49.99
  Total: $109.96

=== std::map ===
  Alice: 95
  Bob: 87
  Charlie: 92

=== std::string ===
  Characters: [H] [e] [l] [l] [o] [!]

=== Initializer list ===
  Squares: 1 4 9 16 25
*/
