// CodeNebula - C++98 Example: Inline Functions
// Compile: g++ -std=c++98 -Wall -Wextra -o example inline_functions.cpp

// Demonstrates inline functions in C++98: the inline keyword, when to use it,
// comparison with macros, inline member functions, and performance reasoning.

#include <iostream>

// ------------------------------------------------------------------
// 1. Basic inline function
//    The "inline" keyword is a HINT to the compiler to replace the
//    function call with the function body (avoiding call overhead).
//    The compiler may ignore the hint.
// ------------------------------------------------------------------
inline int square(int x)
{
    return x * x;
}

inline int maxOf(int a, int b)
{
    return (a > b) ? a : b;
}

inline int minOf(int a, int b)
{
    return (a < b) ? a : b;
}

inline int absValue(int x)
{
    return (x < 0) ? -x : x;
}

// ------------------------------------------------------------------
// 2. Inline function with multiple statements
//    Still a hint - complex functions are less likely to be inlined.
// ------------------------------------------------------------------
inline int clamp(int value, int low, int high)
{
    if (value < low)  return low;
    if (value > high) return high;
    return value;
}

// ------------------------------------------------------------------
// 3. Comparison: macro vs inline function
//    Macros have dangerous pitfalls that inline functions avoid.
// ------------------------------------------------------------------

// DANGEROUS macro: no type safety, double evaluation of arguments
#define SQUARE_MACRO(x) ((x) * (x))

// SAFE inline function: type-safe, evaluates arguments only once
inline int squareSafe(int x)
{
    return x * x;
}

// ------------------------------------------------------------------
// 4. Inline functions for type conversion helpers
// ------------------------------------------------------------------
inline double celsiusToFahrenheit(double c)
{
    return c * 9.0 / 5.0 + 32.0;
}

inline double fahrenheitToCelsius(double f)
{
    return (f - 32.0) * 5.0 / 9.0;
}

inline double degreesToRadians(double deg)
{
    return deg * 3.14159265358979 / 180.0;
}

