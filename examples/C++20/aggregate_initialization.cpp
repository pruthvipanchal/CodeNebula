// CodeNebula - C++20 Example: Aggregate Initialization Improvements
// Compile: g++ -std=c++20 -Wall -Wextra -o example aggregate_initialization.cpp

// C++20 improves aggregate initialization in several ways:
//   1. Parenthesized initialization of aggregates: T(args...)
//   2. Designated initializers: T{.member = value}
//   3. CTAD (class template argument deduction) for aggregates

#include <iostream>
#include <array>
#include <string>
#include <memory>

// A simple aggregate (all public, no user-declared constructors)
struct Point {
    double x;
    double y;
    double z;
};

// Aggregate with default member initializers
struct Config {
    std::string name = "default";
    int width = 800;
    int height = 600;
    bool fullscreen = false;
};

// Nested aggregates
struct Line {
    Point start;
    Point end;
};

struct Color {
    unsigned char r, g, b, a;
};

struct ColoredPoint {
    Point position;
    Color color;
    std::string label;
};

void print_point(const Point& p) {
    std::cout << "(" << p.x << ", " << p.y << ", " << p.z << ")";
}

void print_config(const Config& c) {
    std::cout << "Config{name=\"" << c.name << "\", "
              << c.width << "x" << c.height
              << (c.fullscreen ? ", fullscreen" : ", windowed") << "}";
}

int main() {
    std::cout << "=== C++20 Aggregate Initialization ===\n\n";

    // --- Designated initializers (C++20) ---
    std::cout << "Designated initializers:\n";
    Point p1{.x = 1.0, .y = 2.0, .z = 3.0};
    std::cout << "  Point{.x=1, .y=2, .z=3} = ";
    print_point(p1);
    std::cout << "\n";

    // Can skip members — they get default-initialized
    Point p2{.x = 5.0, .z = 10.0};  // y is 0.0
    std::cout << "  Point{.x=5, .z=10}      = ";
    print_point(p2);
    std::cout << "\n";

    // Designated initializers with defaults
    Config cfg{.name = "MyApp", .fullscreen = true};
    std::cout << "  "; print_config(cfg); std::cout << "\n\n";

    // --- Parenthesized initialization of aggregates (C++20) ---
    std::cout << "Parenthesized aggregate init:\n";
    Point p3(10.0, 20.0, 30.0);  // new in C++20!
    std::cout << "  Point(10, 20, 30) = ";
    print_point(p3);
    std::cout << "\n";

    // This enables make_unique/make_shared with aggregates!
    auto ptr = std::make_unique<Point>(1.0, 2.0, 3.0);
    std::cout << "  make_unique<Point>(1,2,3) = ";
    print_point(*ptr);
    std::cout << "\n\n";

    // --- Nested aggregate initialization ---
    std::cout << "Nested aggregates:\n";
    Line line{
        .start = {.x = 0.0, .y = 0.0, .z = 0.0},
        .end   = {.x = 1.0, .y = 1.0, .z = 1.0}
    };
    std::cout << "  Line from ";
    print_point(line.start);
    std::cout << " to ";
    print_point(line.end);
    std::cout << "\n";

    ColoredPoint cp{
        .position = {.x = 5.0, .y = 10.0, .z = 0.0},
        .color    = {255, 0, 128, 255},
        .label    = "marker"
    };
    std::cout << "  ColoredPoint \"" << cp.label << "\" at ";
    print_point(cp.position);
    std::cout << " color=RGBA(" << (int)cp.color.r << ","
              << (int)cp.color.g << "," << (int)cp.color.b << ","
              << (int)cp.color.a << ")\n\n";

    // --- Array initialization ---
    std::cout << "Array aggregate init:\n";
    std::array arr{1, 2, 3, 4, 5};  // CTAD deduces std::array<int,5>
    std::cout << "  std::array{1,2,3,4,5}: ";
    for (int v : arr) std::cout << v << " ";
    std::cout << "\n";

    return 0;
}

// Expected output:
// === C++20 Aggregate Initialization ===
//
// Designated initializers:
//   Point{.x=1, .y=2, .z=3} = (1, 2, 3)
//   Point{.x=5, .z=10}      = (5, 0, 10)
//   Config{name="MyApp", 800x600, fullscreen}
//
// Parenthesized aggregate init:
//   Point(10, 20, 30) = (10, 20, 30)
//   make_unique<Point>(1,2,3) = (1, 2, 3)
//
// Nested aggregates:
//   Line from (0, 0, 0) to (1, 1, 1)
//   ColoredPoint "marker" at (5, 10, 0) color=RGBA(255,0,128,255)
//
// Array aggregate init:
//   std::array{1,2,3,4,5}: 1 2 3 4 5
