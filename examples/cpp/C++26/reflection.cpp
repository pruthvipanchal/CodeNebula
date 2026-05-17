// CodeNebula - C++26 Example: Static Reflection (P2996)
// Compile: g++ -std=c++26 -Wall -Wextra -o example reflection.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// P2996 introduces static reflection via std::meta::info. This allows
// compile-time introspection of types, members, enumerators, and more.
// ^^ (reflexpr) gives a meta::info handle for any named entity.

#include <iostream>
#include <string>
#include <vector>

// --- C++26 Reflection Syntax (not yet compilable) ---
//
// #include <meta>
//
// struct Point { double x; double y; double z; };
//
// // Get meta::info for a type
// constexpr auto point_info = ^^Point;
//
// // Iterate over members at compile time
// template<typename T>
// void print_members() {
//     [:expand(std::meta::nonstatic_data_members_of(^^T)):] >> [&]<auto mem> {
//         std::cout << std::meta::name_of(mem) << " = "
//                   << obj.[:mem:] << "\n";
//     };
// }
//
// // Get enumerator names automatically
// enum class Color { Red, Green, Blue };
// constexpr auto color_name(Color c) -> std::string {
//     // Iterate enumerators of Color via reflection
//     for (auto e : std::meta::enumerators_of(^^Color))
//         if (std::meta::value_of<Color>(e) == c)
//             return std::string(std::meta::name_of(e));
//     return "unknown";
// }

// --- Simulation using C++20 features ---

struct Point { double x; double y; double z; };

enum class Color { Red, Green, Blue };

// Manual simulation of what reflection would automate
void print_point_members(const Point& p) {
    std::cout << "  x = " << p.x << std::endl;
    std::cout << "  y = " << p.y << std::endl;
    std::cout << "  z = " << p.z << std::endl;
}

std::string color_name(Color c) {
    switch (c) {
        case Color::Red:   return "Red";
        case Color::Green: return "Green";
        case Color::Blue:  return "Blue";
    }
    return "unknown";
}

int main() {
    std::cout << "=== C++26 Static Reflection (Simulated) ===" << std::endl;

    Point p{1.0, 2.5, 3.7};
    std::cout << "Point members:" << std::endl;
    print_point_members(p);

    std::cout << "Color names:" << std::endl;
    std::cout << "  " << color_name(Color::Red) << std::endl;
    std::cout << "  " << color_name(Color::Green) << std::endl;
    std::cout << "  " << color_name(Color::Blue) << std::endl;

    std::cout << "Reflection eliminates boilerplate for serialization, "
              << "enum-to-string, etc." << std::endl;
    return 0;
}

// Expected output:
// === C++26 Static Reflection (Simulated) ===
// Point members:
//   x = 1
//   y = 2.5
//   z = 3.7
// Color names:
//   Red
//   Green
//   Blue
// Reflection eliminates boilerplate for serialization, enum-to-string, etc.
