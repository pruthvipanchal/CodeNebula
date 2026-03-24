// CodeNebula - C++17 Example: Hexadecimal Floating-Point Literals
// Compile: g++ -std=c++17 -Wall -Wextra -o example hex_float_literals.cpp

// Demonstrates C++17 hexadecimal floating-point literals. Format:
//   0xMMMp+EEE  or  0xMMM.FFFpEEE
// where M/F are hex mantissa digits and E is a decimal (base-2) exponent.
// The value is: mantissa * 2^exponent
// Hex floats provide exact representation without decimal rounding issues.

#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic hex float literals
    // ------------------------------------------------------------------
    double a = 0x1p0;       // 1.0 * 2^0 = 1.0
    double b = 0x1p1;       // 1.0 * 2^1 = 2.0
    double c = 0x1p4;       // 1.0 * 2^4 = 16.0
    double d = 0xAp0;       // 10.0 * 2^0 = 10.0
    double e = 0x1p-1;      // 1.0 * 2^(-1) = 0.5

    std::cout << "=== basic hex floats ===" << std::endl;
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "  0x1p0   = " << a << "  (1 * 2^0)" << std::endl;
    std::cout << "  0x1p1   = " << b << "  (1 * 2^1)" << std::endl;
    std::cout << "  0x1p4   = " << c << "  (1 * 2^4)" << std::endl;
    std::cout << "  0xAp0   = " << d << "  (10 * 2^0)" << std::endl;
    std::cout << "  0x1p-1  = " << e << "  (1 * 2^-1)" << std::endl;

    // ------------------------------------------------------------------
    // 2. Hex floats with fractional hex digits
    // ------------------------------------------------------------------
    double f = 0x1.8p0;     // (1 + 8/16) * 2^0 = 1.5
    double g = 0x1.8p1;     // (1 + 8/16) * 2^1 = 3.0
    double h = 0x1.4p2;     // (1 + 4/16) * 2^2 = 5.0
    double i = 0x1.Cp3;     // (1 + 12/16) * 2^3 = 14.0

    std::cout << "\n=== fractional hex digits ===" << std::endl;
    std::cout << "  0x1.8p0 = " << f << "  (1.5 * 2^0)" << std::endl;
    std::cout << "  0x1.8p1 = " << g << "  (1.5 * 2^1)" << std::endl;
    std::cout << "  0x1.4p2 = " << h << "  (1.25 * 2^2)" << std::endl;
    std::cout << "  0x1.Cp3 = " << i << "  (1.75 * 2^3)" << std::endl;

    // ------------------------------------------------------------------
    // 3. Representing well-known constants exactly
    // ------------------------------------------------------------------
    double pi_approx = 0x1.921FB54442D18p+1;  // closest double to pi
    double e_approx  = 0x1.5BF0A8B145769p+1;  // closest double to e

    std::cout << "\n=== well-known constants ===" << std::endl;
    std::cout << std::setprecision(15);
    std::cout << "  pi (hex float) = " << pi_approx << std::endl;
    std::cout << "  pi (M_PI)      = " << M_PI << std::endl;
    std::cout << "  e  (hex float) = " << e_approx << std::endl;

    // ------------------------------------------------------------------
    // 4. float suffix (f) and long double suffix (L)
    // ------------------------------------------------------------------
    float  fval = 0x1.0p10f;    // 1024.0f
    double dval = 0x1.0p10;     // 1024.0
    long double ldval = 0x1.0p10L;  // 1024.0L

    std::cout << "\n=== type suffixes ===" << std::endl;
    std::cout << std::setprecision(1);
    std::cout << "  0x1.0p10f (float)      : " << fval << std::endl;
    std::cout << "  0x1.0p10  (double)     : " << dval << std::endl;
    std::cout << "  0x1.0p10L (long double): " << static_cast<double>(ldval) << std::endl;

    // ------------------------------------------------------------------
    // 5. Why hex floats matter: exact representation
    // ------------------------------------------------------------------
    double decimal = 0.1;        // not exactly representable in binary
    double hex_tenth = 0x1.999999999999Ap-4;  // exact double for 0.1

    std::cout << "\n=== exact representation ===" << std::endl;
    std::cout << std::setprecision(20);
    std::cout << "  0.1 (decimal)    = " << decimal << std::endl;
    std::cout << "  0x...p-4 (hex)   = " << hex_tenth << std::endl;
    std::cout << "  Are equal?       : " << std::boolalpha
              << (decimal == hex_tenth) << std::endl;

    return 0;
}

/*
Expected output:

=== basic hex floats ===
  0x1p0   = 1.000000  (1 * 2^0)
  0x1p1   = 2.000000  (1 * 2^1)
  0x1p4   = 16.000000  (1 * 2^4)
  0xAp0   = 10.000000  (10 * 2^0)
  0x1p-1  = 0.500000  (1 * 2^-1)

=== fractional hex digits ===
  0x1.8p0 = 1.500000  (1.5 * 2^0)
  0x1.8p1 = 3.000000  (1.5 * 2^1)
  0x1.4p2 = 5.000000  (1.25 * 2^2)
  0x1.Cp3 = 14.000000  (1.75 * 2^3)

=== well-known constants ===
  pi (hex float) = 3.141592653589793
  pi (M_PI)      = 3.141592653589793
  e  (hex float) = 2.718281828459045

=== type suffixes ===
  0x1.0p10f (float)      : 1024.0
  0x1.0p10  (double)     : 1024.0
  0x1.0p10L (long double): 1024.0

=== exact representation ===
  0.1 (decimal)    = 0.10000000000000000555
  0x...p-4 (hex)   = 0.10000000000000000555
  Are equal?       : true
*/
