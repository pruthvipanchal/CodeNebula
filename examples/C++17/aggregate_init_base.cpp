// CodeNebula - C++17 Example: Aggregate Initialization with Base Classes
// Compile: g++ -std=c++17 -Wall -Wextra -o example aggregate_init_base.cpp

// Demonstrates C++17 aggregate initialization for types with base classes.
// Before C++17, a class with base classes could not be an aggregate. Now,
// public non-virtual base classes can be initialized with brace-enclosed
// initializer lists.

#include <iostream>
#include <string>

// ------------------------------------------------------------------
// 1. Simple base + derived aggregate
// ------------------------------------------------------------------
struct Point2D {
    double x;
    double y;
};

struct Point3D : Point2D {
    double z;
};
// Point3D is an aggregate in C++17: base class members come first

// ------------------------------------------------------------------
// 2. Multiple base classes
// ------------------------------------------------------------------
struct Name {
    std::string first;
    std::string last;
};

struct Age {
    int years;
};

struct Person : Name, Age {
    std::string email;
};
// Person has: first, last (from Name), years (from Age), email (own)

// ------------------------------------------------------------------
// 3. Nested aggregate with base
// ------------------------------------------------------------------
struct Color {
    int r, g, b;
};

struct Pixel : Point2D, Color {
    float alpha;
};

// ------------------------------------------------------------------
// 4. Empty base optimization still works
// ------------------------------------------------------------------
struct Tag {};

struct TaggedValue : Tag {
    int value;
    std::string label;
};

int main()
{
    // 1. Single base
    std::cout << "=== Point3D (single base) ===" << std::endl;
    Point3D p = {{1.0, 2.0}, 3.0};  // {Point2D{x, y}, z}
    std::cout << "  x=" << p.x << ", y=" << p.y << ", z=" << p.z << std::endl;

    // Also works without inner braces (flattened)
    Point3D p2 = {4.0, 5.0, 6.0};
    std::cout << "  x=" << p2.x << ", y=" << p2.y << ", z=" << p2.z << std::endl;

    // 2. Multiple bases
    std::cout << "\n=== Person (multiple bases) ===" << std::endl;
    Person person = {{"Alice", "Smith"}, {30}, "alice@example.com"};
    std::cout << "  Name : " << person.first << " " << person.last << std::endl;
    std::cout << "  Age  : " << person.years << std::endl;
    std::cout << "  Email: " << person.email << std::endl;

    // 3. Complex nested aggregate
    std::cout << "\n=== Pixel (two bases) ===" << std::endl;
    Pixel px = {{10.0, 20.0}, {255, 128, 0}, 0.75f};
    std::cout << "  pos  : (" << px.x << ", " << px.y << ")" << std::endl;
    std::cout << "  color: (" << px.r << ", " << px.g << ", " << px.b << ")" << std::endl;
    std::cout << "  alpha: " << px.alpha << std::endl;

    // 4. Empty base
    std::cout << "\n=== TaggedValue (empty base) ===" << std::endl;
    TaggedValue tv = {{}, 42, "answer"};  // {} for empty Tag base
    std::cout << "  value: " << tv.value << std::endl;
    std::cout << "  label: " << tv.label << std::endl;

    // 5. Array of aggregates with bases
    std::cout << "\n=== array of Point3D ===" << std::endl;
    Point3D points[] = {
        {{0, 0}, 0},
        {{1, 0}, 0},
        {{0, 1}, 0},
        {{1, 1}, 1}
    };
    for (const auto& pt : points) {
        std::cout << "  (" << pt.x << ", " << pt.y << ", " << pt.z << ")" << std::endl;
    }

    return 0;
}

/*
Expected output:

=== Point3D (single base) ===
  x=1, y=2, z=3
  x=4, y=5, z=6

=== Person (multiple bases) ===
  Name : Alice Smith
  Age  : 30
  Email: alice@example.com

=== Pixel (two bases) ===
  pos  : (10, 20)
  color: (255, 128, 0)
  alpha: 0.75

=== TaggedValue (empty base) ===
  value: 42
  label: answer

=== array of Point3D ===
  (0, 0, 0)
  (1, 0, 0)
  (0, 1, 0)
  (1, 1, 1)
*/
