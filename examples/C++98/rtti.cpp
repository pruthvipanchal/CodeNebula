// CodeNebula - C++98 Example: RTTI (Runtime Type Identification)
// Compile: g++ -std=c++98 -Wall -Wextra -o example rtti.cpp

// RTTI allows programs to determine the actual type of an object at runtime.
// C++98 provides two RTTI mechanisms:
//   1. dynamic_cast - safely downcast polymorphic pointers/references
//   2. typeid       - get the type_info of an expression
// RTTI requires at least one virtual function in the class hierarchy.

#include <iostream>
#include <typeinfo>   // Required for typeid and type_info
#include <string>

// ------------------------------------------------------------------
// Polymorphic base class (virtual function enables RTTI)
// ------------------------------------------------------------------
class Shape {
public:
    virtual double area() const = 0;   // pure virtual
    virtual std::string name() const { return "Shape"; }
    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const { return 3.14159265 * radius * radius; }
    std::string name() const { return "Circle"; }
    double getRadius() const { return radius; }
};

class Rectangle : public Shape {
private:
    double w, h;
public:
    Rectangle(double width, double height) : w(width), h(height) {}
    double area() const { return w * h; }
    std::string name() const { return "Rectangle"; }
    double getWidth() const { return w; }
    double getHeight() const { return h; }
};

class Triangle : public Shape {
private:
    double base, height;
public:
    Triangle(double b, double h) : base(b), height(h) {}
    double area() const { return 0.5 * base * height; }
    std::string name() const { return "Triangle"; }
    double getBase() const { return base; }
    double getHeight() const { return height; }
};

// Derived from Circle
class Sphere : public Circle {
private:
    // Sphere extends Circle, using radius for a 3D calculation
public:
    Sphere(double r) : Circle(r) {}
    double area() const {
        // Surface area of a sphere
        return 4.0 * 3.14159265 * getRadius() * getRadius();
    }
    std::string name() const { return "Sphere"; }
    double volume() const {
        double r = getRadius();
        return (4.0 / 3.0) * 3.14159265 * r * r * r;
    }
};

// ------------------------------------------------------------------
// Function that uses dynamic_cast for safe downcasting
// ------------------------------------------------------------------
void describeShape(Shape* shape) {
    std::cout << "  Shape name: " << shape->name()
              << ", area: " << shape->area() << std::endl;

    // Try to downcast to specific types using dynamic_cast
    Circle* circle = dynamic_cast<Circle*>(shape);
    if (circle != 0) {
        std::cout << "    -> It is a Circle with radius " << circle->getRadius() << std::endl;

        // Check if it's specifically a Sphere (further down the hierarchy)
        Sphere* sphere = dynamic_cast<Sphere*>(shape);
        if (sphere != 0) {
            std::cout << "    -> Actually a Sphere, volume: " << sphere->volume() << std::endl;
        }
    }

    Rectangle* rect = dynamic_cast<Rectangle*>(shape);
    if (rect != 0) {
        std::cout << "    -> It is a Rectangle "
                  << rect->getWidth() << "x" << rect->getHeight() << std::endl;
    }

    Triangle* tri = dynamic_cast<Triangle*>(shape);
    if (tri != 0) {
        std::cout << "    -> It is a Triangle, base=" << tri->getBase()
                  << " height=" << tri->getHeight() << std::endl;
    }
}

// ------------------------------------------------------------------
// Function using typeid for type comparison
// ------------------------------------------------------------------
void identifyType(const Shape& shape) {
    std::cout << "  typeid name: " << typeid(shape).name() << std::endl;

    // Compare types using typeid
    if (typeid(shape) == typeid(Circle)) {
        std::cout << "    Exact type is Circle" << std::endl;
    } else if (typeid(shape) == typeid(Rectangle)) {
        std::cout << "    Exact type is Rectangle" << std::endl;
    } else if (typeid(shape) == typeid(Triangle)) {
        std::cout << "    Exact type is Triangle" << std::endl;
    } else if (typeid(shape) == typeid(Sphere)) {
        std::cout << "    Exact type is Sphere" << std::endl;
    } else {
        std::cout << "    Unknown derived type" << std::endl;
    }
}

// ------------------------------------------------------------------
// Function that uses dynamic_cast with references (throws on failure)
// ------------------------------------------------------------------
void tryAsCircle(Shape& shape) {
    try {
        Circle& c = dynamic_cast<Circle&>(shape);
        std::cout << "  Successfully cast to Circle, radius="
                  << c.getRadius() << std::endl;
    }
    catch (const std::bad_cast& e) {
        std::cout << "  bad_cast: not a Circle (" << e.what() << ")" << std::endl;
    }
}

