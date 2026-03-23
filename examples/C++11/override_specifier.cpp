// CodeNebula - C++11 Example: override Keyword
// Compile: g++ -std=c++11 -Wall -Wextra -o example override_specifier.cpp

// Demonstrates the 'override' specifier for virtual function overriding.
// Using 'override' causes a compile-time error if the function does not
// actually override a base class virtual, catching signature mismatches early.

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Base class: a shape with virtual methods
class Shape {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::string name() const { return "Shape"; }
    virtual void describe() const
    {
        std::cout << "  " << name() << ": area=" << area()
                  << " perimeter=" << perimeter() << std::endl;
    }
    virtual ~Shape() = default;
};

// Correct overrides with 'override' keyword
class Circle : public Shape {
    double radius_;
public:
    explicit Circle(double r) : radius_(r) {}

    double area() const override       // correctly overrides
    {
        return 3.14159265 * radius_ * radius_;
    }

    double perimeter() const override  // correctly overrides
    {
        return 2.0 * 3.14159265 * radius_;
    }

    std::string name() const override  // correctly overrides
    {
        return "Circle(r=" + std::to_string(radius_) + ")";
    }

    // Without override, these bugs would compile silently:
    // double area() { ... }            // missing const -> new function, NOT override
    // double perimetre() const { ... } // typo -> new function, NOT override
    // std::string name() { ... }       // missing const -> NOT override
};

class Rectangle : public Shape {
    double width_, height_;
public:
    Rectangle(double w, double h) : width_(w), height_(h) {}

    double area() const override
    {
        return width_ * height_;
    }

    double perimeter() const override
    {
        return 2.0 * (width_ + height_);
    }

    std::string name() const override
    {
        return "Rect(" + std::to_string(width_) + "x" + std::to_string(height_) + ")";
    }
};

// Multi-level inheritance: override also works
class Square : public Rectangle {
public:
    explicit Square(double side) : Rectangle(side, side) {}

    std::string name() const override
    {
        return "Square(" + std::to_string(area()) + " sq)";
    }
    // area() and perimeter() inherited from Rectangle -- correct behavior
};

int main()
{
    // ------------------------------------------------------------------
    // 1. Polymorphic usage with override
    // ------------------------------------------------------------------
    std::cout << "=== Polymorphic shapes ===" << std::endl;
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::unique_ptr<Shape>(new Circle(5.0)));
    shapes.push_back(std::unique_ptr<Shape>(new Rectangle(4.0, 6.0)));
    shapes.push_back(std::unique_ptr<Shape>(new Square(3.0)));

    for (const auto& s : shapes) {
        s->describe();
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Override prevents silent bugs
    // ------------------------------------------------------------------
    std::cout << "=== Why override matters ===" << std::endl;
    std::cout << "  Without override:" << std::endl;
    std::cout << "    double area() { }         // oops, missing const" << std::endl;
    std::cout << "    -> Creates NEW function instead of overriding" << std::endl;
    std::cout << "    -> Base version called through pointer = WRONG result" << std::endl;
    std::cout << std::endl;
    std::cout << "  With override:" << std::endl;
    std::cout << "    double area() override { } // compiler ERROR" << std::endl;
    std::cout << "    -> \"does not override any base class method\"" << std::endl;
    std::cout << "    -> Bug caught at compile time!" << std::endl;

    return 0;
}

/*
Expected output:

=== Polymorphic shapes ===
  Circle(r=5.000000): area=78.5398 perimeter=31.4159
  Rect(4.000000x6.000000): area=24 perimeter=20
  Square(9.000000 sq): area=9 perimeter=12

=== Why override matters ===
  Without override:
    double area() { }         // oops, missing const
    -> Creates NEW function instead of overriding
    -> Base version called through pointer = WRONG result

  With override:
    double area() override { } // compiler ERROR
    -> "does not override any base class method"
    -> Bug caught at compile time!
*/
