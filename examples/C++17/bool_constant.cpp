// CodeNebula - C++17 Example: std::bool_constant
// Compile: g++ -std=c++17 -Wall -Wextra -o example bool_constant.cpp

// Demonstrates std::bool_constant, a C++17 alias for
// std::integral_constant<bool, B>. It simplifies writing custom type
// traits and serves as the base for std::true_type and std::false_type.

#include <iostream>
#include <type_traits>
#include <string>
#include <vector>

// ------------------------------------------------------------------
// Custom traits using bool_constant
// ------------------------------------------------------------------

// Check if a type is a pointer-to-const
template <typename T>
struct is_pointer_to_const : std::bool_constant<
    std::is_pointer_v<T> && std::is_const_v<std::remove_pointer_t<T>>
> {};

// Check if a type is small (fits in a register)
template <typename T>
struct is_small : std::bool_constant<(sizeof(T) <= sizeof(void*))> {};

// Check if a type is a signed integer type
template <typename T>
struct is_signed_integer : std::bool_constant<
    std::is_integral_v<T> && std::is_signed_v<T> && !std::is_same_v<T, bool>
> {};

// Conditional trait composition
template <typename T>
struct is_numeric_and_small : std::bool_constant<
    std::is_arithmetic_v<T> && is_small<T>::value
> {};

int main()
{
    // ------------------------------------------------------------------
    // 1. bool_constant basics
    // ------------------------------------------------------------------
    using always_true  = std::bool_constant<true>;
    using always_false = std::bool_constant<false>;

    std::cout << "=== bool_constant Basics ===" << std::endl;
    std::cout << "  bool_constant<true>  = " << always_true::value << std::endl;
    std::cout << "  bool_constant<false> = " << always_false::value << std::endl;
    std::cout << "  Same as true_type?   : "
              << std::is_same_v<always_true, std::true_type> << std::endl;

    // ------------------------------------------------------------------
    // 2. is_pointer_to_const
    // ------------------------------------------------------------------
    std::cout << "\n=== is_pointer_to_const ===" << std::endl;
    std::cout << "  const int*   : " << is_pointer_to_const<const int*>::value << std::endl;
    std::cout << "  int*         : " << is_pointer_to_const<int*>::value << std::endl;
    std::cout << "  int* const   : " << is_pointer_to_const<int* const>::value << std::endl;

    // ------------------------------------------------------------------
    // 3. is_small
    // ------------------------------------------------------------------
    std::cout << "\n=== is_small (<=8 bytes) ===" << std::endl;
    std::cout << "  int          : " << is_small<int>::value << std::endl;
    std::cout << "  double       : " << is_small<double>::value << std::endl;
    std::cout << "  std::string  : " << is_small<std::string>::value << std::endl;

    // ------------------------------------------------------------------
    // 4. is_signed_integer
    // ------------------------------------------------------------------
    std::cout << "\n=== is_signed_integer ===" << std::endl;
    std::cout << "  int          : " << is_signed_integer<int>::value << std::endl;
    std::cout << "  unsigned     : " << is_signed_integer<unsigned>::value << std::endl;
    std::cout << "  bool         : " << is_signed_integer<bool>::value << std::endl;
    std::cout << "  double       : " << is_signed_integer<double>::value << std::endl;

    // ------------------------------------------------------------------
    // 5. Composed trait
    // ------------------------------------------------------------------
    std::cout << "\n=== is_numeric_and_small ===" << std::endl;
    std::cout << "  int          : " << is_numeric_and_small<int>::value << std::endl;
    std::cout << "  float        : " << is_numeric_and_small<float>::value << std::endl;
    std::cout << "  long double  : " << is_numeric_and_small<long double>::value << std::endl;
    std::cout << "  std::string  : " << is_numeric_and_small<std::string>::value << std::endl;

    return 0;
}

/*
Expected output:

=== bool_constant Basics ===
  bool_constant<true>  = 1
  bool_constant<false> = 0
  Same as true_type?   : 1

=== is_pointer_to_const ===
  const int*   : 1
  int*         : 0
  int* const   : 0

=== is_small (<=8 bytes) ===
  int          : 1
  double       : 1
  std::string  : 0

=== is_signed_integer ===
  int          : 1
  unsigned     : 0
  bool         : 0
  double       : 0

=== is_numeric_and_small ===
  int          : 1
  float        : 1
  long double  : 0
  std::string  : 0
*/
