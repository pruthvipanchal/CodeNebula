// CodeNebula - C++17 Example: std::void_t
// Compile: g++ -std=c++17 -Wall -Wextra -o example void_t.cpp

// Demonstrates std::void_t, a utility alias template that maps any set of
// types to void. It is the key building block for SFINAE-based detection
// idioms -- checking if a type has certain members, typedefs, or operations.

#include <iostream>
#include <type_traits>
#include <string>
#include <vector>

// ------------------------------------------------------------------
// 1. Detect if a type has a .size() member function
// ------------------------------------------------------------------
template <typename, typename = std::void_t<>>
struct has_size : std::false_type {};

template <typename T>
struct has_size<T, std::void_t<decltype(std::declval<T>().size())>>
    : std::true_type {};

// ------------------------------------------------------------------
// 2. Detect if a type has a nested ::value_type typedef
// ------------------------------------------------------------------
template <typename, typename = std::void_t<>>
struct has_value_type : std::false_type {};

template <typename T>
struct has_value_type<T, std::void_t<typename T::value_type>>
    : std::true_type {};

// ------------------------------------------------------------------
// 3. Detect if a type supports operator+ with itself
// ------------------------------------------------------------------
template <typename, typename = std::void_t<>>
struct is_addable : std::false_type {};

template <typename T>
struct is_addable<T, std::void_t<decltype(std::declval<T>() + std::declval<T>())>>
    : std::true_type {};

// ------------------------------------------------------------------
// 4. Detect if a type has begin/end (iterable)
// ------------------------------------------------------------------
template <typename, typename = std::void_t<>>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T, std::void_t<
    decltype(std::declval<T>().begin()),
    decltype(std::declval<T>().end())>>
    : std::true_type {};

struct SimpleStruct { int x; };

int main()
{
    std::cout << "=== has_size ===" << std::endl;
    std::cout << "  vector<int>  : " << has_size<std::vector<int>>::value << std::endl;
    std::cout << "  string       : " << has_size<std::string>::value << std::endl;
    std::cout << "  int          : " << has_size<int>::value << std::endl;
    std::cout << "  SimpleStruct : " << has_size<SimpleStruct>::value << std::endl;

    std::cout << "\n=== has_value_type ===" << std::endl;
    std::cout << "  vector<int>  : " << has_value_type<std::vector<int>>::value << std::endl;
    std::cout << "  string       : " << has_value_type<std::string>::value << std::endl;
    std::cout << "  int          : " << has_value_type<int>::value << std::endl;

    std::cout << "\n=== is_addable ===" << std::endl;
    std::cout << "  int          : " << is_addable<int>::value << std::endl;
    std::cout << "  string       : " << is_addable<std::string>::value << std::endl;
    std::cout << "  SimpleStruct : " << is_addable<SimpleStruct>::value << std::endl;

    std::cout << "\n=== is_iterable ===" << std::endl;
    std::cout << "  vector<int>  : " << is_iterable<std::vector<int>>::value << std::endl;
    std::cout << "  string       : " << is_iterable<std::string>::value << std::endl;
    std::cout << "  int          : " << is_iterable<int>::value << std::endl;

    return 0;
}

/*
Expected output:

=== has_size ===
  vector<int>  : 1
  string       : 1
  int          : 0
  SimpleStruct : 0

=== has_value_type ===
  vector<int>  : 1
  string       : 1
  int          : 0

=== is_addable ===
  int          : 1
  string       : 1
  SimpleStruct : 0

=== is_iterable ===
  vector<int>  : 1
  string       : 1
  int          : 0
*/
