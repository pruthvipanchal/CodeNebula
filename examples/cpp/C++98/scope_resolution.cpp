// CodeNebula - C++98 Example: Scope Resolution Operator (::)
// Compile: g++ -std=c++98 -Wall -Wextra -o example scope_resolution.cpp

// The scope resolution operator (::) is used to:
// 1. Access a global variable when a local variable has the same name
// 2. Define class member functions outside the class body
// 3. Access static class members
// 4. Access members of a namespace
// 5. Access members of a base class from a derived class

#include <iostream>
#include <string>

// ------------------------------------------------------------------
// Global variable
// ------------------------------------------------------------------
int value = 100;
std::string name = "GlobalName";

// ------------------------------------------------------------------
// Namespace scope
// ------------------------------------------------------------------
namespace Config {
    int maxRetries = 3;
    std::string version = "1.0.0";

    void printVersion() {
        std::cout << "Config version: " << version << std::endl;
    }
}

namespace Network {
    int maxRetries = 5; // Same name as Config::maxRetries

    void connect() {
        std::cout << "Network::connect with max retries = "
                  << maxRetries << std::endl;
    }
}

// ------------------------------------------------------------------
// Class with member functions defined outside the class
// ------------------------------------------------------------------
class Rectangle {
private:
    double width;
    double height;

public:
    // Static member variable (declaration)
    static int instanceCount;

    // Constructor declared here, defined outside
    Rectangle(double w, double h);

    // Destructor
    ~Rectangle();

    // Member functions declared here, defined outside
    double area() const;
    double perimeter() const;
    void print() const;

    // Static member function
    static int getInstanceCount();
};

// Static member initialization (uses :: to specify it belongs to Rectangle)
int Rectangle::instanceCount = 0;

// Constructor definition outside the class using ::
Rectangle::Rectangle(double w, double h) : width(w), height(h) {
    ++instanceCount;
}

Rectangle::~Rectangle() {
    --instanceCount;
}

// Member function definitions using ::
double Rectangle::area() const {
    return width * height;
}

double Rectangle::perimeter() const {
    return 2.0 * (width + height);
}

void Rectangle::print() const {
    std::cout << "Rectangle(" << width << " x " << height
              << ") area=" << area() << std::endl;
}

// Static member function definition
int Rectangle::getInstanceCount() {
    return instanceCount;
}

// ------------------------------------------------------------------
// Inheritance: base class member access via ::
// ------------------------------------------------------------------
class Shape {
public:
    std::string type;

    Shape(const std::string& t) : type(t) {}

    virtual void describe() const {
        std::cout << "Shape: " << type << std::endl;
    }

    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : Shape("Circle"), radius(r) {}

    // Override describe, but also call the base class version
    void describe() const {
        // Using :: to explicitly call the base class method
        Shape::describe();
        std::cout << "  Radius: " << radius << std::endl;
    }
};

class Square : public Shape {
private:
    double side;

public:
    Square(double s) : Shape("Square"), side(s) {}

    void describe() const {
        Shape::describe();
        std::cout << "  Side: " << side << std::endl;
    }
};

// ------------------------------------------------------------------
// Enum scope (C++98 enums are not scoped, but we can use classes)
// ------------------------------------------------------------------
struct Color {
    enum Type { RED, GREEN, BLUE };
};

struct Priority {
    enum Type { LOW, MEDIUM, HIGH };
};

int main() {
    std::cout << "=== C++98 Scope Resolution Operator ===" << std::endl;

    // --- 1. Global scope access with :: ---
    std::cout << "\n--- 1. Global scope (::variable) ---" << std::endl;
    int value = 42; // Local variable shadows global
    std::string name = "LocalName";

    std::cout << "Local value:  " << value << std::endl;
    // Expected: 42
    std::cout << "Global value: " << ::value << std::endl;
    // Expected: 100
    std::cout << "Local name:   " << name << std::endl;
    // Expected: LocalName
    std::cout << "Global name:  " << ::name << std::endl;
    // Expected: GlobalName

    // --- 2. Namespace scope ---
    std::cout << "\n--- 2. Namespace scope ---" << std::endl;
    Config::printVersion();
    // Expected: Config version: 1.0.0
    Network::connect();
    // Expected: Network::connect with max retries = 5

    std::cout << "Config retries: " << Config::maxRetries << std::endl;
    std::cout << "Network retries: " << Network::maxRetries << std::endl;
    // Expected: 3, 5

    // --- 3. Class member function definition (already done above with ::) ---
    std::cout << "\n--- 3. Class member functions defined with :: ---" << std::endl;
    Rectangle r1(5.0, 3.0);
    Rectangle r2(10.0, 7.0);
    r1.print();
    // Expected: Rectangle(5 x 3) area=15
    r2.print();
    // Expected: Rectangle(10 x 7) area=70
    std::cout << "Perimeter of r1: " << r1.perimeter() << std::endl;
    // Expected: 16

    // --- 4. Static members accessed via :: ---
    std::cout << "\n--- 4. Static members (Class::member) ---" << std::endl;
    std::cout << "Instance count: " << Rectangle::getInstanceCount() << std::endl;
    // Expected: 2
    std::cout << "Via instance:   " << r1.getInstanceCount() << std::endl;
    // Expected: 2 (same static member)

    {
        Rectangle r3(1.0, 1.0);
        std::cout << "After creating r3: " << Rectangle::instanceCount << std::endl;
        // Expected: 3
    }
    std::cout << "After r3 destroyed: " << Rectangle::instanceCount << std::endl;
    // Expected: 2

    // --- 5. Base class method access via :: ---
    std::cout << "\n--- 5. Base class access (Base::method) ---" << std::endl;
    Circle c(5.0);
    Square s(4.0);

    c.describe();
    // Expected:
    // Shape: Circle
    //   Radius: 5
    s.describe();
    // Expected:
    // Shape: Square
    //   Side: 4

    // --- 6. Enum "scope" using struct ---
    std::cout << "\n--- 6. Enum scope pattern ---" << std::endl;
    Color::Type myColor = Color::RED;
    Priority::Type myPrio = Priority::HIGH;
    std::cout << "Color value: " << myColor << std::endl;
    // Expected: 0
    std::cout << "Priority value: " << myPrio << std::endl;
    // Expected: 2

    return 0;
}

/*
Expected Output:
=== C++98 Scope Resolution Operator ===

--- 1. Global scope (::variable) ---
Local value:  42
Global value: 100
Local name:   LocalName
Global name:  GlobalName

--- 2. Namespace scope ---
Config version: 1.0.0
Network::connect with max retries = 5
Config retries: 3
Network retries: 5

--- 3. Class member functions defined with :: ---
Rectangle(5 x 3) area=15
Rectangle(10 x 7) area=70
Perimeter of r1: 16

--- 4. Static members (Class::member) ---
Instance count: 2
Via instance:   2
After creating r3: 3
After r3 destroyed: 2

--- 5. Base class access (Base::method) ---
Shape: Circle
  Radius: 5
Shape: Square
  Side: 4

--- 6. Enum scope pattern ---
Color value: 0
Priority value: 2
*/
