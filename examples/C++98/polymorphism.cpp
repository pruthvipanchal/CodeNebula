// CodeNebula - C++98 Example: Polymorphism
// Compile: g++ -std=c++98 -Wall -Wextra -o example polymorphism.cpp
//
// This example demonstrates:
// - Runtime polymorphism through base pointers/references to derived objects
// - Virtual functions enabling dynamic dispatch
// - Polymorphic arrays of base pointers
// - The power of writing code that works with the base type
//   but executes derived behaviour at runtime

#include <iostream>
#include <cstring>

// ============================================================
// Base class: Shape
// ============================================================
class Shape {
protected:
    char name[32];

public:
    Shape(const char* n) {
        std::strncpy(name, n, 31);
        name[31] = '\0';
    }

    virtual ~Shape() {}

    // Virtual functions -- overridden by derived classes
    virtual double area() const {
        return 0.0;
    }

    virtual double perimeter() const {
        return 0.0;
    }

    virtual void draw() const {
        std::cout << "  Drawing a generic shape: " << name << std::endl;
    }

    const char* getName() const { return name; }
};

// ============================================================
// Derived: Circle
// ============================================================
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : Shape("Circle"), radius(r) {}

    double area() const {
        return 3.14159265 * radius * radius;
    }

    double perimeter() const {
        return 2.0 * 3.14159265 * radius;
    }

    void draw() const {
        std::cout << "  Drawing a Circle (radius=" << radius << ")" << std::endl;
    }
};

// ============================================================
// Derived: Rectangle
// ============================================================
class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h) : Shape("Rectangle"), width(w), height(h) {}

    double area() const {
        return width * height;
    }

    double perimeter() const {
        return 2.0 * (width + height);
    }

    void draw() const {
        std::cout << "  Drawing a Rectangle (" << width
                  << " x " << height << ")" << std::endl;
    }
};

// ============================================================
// Derived: Triangle
// ============================================================
class Triangle : public Shape {
private:
    double base, height, side1, side2, side3;

public:
    Triangle(double b, double h, double s1, double s2, double s3)
        : Shape("Triangle"), base(b), height(h), side1(s1), side2(s2), side3(s3) {}

    double area() const {
        return 0.5 * base * height;
    }

    double perimeter() const {
        return side1 + side2 + side3;
    }

    void draw() const {
        std::cout << "  Drawing a Triangle (base=" << base
                  << ", height=" << height << ")" << std::endl;
    }
};

// ============================================================
// A function that works with ANY Shape -- polymorphism in action
// ============================================================
void describeShape(const Shape& s) {
    std::cout << "  Shape: " << s.getName() << std::endl;
    s.draw();                             // virtual dispatch
    std::cout << "  Area:      " << s.area() << std::endl;
    std::cout << "  Perimeter: " << s.perimeter() << std::endl;
}

// Calculate total area of an array of Shape pointers
double totalArea(Shape* shapes[], int count) {
    double sum = 0.0;
    for (int i = 0; i < count; ++i) {
        sum += shapes[i]->area();  // virtual dispatch on each
    }
    return sum;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "1. POLYMORPHISM VIA BASE REFERENCE" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        Circle    c(5.0);
        Rectangle r(4.0, 6.0);
        Triangle  t(3.0, 4.0, 3.0, 4.0, 5.0);

        // Same function, different runtime behaviour
        describeShape(c);
        std::cout << std::endl;
        describeShape(r);
        std::cout << std::endl;
        describeShape(t);
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "2. POLYMORPHIC ARRAY OF BASE POINTERS" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        const int COUNT = 4;
        Shape* shapes[COUNT];

        shapes[0] = new Circle(3.0);
        shapes[1] = new Rectangle(2.0, 5.0);
        shapes[2] = new Triangle(6.0, 3.0, 6.0, 5.0, 5.0);
        shapes[3] = new Circle(1.0);

        std::cout << "  Drawing all shapes:" << std::endl;
        for (int i = 0; i < COUNT; ++i) {
            shapes[i]->draw();    // each calls its own version
        }

        std::cout << "\n  Total area of all shapes: "
                  << totalArea(shapes, COUNT) << std::endl;

        // Cleanup
        for (int i = 0; i < COUNT; ++i) {
            delete shapes[i];  // virtual destructor ensures proper cleanup
        }
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "3. BASE POINTER vs DERIVED POINTER" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        Circle c(7.0);

        // Derived pointer -- sees everything
        Circle* cPtr = &c;
        std::cout << "  Via Circle*:" << std::endl;
        cPtr->draw();

        // Base pointer -- only sees Shape interface, but calls Circle's methods
        Shape* sPtr = &c;
        std::cout << "  Via Shape*:" << std::endl;
        sPtr->draw();           // still calls Circle::draw() (virtual dispatch!)
        std::cout << "  Area = " << sPtr->area() << std::endl;

        std::cout << "\n  Both pointers call the SAME function at runtime" << std::endl;
        std::cout << "  because draw() and area() are virtual." << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "4. WHY POLYMORPHISM MATTERS" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "  - Write code against the BASE type (Shape)" << std::endl;
    std::cout << "  - At runtime, the DERIVED type's methods execute" << std::endl;
    std::cout << "  - Adding new shapes requires NO changes to existing code" << std::endl;
    std::cout << "  - This is the Open/Closed Principle in action" << std::endl;

    return 0;
}

// Expected output:
// ========================================
// 1. POLYMORPHISM VIA BASE REFERENCE
// ========================================
//   Shape: Circle
//   Drawing a Circle (radius=5)
//   Area:      78.5398
//   Perimeter: 31.4159
//
//   Shape: Rectangle
//   Drawing a Rectangle (4 x 6)
//   Area:      24
//   Perimeter: 20
//
//   Shape: Triangle
//   Drawing a Triangle (base=3, height=4)
//   Area:      6
//   Perimeter: 12
//
// ========================================
// 2. POLYMORPHIC ARRAY OF BASE POINTERS
// ========================================
//   Drawing all shapes:
//   Drawing a Circle (radius=3)
//   Drawing a Rectangle (2 x 5)
//   Drawing a Triangle (base=6, height=3)
//   Drawing a Circle (radius=1)
//
//   Total area of all shapes: 41.4159
//
// ========================================
// 3. BASE POINTER vs DERIVED POINTER
// ========================================
//   Via Circle*:
//   Drawing a Circle (radius=7)
//   Via Shape*:
//   Drawing a Circle (radius=7)
//   Area = 153.938
//   Both pointers call the SAME function at runtime
//   because draw() and area() are virtual.
//
// ========================================
// 4. WHY POLYMORPHISM MATTERS
// ========================================
//   ...summary...
