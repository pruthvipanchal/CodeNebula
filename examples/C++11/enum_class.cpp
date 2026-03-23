// CodeNebula - C++11 Example: Scoped Enums (enum class)
// Compile: g++ -std=c++11 -Wall -Wextra -o example enum_class.cpp

// Demonstrates enum class (scoped enumerations) introduced in C++11.
// Unlike traditional enums, scoped enums prevent implicit conversions to int,
// avoid name collisions, and allow specifying the underlying storage type.

#include <iostream>
#include <cstdint>
#include <string>

// Real-world scenario: traffic light states
enum class TrafficLight { Red, Yellow, Green };

// Specifying underlying type (useful for serialization, saving memory)
enum class HttpStatus : uint16_t {
    OK            = 200,
    NotFound      = 404,
    ServerError   = 500
};

// Compare with old-style enum (names leak into enclosing scope)
enum OldColor { RED, GREEN, BLUE };
// enum OldTraffic { RED, YELLOW, GREEN };  // ERROR: RED, GREEN clash!

// Scoped enums avoid this completely
enum class Color : uint8_t { Red, Green, Blue };
enum class Fruit { Apple, Orange, Banana };

// Helper function using scoped enum
std::string lightToString(TrafficLight light)
{
    switch (light) {
        case TrafficLight::Red:    return "RED - Stop";
        case TrafficLight::Yellow: return "YELLOW - Caution";
        case TrafficLight::Green:  return "GREEN - Go";
    }
    return "Unknown";
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic scoped enum usage
    // ------------------------------------------------------------------
    TrafficLight current = TrafficLight::Red;

    std::cout << "=== Basic enum class ===" << std::endl;
    std::cout << "  Light: " << lightToString(current) << std::endl;
    current = TrafficLight::Green;
    std::cout << "  Light: " << lightToString(current) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. No implicit conversion to int (type safety)
    // ------------------------------------------------------------------
    // int val = TrafficLight::Red;  // ERROR: no implicit conversion
    int val = static_cast<int>(TrafficLight::Red);  // explicit cast OK

    std::cout << "=== Type safety ===" << std::endl;
    std::cout << "  Red as int (explicit cast): " << val << std::endl;
    std::cout << "  Yellow as int: " << static_cast<int>(TrafficLight::Yellow) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Underlying type specification
    // ------------------------------------------------------------------
    HttpStatus code = HttpStatus::NotFound;

    std::cout << "=== Underlying type ===" << std::endl;
    std::cout << "  HttpStatus::NotFound : " << static_cast<uint16_t>(code) << std::endl;
    std::cout << "  HttpStatus::OK       : " << static_cast<uint16_t>(HttpStatus::OK) << std::endl;
    std::cout << "  sizeof(HttpStatus)   : " << sizeof(HttpStatus) << " byte(s)" << std::endl;
    std::cout << "  sizeof(Color)        : " << sizeof(Color) << " byte(s)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. No name collisions between scoped enums
    // ------------------------------------------------------------------
    Color c = Color::Red;
    Fruit f = Fruit::Apple;

    std::cout << "=== No name collisions ===" << std::endl;
    std::cout << "  Color::Red   = " << static_cast<int>(c) << std::endl;
    std::cout << "  Fruit::Apple = " << static_cast<int>(f) << std::endl;
    // Color::Red and TrafficLight::Red are completely distinct types
    // if (c == current) {}  // ERROR: cannot compare different enum types
    std::cout << "  (Color::Red and TrafficLight::Red are distinct types)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Scoped enums in switch statements
    // ------------------------------------------------------------------
    HttpStatus response = HttpStatus::ServerError;

    std::cout << "=== Switch on enum class ===" << std::endl;
    switch (response) {
        case HttpStatus::OK:
            std::cout << "  200: Success" << std::endl;
            break;
        case HttpStatus::NotFound:
            std::cout << "  404: Resource not found" << std::endl;
            break;
        case HttpStatus::ServerError:
            std::cout << "  500: Internal server error" << std::endl;
            break;
    }

    return 0;
}

/*
Expected output:

=== Basic enum class ===
  Light: RED - Stop
  Light: GREEN - Go

=== Type safety ===
  Red as int (explicit cast): 0
  Yellow as int: 1

=== Underlying type ===
  HttpStatus::NotFound : 404
  HttpStatus::OK       : 200
  sizeof(HttpStatus)   : 2 byte(s)
  sizeof(Color)        : 1 byte(s)

=== No name collisions ===
  Color::Red   = 0
  Fruit::Apple = 0
  (Color::Red and TrafficLight::Red are distinct types)

=== Switch on enum class ===
  500: Internal server error
*/
