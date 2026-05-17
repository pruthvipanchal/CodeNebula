// CodeNebula - C++11 Example: Explicit Conversion Operators
// Compile: g++ -std=c++11 -Wall -Wextra -o example explicit_conversion.cpp

// Demonstrates explicit conversion operators introduced in C++11. Without
// 'explicit', conversion operators can cause surprising implicit conversions.
// Marking them explicit requires a cast or boolean context, improving safety.

#include <iostream>
#include <string>

// Real-world scenario: a safe boolean wrapper (like smart pointers)
class OptionalInt {
    int value_;
    bool hasValue_;

public:
    OptionalInt() : value_(0), hasValue_(false) {}
    explicit OptionalInt(int v) : value_(v), hasValue_(true) {}

    // Explicit conversion to bool (safe for if-statements)
    explicit operator bool() const
    {
        return hasValue_;
    }

    int value() const { return value_; }
    bool has_value() const { return hasValue_; }
};

// Without explicit: dangerous implicit conversions
class UnsafeHandle {
    int id_;
public:
    UnsafeHandle(int id) : id_(id) {}

    // Non-explicit: allows int x = handle; silently
    operator int() const { return id_; }
};

// With explicit: safe, requires intentional cast
class SafeHandle {
    int id_;
public:
    explicit SafeHandle(int id) : id_(id) {}

    explicit operator int() const { return id_; }

    int id() const { return id_; }
};

// Percentage class with explicit double conversion
class Percentage {
    double value_;
public:
    explicit Percentage(double v) : value_(v) {}

    explicit operator double() const { return value_ / 100.0; }

    double raw() const { return value_; }
};

int main()
{
    // ------------------------------------------------------------------
    // 1. Explicit operator bool (the most common use case)
    // ------------------------------------------------------------------
    OptionalInt empty;
    OptionalInt present(42);

    std::cout << "=== Explicit operator bool ===" << std::endl;
    if (present) {
        std::cout << "  present has value: " << present.value() << std::endl;
    }
    if (!empty) {
        std::cout << "  empty has no value" << std::endl;
    }
    // bool b = present;     // ERROR: explicit prevents implicit conversion
    bool b = static_cast<bool>(present);  // OK: explicit cast
    std::cout << "  static_cast<bool>(present): " << b << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Unsafe (non-explicit) conversion operator
    // ------------------------------------------------------------------
    UnsafeHandle uh(42);
    int x = uh;                // compiles! implicit conversion
    int y = uh + 10;           // compiles! uh silently becomes int

    std::cout << "=== Unsafe (non-explicit) ===" << std::endl;
    std::cout << "  int x = handle:    " << x << std::endl;
    std::cout << "  handle + 10:       " << y << " (implicit conversion!)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Safe (explicit) conversion operator
    // ------------------------------------------------------------------
    SafeHandle sh(42);
    // int a = sh;            // ERROR: no implicit conversion
    // int b = sh + 10;       // ERROR: no implicit conversion
    int a = static_cast<int>(sh);     // OK: explicit cast
    int c = static_cast<int>(sh) + 10;

    std::cout << "=== Safe (explicit) ===" << std::endl;
    std::cout << "  static_cast<int>(sh):      " << a << std::endl;
    std::cout << "  static_cast<int>(sh) + 10: " << c << std::endl;
    std::cout << "  sh.id():                   " << sh.id() << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Percentage with explicit double conversion
    // ------------------------------------------------------------------
    Percentage score(85.5);
    // double d = score;           // ERROR: explicit
    double d = static_cast<double>(score);  // OK: 0.855

    std::cout << "=== Percentage ===" << std::endl;
    std::cout << "  raw value: " << score.raw() << "%" << std::endl;
    std::cout << "  as double: " << d << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Explicit bool in logical expressions (contextual conversion)
    // ------------------------------------------------------------------
    OptionalInt opt1(10);
    OptionalInt opt2(20);

    std::cout << "=== Contextual bool conversion ===" << std::endl;
    // These work because &&, ||, !, ?: use contextual conversion to bool
    std::cout << "  opt1 && opt2  : " << (opt1 && opt2 ? "both set" : "not both") << std::endl;
    std::cout << "  opt1 || empty : " << (opt1 || empty ? "at least one" : "none") << std::endl;
    std::cout << "  !empty        : " << (!empty ? "true" : "false") << std::endl;

    return 0;
}

/*
Expected output:

=== Explicit operator bool ===
  present has value: 42
  empty has no value
  static_cast<bool>(present): 1

=== Unsafe (non-explicit) ===
  int x = handle:    42
  handle + 10:       52 (implicit conversion!)

=== Safe (explicit) ===
  static_cast<int>(sh):      42
  static_cast<int>(sh) + 10: 52
  sh.id():                   42

=== Percentage ===
  raw value: 85.5%
  as double: 0.855

=== Contextual bool conversion ===
  opt1 && opt2  : both set
  opt1 || empty : at least one
  !empty        : true
*/
