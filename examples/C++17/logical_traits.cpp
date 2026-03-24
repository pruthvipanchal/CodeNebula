// CodeNebula - C++17 Example: std::conjunction / std::disjunction / std::negation
// Compile: g++ -std=c++17 -Wall -Wextra -o example logical_traits.cpp

// Demonstrates the C++17 logical operator traits for composing type traits.
// These short-circuit at compile time, unlike raw && / || on ::value members,
// and can be used as base classes for custom traits.

#include <iostream>
#include <type_traits>
#include <string>

// ------------------------------------------------------------------
// Custom trait: is a type a numeric scalar that fits in a register?
// ------------------------------------------------------------------
template <typename T>
using is_small_numeric = std::conjunction<
    std::is_arithmetic<T>,
    std::bool_constant<(sizeof(T) <= 8)>
>;

// ------------------------------------------------------------------
// Custom trait: is a type either integral or floating point?
// ------------------------------------------------------------------
template <typename T>
using is_number = std::disjunction<
    std::is_integral<T>,
    std::is_floating_point<T>
>;

// ------------------------------------------------------------------
// Custom trait: check ALL types in a pack are integral
// ------------------------------------------------------------------
template <typename... Ts>
using all_integral = std::conjunction<std::is_integral<Ts>...>;

// ------------------------------------------------------------------
// Custom trait: check ANY type in a pack is floating point
// ------------------------------------------------------------------
template <typename... Ts>
using any_floating = std::disjunction<std::is_floating_point<Ts>...>;

int main()
{
    // ------------------------------------------------------------------
    // 1. std::conjunction (logical AND, short-circuiting)
    // ------------------------------------------------------------------
    std::cout << "=== std::conjunction ===" << std::endl;
    std::cout << "  is_small_numeric<int>        : "
              << is_small_numeric<int>::value << std::endl;
    std::cout << "  is_small_numeric<double>     : "
              << is_small_numeric<double>::value << std::endl;
    std::cout << "  is_small_numeric<std::string>: "
              << is_small_numeric<std::string>::value << std::endl;

    std::cout << "  all_integral<int,short,char> : "
              << all_integral<int, short, char>::value << std::endl;
    std::cout << "  all_integral<int,double>     : "
              << all_integral<int, double>::value << std::endl;

    // ------------------------------------------------------------------
    // 2. std::disjunction (logical OR, short-circuiting)
    // ------------------------------------------------------------------
    std::cout << "\n=== std::disjunction ===" << std::endl;
    std::cout << "  is_number<int>               : "
              << is_number<int>::value << std::endl;
    std::cout << "  is_number<std::string>       : "
              << is_number<std::string>::value << std::endl;
    std::cout << "  any_floating<int,float,char> : "
              << any_floating<int, float, char>::value << std::endl;
    std::cout << "  any_floating<int,short,char> : "
              << any_floating<int, short, char>::value << std::endl;

    // ------------------------------------------------------------------
    // 3. std::negation (logical NOT)
    // ------------------------------------------------------------------
    std::cout << "\n=== std::negation ===" << std::endl;
    std::cout << "  negation<is_integral<int>>   : "
              << std::negation<std::is_integral<int>>::value << std::endl;
    std::cout << "  negation<is_integral<float>> : "
              << std::negation<std::is_integral<float>>::value << std::endl;

    // ------------------------------------------------------------------
    // 4. Combining all three
    // ------------------------------------------------------------------
    // is_non_bool_integer: integral AND NOT bool
    using is_non_bool_int_v = std::conjunction<
        std::is_integral<int>,
        std::negation<std::is_same<int, bool>>
    >;
    using is_non_bool_bool_v = std::conjunction<
        std::is_integral<bool>,
        std::negation<std::is_same<bool, bool>>
    >;

    std::cout << "\n=== Combined ===" << std::endl;
    std::cout << "  non_bool_integer<int>  : " << is_non_bool_int_v::value << std::endl;
    std::cout << "  non_bool_integer<bool> : " << is_non_bool_bool_v::value << std::endl;

    return 0;
}

/*
Expected output:

=== std::conjunction ===
  is_small_numeric<int>        : 1
  is_small_numeric<double>     : 1
  is_small_numeric<std::string>: 0
  all_integral<int,short,char> : 1
  all_integral<int,double>     : 0

=== std::disjunction ===
  is_number<int>               : 1
  is_number<std::string>       : 0
  any_floating<int,float,char> : 1
  any_floating<int,short,char> : 0

=== std::negation ===
  negation<is_integral<int>>   : 0
  negation<is_integral<float>> : 1

=== Combined ===
  non_bool_integer<int>  : 1
  non_bool_integer<bool> : 0
*/
