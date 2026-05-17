// CodeNebula - C++11 Example: integral_constant
// Compile: g++ -std=c++11 -Wall -Wextra -o example integral_constant.cpp

// Demonstrates std::integral_constant, the foundation of type traits.
// std::true_type and std::false_type are integral_constant<bool, true/false>.

#include <iostream>
#include <type_traits>

// Custom type trait using integral_constant
template<typename T>
struct is_int : std::false_type {};

template<>
struct is_int<int> : std::true_type {};

// Tag dispatch example using true_type / false_type
template<typename T>
void process_impl(T val, std::true_type) {
    std::cout << "  Integer path: " << val << std::endl;
}

template<typename T>
void process_impl(T val, std::false_type) {
    std::cout << "  Non-integer path: " << val << std::endl;
}

template<typename T>
void process(T val) {
    process_impl(val, std::is_integral<T>{});
}

int main() {
    std::cout << "=== std::integral_constant ===" << std::endl;

    // integral_constant wraps a compile-time value
    using two = std::integral_constant<int, 2>;
    std::cout << "two::value = " << two::value << std::endl;
    std::cout << "two() =      " << two() << std::endl;  // operator()

    // true_type and false_type
    std::cout << "true_type:   " << std::true_type::value << std::endl;
    std::cout << "false_type:  " << std::false_type::value << std::endl;

    // Custom trait
    std::cout << "is_int<int>:    " << is_int<int>::value << std::endl;
    std::cout << "is_int<double>: " << is_int<double>::value << std::endl;

    // Tag dispatch
    std::cout << "\nTag dispatch:" << std::endl;
    process(42);
    process(3.14);

    static_assert(two::value == 2, "two is 2");
    static_assert(std::true_type::value, "true_type is true");

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::integral_constant ===
// two::value = 2
// two() =      2
// true_type:   1
// false_type:  0
// is_int<int>:    1
// is_int<double>: 0
//
// Tag dispatch:
//   Integer path: 42
//   Non-integer path: 3.14
//
// All checks passed!
