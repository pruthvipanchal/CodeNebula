// CodeNebula - C++98 Example: Conversion Functions
// Compile: g++ -std=c++98 -Wall -Wextra -o example conversion_functions.cpp
//
// This example demonstrates:
// - User-defined conversion operators: operator double(), operator int()
// - Simulating operator bool() safely in C++98 (the "safe bool" idiom)
// - Converting constructors (implicit type conversion via single-arg ctor)
// - Controlling implicit conversions
//
// NOTE: C++98 does not have the 'explicit' keyword for conversion operators.
// 'explicit' on constructors IS available in C++98 to prevent implicit
// converting construction.

#include <iostream>

// ============================================================
// 1. Temperature class with operator double()
// ============================================================
class Temperature {
private:
    double celsius;

public:
    Temperature(double c) : celsius(c) {
        // This is a "converting constructor": allows double -> Temperature
    }

    // Conversion operator: Temperature -> double
    // Allows Temperature objects to be used where a double is expected
    operator double() const {
        std::cout << "    (operator double() called)" << std::endl;
        return celsius;
    }

    double getFahrenheit() const {
        return celsius * 9.0 / 5.0 + 32.0;
    }

    void print() const {
        std::cout << "  " << celsius << " C  ("
                  << getFahrenheit() << " F)" << std::endl;
    }
};

// ============================================================
// 2. Fraction class with operator double() and operator int()
// ============================================================
class Fraction {
private:
    int numerator;
    int denominator;

public:
    Fraction(int n, int d) : numerator(n), denominator(d) {
        if (denominator == 0) {
            std::cout << "  WARNING: zero denominator, setting to 1" << std::endl;
            denominator = 1;
        }
    }

    // Convert to double (floating-point division)
    operator double() const {
        return static_cast<double>(numerator) / denominator;
    }

    // Convert to int (integer division, truncates)
    operator int() const {
        return numerator / denominator;
    }

    void print() const {
        std::cout << "  " << numerator << "/" << denominator << std::endl;
    }
};

// ============================================================
// 3. SafeFlag: simulating "operator bool()" in C++98
//
// In C++98, a plain "operator bool()" is dangerous because bool
// implicitly converts to int, allowing nonsense like:
//    SafeFlag f;  int x = f + 3;   // compiles but is meaningless
//
// The "safe bool" idiom uses a pointer-to-member instead.
// ============================================================
class SafeFlag {
private:
    bool value;

    // Private type used only for the safe bool conversion
    typedef void (SafeFlag::*BoolType)() const;
    void safeTrue() const {}  // unused, exists only for its address

public:
    SafeFlag(bool v) : value(v) {}

    // Safe bool idiom: returns a non-NULL pointer-to-member if true,
    // NULL if false.  Works in if(), while(), &&, ||, but NOT in
    // arithmetic expressions.
    operator BoolType() const {
        return value ? &SafeFlag::safeTrue : 0;
    }
};

// ============================================================
// 4. Distance: explicit constructor to prevent implicit conversion
// ============================================================
class Distance {
private:
    double meters;

public:
    // 'explicit' prevents: Distance d = 5.0;  (must write Distance d(5.0); )
    explicit Distance(double m) : meters(m) {}

    operator double() const { return meters; }

    void print() const {
        std::cout << "  " << meters << " meters" << std::endl;
    }
};

// A function that takes a double -- demonstrates implicit conversion
void showValue(double v) {
    std::cout << "  showValue received: " << v << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "1. operator double() -- Temperature" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        Temperature t(100.0);
        t.print();

        // Implicit conversion to double via operator double()
        std::cout << "\n  Using Temperature where double is expected:" << std::endl;
        double d = t;    // calls operator double()
        std::cout << "  d = " << d << std::endl;

        std::cout << "\n  Passing Temperature to showValue(double):" << std::endl;
        showValue(t);    // implicit conversion

        std::cout << "\n  Arithmetic with Temperature:" << std::endl;
        double sum = t + 50.0;  // Temperature -> double, then + 50.0
        std::cout << "  t + 50.0 = " << sum << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "2. operator double() and operator int() -- Fraction" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        Fraction f(7, 2);
        f.print();

        double asDouble = static_cast<double>(f);  // explicit cast to pick double
        int    asInt    = static_cast<int>(f);      // explicit cast to pick int

        std::cout << "  As double: " << asDouble << std::endl;
        std::cout << "  As int:    " << asInt << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "3. SAFE BOOL IDIOM" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        SafeFlag on(true);
        SafeFlag off(false);

        // Works in boolean contexts:
        if (on)  std::cout << "  on  is truthy" << std::endl;
        if (!off) std::cout << "  off is falsy" << std::endl;

        // The following would NOT compile (safe bool prevents misuse):
        // int x = on + 3;   // ERROR: no matching operator+
        // int y = on;        // ERROR: cannot convert to int
        std::cout << "  (int x = on + 3;  would NOT compile -- safe!)" << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "4. EXPLICIT CONSTRUCTOR" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        // Distance d = 5.0;   // Would NOT compile: explicit ctor
        Distance d(5.0);       // OK: direct initialisation
        d.print();

        // But operator double() still allows implicit conversion OUT:
        double val = d;
        std::cout << "  Converted to double: " << val << std::endl;

        // Converting constructor example (Temperature allows implicit):
        Temperature t2 = 36.6;  // implicit: double -> Temperature via ctor
        std::cout << "  Implicit ctor (Temperature t2 = 36.6):" << std::endl;
        t2.print();
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "5. SUMMARY" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "  - operator T() lets a class convert to type T" << std::endl;
    std::cout << "  - Converting constructors let type T convert TO the class" << std::endl;
    std::cout << "  - Use 'explicit' on constructors to prevent surprise conversions" << std::endl;
    std::cout << "  - In C++98, use the safe-bool idiom instead of operator bool()" << std::endl;

    return 0;
}

// Expected output:
// ========================================
// 1. operator double() -- Temperature
// ========================================
//   100 C  (212 F)
//
//   Using Temperature where double is expected:
//     (operator double() called)
//   d = 100
//
//   Passing Temperature to showValue(double):
//     (operator double() called)
//   showValue received: 100
//
//   Arithmetic with Temperature:
//     (operator double() called)
//   t + 50.0 = 150
//
// ========================================
// 2. operator double() and operator int() -- Fraction
// ========================================
//   7/2
//   As double: 3.5
//   As int:    3
//
// ========================================
// 3. SAFE BOOL IDIOM
// ========================================
//   on  is truthy
//   off is falsy
//   (int x = on + 3;  would NOT compile -- safe!)
//
// ========================================
// 4. EXPLICIT CONSTRUCTOR
// ========================================
//   5 meters
//     (operator double() called)
//   Converted to double: 5
//   Implicit ctor (Temperature t2 = 36.6):
//   36.6 C  (97.88 F)
//
// ========================================
// 5. SUMMARY
// ========================================
//   ...summary text...
