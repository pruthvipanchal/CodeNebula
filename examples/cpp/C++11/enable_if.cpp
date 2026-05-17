// CodeNebula - C++11 Example: enable_if
// Compile: g++ -std=c++11 -Wall -Wextra -o example enable_if.cpp

// Demonstrates std::enable_if for SFINAE (Substitution Failure Is Not An Error).
// enable_if conditionally removes function overloads from consideration.

#include <iostream>
#include <type_traits>
#include <string>

// Only enabled for integral types
template<typename T>
typename std::enable_if<std::is_integral<T>::value, std::string>::type
classify(T val) {
    return std::to_string(val) + " is an integer";
}

// Only enabled for floating-point types
template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, std::string>::type
classify(T val) {
    return std::to_string(val) + " is a float";
}

// enable_if as default template parameter
template<typename T,
         typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0>
T safe_add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << "=== std::enable_if ===" << std::endl;

    // SFINAE selects the correct overload
    std::cout << classify(42) << std::endl;
    std::cout << classify(3.14) << std::endl;
    std::cout << classify(true) << std::endl;
    std::cout << classify(2.5f) << std::endl;

    // safe_add only works with arithmetic types
    std::cout << "\nsafe_add(10, 20) = " << safe_add(10, 20) << std::endl;
    std::cout << "safe_add(1.5, 2.5) = " << safe_add(1.5, 2.5) << std::endl;

    // Uncommenting below would cause a compile error:
    // classify(std::string("hello"));  // no matching overload
    // safe_add(std::string("a"), std::string("b"));  // not arithmetic

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::enable_if ===
// 42 is an integer
// 3.140000 is a float
// 1 is an integer
// 2.500000 is a float
//
// safe_add(10, 20) = 30
// safe_add(1.5, 2.5) = 4
//
// All checks passed!
