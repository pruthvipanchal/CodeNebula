// CodeNebula - C++11 Example: Decltype for Type Inference
// Compile: g++ -std=c++11 -Wall -Wextra -o example decltype.cpp

// Demonstrates decltype, which inspects the declared type of an expression
// without evaluating it. Essential for generic code where you need to declare
// variables or return types matching another expression's type.

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

// Real-world scenario: generic add function using trailing return type
template <typename T, typename U>
auto add(T a, U b) -> decltype(a + b)
{
    return a + b;
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic decltype usage
    // ------------------------------------------------------------------
    int x = 42;
    decltype(x) y = 100;           // y is int
    const double pi = 3.14159;
    decltype(pi) e = 2.71828;      // e is const double

    std::cout << "=== Basic decltype ===" << std::endl;
    std::cout << "  y (decltype(x))  : " << y << std::endl;
    std::cout << "  e (decltype(pi)) : " << e << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. decltype with expressions
    // ------------------------------------------------------------------
    int a = 10, b = 20;
    decltype(a + b) sum = a + b;           // int (prvalue -> type)
    decltype((a)) refA = a;                // int& (lvalue expression in parens)
    refA = 99;

    std::cout << "=== Decltype with expressions ===" << std::endl;
    std::cout << "  sum = a + b      : " << sum << std::endl;
    std::cout << "  a after refA=99  : " << a << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. decltype in generic function (trailing return type)
    // ------------------------------------------------------------------
    auto intResult    = add(3, 4);       // int + int = int
    auto doubleResult = add(3, 4.5);     // int + double = double
    auto strResult    = add(std::string("Hello, "), std::string("World!"));

    std::cout << "=== Generic add with decltype ===" << std::endl;
    std::cout << "  add(3, 4)               : " << intResult << std::endl;
    std::cout << "  add(3, 4.5)             : " << doubleResult << std::endl;
    std::cout << "  add(\"Hello, \",\"World!\") : " << strResult << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. decltype for container element types
    // ------------------------------------------------------------------
    std::vector<int> nums = {1, 2, 3, 4, 5};
    decltype(nums)::value_type elem = 42;     // int
    decltype(nums.size()) count = nums.size(); // std::vector<int>::size_type

    std::cout << "=== Decltype with containers ===" << std::endl;
    std::cout << "  elem (value_type) : " << elem << std::endl;
    std::cout << "  count (size_type) : " << count << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. decltype preserves references and cv-qualifiers
    // ------------------------------------------------------------------
    int val = 7;
    int& ref = val;
    const int cval = 50;

    decltype(ref) ref2 = val;       // int& (preserves reference)
    decltype(cval) cval2 = 60;      // const int (preserves const)
    ref2 = 777;

    std::cout << "=== Preserving qualifiers ===" << std::endl;
    std::cout << "  val after ref2=777 : " << val << std::endl;
    std::cout << "  cval2              : " << cval2 << std::endl;

    return 0;
}

/*
Expected output:

=== Basic decltype ===
  y (decltype(x))  : 100
  e (decltype(pi)) : 2.71828

=== Decltype with expressions ===
  sum = a + b      : 30
  a after refA=99  : 99

=== Generic add with decltype ===
  add(3, 4)               : 7
  add(3, 4.5)             : 7.5
  add("Hello, ","World!") : Hello, World!

=== Decltype with containers ===
  elem (value_type) : 42
  count (size_type) : 5

=== Preserving qualifiers ===
  val after ref2=777 : 777
  cval2              : 60
*/
