// CodeNebula - C++11 Example: common_type
// Compile: g++ -std=c++11 -Wall -Wextra -o example common_type.cpp

// Demonstrates std::common_type which determines the common type that
// all template arguments can be implicitly converted to.

#include <iostream>
#include <type_traits>

// Generic max using common_type for return type
template<typename T, typename U>
typename std::common_type<T, U>::type
generic_max(T a, U b) {
    return (a > b) ? a : b;
}

int main() {
    std::cout << "=== std::common_type ===" << std::endl;

    // Common type of numeric types follows promotion rules
    using IntDouble = std::common_type<int, double>::type;
    using IntFloat = std::common_type<int, float>::type;
    using IntLong = std::common_type<int, long long>::type;
    using CharInt = std::common_type<char, int>::type;

    std::cout << "common(int, double):    is double? "
              << std::is_same<IntDouble, double>::value << std::endl;
    std::cout << "common(int, float):     is float?  "
              << std::is_same<IntFloat, float>::value << std::endl;
    std::cout << "common(int, long long): is long long? "
              << std::is_same<IntLong, long long>::value << std::endl;
    std::cout << "common(char, int):      is int?    "
              << std::is_same<CharInt, int>::value << std::endl;

    // Three or more types
    using Triple = std::common_type<char, int, double>::type;
    std::cout << "common(char, int, double): is double? "
              << std::is_same<Triple, double>::value << std::endl;

    // Practical use: mixed-type arithmetic
    auto result = generic_max(42, 3.14);
    std::cout << "\ngeneric_max(42, 3.14) = " << result << std::endl;
    std::cout << "Result is double: "
              << std::is_same<decltype(result), double>::value << std::endl;

    static_assert(std::is_same<IntDouble, double>::value, "int+double -> double");

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::common_type ===
// common(int, double):    is double? 1
// common(int, float):     is float?  1
// common(int, long long): is long long? 1
// common(char, int):      is int?    1
// common(char, int, double): is double? 1
//
// generic_max(42, 3.14) = 42
// Result is double: 1
//
// All checks passed!
