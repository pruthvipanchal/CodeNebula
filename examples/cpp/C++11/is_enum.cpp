// CodeNebula - C++11 Example: is_enum
// Compile: g++ -std=c++11 -Wall -Wextra -o example is_enum.cpp

// Demonstrates std::is_enum to check if a type is an enumeration.
// Works with both unscoped (C-style) and scoped (enum class) enums.

#include <iostream>
#include <type_traits>

enum Color { Red, Green, Blue };
enum class Direction : int { North, South, East, West };
struct MyStruct {};
class MyClass {};

int main() {
    std::cout << "=== std::is_enum ===" << std::endl;

    std::cout << "Color:          " << std::is_enum<Color>::value << std::endl;
    std::cout << "Direction:      " << std::is_enum<Direction>::value << std::endl;
    std::cout << "int:            " << std::is_enum<int>::value << std::endl;
    std::cout << "MyStruct:       " << std::is_enum<MyStruct>::value << std::endl;
    std::cout << "MyClass:        " << std::is_enum<MyClass>::value << std::endl;
    std::cout << "bool:           " << std::is_enum<bool>::value << std::endl;
    std::cout << "char:           " << std::is_enum<char>::value << std::endl;

    static_assert(std::is_enum<Color>::value, "Color is an enum");
    static_assert(std::is_enum<Direction>::value, "Direction is an enum");
    static_assert(!std::is_enum<int>::value, "int is not an enum");
    static_assert(!std::is_enum<MyStruct>::value, "struct is not an enum");

    // cv-qualified enums still match
    std::cout << "\nconst Color:    " << std::is_enum<const Color>::value << std::endl;
    std::cout << "volatile Color: " << std::is_enum<volatile Color>::value << std::endl;
    std::cout << "Color*:         " << std::is_enum<Color*>::value << std::endl;

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::is_enum ===
// Color:          1
// Direction:      1
// int:            0
// MyStruct:       0
// MyClass:        0
// bool:           0
// char:           0
//
// const Color:    1
// volatile Color: 1
// Color*:         0
//
// All checks passed!
