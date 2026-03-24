// CodeNebula - C++20 Example: Constexpr Virtual Functions
// Compile: g++ -std=c++20 -Wall -Wextra -o example constexpr_virtual.cpp

// Demonstrates C++20 constexpr virtual functions: virtual dispatch can now
// happen at compile time when the dynamic type is known.

#include <iostream>
#include <array>

// ------------------------------------------------------------------
// 1. Base class with constexpr virtual functions
// ------------------------------------------------------------------
class Shape {
public:
    constexpr virtual ~Shape() = default;
    constexpr virtual double area() const = 0;
    constexpr virtual const char* name() const = 0;
    constexpr virtual int sides() const { return 0; }
};

// ------------------------------------------------------------------
// 2. Derived classes with constexpr overrides
// ------------------------------------------------------------------
class Circle : public Shape {
    double radius_;
public:
    constexpr explicit Circle(double r) : radius_(r) {}
    constexpr double area() const override { return 3.14159265 * radius_ * radius_; }
    constexpr const char* name() const override { return "Circle"; }
    constexpr int sides() const override { return 0; }
};

class Rectangle : public Shape {
    double w_, h_;
public:
    constexpr Rectangle(double w, double h) : w_(w), h_(h) {}
    constexpr double area() const override { return w_ * h_; }
    constexpr const char* name() const override { return "Rectangle"; }
    constexpr int sides() const override { return 4; }
};

class Triangle : public Shape {
    double base_, height_;
public:
    constexpr Triangle(double b, double h) : base_(b), height_(h) {}
    constexpr double area() const override { return 0.5 * base_ * height_; }
    constexpr const char* name() const override { return "Triangle"; }
    constexpr int sides() const override { return 3; }
};

// ------------------------------------------------------------------
// 3. constexpr function using virtual dispatch
// ------------------------------------------------------------------
constexpr double compute_area(const Shape& s) {
    return s.area();  // Virtual call resolved at compile time!
}

constexpr const char* get_name(const Shape& s) {
    return s.name();
}

// ------------------------------------------------------------------
// 4. constexpr function comparing shapes
// ------------------------------------------------------------------
constexpr bool is_larger(const Shape& a, const Shape& b) {
    return a.area() > b.area();
}

// ------------------------------------------------------------------
// 5. constexpr with polymorphic objects
// ------------------------------------------------------------------
constexpr double total_area() {
    Circle c(5.0);
    Rectangle r(4.0, 6.0);
    Triangle t(3.0, 8.0);

    // Using references for virtual dispatch
    const Shape& s1 = c;
    const Shape& s2 = r;
    const Shape& s3 = t;

    return s1.area() + s2.area() + s3.area();
}

// ------------------------------------------------------------------
// 6. Another hierarchy: Animal
// ------------------------------------------------------------------
class Animal {
public:
    constexpr virtual ~Animal() = default;
    constexpr virtual int legs() const = 0;
    constexpr virtual const char* species() const = 0;
};

class Dog : public Animal {
public:
    constexpr int legs() const override { return 4; }
    constexpr const char* species() const override { return "Dog"; }
};

class Bird : public Animal {
public:
    constexpr int legs() const override { return 2; }
    constexpr const char* species() const override { return "Bird"; }
};

class Spider : public Animal {
public:
    constexpr int legs() const override { return 8; }
    constexpr const char* species() const override { return "Spider"; }
};

constexpr int total_legs() {
    Dog d;
    Bird b;
    Spider s;
    const Animal& a1 = d;
    const Animal& a2 = b;
    const Animal& a3 = s;
    return a1.legs() + a2.legs() + a3.legs();
}

int main()
{
    std::cout << "=== Constexpr Virtual Dispatch ===" << std::endl;
    constexpr Circle c(5.0);
    constexpr Rectangle r(4.0, 6.0);
    constexpr Triangle t(3.0, 8.0);

    constexpr double ca = compute_area(c);
    constexpr double ra = compute_area(r);
    constexpr double ta = compute_area(t);

    std::cout << "  " << get_name(c) << " area: " << ca << std::endl;
    std::cout << "  " << get_name(r) << " area: " << ra << std::endl;
    std::cout << "  " << get_name(t) << " area: " << ta << std::endl;

    std::cout << "\n=== Sides (virtual) ===" << std::endl;
    std::cout << "  " << c.name() << ": " << c.sides() << " sides" << std::endl;
    std::cout << "  " << r.name() << ": " << r.sides() << " sides" << std::endl;
    std::cout << "  " << t.name() << ": " << t.sides() << " sides" << std::endl;

    std::cout << "\n=== Compile-Time Comparison ===" << std::endl;
    constexpr bool c_gt_r = is_larger(c, r);
    constexpr bool r_gt_t = is_larger(r, t);
    std::cout << "  Circle > Rectangle? " << c_gt_r << std::endl;
    std::cout << "  Rectangle > Triangle? " << r_gt_t << std::endl;

    std::cout << "\n=== Total Area (compile-time) ===" << std::endl;
    constexpr double total = total_area();
    std::cout << "  Total: " << total << std::endl;
    static_assert(total > 100.0, "Total area should exceed 100");

    std::cout << "\n=== Animal Hierarchy ===" << std::endl;
    constexpr int legs = total_legs();
    std::cout << "  Dog + Bird + Spider legs: " << legs << std::endl;
    static_assert(legs == 14);
    std::cout << "  static_assert(legs == 14) passed" << std::endl;

    return 0;
}

/*
Expected output:

=== Constexpr Virtual Dispatch ===
  Circle area: 78.5398
  Rectangle area: 24
  Triangle area: 12

=== Sides (virtual) ===
  Circle: 0 sides
  Rectangle: 4 sides
  Triangle: 3 sides

=== Compile-Time Comparison ===
  Circle > Rectangle? 1
  Rectangle > Triangle? 1

=== Total Area (compile-time) ===
  Total: 114.54

=== Animal Hierarchy ===
  Dog + Bird + Spider legs: 14
  static_assert(legs == 14) passed
*/
