// CodeNebula - C++11 Example: Variadic Templates
// Compile: g++ -std=c++11 -Wall -Wextra -o example variadic_templates.cpp

// Demonstrates variadic templates: templates that accept any number of
// arguments via parameter packs. This enables type-safe printf, tuple-like
// classes, and recursive template expansion patterns.

#include <iostream>
#include <string>
#include <sstream>

// ------------------------------------------------------------------
// 1. Recursive print: base case + variadic expansion
// ------------------------------------------------------------------
// Base case: no arguments left
void print()
{
    std::cout << std::endl;
}

// Recursive case: peel off first argument, recurse on rest
template <typename T, typename... Args>
void print(const T& first, const Args&... rest)
{
    std::cout << first;
    if (sizeof...(rest) > 0) {
        std::cout << ", ";
    }
    print(rest...);
}

// ------------------------------------------------------------------
// 2. Variadic sum (compile-time recursion)
// ------------------------------------------------------------------
template <typename T>
T sum(T value)
{
    return value;
}

template <typename T, typename... Args>
T sum(T first, Args... rest)
{
    return first + sum(rest...);
}

// ------------------------------------------------------------------
// 3. Type-safe string builder
// ------------------------------------------------------------------
void buildString(std::ostringstream&) { }

template <typename T, typename... Args>
void buildString(std::ostringstream& oss, const T& first, const Args&... rest)
{
    oss << first;
    buildString(oss, rest...);
}

template <typename... Args>
std::string concat(const Args&... args)
{
    std::ostringstream oss;
    buildString(oss, args...);
    return oss.str();
}

// ------------------------------------------------------------------
// 4. Count arguments with sizeof...
// ------------------------------------------------------------------
template <typename... Args>
std::size_t countArgs(const Args&...)
{
    return sizeof...(Args);
}

int main()
{
    // ------------------------------------------------------------------
    // Variadic print
    // ------------------------------------------------------------------
    std::cout << "=== Variadic print ===" << std::endl;
    std::cout << "  ";
    print(1, 2.5, "hello", 'A', true);
    std::cout << "  ";
    print("single argument");
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Variadic sum
    // ------------------------------------------------------------------
    std::cout << "=== Variadic sum ===" << std::endl;
    std::cout << "  sum(1,2,3,4,5)     : " << sum(1, 2, 3, 4, 5) << std::endl;
    std::cout << "  sum(1.1, 2.2, 3.3) : " << sum(1.1, 2.2, 3.3) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Type-safe string concatenation
    // ------------------------------------------------------------------
    std::string result = concat("User ", "Alice", " scored ", 95, " points");

    std::cout << "=== String builder ===" << std::endl;
    std::cout << "  " << result << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // sizeof... operator
    // ------------------------------------------------------------------
    std::cout << "=== sizeof... ===" << std::endl;
    std::cout << "  countArgs(1,2,3)          : " << countArgs(1, 2, 3) << std::endl;
    std::cout << "  countArgs('a',\"b\",3.0,4) : " << countArgs('a', "b", 3.0, 4) << std::endl;
    std::cout << "  countArgs()               : " << countArgs() << std::endl;

    return 0;
}

/*
Expected output:

=== Variadic print ===
  1, 2.5, hello, A, 1
  single argument

=== Variadic sum ===
  sum(1,2,3,4,5)     : 15
  sum(1.1, 2.2, 3.3) : 6.6

=== String builder ===
  User Alice scored 95 points

=== sizeof... ===
  countArgs(1,2,3)          : 3
  countArgs('a',"b",3.0,4) : 4
  countArgs()               : 0
*/
