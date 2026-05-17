// CodeNebula - C++26 Example: User-Generated static_assert Messages
// Compile: g++ -std=c++26 -Wall -Wextra -o example static_assert_message.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// C++26 allows static_assert messages to be generated at compile time,
// not just string literals. The message can be any constant expression
// that is convertible to a string-like type (has .data() and .size()).

#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>

// --- C++26 static_assert Message Syntax ---
//
// // Previously (C++11): message must be a string literal
// static_assert(sizeof(int) == 4, "int must be 4 bytes");
//
// // C++26: message can be a constexpr expression with .data()/.size()
// template<typename T>
// constexpr auto type_size_msg() {
//     // Build message at compile time
//     return std::format("Expected size 8, got {}", sizeof(T));
// }
// static_assert(sizeof(double) == 8, type_size_msg<double>());
//
// // Useful for template libraries: generate contextual error messages
// template<typename T>
// void process() {
//     static_assert(std::is_integral_v<T>,
//         std::format("process() requires integral type, got: {}",
//                     std::meta::name_of(^^T)));  // With reflection!
// }

// --- Simulation using C++20 features ---

// Demonstrate the concept with runtime messages
template<typename T>
constexpr bool check_integral() { return std::is_integral_v<T>; }

template<typename T>
constexpr bool check_size(std::size_t expected) { return sizeof(T) == expected; }

// C++20 static_assert still requires string literals
static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");
static_assert(std::is_integral_v<int>, "int must be integral");

// Simulate what generated messages would look like
template<typename T>
std::string generate_type_message(std::string_view context) {
    std::string msg = std::string(context) + ": sizeof(T) = "
                      + std::to_string(sizeof(T)) + " bytes";
    return msg;
}

int main() {
    std::cout << "=== C++26 User-Generated static_assert Messages (Simulated) ==="
              << std::endl;

    // Show compile-time checks that pass
    std::cout << "static_assert(sizeof(int) >= 4) : passed" << std::endl;
    std::cout << "static_assert(is_integral<int>) : passed" << std::endl;

    // Demonstrate the kind of messages C++26 can generate
    std::cout << "\nGenerated messages (would be compile-time in C++26):" << std::endl;
    std::cout << "  " << generate_type_message<int>("check_int") << std::endl;
    std::cout << "  " << generate_type_message<double>("check_double") << std::endl;
    std::cout << "  " << generate_type_message<char>("check_char") << std::endl;

    // Show the improvement
    std::cout << "\nC++11: static_assert(cond, \"fixed string\");" << std::endl;
    std::cout << "C++26: static_assert(cond, format(\"size={}\", sizeof(T)));" << std::endl;

    std::cout << "User-generated messages make template errors readable." << std::endl;
    return 0;
}

// Expected output:
// === C++26 User-Generated static_assert Messages (Simulated) ===
// static_assert(sizeof(int) >= 4) : passed
// static_assert(is_integral<int>) : passed
//
// Generated messages (would be compile-time in C++26):
//   check_int: sizeof(T) = 4 bytes
//   check_double: sizeof(T) = 8 bytes
//   check_char: sizeof(T) = 1 bytes
//
// C++11: static_assert(cond, "fixed string");
// C++26: static_assert(cond, format("size={}", sizeof(T)));
// User-generated messages make template errors readable.
