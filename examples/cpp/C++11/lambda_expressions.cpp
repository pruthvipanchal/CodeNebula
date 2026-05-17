// CodeNebula - C++11 Example: Lambda Expressions
// Compile: g++ -std=c++11 -Wall -Wextra -o example lambda_expressions.cpp

// Demonstrates lambda expressions: inline anonymous functions with capture
// clauses, parameters, and return types. Lambdas replace verbose functor
// classes and enable concise callbacks for algorithms and event handlers.

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic lambda (no capture, no parameters)
    // ------------------------------------------------------------------
    auto greet = []() { std::cout << "  Hello from a lambda!" << std::endl; };

    std::cout << "=== Basic lambda ===" << std::endl;
    greet();
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Lambda with parameters and return type
    // ------------------------------------------------------------------
    auto add = [](int a, int b) -> int { return a + b; };
    auto multiply = [](double a, double b) { return a * b; };  // deduced

    std::cout << "=== Parameters and return ===" << std::endl;
    std::cout << "  add(3, 4)          : " << add(3, 4) << std::endl;
    std::cout << "  multiply(2.5, 4.0) : " << multiply(2.5, 4.0) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Capture by value [=] and by reference [&]
    // ------------------------------------------------------------------
    int x = 10, y = 20;

    auto captureByVal = [x, y]() { return x + y; };
    auto captureByRef = [&x, &y]() { x += 5; y += 5; };

    captureByRef();
    std::cout << "=== Capture modes ===" << std::endl;
    std::cout << "  After capture-by-ref: x=" << x << ", y=" << y << std::endl;
    std::cout << "  Capture-by-val sum  : " << captureByVal() << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Mutable lambdas (modify captured-by-value copies)
    // ------------------------------------------------------------------
    int counter = 0;
    auto increment = [counter]() mutable -> int {
        return ++counter;
    };

    std::cout << "=== Mutable lambda ===" << std::endl;
    std::cout << "  Call 1: " << increment() << std::endl;
    std::cout << "  Call 2: " << increment() << std::endl;
    std::cout << "  Original counter: " << counter << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Lambdas with STL algorithms
    // ------------------------------------------------------------------
    std::vector<int> nums = {5, 2, 8, 1, 9, 3, 7};

    std::sort(nums.begin(), nums.end(), [](int a, int b) {
        return a > b;   // descending order
    });

    std::cout << "=== Lambda with std::sort ===" << std::endl;
    std::cout << "  Descending: ";
    std::for_each(nums.begin(), nums.end(), [](int n) {
        std::cout << n << " ";
    });
    std::cout << std::endl;

    auto count = std::count_if(nums.begin(), nums.end(),
                               [](int n) { return n > 5; });
    std::cout << "  Elements > 5: " << count << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 6. Storing lambdas with std::function
    // ------------------------------------------------------------------
    std::function<std::string(const std::string&)> shout =
        [](const std::string& s) -> std::string {
            return s + "!!!";
        };

    std::cout << "=== std::function ===" << std::endl;
    std::cout << "  " << shout("Lambdas are powerful") << std::endl;

    return 0;
}

/*
Expected output:

=== Basic lambda ===
  Hello from a lambda!

=== Parameters and return ===
  add(3, 4)          : 7
  multiply(2.5, 4.0) : 10

=== Capture modes ===
  After capture-by-ref: x=15, y=25
  Capture-by-val sum  : 30

=== Mutable lambda ===
  Call 1: 1
  Call 2: 2
  Original counter: 0

=== Lambda with std::sort ===
  Descending: 9 8 7 5 3 2 1
  Elements > 5: 3

=== std::function ===
  Lambdas are powerful!!!
*/
