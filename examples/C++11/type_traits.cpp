// CodeNebula - C++11 Example: Type Traits Overview
// Compile: g++ -std=c++11 -Wall -Wextra -o example type_traits.cpp

// Demonstrates the <type_traits> header: compile-time type inspection and
// transformation utilities. Type traits enable SFINAE, static dispatch, and
// generic programming by querying properties of types at compile time.

#include <iostream>
#include <type_traits>
#include <string>
#include <vector>

// Real-world scenario: optimized copy for trivially copyable types
template <typename T>
void smartCopy(const T& src, T& dst)
{
    if (std::is_trivially_copyable<T>::value) {
        std::cout << "  -> Using fast memcpy-style copy" << std::endl;
    } else {
        std::cout << "  -> Using element-wise copy" << std::endl;
    }
    dst = src;
}

// Compile-time dispatch based on type category
template <typename T>
void describe()
{
    std::cout << "  is_integral      : " << std::is_integral<T>::value << std::endl;
    std::cout << "  is_floating_point: " << std::is_floating_point<T>::value << std::endl;
    std::cout << "  is_arithmetic    : " << std::is_arithmetic<T>::value << std::endl;
    std::cout << "  is_class         : " << std::is_class<T>::value << std::endl;
    std::cout << "  is_pointer       : " << std::is_pointer<T>::value << std::endl;
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Primary type categories
    // ------------------------------------------------------------------
    std::cout << "=== int traits ===" << std::endl;
    describe<int>();
    std::cout << std::endl;

    std::cout << "=== double traits ===" << std::endl;
    describe<double>();
    std::cout << std::endl;

    std::cout << "=== std::string traits ===" << std::endl;
    describe<std::string>();
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Type properties
    // ------------------------------------------------------------------
    std::cout << "=== Type properties ===" << std::endl;
    std::cout << "  is_const<const int>     : " << std::is_const<const int>::value << std::endl;
    std::cout << "  is_volatile<volatile int>: " << std::is_volatile<volatile int>::value << std::endl;
    std::cout << "  is_signed<int>          : " << std::is_signed<int>::value << std::endl;
    std::cout << "  is_unsigned<unsigned>    : " << std::is_unsigned<unsigned>::value << std::endl;
    std::cout << "  is_empty<std::string>   : " << std::is_empty<std::string>::value << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Type relationships
    // ------------------------------------------------------------------
    std::cout << "=== Type relationships ===" << std::endl;
    std::cout << "  is_same<int, int>       : " << std::is_same<int, int>::value << std::endl;
    std::cout << "  is_same<int, long>      : " << std::is_same<int, long>::value << std::endl;
    std::cout << "  is_convertible<int,double>: " << std::is_convertible<int, double>::value << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Type transformations
    // ------------------------------------------------------------------
    typedef std::remove_const<const int>::type NoConstInt;
    typedef std::remove_reference<int&>::type NoRefInt;
    typedef std::add_pointer<int>::type IntPtr;

    std::cout << "=== Type transformations ===" << std::endl;
    std::cout << "  remove_const<const int> is int  : "
              << std::is_same<NoConstInt, int>::value << std::endl;
    std::cout << "  remove_reference<int&> is int   : "
              << std::is_same<NoRefInt, int>::value << std::endl;
    std::cout << "  add_pointer<int> is int*        : "
              << std::is_same<IntPtr, int*>::value << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Practical use: optimized copy selection
    // ------------------------------------------------------------------
    int a = 42, b = 0;
    std::string s1 = "hello", s2;

    std::cout << "=== Smart copy dispatch ===" << std::endl;
    std::cout << "  Copying int:" << std::endl;
    smartCopy(a, b);
    std::cout << "  Result: " << b << std::endl;

    std::cout << "  Copying string:" << std::endl;
    smartCopy(s1, s2);
    std::cout << "  Result: " << s2 << std::endl;

    return 0;
}

/*
Expected output:

=== int traits ===
  is_integral      : 1
  is_floating_point: 0
  is_arithmetic    : 1
  is_class         : 0
  is_pointer       : 0

=== double traits ===
  is_integral      : 0
  is_floating_point: 1
  is_arithmetic    : 1
  is_class         : 0
  is_pointer       : 0

=== std::string traits ===
  is_integral      : 0
  is_floating_point: 0
  is_arithmetic    : 0
  is_class         : 1
  is_pointer       : 0

=== Type properties ===
  is_const<const int>     : 1
  is_volatile<volatile int>: 1
  is_signed<int>          : 1
  is_unsigned<unsigned>    : 1
  is_empty<std::string>   : 0

=== Type relationships ===
  is_same<int, int>       : 1
  is_same<int, long>      : 0
  is_convertible<int,double>: 1

=== Type transformations ===
  remove_const<const int> is int  : 1
  remove_reference<int&> is int   : 1
  add_pointer<int> is int*        : 1

=== Smart copy dispatch ===
  Copying int:
  -> Using fast memcpy-style copy
  Result: 42
  Copying string:
  -> Using element-wise copy
  Result: hello
*/
