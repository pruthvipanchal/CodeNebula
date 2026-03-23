// CodeNebula - C++11 Example: constexpr Functions and Variables
// Compile: g++ -std=c++11 -Wall -Wextra -o example constexpr.cpp

// Demonstrates constexpr for compile-time evaluation. constexpr functions
// can be evaluated at compile time when called with constant expressions,
// enabling efficient zero-cost abstractions and compile-time computation.

#include <iostream>
#include <array>
#include <cstddef>

// ------------------------------------------------------------------
// 1. constexpr variables (compile-time constants)
// ------------------------------------------------------------------
constexpr double PI       = 3.14159265358979323846;
constexpr double TAU      = 2.0 * PI;
constexpr int    MAX_SIZE = 1024;

// ------------------------------------------------------------------
// 2. constexpr functions (C++11: single return statement)
// ------------------------------------------------------------------
constexpr int factorial(int n)
{
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

constexpr int fibonacci(int n)
{
    return (n <= 1) ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

constexpr double circleArea(double radius)
{
    return PI * radius * radius;
}

constexpr int max(int a, int b)
{
    return (a > b) ? a : b;
}

constexpr bool isPrime(int n)
{
    return (n < 2) ? false :
           (n == 2) ? true :
           (n % 2 == 0) ? false :
           // Check odd divisors up to sqrt(n) approximation
           (n < 9) ? true :
           (n % 3 != 0 && n % 5 != 0 && n % 7 != 0);
}

// ------------------------------------------------------------------
// 3. constexpr with user-defined types
// ------------------------------------------------------------------
struct Point {
    double x, y;

    constexpr Point(double px, double py) : x(px), y(py) {}

    constexpr double distanceSquared(const Point& other) const
    {
        return (x - other.x) * (x - other.x) +
               (y - other.y) * (y - other.y);
    }
};

int main()
{
    // ------------------------------------------------------------------
    // constexpr variables
    // ------------------------------------------------------------------
    std::cout << "=== constexpr variables ===" << std::endl;
    std::cout << "  PI       = " << PI << std::endl;
    std::cout << "  TAU      = " << TAU << std::endl;
    std::cout << "  MAX_SIZE = " << MAX_SIZE << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Compile-time function evaluation
    // ------------------------------------------------------------------
    constexpr int fact5 = factorial(5);     // computed at compile time
    constexpr int fib10 = fibonacci(10);
    constexpr double area = circleArea(5.0);

    std::cout << "=== Compile-time functions ===" << std::endl;
    std::cout << "  factorial(5)    = " << fact5 << std::endl;
    std::cout << "  fibonacci(10)   = " << fib10 << std::endl;
    std::cout << "  circleArea(5.0) = " << area << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // constexpr as array bounds (must be compile-time)
    // ------------------------------------------------------------------
    constexpr int SIZE = max(10, 20);
    std::array<int, SIZE> arr{};
    arr[0] = 42;

    std::cout << "=== Array with constexpr size ===" << std::endl;
    std::cout << "  max(10, 20) = " << SIZE << std::endl;
    std::cout << "  arr.size()  = " << arr.size() << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // constexpr with static_assert
    // ------------------------------------------------------------------
    static_assert(factorial(5) == 120, "5! must be 120");
    static_assert(fibonacci(10) == 55, "fib(10) must be 55");
    static_assert(isPrime(17), "17 must be prime");

    std::cout << "=== Compile-time primality ===" << std::endl;
    for (int i = 2; i <= 20; ++i) {
        if (isPrime(i)) {
            std::cout << "  " << i << " is prime" << std::endl;
        }
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // constexpr user-defined types
    // ------------------------------------------------------------------
    constexpr Point origin(0.0, 0.0);
    constexpr Point p(3.0, 4.0);
    constexpr double d2 = origin.distanceSquared(p);

    std::cout << "=== constexpr Point ===" << std::endl;
    std::cout << "  origin: (" << origin.x << ", " << origin.y << ")" << std::endl;
    std::cout << "  p:      (" << p.x << ", " << p.y << ")" << std::endl;
    std::cout << "  distanceSquared = " << d2 << std::endl;

    static_assert(origin.distanceSquared(p) == 25.0, "3-4-5 triangle");

    return 0;
}

/*
Expected output:

=== constexpr variables ===
  PI       = 3.14159
  TAU      = 6.28319
  MAX_SIZE = 1024

=== Compile-time functions ===
  factorial(5)    = 120
  fibonacci(10)   = 55
  circleArea(5.0) = 78.5398

=== Array with constexpr size ===
  max(10, 20) = 20
  arr.size()  = 20

=== Compile-time primality ===
  2 is prime
  3 is prime
  5 is prime
  7 is prime
  11 is prime
  13 is prime
  17 is prime
  19 is prime

=== constexpr Point ===
  origin: (0, 0)
  p:      (3, 4)
  distanceSquared = 25
*/
