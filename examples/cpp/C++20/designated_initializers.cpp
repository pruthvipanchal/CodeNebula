// CodeNebula - C++20 Example: Designated Initializers
// Compile: g++ -std=c++20 -Wall -Wextra -o example designated_initializers.cpp

// Demonstrates C++20 designated initializers: naming fields in aggregate
// initialization with .member = value syntax.

#include <iostream>
#include <string>

// ------------------------------------------------------------------
// 1. Simple aggregate with designated initializers
// ------------------------------------------------------------------
struct Point {
    double x;
    double y;
    double z;
};

// ------------------------------------------------------------------
// 2. Struct with mixed types
// ------------------------------------------------------------------
struct Config {
    int width;
    int height;
    bool fullscreen;
    double scale;
    std::string title;
};

// ------------------------------------------------------------------
// 3. Nested aggregates
// ------------------------------------------------------------------
struct Color {
    int r, g, b, a;
};

struct Rectangle {
    Point origin;
    double width;
    double height;
    Color color;
};

// ------------------------------------------------------------------
// 4. Struct with default member values
// ------------------------------------------------------------------
struct Options {
    int maxRetries = 3;
    double timeout = 30.0;
    bool verbose = false;
    std::string logFile = "app.log";
};

void print_point(const Point& p) {
    std::cout << "  (" << p.x << ", " << p.y << ", " << p.z << ")" << std::endl;
}

void print_config(const Config& c) {
    std::cout << "  Title: " << c.title << std::endl;
    std::cout << "  Size: " << c.width << "x" << c.height << std::endl;
    std::cout << "  Fullscreen: " << (c.fullscreen ? "yes" : "no") << std::endl;
    std::cout << "  Scale: " << c.scale << std::endl;
}

void print_rect(const Rectangle& r) {
    std::cout << "  Origin: (" << r.origin.x << ", " << r.origin.y << ")" << std::endl;
    std::cout << "  Size: " << r.width << "x" << r.height << std::endl;
    std::cout << "  Color: rgba(" << r.color.r << "," << r.color.g
              << "," << r.color.b << "," << r.color.a << ")" << std::endl;
}

void print_opts(const Options& o) {
    std::cout << "  maxRetries=" << o.maxRetries
              << " timeout=" << o.timeout
              << " verbose=" << o.verbose
              << " log=" << o.logFile << std::endl;
}

int main()
{
    std::cout << "=== Simple Designated Initializers ===" << std::endl;
    Point p1 = {.x = 1.0, .y = 2.0, .z = 3.0};
    print_point(p1);

    // Omit some fields (they are zero-initialized)
    Point p2 = {.x = 5.0, .z = 10.0};
    print_point(p2);

    std::cout << "\n=== Config Struct ===" << std::endl;
    Config cfg = {
        .width = 1920,
        .height = 1080,
        .fullscreen = true,
        .scale = 1.5,
        .title = "My Application"
    };
    print_config(cfg);

    std::cout << "\n=== Nested Aggregates ===" << std::endl;
    Rectangle rect = {
        .origin = {.x = 10.0, .y = 20.0, .z = 0.0},
        .width = 100.0,
        .height = 50.0,
        .color = {.r = 255, .g = 128, .b = 0, .a = 255}
    };
    print_rect(rect);

    std::cout << "\n=== With Default Values ===" << std::endl;
    Options defaults = {};
    std::cout << "  Defaults:";
    print_opts(defaults);

    Options custom = {.maxRetries = 5, .verbose = true, .logFile = "debug.log"};
    std::cout << "  Custom: ";
    print_opts(custom);

    Options minimal = {.timeout = 60.0};
    std::cout << "  Minimal:";
    print_opts(minimal);

    return 0;
}

/*
Expected output:

=== Simple Designated Initializers ===
  (1, 2, 3)
  (5, 0, 10)

=== Config Struct ===
  Title: My Application
  Size: 1920x1080
  Fullscreen: yes
  Scale: 1.5

=== Nested Aggregates ===
  Origin: (10, 20)
  Size: 100x50
  Color: rgba(255,128,0,255)

=== With Default Values ===
  Defaults:  maxRetries=3 timeout=30 verbose=0 log=app.log
  Custom:   maxRetries=5 timeout=30 verbose=1 log=debug.log
  Minimal:  maxRetries=3 timeout=60 verbose=0 log=app.log
*/
