// CodeNebula - C++20 Example: Spaceship Operator
// Compile: g++ -std=c++20 -Wall -Wextra -o example spaceship_operator.cpp

// Demonstrates the <=> three-way comparison operator: default generation,
// custom implementations, and how it replaces all six comparison operators.

#include <iostream>
#include <compare>
#include <string>
#include <vector>
#include <algorithm>

// ------------------------------------------------------------------
// 1. Default spaceship operator - compiler generates all comparisons
// ------------------------------------------------------------------
struct Point {
    int x;
    int y;

    auto operator<=>(const Point&) const = default;
};

// ------------------------------------------------------------------
// 2. Custom spaceship operator - compare by magnitude
// ------------------------------------------------------------------
struct Vector2D {
    double x;
    double y;

    double magnitude() const { return x * x + y * y; }

    auto operator<=>(const Vector2D& other) const {
        return magnitude() <=> other.magnitude();
    }

    bool operator==(const Vector2D& other) const {
        return x == other.x && y == other.y;
    }
};

// ------------------------------------------------------------------
// 3. Struct with mixed member types
// ------------------------------------------------------------------
struct Employee {
    std::string lastName;
    std::string firstName;
    int id;

    // Lexicographic comparison: last name, then first name, then id
    auto operator<=>(const Employee&) const = default;
};

// ------------------------------------------------------------------
// 4. Spaceship with heterogeneous comparison
// ------------------------------------------------------------------
struct Celsius {
    double temp;

    auto operator<=>(const Celsius& other) const = default;

    // Compare Celsius directly with a double
    auto operator<=>(double other) const {
        return temp <=> other;
    }

    bool operator==(double other) const {
        return temp == other;
    }
};

int main()
{
    std::cout << "=== Default Spaceship (Point) ===" << std::endl;
    Point p1{1, 2}, p2{1, 3}, p3{1, 2};
    std::cout << "  (1,2) == (1,2)? " << (p1 == p3) << std::endl;
    std::cout << "  (1,2) != (1,3)? " << (p1 != p2) << std::endl;
    std::cout << "  (1,2) <  (1,3)? " << (p1 < p2) << std::endl;
    std::cout << "  (1,2) >= (1,2)? " << (p1 >= p3) << std::endl;

    std::cout << "\n=== Custom Spaceship (Vector2D) ===" << std::endl;
    Vector2D v1{3, 4}, v2{1, 1}, v3{4, 3};
    std::cout << "  (3,4) > (1,1)? " << (v1 > v2) << std::endl;
    std::cout << "  (3,4) == (4,3)? " << (v1 == v3) << std::endl;
    std::cout << "  (3,4) equivalent to (4,3)? " << !(v1 < v3) && !(v1 > v3)
              << std::endl;

    std::cout << "\n=== Sorting with Spaceship (Employee) ===" << std::endl;
    std::vector<Employee> emps = {
        {"Smith", "Bob", 102},
        {"Adams", "Alice", 101},
        {"Smith", "Alice", 103},
        {"Adams", "Alice", 100}
    };
    std::sort(emps.begin(), emps.end());
    for (const auto& e : emps) {
        std::cout << "  " << e.lastName << ", " << e.firstName
                  << " (#" << e.id << ")" << std::endl;
    }

    std::cout << "\n=== Heterogeneous Comparison (Celsius) ===" << std::endl;
    Celsius c{100.0};
    std::cout << "  100C > 99.9?  " << (c > 99.9) << std::endl;
    std::cout << "  100C == 100.0? " << (c == 100.0) << std::endl;
    std::cout << "  100C < 200.0?  " << (c < 200.0) << std::endl;

    std::cout << "\n=== Spaceship Result Inspection ===" << std::endl;
    auto result = (5 <=> 10);
    if (result < 0) std::cout << "  5 <=> 10: less" << std::endl;
    if (result == 0) std::cout << "  5 <=> 10: equal" << std::endl;
    if (result > 0) std::cout << "  5 <=> 10: greater" << std::endl;

    return 0;
}

/*
Expected output:

=== Default Spaceship (Point) ===
  (1,2) == (1,2)? 1
  (1,2) != (1,3)? 1
  (1,2) <  (1,3)? 1
  (1,2) >= (1,2)? 1

=== Custom Spaceship (Vector2D) ===
  (3,4) > (1,1)? 1
  (3,4) == (4,3)? 0
  (3,4) equivalent to (4,3)? 1

=== Sorting with Spaceship (Employee) ===
  Adams, Alice (#100)
  Adams, Alice (#101)
  Smith, Alice (#103)
  Smith, Bob (#102)

=== Heterogeneous Comparison (Celsius) ===
  100C > 99.9?  1
  100C == 100.0? 1
  100C < 200.0?  1

=== Spaceship Result Inspection ===
  5 <=> 10: less
*/
