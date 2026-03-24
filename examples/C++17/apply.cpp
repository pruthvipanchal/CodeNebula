// CodeNebula - C++17 Example: std::apply
// Compile: g++ -std=c++17 -Wall -Wextra -o example apply.cpp

// Demonstrates std::apply, which unpacks a tuple and passes its elements
// as individual arguments to a callable. This bridges tuple-based storage
// with regular function call syntax.

#include <iostream>
#include <tuple>
#include <string>
#include <functional>

// A simple function to call with tuple arguments
int add(int a, int b, int c)
{
    return a + b + c;
}

// A function taking mixed types
std::string format_person(const std::string& name, int age, double height)
{
    return name + " (age " + std::to_string(age) + ", " +
           std::to_string(height).substr(0, 4) + "m)";
}

struct Multiplier {
    int factor;
    int operator()(int x, int y) const { return factor * (x + y); }
};

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic: apply a free function to a tuple
    // ------------------------------------------------------------------
    auto args = std::make_tuple(10, 20, 30);
    int sum = std::apply(add, args);

    std::cout << "=== Free Function ===" << std::endl;
    std::cout << "  add(10, 20, 30) = " << sum << std::endl;

    // ------------------------------------------------------------------
    // 2. Mixed types in the tuple
    // ------------------------------------------------------------------
    auto person = std::make_tuple(std::string("Alice"), 30, 1.72);
    std::string desc = std::apply(format_person, person);

    std::cout << "\n=== Mixed Types ===" << std::endl;
    std::cout << "  " << desc << std::endl;

    // ------------------------------------------------------------------
    // 3. Using a lambda
    // ------------------------------------------------------------------
    auto product = std::apply(
        [](int a, int b) { return a * b; },
        std::make_tuple(7, 8)
    );
    std::cout << "\n=== Lambda ===" << std::endl;
    std::cout << "  7 * 8 = " << product << std::endl;

    // ------------------------------------------------------------------
    // 4. Using a function object
    // ------------------------------------------------------------------
    Multiplier m{3};
    int result = std::apply(m, std::make_tuple(4, 5));
    std::cout << "\n=== Function Object ===" << std::endl;
    std::cout << "  3 * (4 + 5) = " << result << std::endl;

    // ------------------------------------------------------------------
    // 5. Applying std::make_pair via a tuple
    // ------------------------------------------------------------------
    auto pair_args = std::make_tuple(42, std::string("hello"));
    auto p = std::apply([](auto a, auto b) { return std::make_pair(a, b); },
                        pair_args);
    std::cout << "\n=== make_pair ===" << std::endl;
    std::cout << "  pair = {" << p.first << ", " << p.second << "}" << std::endl;

    return 0;
}

/*
Expected output:

=== Free Function ===
  add(10, 20, 30) = 60

=== Mixed Types ===
  Alice (age 30, 1.72m)

=== Lambda ===
  7 * 8 = 56

=== Function Object ===
  3 * (4 + 5) = 27

=== make_pair ===
  pair = {42, hello}
*/
