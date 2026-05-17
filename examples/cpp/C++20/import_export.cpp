// CodeNebula - C++20 Example: Import/Export Declarations
// Compile: g++ -std=c++20 -Wall -Wextra -o example import_export.cpp
//
// NOTE: Full module import/export requires compiler-specific build steps.
// This file documents the syntax and semantics, with a compilable fallback.
//
// === C++20 Module Import/Export Syntax ===
//
// --- Module interface unit (geometry.cppm) ---
//   export module geometry;              // declares this as module "geometry"
//
//   // Export individual declarations
//   export struct Point { double x, y; };
//
//   export double distance(Point a, Point b);
//
//   // Export a block of declarations
//   export {
//       struct Circle {
//           Point center;
//           double radius;
//       };
//       double area(const Circle& c);
//       double circumference(const Circle& c);
//   }
//
//   // Non-exported (module-private) helper
//   double square(double x) { return x * x; }  // not visible to importers
//
// --- Module implementation unit (geometry_impl.cpp) ---
//   module geometry;                     // implements module "geometry"
//   import <cmath>;                      // import a header unit
//
//   double distance(Point a, Point b) {
//       return std::sqrt(square(a.x - b.x) + square(a.y - b.y));
//   }
//
// --- Consumer (main.cpp) ---
//   import geometry;                     // import the module
//   import <iostream>;                   // import header unit

#include <iostream>
#include <cmath>

// Compilable fallback simulating module structure
namespace geometry {
    struct Point { double x, y; };

    // Private to the "module" — not exported
    namespace detail {
        double square(double v) { return v * v; }
    }

    // Exported declarations
    double distance(Point a, Point b) {
        return std::sqrt(detail::square(a.x - b.x) + detail::square(a.y - b.y));
    }

    struct Circle {
        Point center;
        double radius;
    };

    double area(const Circle& c) {
        return 3.14159265358979 * c.radius * c.radius;
    }

    double circumference(const Circle& c) {
        return 2.0 * 3.14159265358979 * c.radius;
    }
}

int main() {
    using namespace geometry;

    std::cout << "=== C++20 Import/Export (simulated) ===\n\n";

    Point a{0.0, 0.0}, b{3.0, 4.0};
    std::cout << "distance({0,0}, {3,4}) = " << distance(a, b) << "\n";

    Circle c{{1.0, 2.0}, 5.0};
    std::cout << "Circle at (1,2) r=5:\n";
    std::cout << "  area          = " << area(c) << "\n";
    std::cout << "  circumference = " << circumference(c) << "\n";

    std::cout << "\nImport/Export key points:\n";
    std::cout << "  - 'export module X;' declares a module interface\n";
    std::cout << "  - 'module X;' declares an implementation unit\n";
    std::cout << "  - 'import X;' brings in exported names\n";
    std::cout << "  - 'import <header>;' imports a header unit\n";
    std::cout << "  - Non-exported names stay module-private\n";

    return 0;
}

// Expected output:
// === C++20 Import/Export (simulated) ===
//
// distance({0,0}, {3,4}) = 5
// Circle at (1,2) r=5:
//   area          = 78.5398
//   circumference = 31.4159
//
// Import/Export key points:
//   - 'export module X;' declares a module interface
//   - 'module X;' declares an implementation unit
//   - 'import X;' brings in exported names
//   - 'import <header>;' imports a header unit
//   - Non-exported names stay module-private