int main() {
    std::cout << "=== C++98 RTTI (Runtime Type Identification) ===" << std::endl;

    // Create shape objects
    Circle circle(5.0);
    Rectangle rect(4.0, 6.0);
    Triangle tri(3.0, 8.0);
    Sphere sphere(3.0);

    // --- 1. dynamic_cast with pointers ---
    std::cout << "\n--- 1. dynamic_cast with pointers ---" << std::endl;
    Shape* shapes[4];
    shapes[0] = &circle;
    shapes[1] = &rect;
    shapes[2] = &tri;
    shapes[3] = &sphere;

    for (int i = 0; i < 4; ++i) {
        std::cout << "\nshapes[" << i << "]:" << std::endl;
        describeShape(shapes[i]);
    }

    // --- 2. dynamic_cast returns NULL on failure ---
    std::cout << "\n--- 2. dynamic_cast NULL check ---" << std::endl;
    Shape* s = &rect;
    Circle* asCircle = dynamic_cast<Circle*>(s);
    if (asCircle == 0) {
        std::cout << "Rectangle is NOT a Circle (dynamic_cast returned NULL)" << std::endl;
    }

    s = &circle;
    asCircle = dynamic_cast<Circle*>(s);
    if (asCircle != 0) {
        std::cout << "Circle IS a Circle, radius=" << asCircle->getRadius() << std::endl;
    }

    // Sphere is-a Circle (inheritance)
    s = &sphere;
    asCircle = dynamic_cast<Circle*>(s);
    if (asCircle != 0) {
        std::cout << "Sphere IS-A Circle, radius=" << asCircle->getRadius() << std::endl;
    }

    // --- 3. typeid for type identification ---
    std::cout << "\n--- 3. typeid identification ---" << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << "shapes[" << i << "]:" << std::endl;
        identifyType(*shapes[i]);
    }

    // --- 4. typeid comparison ---
    std::cout << "\n--- 4. typeid comparisons ---" << std::endl;
    // Note: typeid on polymorphic types gives the DYNAMIC type
    std::cout << "typeid(circle) == typeid(Circle): "
              << (typeid(circle) == typeid(Circle) ? "true" : "false") << std::endl;
    // Expected: true

    // Sphere is NOT the same type as Circle (typeid checks exact type)
    std::cout << "typeid(sphere) == typeid(Circle): "
              << (typeid(sphere) == typeid(Circle) ? "true" : "false") << std::endl;
    // Expected: false

    std::cout << "typeid(sphere) == typeid(Sphere): "
              << (typeid(sphere) == typeid(Sphere) ? "true" : "false") << std::endl;
    // Expected: true

    // Via pointer - typeid dereferences to get dynamic type
    Shape* sp = &sphere;
    std::cout << "typeid(*sp) == typeid(Sphere): "
              << (typeid(*sp) == typeid(Sphere) ? "true" : "false") << std::endl;
    // Expected: true

    // --- 5. dynamic_cast with references ---
    std::cout << "\n--- 5. dynamic_cast with references ---" << std::endl;
    tryAsCircle(circle);
    // Expected: Successfully cast to Circle, radius=5
    tryAsCircle(rect);
    // Expected: bad_cast: not a Circle
    tryAsCircle(sphere);
    // Expected: Successfully cast to Circle, radius=3

    // --- 6. type_info::before() for ordering ---
    std::cout << "\n--- 6. type_info ordering ---" << std::endl;
    const std::type_info& ti1 = typeid(Circle);
    const std::type_info& ti2 = typeid(Rectangle);
    std::cout << "Circle before Rectangle? "
              << (ti1.before(ti2) ? "yes" : "no") << std::endl;
    std::cout << "Rectangle before Circle? "
              << (ti2.before(ti1) ? "yes" : "no") << std::endl;
    // Results are implementation-defined but consistent

    return 0;
}

/*
Expected Output:
=== C++98 RTTI (Runtime Type Identification) ===

--- 1. dynamic_cast with pointers ---

shapes[0]:
  Shape name: Circle, area: 78.5398
    -> It is a Circle with radius 5

shapes[1]:
  Shape name: Rectangle, area: 24
    -> It is a Rectangle 4x6

shapes[2]:
  Shape name: Triangle, area: 12
    -> It is a Triangle, base=3 height=8

shapes[3]:
  Shape name: Sphere, area: 113.097
    -> It is a Circle with radius 3
    -> Actually a Sphere, volume: 113.097

--- 2. dynamic_cast NULL check ---
Rectangle is NOT a Circle (dynamic_cast returned NULL)
Circle IS a Circle, radius=5
Sphere IS-A Circle, radius=3

--- 3. typeid identification ---
(typeid names are implementation-defined)

--- 4. typeid comparisons ---
typeid(circle) == typeid(Circle): true
typeid(sphere) == typeid(Circle): false
typeid(sphere) == typeid(Sphere): true
typeid(*sp) == typeid(Sphere): true

--- 5. dynamic_cast with references ---
  Successfully cast to Circle, radius=5
  bad_cast: not a Circle
  Successfully cast to Circle, radius=3

--- 6. type_info ordering ---
(ordering is implementation-defined)
*/
