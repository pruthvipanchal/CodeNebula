// CodeNebula - C++98 Example: Operator Overloading
// Compile: g++ -std=c++98 -Wall -Wextra -o example operator_overloading.cpp

// Demonstrates overloading +, ==, <<, and [] operators for a Vector2D class.
// Operator overloading lets user-defined types behave like built-in types,
// enabling natural syntax such as v1 + v2, v1 == v2, cout << v, and v[0].

#include <iostream>
#include <cmath>

class Vector2D {
private:
    double components[2]; // x stored at [0], y stored at [1]

public:
    // Constructor with default arguments (C++98 style)
    Vector2D(double x = 0.0, double y = 0.0) {
        components[0] = x;
        components[1] = y;
    }

    // Accessor functions
    double getX() const { return components[0]; }
    double getY() const { return components[1]; }

    // ------------------------------------------------------------------
    // Overload: operator+ (member function, returns a new Vector2D)
    // ------------------------------------------------------------------
    Vector2D operator+(const Vector2D& rhs) const {
        return Vector2D(components[0] + rhs.components[0],
                        components[1] + rhs.components[1]);
    }

    // ------------------------------------------------------------------
    // Overload: operator== (member function, compares two vectors)
    // ------------------------------------------------------------------
    bool operator==(const Vector2D& rhs) const {
        // Using a small epsilon for floating-point comparison
        const double eps = 1e-9;
        return std::fabs(components[0] - rhs.components[0]) < eps
            && std::fabs(components[1] - rhs.components[1]) < eps;
    }

    // ------------------------------------------------------------------
    // Overload: operator[] (allows indexed access to x and y)
    // Non-const version returns a reference for assignment.
    // ------------------------------------------------------------------
    double& operator[](int index) {
        if (index < 0 || index > 1) {
            std::cerr << "Warning: index " << index
                      << " out of range, clamping to 0" << std::endl;
            return components[0];
        }
        return components[index];
    }

    // Const version for read-only access on const objects
    const double& operator[](int index) const {
        if (index < 0 || index > 1) {
            std::cerr << "Warning: index " << index
                      << " out of range, clamping to 0" << std::endl;
            return components[0];
        }
        return components[index];
    }

    // ------------------------------------------------------------------
    // Overload: operator<< (must be a friend, not a member)
    // This lets us write: std::cout << myVector;
    // ------------------------------------------------------------------
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);
};

// Definition of the friend operator<<
std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
    os << "(" << v.components[0] << ", " << v.components[1] << ")";
    return os;
}

int main() {
    std::cout << "=== C++98 Operator Overloading ===" << std::endl;

    // --- operator+ ---
    Vector2D a(3.0, 4.0);
    Vector2D b(1.0, 2.0);
    Vector2D c = a + b;

    std::cout << "\n--- operator+ ---" << std::endl;
    std::cout << "a     = " << a << std::endl;
    std::cout << "b     = " << b << std::endl;
    std::cout << "a + b = " << c << std::endl;
    // Expected: a + b = (4, 6)

    // Chained addition
    Vector2D d(0.5, 0.5);
    Vector2D sum = a + b + d;
    std::cout << "a + b + d = " << sum << std::endl;
    // Expected: (4.5, 6.5)

    // --- operator== ---
    std::cout << "\n--- operator== ---" << std::endl;
    Vector2D e(4.0, 6.0);
    std::cout << "c == (4,6)? " << (c == e ? "true" : "false") << std::endl;
    // Expected: true
    std::cout << "a == b?     " << (a == b ? "true" : "false") << std::endl;
    // Expected: false

    // --- operator[] ---
    std::cout << "\n--- operator[] ---" << std::endl;
    std::cout << "a[0] = " << a[0] << std::endl; // Expected: 3
    std::cout << "a[1] = " << a[1] << std::endl; // Expected: 4

    // Using [] for assignment
    Vector2D m;
    m[0] = 10.0;
    m[1] = 20.0;
    std::cout << "m after assignment via []: " << m << std::endl;
    // Expected: (10, 20)

    // --- operator<< ---
    std::cout << "\n--- operator<< ---" << std::endl;
    std::cout << "Printing directly: " << a << " and " << b << std::endl;
    // Expected: Printing directly: (3, 4) and (1, 2)

    return 0;
}

/*
Expected Output:
=== C++98 Operator Overloading ===

--- operator+ ---
a     = (3, 4)
b     = (1, 2)
a + b = (4, 6)
a + b + d = (4.5, 6.5)

--- operator== ---
c == (4,6)? true
a == b?     false

--- operator[] ---
a[0] = 3
a[1] = 4
m after assignment via []: (10, 20)

--- operator<< ---
Printing directly: (3, 4) and (1, 2)
*/