// ------------------------------------------------------------------
// 5. Inline swap (generic via pointer, C++98 style)
// ------------------------------------------------------------------
inline void swapInt(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

// ------------------------------------------------------------------
// 6. Class with inline member functions
//    Functions defined inside the class body are implicitly inline.
// ------------------------------------------------------------------
class Point {
private:
    double x_;
    double y_;

public:
    // Constructor (implicitly inline - defined in class body)
    Point(double x, double y) : x_(x), y_(y) {}

    // Getters (implicitly inline)
    double getX() const { return x_; }
    double getY() const { return y_; }

    // Setters (implicitly inline)
    void setX(double x) { x_ = x; }
    void setY(double y) { y_ = y; }

    // Declared here, defined outside with explicit inline
    double distanceTo(const Point& other) const;

    void print() const
    {
        std::cout << "(" << x_ << ", " << y_ << ")";
    }
};

// Explicit inline on member function defined outside the class
inline double Point::distanceTo(const Point& other) const
{
    double dx = x_ - other.x_;
    double dy = y_ - other.y_;
    // Using manual sqrt approximation to avoid <cmath> dependency for inline demo
    double sum = dx * dx + dy * dy;
    // Newton's method for sqrt (3 iterations, good enough for demo)
    double guess = sum / 2.0;
    if (guess > 0) {
        for (int i = 0; i < 10; ++i) {
            guess = (guess + sum / guess) / 2.0;
        }
    }
    return guess;
}

// ------------------------------------------------------------------
// 7. Inline predicates (commonly inlined in real code)
// ------------------------------------------------------------------
inline bool isEven(int n)   { return (n % 2) == 0; }
inline bool isOdd(int n)    { return (n % 2) != 0; }
inline bool isPositive(int n) { return n > 0; }
inline bool isInRange(int n, int low, int high) { return n >= low && n <= high; }

int main()
{
    // ------------------------------------------------------------------
    // Demo 1: Basic inline functions
    // ------------------------------------------------------------------
    std::cout << "=== Basic Inline Functions ===" << std::endl;

    std::cout << "  square(5)    = " << square(5) << std::endl;
    std::cout << "  square(12)   = " << square(12) << std::endl;
    std::cout << "  maxOf(10,20) = " << maxOf(10, 20) << std::endl;
    std::cout << "  minOf(10,20) = " << minOf(10, 20) << std::endl;
    std::cout << "  absValue(-7) = " << absValue(-7) << std::endl;
    std::cout << "  absValue(3)  = " << absValue(3) << std::endl;
    std::cout << "  clamp(150, 0, 100) = " << clamp(150, 0, 100) << std::endl;
    std::cout << "  clamp(-5, 0, 100)  = " << clamp(-5, 0, 100) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 2: Macro vs Inline - demonstrating the macro pitfall
    // ------------------------------------------------------------------
    std::cout << "=== Macro vs Inline ===" << std::endl;

    int a = 5;

    // Both give correct result with simple argument
    std::cout << "  SQUARE_MACRO(5) = " << SQUARE_MACRO(5) << std::endl;
    std::cout << "  squareSafe(5)   = " << squareSafe(5) << std::endl;

    // The macro pitfall: side effects are doubled!
    a = 5;
    int macroResult = SQUARE_MACRO(a++);
    // Macro expands to: ((a++) * (a++)) => a is incremented TWICE
    std::cout << "  SQUARE_MACRO(a++) = " << macroResult
              << " (a is now " << a << " - incremented twice!)" << std::endl;

    a = 5;
    int inlineResult = squareSafe(a++);
    // Inline function: a++ evaluated once, then squared
    std::cout << "  squareSafe(a++)  = " << inlineResult
              << " (a is now " << a << " - incremented once)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 3: Unit conversion inline functions
    // ------------------------------------------------------------------
    std::cout << "=== Temperature Conversion ===" << std::endl;

    double temps[] = {0.0, 20.0, 37.0, 100.0};
    for (int i = 0; i < 4; ++i) {
        std::cout << "  " << temps[i] << " C = "
                  << celsiusToFahrenheit(temps[i]) << " F" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "  212 F = " << fahrenheitToCelsius(212.0) << " C" << std::endl;
    std::cout << "  32  F = " << fahrenheitToCelsius(32.0) << " C" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 4: Inline swap
    // ------------------------------------------------------------------
    std::cout << "=== Inline Swap ===" << std::endl;

    int x = 10, y = 20;
    std::cout << "  Before: x=" << x << ", y=" << y << std::endl;
    swapInt(x, y);
    std::cout << "  After:  x=" << x << ", y=" << y << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 5: Class with inline member functions
    // ------------------------------------------------------------------
    std::cout << "=== Inline Member Functions ===" << std::endl;

    Point p1(3.0, 4.0);
    Point p2(6.0, 8.0);

    std::cout << "  p1 = "; p1.print(); std::cout << std::endl;
    std::cout << "  p2 = "; p2.print(); std::cout << std::endl;
    std::cout << "  p1.getX() = " << p1.getX() << std::endl;
    std::cout << "  p1.getY() = " << p1.getY() << std::endl;
    std::cout << "  Distance p1 to p2 = " << p1.distanceTo(p2) << std::endl;

    p1.setX(0.0);
    p1.setY(0.0);
    std::cout << "  After setX(0), setY(0): "; p1.print(); std::cout << std::endl;
    std::cout << "  Distance to p2 = " << p1.distanceTo(p2) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 6: Inline predicates
    // ------------------------------------------------------------------
    std::cout << "=== Inline Predicates ===" << std::endl;

    for (int i = -2; i <= 5; ++i) {
        std::cout << "  " << i << ": "
                  << (isEven(i) ? "even" : "odd ")
                  << (isPositive(i) ? " positive" : " non-pos ")
                  << (isInRange(i, 1, 4) ? " [in 1..4]" : "")
                  << std::endl;
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Key points about inline
    // ------------------------------------------------------------------
    std::cout << "=== Key Points ===" << std::endl;
    std::cout << "  1. 'inline' is a HINT, not a command - compiler decides" << std::endl;
    std::cout << "  2. Best for small, frequently-called functions" << std::endl;
    std::cout << "  3. Functions defined in class body are implicitly inline" << std::endl;
    std::cout << "  4. Prefer inline functions over macros for type safety" << std::endl;
    std::cout << "  5. Inline functions must be defined in every translation" << std::endl;
    std::cout << "     unit that uses them (typically in headers)" << std::endl;

    return 0;
}

/*
Expected output:

=== Basic Inline Functions ===
  square(5)    = 25
  square(12)   = 144
  maxOf(10,20) = 20
  minOf(10,20) = 10
  absValue(-7) = 7
  absValue(3)  = 3
  clamp(150, 0, 100) = 100
  clamp(-5, 0, 100)  = 0

=== Macro vs Inline ===
  SQUARE_MACRO(5) = 25
  squareSafe(5)   = 25
  SQUARE_MACRO(a++) = 30 (a is now 7 - incremented twice!)
  squareSafe(a++)  = 25 (a is now 6 - incremented once)

=== Temperature Conversion ===
  0 C = 32 F
  20 C = 68 F
  37 C = 98.6 F
  100 C = 212 F

  212 F = 100 C
  32  F = 0 C

=== Inline Swap ===
  Before: x=10, y=20
  After:  x=20, y=10

=== Inline Member Functions ===
  p1 = (3, 4)
  p2 = (6, 8)
  p1.getX() = 3
  p1.getY() = 4
  Distance p1 to p2 = 5
  After setX(0), setY(0): (0, 0)
  Distance to p2 = 10

=== Inline Predicates ===
  -2: even non-pos
  -1: odd  non-pos
  0: even non-pos
  1: odd  positive [in 1..4]
  2: even positive [in 1..4]
  3: odd  positive [in 1..4]
  4: even positive [in 1..4]
  5: odd  positive

=== Key Points ===
  1. 'inline' is a HINT, not a command - compiler decides
  2. Best for small, frequently-called functions
  3. Functions defined in class body are implicitly inline
  4. Prefer inline functions over macros for type safety
  5. Inline functions must be defined in every translation
     unit that uses them (typically in headers)
*/
