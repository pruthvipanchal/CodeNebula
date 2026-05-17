// CodeNebula - C++14 Example: Generic Lambda Expressions
// Compile: g++ -std=c++14 -Wall -Wextra -o example generic_lambda_expressions.cpp

// Demonstrates auto parameters in lambdas (polymorphic lambdas). In C++14,
// lambda parameters can use 'auto' instead of concrete types, making them
// behave like templates. Real-world use: generic callbacks, algorithm
// predicates that work with any type, and reducing boilerplate.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic generic lambda - works with any type that supports <<
    // ------------------------------------------------------------------
    auto print = [](const auto& value) {
        std::cout << "  " << value << std::endl;
    };

    std::cout << "=== Basic Generic Lambda ===" << std::endl;
    print(42);
    print(3.14);
    print(std::string("hello"));
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Generic lambda with multiple auto parameters
    // ------------------------------------------------------------------
    auto add = [](auto a, auto b) {
        return a + b;
    };

    std::cout << "=== Multi-Parameter Generic Lambda ===" << std::endl;
    std::cout << "  int + int       : " << add(3, 4) << std::endl;
    std::cout << "  double + double : " << add(1.5, 2.7) << std::endl;
    std::cout << "  string + string : " << add(std::string("Code"), std::string("Nebula")) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Generic lambda used with STL algorithms
    // ------------------------------------------------------------------
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3};
    std::vector<std::string> words = {"banana", "apple", "cherry"};

    auto less_than = [](const auto& a, const auto& b) {
        return a < b;
    };

    std::sort(numbers.begin(), numbers.end(), less_than);
    std::sort(words.begin(), words.end(), less_than);

    std::cout << "=== Generic Lambda with STL Algorithms ===" << std::endl;
    std::cout << "  Sorted ints   :";
    for (const auto& n : numbers) std::cout << " " << n;
    std::cout << std::endl;

    std::cout << "  Sorted strings:";
    for (const auto& w : words) std::cout << " " << w;
    std::cout << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Generic lambda returning different types
    // ------------------------------------------------------------------
    auto identity = [](auto x) { return x; };

    std::cout << "=== Return Type Deduction in Generic Lambdas ===" << std::endl;
    std::cout << "  identity(100)     : " << identity(100) << std::endl;
    std::cout << "  identity(\"text\")  : " << identity("text") << std::endl;
    std::cout << "  identity(true)    : " << std::boolalpha << identity(true) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Nested generic lambda (higher-order polymorphic function)
    // ------------------------------------------------------------------
    auto make_multiplier = [](auto factor) {
        return [factor](auto value) {
            return factor * value;
        };
    };

    auto triple = make_multiplier(3);
    auto scale  = make_multiplier(2.5);

    std::cout << "=== Higher-Order Generic Lambdas ===" << std::endl;
    std::cout << "  triple(7)   : " << triple(7) << std::endl;
    std::cout << "  scale(4.0)  : " << scale(4.0) << std::endl;
    std::cout << "  triple(1.5) : " << triple(1.5) << std::endl;

    return 0;
}

/*
Expected output:

=== Basic Generic Lambda ===
  42
  3.14
  hello

=== Multi-Parameter Generic Lambda ===
  int + int       : 7
  double + double : 4.2
  string + string : CodeNebula

=== Generic Lambda with STL Algorithms ===
  Sorted ints   : 1 2 3 5 8 9
  Sorted strings: apple banana cherry

=== Return Type Deduction in Generic Lambdas ===
  identity(100)     : 100
  identity("text")  : text
  identity(true)    : true

=== Higher-Order Generic Lambdas ===
  triple(7)   : 21
  scale(4.0)  : 10
  triple(1.5) : 4.5
*/
