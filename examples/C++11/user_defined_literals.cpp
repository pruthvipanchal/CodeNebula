// CodeNebula - C++11 Example: User-Defined Literals
// Compile: g++ -std=c++11 -Wall -Wextra -o example user_defined_literals.cpp

// Demonstrates user-defined literals (operator"") for creating custom
// suffixes. This enables type-safe, readable unit representations
// that catch dimension errors at compile time.

#include <iostream>
#include <string>
#include <cstddef>

// ------------------------------------------------------------------
// 1. Distance literals (type-safe unit conversion)
// ------------------------------------------------------------------
struct Meters {
    double value;
    explicit Meters(double v) : value(v) {}
};

struct Kilometers {
    double value;
    explicit Kilometers(double v) : value(v) {}
};

// User-defined literal operators (must start with _)
Meters operator"" _m(long double val)
{
    return Meters(static_cast<double>(val));
}

Meters operator"" _m(unsigned long long val)
{
    return Meters(static_cast<double>(val));
}

Kilometers operator"" _km(long double val)
{
    return Kilometers(static_cast<double>(val));
}

Meters toMeters(Kilometers km)
{
    return Meters(km.value * 1000.0);
}

// ------------------------------------------------------------------
// 2. Duration literals
// ------------------------------------------------------------------
struct Seconds {
    double value;
    explicit Seconds(double v) : value(v) {}
};

Seconds operator"" _sec(long double val)
{
    return Seconds(static_cast<double>(val));
}

Seconds operator"" _min(long double val)
{
    return Seconds(static_cast<double>(val) * 60.0);
}

Seconds operator"" _hr(long double val)
{
    return Seconds(static_cast<double>(val) * 3600.0);
}

// ------------------------------------------------------------------
// 3. Temperature literal
// ------------------------------------------------------------------
struct Celsius {
    double value;
    explicit Celsius(double v) : value(v) {}
    double toFahrenheit() const { return value * 9.0 / 5.0 + 32.0; }
};

Celsius operator"" _degC(long double val)
{
    return Celsius(static_cast<double>(val));
}

// ------------------------------------------------------------------
// 4. String literal (integer suffix for repeated strings)
// ------------------------------------------------------------------
std::string operator"" _times3(const char* str, std::size_t len)
{
    std::string base(str, len);
    return base + base + base;
}

int main()
{
    // ------------------------------------------------------------------
    // Distance literals
    // ------------------------------------------------------------------
    auto height = 1.75_m;
    auto runway = 3_m;
    auto marathon = 42.195_km;
    Meters marathonM = toMeters(marathon);

    std::cout << "=== Distance literals ===" << std::endl;
    std::cout << "  Height:   " << height.value << " m" << std::endl;
    std::cout << "  Runway:   " << runway.value << " m" << std::endl;
    std::cout << "  Marathon: " << marathon.value << " km = "
              << marathonM.value << " m" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Duration literals
    // ------------------------------------------------------------------
    auto sprint   = 9.58_sec;
    auto meeting  = 30.0_min;
    auto workday  = 8.0_hr;

    std::cout << "=== Duration literals ===" << std::endl;
    std::cout << "  Sprint:  " << sprint.value << " seconds" << std::endl;
    std::cout << "  Meeting: " << meeting.value << " seconds" << std::endl;
    std::cout << "  Workday: " << workday.value << " seconds" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Temperature literal
    // ------------------------------------------------------------------
    auto boiling = 100.0_degC;
    auto body    = 37.0_degC;

    std::cout << "=== Temperature literals ===" << std::endl;
    std::cout << "  Boiling: " << boiling.value << " C = "
              << boiling.toFahrenheit() << " F" << std::endl;
    std::cout << "  Body:    " << body.value << " C = "
              << body.toFahrenheit() << " F" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // String literal
    // ------------------------------------------------------------------
    auto cheer = "Hip! "_times3;

    std::cout << "=== String literal ===" << std::endl;
    std::cout << "  " << cheer << std::endl;
    std::cout << "  " << "Go! "_times3 << std::endl;

    return 0;
}

/*
Expected output:

=== Distance literals ===
  Height:   1.75 m
  Runway:   3 m
  Marathon: 42.195 km = 42195 m

=== Duration literals ===
  Sprint:  9.58 seconds
  Meeting: 1800 seconds
  Workday: 28800 seconds

=== Temperature literals ===
  Boiling: 100 C = 212 F
  Body:    37 C = 98.6 F

=== String literal ===
  Hip! Hip! Hip!
  Go! Go! Go!
*/
