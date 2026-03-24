// CodeNebula - C++14 Example: Relaxed constexpr
// Compile: g++ -std=c++14 -Wall -Wextra -o example relaxed_constexpr.cpp

// Demonstrates relaxed constexpr restrictions in C++14. Functions marked
// constexpr can now contain loops, local variables, if/else, switch, and
// multiple return statements. In C++11, constexpr was limited to a single
// return expression. Real-world use: compile-time algorithms, lookup tables,
// hash functions, and mathematical computations.

#include <iostream>
#include <array>

// ------------------------------------------------------------------
// 1. constexpr with loops and local variables (impossible in C++11)
// ------------------------------------------------------------------
constexpr int factorial(int n)
{
    int result = 1;
    for (int i = 2; i <= n; ++i)
        result *= i;
    return result;
}

// ------------------------------------------------------------------
// 2. constexpr with if/else and multiple returns
// ------------------------------------------------------------------
constexpr int fibonacci(int n)
{
    if (n <= 0) return 0;
    if (n == 1) return 1;

    int a = 0, b = 1;
    for (int i = 2; i <= n; ++i)
    {
        int temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

// ------------------------------------------------------------------
// 3. constexpr with switch statement
// ------------------------------------------------------------------
constexpr const char* day_name(int day)
{
    switch (day)
    {
        case 0: return "Sunday";
        case 1: return "Monday";
        case 2: return "Tuesday";
        case 3: return "Wednesday";
        case 4: return "Thursday";
        case 5: return "Friday";
        case 6: return "Saturday";
        default: return "Invalid";
    }
}

// ------------------------------------------------------------------
// 4. constexpr GCD using Euclidean algorithm with a loop
// ------------------------------------------------------------------
constexpr int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// ------------------------------------------------------------------
// 5. constexpr string length (pointer iteration)
// ------------------------------------------------------------------
constexpr int str_length(const char* s)
{
    int len = 0;
    while (s[len] != '\0')
        ++len;
    return len;
}

int main()
{
    // ------------------------------------------------------------------
    // Compile-time evaluations (used as template args / array sizes)
    // ------------------------------------------------------------------
    constexpr int fact5 = factorial(5);
    constexpr int fib10 = fibonacci(10);
    constexpr int g     = gcd(48, 18);
    constexpr int slen  = str_length("Hello, C++14!");

    // Array size from constexpr result proves compile-time evaluation
    std::array<int, fact5> arr{};   // array of 120 elements

    std::cout << "=== Constexpr with Loops ===" << std::endl;
    std::cout << "  factorial(5)  = " << fact5 << std::endl;
    std::cout << "  factorial(10) = " << factorial(10) << std::endl;
    std::cout << "  Array size    = " << arr.size() << " (proves compile-time)" << std::endl;
    std::cout << std::endl;

    std::cout << "=== Constexpr Fibonacci ===" << std::endl;
    std::cout << "  fibonacci(10) = " << fib10 << std::endl;
    std::cout << "  fibonacci(20) = " << fibonacci(20) << std::endl;
    std::cout << std::endl;

    std::cout << "=== Constexpr Switch ===" << std::endl;
    for (int d = 0; d < 7; ++d)
        std::cout << "  Day " << d << ": " << day_name(d) << std::endl;
    std::cout << std::endl;

    std::cout << "=== Constexpr GCD ===" << std::endl;
    std::cout << "  gcd(48, 18)  = " << g << std::endl;
    std::cout << "  gcd(100, 75) = " << gcd(100, 75) << std::endl;
    std::cout << std::endl;

    std::cout << "=== Constexpr String Length ===" << std::endl;
    std::cout << "  strlen(\"Hello, C++14!\") = " << slen << std::endl;

    return 0;
}

/*
Expected output:

=== Constexpr with Loops ===
  factorial(5)  = 120
  factorial(10) = 3628800
  Array size    = 120 (proves compile-time)

=== Constexpr Fibonacci ===
  fibonacci(10) = 55
  fibonacci(20) = 6765

=== Constexpr Switch ===
  Day 0: Sunday
  Day 1: Monday
  Day 2: Tuesday
  Day 3: Wednesday
  Day 4: Thursday
  Day 5: Friday
  Day 6: Saturday

=== Constexpr GCD ===
  gcd(48, 18)  = 6
  gcd(100, 75) = 25

=== Constexpr String Length ===
  strlen("Hello, C++14!") = 13
*/
