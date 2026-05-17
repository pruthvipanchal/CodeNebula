// CodeNebula - C++14 Example: Variable Templates
// Compile: g++ -std=c++14 -Wall -Wextra -o example variable_templates.cpp

// Demonstrates variable templates introduced in C++14. A variable template
// defines a family of variables parameterized by type. Real-world use:
// type-specific constants like pi<float> vs pi<double>, compile-time
// configuration values, and cleaner trait-style boolean checks.

#include <iostream>
#include <cmath>
#include <iomanip>
#include <type_traits>

// ------------------------------------------------------------------
// 1. Classic use case: mathematical constants with appropriate precision
// ------------------------------------------------------------------
template<typename T>
constexpr T pi = T(3.14159265358979323846264338327950288L);

template<typename T>
constexpr T e = T(2.71828182845904523536028747135266250L);

template<typename T>
constexpr T golden_ratio = T(1.61803398874989484820458683436563812L);

// ------------------------------------------------------------------
// 2. Type trait shortcut (like C++17's _v traits, but hand-rolled)
// ------------------------------------------------------------------
template<typename T>
constexpr bool is_integral_v = std::is_integral<T>::value;

template<typename T>
constexpr bool is_floating_point_v = std::is_floating_point<T>::value;

// ------------------------------------------------------------------
// 3. Configuration constants per type
// ------------------------------------------------------------------
template<typename T>
constexpr T default_tolerance = T(1e-6);

template<>
constexpr float default_tolerance<float> = 1e-4f;  // specialization

template<>
constexpr double default_tolerance<double> = 1e-10;

// ------------------------------------------------------------------
// Helper: compute circle area using variable template pi
// ------------------------------------------------------------------
template<typename T>
T circle_area(T radius)
{
    return pi<T> * radius * radius;
}

int main()
{
    std::cout << std::setprecision(15);

    // ------------------------------------------------------------------
    // 1. Mathematical constants with different precisions
    // ------------------------------------------------------------------
    std::cout << "=== Mathematical Constants ===" << std::endl;
    std::cout << "  pi<float>        : " << pi<float> << std::endl;
    std::cout << "  pi<double>       : " << pi<double> << std::endl;
    std::cout << "  pi<long double>  : " << static_cast<double>(pi<long double>) << std::endl;
    std::cout << "  e<double>        : " << e<double> << std::endl;
    std::cout << "  golden_ratio<dbl>: " << golden_ratio<double> << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Using constants in computations
    // ------------------------------------------------------------------
    std::cout << "=== Circle Area (radius=5) ===" << std::endl;
    std::cout << std::setprecision(6);
    std::cout << "  float  : " << circle_area(5.0f) << std::endl;
    std::cout << "  double : " << circle_area(5.0) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Type trait variable templates
    // ------------------------------------------------------------------
    std::cout << "=== Type Trait Variable Templates ===" << std::endl;
    std::cout << std::boolalpha;
    std::cout << "  is_integral_v<int>      : " << is_integral_v<int> << std::endl;
    std::cout << "  is_integral_v<double>   : " << is_integral_v<double> << std::endl;
    std::cout << "  is_floating_point_v<float>: " << is_floating_point_v<float> << std::endl;
    std::cout << "  is_floating_point_v<int>  : " << is_floating_point_v<int> << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Specialized tolerance values
    // ------------------------------------------------------------------
    std::cout << "=== Specialized Tolerances ===" << std::endl;
    std::cout << std::setprecision(15);
    std::cout << "  default_tolerance<float>  : " << default_tolerance<float> << std::endl;
    std::cout << "  default_tolerance<double> : " << default_tolerance<double> << std::endl;

    return 0;
}

/*
Expected output:

=== Mathematical Constants ===
  pi<float>        : 3.14159274101257
  pi<double>       : 3.14159265358979
  pi<long double>  : 3.14159265358979
  e<double>        : 2.71828182845905
  golden_ratio<dbl>: 1.61803398874989

=== Circle Area (radius=5) ===
  float  : 78.5398
  double : 78.5398

=== Type Trait Variable Templates ===
  is_integral_v<int>      : true
  is_integral_v<double>   : false
  is_floating_point_v<float>: true
  is_floating_point_v<int>  : false

=== Specialized Tolerances ===
  default_tolerance<float>  : 0.000100000004749745
  default_tolerance<double> : 1e-10
*/
