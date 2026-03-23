// CodeNebula - C++11 Example: underlying_type
// Compile: g++ -std=c++11 -Wall -Wextra -o example underlying_type.cpp

// Demonstrates std::underlying_type to get the integer type backing an enum.
// Especially useful with scoped enums (enum class) that have explicit types.

#include <iostream>
#include <type_traits>
#include <cstdint>

enum Color { Red, Green, Blue };
enum class Direction : uint8_t { North, South, East, West };
enum class BigEnum : int64_t { Value1 = 1000000000LL, Value2 };
enum SmallEnum : short { X = 1, Y = 2 };

// Generic enum-to-integer converter
template<typename E>
typename std::underlying_type<E>::type to_underlying(E e) {
    return static_cast<typename std::underlying_type<E>::type>(e);
}

int main() {
    std::cout << "=== std::underlying_type ===" << std::endl;

    // Check underlying types
    using ColorType = std::underlying_type<Color>::type;
    using DirType = std::underlying_type<Direction>::type;
    using BigType = std::underlying_type<BigEnum>::type;
    using SmallType = std::underlying_type<SmallEnum>::type;

    std::cout << "Color underlying size:     " << sizeof(ColorType) << " bytes" << std::endl;
    std::cout << "Direction is uint8_t:      "
              << std::is_same<DirType, uint8_t>::value << std::endl;
    std::cout << "BigEnum is int64_t:        "
              << std::is_same<BigType, int64_t>::value << std::endl;
    std::cout << "SmallEnum is short:        "
              << std::is_same<SmallType, short>::value << std::endl;

    // Convert enums to their underlying value
    std::cout << "\nDirection::East = " << to_underlying(Direction::East) << std::endl;
    std::cout << "BigEnum::Value1 = " << to_underlying(BigEnum::Value1) << std::endl;
    std::cout << "SmallEnum::Y = " << to_underlying(SmallEnum::Y) << std::endl;

    static_assert(std::is_same<DirType, uint8_t>::value, "Direction backed by uint8_t");
    static_assert(std::is_same<BigType, int64_t>::value, "BigEnum backed by int64_t");

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::underlying_type ===
// Color underlying size:     4 bytes
// Direction is uint8_t:      1
// BigEnum is int64_t:        1
// SmallEnum is short:        1
//
// Direction::East = 2
// BigEnum::Value1 = 1000000000
// SmallEnum::Y = 2
//
// All checks passed!
