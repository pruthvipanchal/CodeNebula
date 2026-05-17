// CodeNebula - C++17 Example: constexpr Lambda Expressions
// Compile: g++ -std=c++17 -Wall -Wextra -o example constexpr_lambdas.cpp

// Demonstrates C++17 constexpr lambdas. Lambda call operators are implicitly
// constexpr when possible, and can be explicitly marked constexpr. This allows
// lambdas to be used in constant expressions like template arguments and
// static_assert.

#include <iostream>
#include <array>
#include <algorithm>

int main()
{
    // ------------------------------------------------------------------
    // 1. Implicitly constexpr lambda (C++17 makes this automatic)
    // ------------------------------------------------------------------
    auto square = [](int n) { return n * n; };

    // Can be used at compile time:
    constexpr int sq5 = square(5);
    static_assert(sq5 == 25, "5*5 should be 25");

    std::cout << "=== implicitly constexpr ===" << std::endl;
    std::cout << "  square(5) = " << sq5 << " (compile-time)" << std::endl;
    std::cout << "  square(7) = " << square(7) << " (runtime)" << std::endl;

    // ------------------------------------------------------------------
    // 2. Explicitly constexpr lambda
    // ------------------------------------------------------------------
    auto factorial = [](int n) constexpr -> int {
        int result = 1;
        for (int i = 2; i <= n; ++i)
            result *= i;
        return result;
    };

    constexpr int f6 = factorial(6);
    static_assert(f6 == 720, "6! should be 720");

    std::cout << "\n=== explicitly constexpr ===" << std::endl;
    std::cout << "  factorial(6) = " << f6 << std::endl;
    std::cout << "  factorial(10) = " << factorial(10) << std::endl;

    // ------------------------------------------------------------------
    // 3. constexpr lambda as template argument (array size)
    // ------------------------------------------------------------------
    constexpr auto array_size = [](int rows, int cols) { return rows * cols; };
    std::array<int, array_size(3, 4)> grid{};  // 12-element array

    std::cout << "\n=== constexpr lambda as template arg ===" << std::endl;
    std::cout << "  grid size (3*4): " << grid.size() << std::endl;

    // ------------------------------------------------------------------
    // 4. constexpr lambda with captures
    // ------------------------------------------------------------------
    constexpr int base = 10;
    constexpr auto add_base = [base](int x) { return x + base; };
    constexpr int result = add_base(32);
    static_assert(result == 42, "10+32=42");

    std::cout << "\n=== constexpr lambda with capture ===" << std::endl;
    std::cout << "  base=10, add_base(32) = " << result << std::endl;

    // ------------------------------------------------------------------
    // 5. constexpr lambda for compile-time computation
    // ------------------------------------------------------------------
    constexpr auto fibonacci = [](int n) constexpr -> int {
        if (n <= 1) return n;
        int a = 0, b = 1;
        for (int i = 2; i <= n; ++i) {
            int t = a + b;
            a = b;
            b = t;
        }
        return b;
    };

    constexpr int fib10 = fibonacci(10);
    static_assert(fib10 == 55, "fib(10) should be 55");

    std::cout << "\n=== compile-time fibonacci ===" << std::endl;
    for (int i = 0; i <= 10; ++i) {
        std::cout << "  fib(" << i << ") = " << fibonacci(i) << std::endl;
    }

    // ------------------------------------------------------------------
    // 6. Using constexpr lambda at runtime too
    // ------------------------------------------------------------------
    std::cout << "\n=== constexpr lambda at runtime ===" << std::endl;
    int runtime_val = 8;
    std::cout << "  square(" << runtime_val << ") = " << square(runtime_val) << std::endl;

    return 0;
}

/*
Expected output:

=== implicitly constexpr ===
  square(5) = 25 (compile-time)
  square(7) = 49 (runtime)

=== explicitly constexpr ===
  factorial(6) = 720
  factorial(10) = 3628800

=== constexpr lambda as template arg ===
  grid size (3*4): 12

=== constexpr lambda with capture ===
  base=10, add_base(32) = 42

=== compile-time fibonacci ===
  fib(0) = 0
  fib(1) = 1
  fib(2) = 1
  fib(3) = 2
  fib(4) = 3
  fib(5) = 5
  fib(6) = 8
  fib(7) = 13
  fib(8) = 21
  fib(9) = 34
  fib(10) = 55

=== constexpr lambda at runtime ===
  square(8) = 64
*/
