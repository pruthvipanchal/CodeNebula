// CodeNebula - C++98 Example: Namespaces
// Compile: g++ -std=c++98 -Wall -Wextra -o example namespaces.cpp

// Namespaces prevent name collisions by grouping related declarations under
// a named scope. This example covers: declaring namespaces, using directive,
// using declaration, nested namespaces, namespace aliases, and anonymous
// (unnamed) namespaces.

#include <iostream>
#include <string>
#include <cmath>

// ------------------------------------------------------------------
// Two libraries with conflicting names
// ------------------------------------------------------------------
namespace Graphics {
    struct Point {
        double x, y;
        Point(double px, double py) : x(px), y(py) {}
    };

    void draw(const Point& p) {
        std::cout << "Graphics::draw -> pixel at (" << p.x << ", " << p.y << ")" << std::endl;
    }

    double distance(const Point& a, const Point& b) {
        double dx = a.x - b.x;
        double dy = a.y - b.y;
        return std::sqrt(dx * dx + dy * dy);
    }
}

namespace Physics {
    struct Point {
        double x, y, z;
        Point(double px, double py, double pz) : x(px), y(py), z(pz) {}
    };

    void draw(const Point& p) {
        std::cout << "Physics::draw -> particle at ("
                  << p.x << ", " << p.y << ", " << p.z << ")" << std::endl;
    }

    double mass(double volume, double density) {
        return volume * density;
    }
}

// ------------------------------------------------------------------
// Nested namespaces (C++98 style - must nest explicitly)
// ------------------------------------------------------------------
namespace Company {
    namespace Department {
        namespace Team {
            std::string getName() {
                return "Alpha Team";
            }
            int getSize() {
                return 5;
            }
        }
    }

    std::string getCompanyName() {
        return "CodeNebula Corp";
    }
}

// ------------------------------------------------------------------
// Namespace alias
// ------------------------------------------------------------------
namespace CDT = Company::Department::Team;

// ------------------------------------------------------------------
// Adding to an existing namespace (namespaces are open)
// ------------------------------------------------------------------
namespace Graphics {
    // We can add more members to Graphics at any time
    void drawLine(const Point& a, const Point& b) {
        std::cout << "Graphics::drawLine from (" << a.x << "," << a.y
                  << ") to (" << b.x << "," << b.y << ")" << std::endl;
    }
}

// ------------------------------------------------------------------
// Anonymous (unnamed) namespace - internal linkage, like 'static'
// Visible only in this translation unit
// ------------------------------------------------------------------
namespace {
    int internalCounter = 0;

    void incrementCounter() {
        ++internalCounter;
    }

    int getCounter() {
        return internalCounter;
    }
}

// ------------------------------------------------------------------
// A namespace for math utilities
// ------------------------------------------------------------------
namespace MathUtils {
    const double PI = 3.14159265358979;

    double circleArea(double radius) {
        return PI * radius * radius;
    }

    double degToRad(double degrees) {
        return degrees * PI / 180.0;
    }
}

int main() {
    std::cout << "=== C++98 Namespaces ===" << std::endl;

    // --- 1. Fully qualified names to resolve ambiguity ---
    std::cout << "\n--- 1. Fully qualified names ---" << std::endl;
    Graphics::Point gp(3.0, 4.0);
    Physics::Point pp(1.0, 2.0, 3.0);

    Graphics::draw(gp);
    // Expected: Graphics::draw -> pixel at (3, 4)
    Physics::draw(pp);
    // Expected: Physics::draw -> particle at (1, 2, 3)

    // --- 2. using declaration (imports one name) ---
    std::cout << "\n--- 2. using declaration ---" << std::endl;
    {
        using Graphics::drawLine;
        Graphics::Point a(0.0, 0.0);
        Graphics::Point b(10.0, 10.0);
        drawLine(a, b);  // No need for Graphics:: prefix
        // Expected: Graphics::drawLine from (0,0) to (10,10)
    }

    // --- 3. using directive (imports entire namespace) ---
    std::cout << "\n--- 3. using directive ---" << std::endl;
    {
        using namespace MathUtils;
        std::cout << "PI = " << PI << std::endl;
        std::cout << "Area of circle (r=5): " << circleArea(5.0) << std::endl;
        std::cout << "90 deg in radians: " << degToRad(90.0) << std::endl;
        // Expected:
        // PI = 3.14159
        // Area of circle (r=5): 78.5398
        // 90 deg in radians: 1.5708
    }

    // --- 4. Nested namespaces ---
    std::cout << "\n--- 4. Nested namespaces ---" << std::endl;
    std::cout << "Company: " << Company::getCompanyName() << std::endl;
    std::cout << "Team: " << Company::Department::Team::getName() << std::endl;
    std::cout << "Size: " << Company::Department::Team::getSize() << std::endl;
    // Expected:
    // Company: CodeNebula Corp
    // Team: Alpha Team
    // Size: 5

    // --- 5. Namespace alias ---
    std::cout << "\n--- 5. Namespace alias ---" << std::endl;
    std::cout << "Via alias CDT: " << CDT::getName()
              << " (size " << CDT::getSize() << ")" << std::endl;
    // Expected: Via alias CDT: Alpha Team (size 5)

    // --- 6. Anonymous namespace ---
    std::cout << "\n--- 6. Anonymous namespace ---" << std::endl;
    std::cout << "Counter: " << getCounter() << std::endl;
    // Expected: 0
    incrementCounter();
    incrementCounter();
    incrementCounter();
    std::cout << "Counter after 3 increments: " << getCounter() << std::endl;
    // Expected: 3

    // --- 7. Both namespaces used together ---
    std::cout << "\n--- 7. Mixed usage ---" << std::endl;
    Graphics::Point g1(0, 0);
    Graphics::Point g2(3, 4);
    std::cout << "Distance: " << Graphics::distance(g1, g2) << std::endl;
    // Expected: Distance: 5

    std::cout << "Mass (vol=2, dens=7.8): "
              << Physics::mass(2.0, 7.8) << std::endl;
    // Expected: Mass (vol=2, dens=7.8): 15.6

    return 0;
}

/*
Expected Output:
=== C++98 Namespaces ===

--- 1. Fully qualified names ---
Graphics::draw -> pixel at (3, 4)
Physics::draw -> particle at (1, 2, 3)

--- 2. using declaration ---
Graphics::drawLine from (0,0) to (10,10)

--- 3. using directive ---
PI = 3.14159
Area of circle (r=5): 78.5398
90 deg in radians: 1.5708

--- 4. Nested namespaces ---
Company: CodeNebula Corp
Team: Alpha Team
Size: 5

--- 5. Namespace alias ---
Via alias CDT: Alpha Team (size 5)

--- 6. Anonymous namespace ---
Counter: 0
Counter after 3 increments: 3

--- 7. Mixed usage ---
Distance: 5
Mass (vol=2, dens=7.8): 15.6
*/
