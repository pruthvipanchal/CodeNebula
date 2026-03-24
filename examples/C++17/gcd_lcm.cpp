// CodeNebula - C++17 Example: std::gcd and std::lcm
// Compile: g++ -std=c++17 -Wall -Wextra -o example gcd_lcm.cpp

// Demonstrates std::gcd (greatest common divisor) and std::lcm (least common
// multiple) from <numeric>. These are constexpr functions that work with any
// integer types and handle edge cases like zero and negative values.

#include <iostream>
#include <numeric>
#include <vector>

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic GCD
    // ------------------------------------------------------------------
    std::cout << "=== std::gcd ===" << std::endl;
    std::cout << "  gcd(12, 8)    = " << std::gcd(12, 8) << std::endl;
    std::cout << "  gcd(100, 75)  = " << std::gcd(100, 75) << std::endl;
    std::cout << "  gcd(17, 13)   = " << std::gcd(17, 13) << std::endl;
    std::cout << "  gcd(0, 5)     = " << std::gcd(0, 5) << std::endl;
    std::cout << "  gcd(0, 0)     = " << std::gcd(0, 0) << std::endl;

    // ------------------------------------------------------------------
    // 2. GCD with negative numbers (always non-negative result)
    // ------------------------------------------------------------------
    std::cout << "\n=== GCD with Negatives ===" << std::endl;
    std::cout << "  gcd(-12, 8)   = " << std::gcd(-12, 8) << std::endl;
    std::cout << "  gcd(-12, -8)  = " << std::gcd(-12, -8) << std::endl;

    // ------------------------------------------------------------------
    // 3. Basic LCM
    // ------------------------------------------------------------------
    std::cout << "\n=== std::lcm ===" << std::endl;
    std::cout << "  lcm(4, 6)     = " << std::lcm(4, 6) << std::endl;
    std::cout << "  lcm(12, 8)    = " << std::lcm(12, 8) << std::endl;
    std::cout << "  lcm(7, 5)     = " << std::lcm(7, 5) << std::endl;
    std::cout << "  lcm(0, 5)     = " << std::lcm(0, 5) << std::endl;

    // ------------------------------------------------------------------
    // 4. constexpr usage
    // ------------------------------------------------------------------
    constexpr int g = std::gcd(48, 36);
    constexpr int l = std::lcm(48, 36);
    static_assert(g == 12, "GCD of 48,36 should be 12");
    static_assert(l == 144, "LCM of 48,36 should be 144");

    std::cout << "\n=== constexpr ===" << std::endl;
    std::cout << "  gcd(48, 36) = " << g << std::endl;
    std::cout << "  lcm(48, 36) = " << l << std::endl;

    // ------------------------------------------------------------------
    // 5. Practical: simplify a fraction
    // ------------------------------------------------------------------
    int num = 84, den = 120;
    int divisor = std::gcd(num, den);

    std::cout << "\n=== Simplify Fraction ===" << std::endl;
    std::cout << "  " << num << "/" << den << " = "
              << num / divisor << "/" << den / divisor << std::endl;

    // ------------------------------------------------------------------
    // 6. Practical: GCD/LCM of multiple values
    // ------------------------------------------------------------------
    std::vector<int> values = {12, 18, 24, 36};

    int multi_gcd = values[0];
    int multi_lcm = values[0];
    for (size_t i = 1; i < values.size(); ++i) {
        multi_gcd = std::gcd(multi_gcd, values[i]);
        multi_lcm = std::lcm(multi_lcm, values[i]);
    }

    std::cout << "\n=== Multiple Values {12,18,24,36} ===" << std::endl;
    std::cout << "  GCD = " << multi_gcd << std::endl;
    std::cout << "  LCM = " << multi_lcm << std::endl;

    return 0;
}

/*
Expected output:

=== std::gcd ===
  gcd(12, 8)    = 4
  gcd(100, 75)  = 25
  gcd(17, 13)   = 1
  gcd(0, 5)     = 5
  gcd(0, 0)     = 0

=== GCD with Negatives ===
  gcd(-12, 8)   = 4
  gcd(-12, -8)  = 4

=== std::lcm ===
  lcm(4, 6)     = 12
  lcm(12, 8)    = 24
  lcm(7, 5)     = 35
  lcm(0, 5)     = 0

=== constexpr ===
  gcd(48, 36) = 12
  lcm(48, 36) = 144

=== Simplify Fraction ===
  84/120 = 7/10

=== Multiple Values {12,18,24,36} ===
  GCD = 6
  LCM = 72
*/
