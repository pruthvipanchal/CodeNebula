// CodeNebula - C++23 Example: Lambda Trailing Return Type Scope
// Compile: g++ -std=c++23 -Wall -Wextra -o example lambda_return_scope.cpp
// Note: Requires GCC 14+ / Clang 17+ / MSVC 19.36+

// C++23 changes the scope of the trailing return type in lambdas.
// Previously, the trailing return type could not see the lambda's own captures.
// Now, the trailing return type is evaluated in the lambda's scope.
// This fixes a long-standing quirk where decltype on captured variables failed.

#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <numeric>

int main() {
    std::cout << "=== Lambda Trailing Return Type Scope (C++23) ===" << std::endl;

    // C++23: trailing return type can reference captured variables
    int x = 42;
    // Before C++23, this could fail because 'x' wasn't in scope
    // for the trailing return type. Now it works.
    auto get_ref = [&x]() -> decltype(x)& {
        return x;
    };
    get_ref() = 100;
    std::cout << "Modified via lambda ref: x = " << x << std::endl;

    // Practical example: return type depends on captured variable type
    std::string name = "C++23";
    auto make_greeting = [&name]() -> decltype(name + "!") {
        return "Hello, " + name + "!";
    };
    std::cout << "Greeting: " << make_greeting() << std::endl;

    // Demonstrating with init-capture
    std::cout << "\n=== Init-capture in trailing return type ===" << std::endl;
    auto factory = [val = std::vector<int>{1, 2, 3}]()
        -> decltype(val)  // C++23: 'val' visible in return type
    {
        return val;
    };
    auto result = factory();
    std::cout << "Factory produced: ";
    for (int v : result) std::cout << v << " ";
    std::cout << std::endl;

    // Type deduction with captured variable
    std::cout << "\n=== Type-dependent return ===" << std::endl;
    double pi = 3.14159;
    auto doubler = [&pi]() -> decltype(pi * 2) {
        return pi * 2;
    };
    std::cout << "Doubled pi: " << doubler() << std::endl;
    std::cout << "Return is double: "
              << std::is_same_v<decltype(doubler()), double> << std::endl;

    // Combining with generic lambdas
    std::cout << "\n=== Generic lambda with scope-aware return ===" << std::endl;
    std::vector<int> data = {1, 2, 3, 4, 5};
    auto summer = [&data](auto init) -> decltype(init) {
        return std::accumulate(data.begin(), data.end(), init);
    };
    std::cout << "Sum (int):    " << summer(0) << std::endl;
    std::cout << "Sum (double): " << summer(0.0) << std::endl;

    return 0;
}

/*
Expected output:
=== Lambda Trailing Return Type Scope (C++23) ===
Modified via lambda ref: x = 100
Greeting: Hello, C++23!

=== Init-capture in trailing return type ===
Factory produced: 1 2 3

=== Type-dependent return ===
Doubled pi: 6.28318
Return is double: 1

=== Generic lambda with scope-aware return ===
Sum (int):    15
Sum (double): 15
*/
