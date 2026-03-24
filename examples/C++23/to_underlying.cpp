// CodeNebula - C++23 Example: std::to_underlying
// Compile: g++ -std=c++23 -Wall -Wextra -o example to_underlying.cpp
// Note: Requires GCC 13+ / Clang 17+

#include <iostream>
#include <type_traits>
#include <utility>

// std::to_underlying converts a scoped enum to its underlying integer type.
// It replaces the verbose static_cast<std::underlying_type_t<E>>(value) pattern.

enum class Color : unsigned char { Red = 1, Green = 2, Blue = 4 };
enum class Flags : unsigned int { None = 0, Read = 1, Write = 2, Execute = 4 };
enum class Severity : int { Debug = -1, Info = 0, Warning = 1, Error = 2 };

// Generic flag printer using to_underlying
template <typename E>
void print_flag_value(const char* name, E value) {
    std::cout << name << " = " << std::to_underlying(value) << "\n";
}

// Combine flags using to_underlying for bitwise ops
Flags operator|(Flags a, Flags b) {
    return static_cast<Flags>(std::to_underlying(a) | std::to_underlying(b));
}

bool has_flag(Flags set, Flags flag) {
    return (std::to_underlying(set) & std::to_underlying(flag)) != 0;
}

int main() {
    std::cout << "=== std::to_underlying ===\n\n";

    // Basic conversion
    std::cout << "Color::Red   = " << std::to_underlying(Color::Red) << "\n";
    std::cout << "Color::Green = " << std::to_underlying(Color::Green) << "\n";
    std::cout << "Color::Blue  = " << std::to_underlying(Color::Blue) << "\n\n";

    // Negative underlying values
    std::cout << "Severity::Debug   = " << std::to_underlying(Severity::Debug) << "\n";
    std::cout << "Severity::Warning = " << std::to_underlying(Severity::Warning) << "\n\n";

    // Combining flags
    Flags perms = Flags::Read | Flags::Write;
    std::cout << "Read | Write = " << std::to_underlying(perms) << "\n";
    std::cout << "Has Read?    " << (has_flag(perms, Flags::Read) ? "yes" : "no") << "\n";
    std::cout << "Has Execute? " << (has_flag(perms, Flags::Execute) ? "yes" : "no") << "\n\n";

    // Type verification
    auto val = std::to_underlying(Color::Red);
    std::cout << "to_underlying(Color) is unsigned char? "
              << std::is_same_v<decltype(val), unsigned char> << "\n";

    // Generic usage
    print_flag_value("Flags::Execute", Flags::Execute);

    return 0;
}

// Expected output:
// === std::to_underlying ===
//
// Color::Red   = 1
// Color::Green = 2
// Color::Blue  = 4
//
// Severity::Debug   = -1
// Severity::Warning = 1
//
// Read | Write = 3
// Has Read?    yes
// Has Execute? no
//
// to_underlying(Color) is unsigned char? 1
// Flags::Execute = 4
