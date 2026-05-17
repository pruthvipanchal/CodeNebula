// CodeNebula - C++14 Example: Transparent Functors
// Compile: g++ -std=c++14 -Wall -Wextra -o example transparent_functors.cpp

// Demonstrates transparent (void-specialized) functors in C++14: std::less<>,
// std::greater<>, std::plus<>, etc. The void specialization deduces argument
// types automatically and enables heterogeneous comparison. Real-world use:
// generic algorithms, containers with mixed-type lookups, and reducing
// template boilerplate in comparator specifications.

#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <set>
#include <string>

int main()
{
    // ------------------------------------------------------------------
    // 1. std::less<> vs std::less<int> - type deduction
    // ------------------------------------------------------------------
    std::cout << "=== std::less<> (Transparent) ===" << std::endl;

    // Old way: must specify type
    std::less<int> old_less;
    std::cout << "  less<int>(3, 5)   : " << std::boolalpha
              << old_less(3, 5) << std::endl;

    // New way: type deduced, works with any comparable types
    std::less<> new_less;
    std::cout << "  less<>(3, 5)      : " << new_less(3, 5) << std::endl;
    std::cout << "  less<>(5.0, 3.0)  : " << new_less(5.0, 3.0) << std::endl;
    std::cout << "  less<>(\"a\", \"b\") : " << new_less(std::string("a"), std::string("b")) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. All transparent comparison functors
    // ------------------------------------------------------------------
    std::cout << "=== All Comparison Functors ===" << std::endl;
    int a = 10, b = 20;

    std::cout << "  a=" << a << ", b=" << b << std::endl;
    std::cout << "  less<>()         : " << std::less<>()(a, b) << std::endl;
    std::cout << "  greater<>()      : " << std::greater<>()(a, b) << std::endl;
    std::cout << "  less_equal<>()   : " << std::less_equal<>()(a, b) << std::endl;
    std::cout << "  greater_equal<>(): " << std::greater_equal<>()(a, b) << std::endl;
    std::cout << "  equal_to<>()     : " << std::equal_to<>()(a, b) << std::endl;
    std::cout << "  not_equal_to<>() : " << std::not_equal_to<>()(a, b) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Transparent arithmetic functors
    // ------------------------------------------------------------------
    std::cout << "=== Arithmetic Functors ===" << std::endl;
    std::cout << "  plus<>()(3, 4)      : " << std::plus<>()(3, 4) << std::endl;
    std::cout << "  minus<>()(10, 3)    : " << std::minus<>()(10, 3) << std::endl;
    std::cout << "  multiplies<>()(5, 6): " << std::multiplies<>()(5, 6) << std::endl;
    std::cout << "  divides<>()(20, 4)  : " << std::divides<>()(20, 4) << std::endl;
    std::cout << "  modulus<>()(17, 5)  : " << std::modulus<>()(17, 5) << std::endl;
    std::cout << "  negate<>()(42)      : " << std::negate<>()(42) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Using with algorithms - no need to specify type
    // ------------------------------------------------------------------
    std::cout << "=== With STL Algorithms ===" << std::endl;
    std::vector<int> nums = {5, 2, 8, 1, 9, 3, 7};

    std::sort(nums.begin(), nums.end(), std::greater<>());  // descending
    std::cout << "  Sorted descending:";
    for (int n : nums) std::cout << " " << n;
    std::cout << std::endl;

    std::sort(nums.begin(), nums.end(), std::less<>());     // ascending
    std::cout << "  Sorted ascending :";
    for (int n : nums) std::cout << " " << n;
    std::cout << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Mixed-type comparisons (the real power of transparent functors)
    // ------------------------------------------------------------------
    std::cout << "=== Mixed-Type Comparisons ===" << std::endl;
    std::cout << "  less<>()(1, 2.5)    : " << std::less<>()(1, 2.5) << std::endl;
    std::cout << "  equal_to<>()(1, 1.0): " << std::equal_to<>()(1, 1.0) << std::endl;
    std::cout << "  plus<>()(1, 2.5)    : " << std::plus<>()(1, 2.5) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 6. In containers for heterogeneous lookup
    // ------------------------------------------------------------------
    std::cout << "=== Container with Transparent Comparator ===" << std::endl;
    std::set<std::string, std::less<>> words = {"hello", "world", "cpp14"};

    // const char* lookup without std::string construction
    std::cout << "  find(\"world\") : "
              << (words.find("world") != words.end() ? "found" : "not found")
              << std::endl;
    std::cout << "  find(\"missing\"): "
              << (words.find("missing") != words.end() ? "found" : "not found")
              << std::endl;

    return 0;
}

/*
Expected output:

=== std::less<> (Transparent) ===
  less<int>(3, 5)   : true
  less<>(3, 5)      : true
  less<>(5.0, 3.0)  : false
  less<>("a", "b") : true

=== All Comparison Functors ===
  a=10, b=20
  less<>()         : true
  greater<>()      : false
  less_equal<>()   : true
  greater_equal<>(): false
  equal_to<>()     : false
  not_equal_to<>() : true

=== Arithmetic Functors ===
  plus<>()(3, 4)      : 7
  minus<>()(10, 3)    : 7
  multiplies<>()(5, 6): 30
  divides<>()(20, 4)  : 5
  modulus<>()(17, 5)  : 2
  negate<>()(42)      : -42

=== With STL Algorithms ===
  Sorted descending: 9 8 7 5 3 2 1
  Sorted ascending : 1 2 3 5 7 8 9

=== Mixed-Type Comparisons ===
  less<>()(1, 2.5)    : true
  equal_to<>()(1, 1.0): true
  plus<>()(1, 2.5)    : 3.5

=== Container with Transparent Comparator ===
  find("world") : found
  find("missing"): not found
*/
