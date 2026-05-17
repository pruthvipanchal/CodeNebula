// CodeNebula - C++20 Example: std::convertible_to Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example convertible_to.cpp

// std::convertible_to<From, To> checks whether a type From is both
// implicitly and explicitly convertible to type To.

#include <concepts>
#include <iostream>
#include <string>

// Accept anything convertible to double
template <typename T>
    requires std::convertible_to<T, double>
double to_double(T value) {
    return static_cast<double>(value);
}

// Accept anything convertible to std::string
template <std::convertible_to<std::string> T>
void print_as_string(T&& value) {
    std::string s = std::forward<T>(value);
    std::cout << "As string: \"" << s << "\"\n";
}

// Compile-time trait inspection
template <typename From, typename To>
void check_convertible(const char* from_name, const char* to_name) {
    std::cout << from_name << " -> " << to_name << ": "
              << std::convertible_to<From, To> << "\n";
}

int main() {
    // int, float, short are all convertible to double
    std::cout << "int as double: " << to_double(42) << "\n";
    std::cout << "float as double: " << to_double(3.14f) << "\n";
    std::cout << "short as double: " << to_double(short(7)) << "\n";

    // const char* and string literals convert to std::string
    print_as_string("hello world");
    print_as_string(std::string("from string"));

    // Check various conversions
    std::cout << "\nConversion checks:\n";
    check_convertible<int, double>("int", "double");
    check_convertible<double, int>("double", "int");
    check_convertible<int, bool>("int", "bool");
    check_convertible<const char*, std::string>("const char*", "string");
    check_convertible<int, std::string>("int", "string");
    check_convertible<float, long>("float", "long");

    return 0;
}

// Expected output:
// int as double: 42
// float as double: 3.14
// short as double: 7
// As string: "hello world"
// As string: "from string"
//
// Conversion checks:
// int -> double: 1
// double -> int: 1
// int -> bool: 1
// const char* -> string: 1
// int -> string: 0
// float -> long: 1
