// CodeNebula - C++14 Example: Return Type Deduction
// Compile: g++ -std=c++14 -Wall -Wextra -o example return_type_deduction.cpp

// Demonstrates auto return type deduction for regular functions in C++14.
// Unlike C++11's trailing return types, C++14 lets the compiler deduce
// the return type from the return statement. Real-world use: simplifying
// template code, factory functions, and wrapper functions.

#include <iostream>
#include <string>
#include <vector>
#include <tuple>

// ------------------------------------------------------------------
// 1. Simple auto return - compiler deduces 'int'
// ------------------------------------------------------------------
auto square(int x)
{
    return x * x;
}

// ------------------------------------------------------------------
// 2. Auto return with different types based on input
// ------------------------------------------------------------------
auto describe(int value)
{
    if (value > 0)
        return std::string("positive");
    else if (value < 0)
        return std::string("negative");
    else
        return std::string("zero");
    // All return paths must yield the same type
}

// ------------------------------------------------------------------
// 3. Auto return in template functions
// ------------------------------------------------------------------
template<typename T, typename U>
auto multiply(T a, U b)
{
    return a * b;   // deduced as common type of T*U
}

// ------------------------------------------------------------------
// 4. Auto return with complex types (avoids verbose typenames)
// ------------------------------------------------------------------
auto make_pair_vector()
{
    std::vector<std::pair<std::string, int>> result;
    result.push_back({"alpha", 1});
    result.push_back({"beta", 2});
    result.push_back({"gamma", 3});
    return result;  // deduced as vector<pair<string,int>>
}

// ------------------------------------------------------------------
// 5. Recursive function with auto return (must have base case first)
// ------------------------------------------------------------------
auto factorial(int n) -> int   // recursive needs trailing return or forward decl
{
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// ------------------------------------------------------------------
// 6. Auto return with lambda-like brevity
// ------------------------------------------------------------------
auto clamp(int value, int lo, int hi)
{
    return (value < lo) ? lo : (value > hi) ? hi : value;
}

int main()
{
    std::cout << "=== Simple Auto Return ===" << std::endl;
    std::cout << "  square(7)  : " << square(7) << std::endl;
    std::cout << "  square(-3) : " << square(-3) << std::endl;
    std::cout << std::endl;

    std::cout << "=== String Return Deduction ===" << std::endl;
    std::cout << "  describe(5)  : " << describe(5) << std::endl;
    std::cout << "  describe(-2) : " << describe(-2) << std::endl;
    std::cout << "  describe(0)  : " << describe(0) << std::endl;
    std::cout << std::endl;

    std::cout << "=== Template Auto Return ===" << std::endl;
    std::cout << "  multiply(3, 4.5)   : " << multiply(3, 4.5) << std::endl;
    std::cout << "  multiply(2.0, 3.0) : " << multiply(2.0, 3.0) << std::endl;
    std::cout << std::endl;

    std::cout << "=== Complex Return Type Deduction ===" << std::endl;
    auto pairs = make_pair_vector();
    for (const auto& p : pairs)
        std::cout << "  " << p.first << " -> " << p.second << std::endl;
    std::cout << std::endl;

    std::cout << "=== Recursive with Auto Return ===" << std::endl;
    std::cout << "  factorial(6) : " << factorial(6) << std::endl;
    std::cout << "  factorial(10): " << factorial(10) << std::endl;
    std::cout << std::endl;

    std::cout << "=== Clamp Function ===" << std::endl;
    std::cout << "  clamp(15, 0, 10) : " << clamp(15, 0, 10) << std::endl;
    std::cout << "  clamp(-5, 0, 10) : " << clamp(-5, 0, 10) << std::endl;
    std::cout << "  clamp(7, 0, 10)  : " << clamp(7, 0, 10) << std::endl;

    return 0;
}

/*
Expected output:

=== Simple Auto Return ===
  square(7)  : 49
  square(-3) : 9

=== String Return Deduction ===
  describe(5)  : positive
  describe(-2) : negative
  describe(0)  : zero

=== Template Auto Return ===
  multiply(3, 4.5)   : 13.5
  multiply(2.0, 3.0) : 6

=== Complex Return Type Deduction ===
  alpha -> 1
  beta -> 2
  gamma -> 3

=== Recursive with Auto Return ===
  factorial(6) : 720
  factorial(10): 3628800

=== Clamp Function ===
  clamp(15, 0, 10) : 10
  clamp(-5, 0, 10) : 0
  clamp(7, 0, 10)  : 7
*/
