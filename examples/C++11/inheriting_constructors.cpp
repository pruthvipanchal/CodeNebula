// CodeNebula - C++11 Example: Inheriting Constructors
// Compile: g++ -std=c++11 -Wall -Wextra -o example inheriting_constructors.cpp
//
// This example demonstrates:
// - using Base::Base to inherit all base class constructors
// - Reducing boilerplate when derived classes add no new data members
// - Interaction with derived class members and default initialization
// - Combining inherited constructors with additional derived constructors

#include <iostream>
#include <string>

// ============================================================
// 1. Base class with multiple constructors
// ============================================================
class Shape {
    std::string name_;
    double x_, y_;
public:
    Shape() : name_("unknown"), x_(0), y_(0) {
        std::cout << "  Shape() default" << std::endl;
    }

    Shape(const std::string& name) : name_(name), x_(0), y_(0) {
        std::cout << "  Shape(name=\"" << name << "\")" << std::endl;
    }

    Shape(const std::string& name, double x, double y)
        : name_(name), x_(x), y_(y) {
        std::cout << "  Shape(name=\"" << name << "\", "
                  << x << ", " << y << ")" << std::endl;
    }

    void print() const {
        std::cout << "  " << name_ << " at (" << x_ << ", " << y_ << ")";
    }

    virtual ~Shape() {}
};

// ============================================================
// 2. Derived class inheriting all constructors
// ============================================================
class ColoredShape : public Shape {
    std::string color_ = "red";  // In-class default initializer
public:
    // Inherit ALL constructors from Shape
    using Shape::Shape;

    // Additional constructor specific to ColoredShape
    ColoredShape(const std::string& name, double x, double y,
                 const std::string& color)
        : Shape(name, x, y), color_(color) {
        std::cout << "  ColoredShape with color=\"" << color << "\"" << std::endl;
    }

    void printFull() const {
        print();
        std::cout << " [color=" << color_ << "]" << std::endl;
    }
};

// ============================================================
// 3. Another example: Database connection
// ============================================================
class Connection {
    std::string host_;
    int port_;
public:
    Connection(const std::string& host, int port)
        : host_(host), port_(port) {}

    Connection(const std::string& host)
        : host_(host), port_(5432) {}

    void describe() const {
        std::cout << "  " << host_ << ":" << port_;
    }
};

class SecureConnection : public Connection {
    bool encrypted_ = true;
public:
    using Connection::Connection;  // Inherit both constructors

    void describe() const {
        Connection::describe();
        std::cout << (encrypted_ ? " [encrypted]" : " [plain]") << std::endl;
    }
};

// ============================================================
// 4. Inheriting from a class with variadic constructor
// ============================================================
class Logger {
    std::string prefix_;
public:
    Logger(const std::string& prefix) : prefix_(prefix) {}

    void log(const std::string& msg) const {
        std::cout << "  [" << prefix_ << "] " << msg << std::endl;
    }
};

class TimestampLogger : public Logger {
public:
    using Logger::Logger;  // Inherit the string constructor

    void logWithTime(const std::string& msg) const {
        std::cout << "  [timestamp] ";
        log(msg);
    }
};

int main() {
    std::cout << "=== Inheriting Constructors ===" << std::endl;

    // Using inherited constructors from Shape
    std::cout << "\n--- ColoredShape using Shape's constructors ---" << std::endl;
    ColoredShape s1;                           // Shape()
    s1.printFull();

    ColoredShape s2("Circle");                 // Shape(name)
    s2.printFull();

    ColoredShape s3("Square", 3.0, 4.0);      // Shape(name, x, y)
    s3.printFull();

    ColoredShape s4("Triangle", 1.0, 2.0, "blue");  // Own constructor
    s4.printFull();

    // SecureConnection using Connection's constructors
    std::cout << "\n--- SecureConnection ---" << std::endl;
    SecureConnection c1("db.example.com", 3306);
    c1.describe();

    SecureConnection c2("localhost");
    c2.describe();

    // TimestampLogger using Logger's constructor
    std::cout << "\n--- TimestampLogger ---" << std::endl;
    TimestampLogger logger("APP");
    logger.log("started");
    logger.logWithTime("processing");

    return 0;
}

// Expected output:
// === Inheriting Constructors ===
//
// --- ColoredShape using Shape's constructors ---
//   Shape() default
//   unknown at (0, 0) [color=red]
//   Shape(name="Circle")
//   Circle at (0, 0) [color=red]
//   Shape(name="Square", 3, 4)
//   Square at (3, 4) [color=red]
//   Shape(name="Triangle", 1, 2)
//   ColoredShape with color="blue"
//   Triangle at (1, 2) [color=blue]
//
// --- SecureConnection ---
//   db.example.com:3306 [encrypted]
//   localhost:5432 [encrypted]
//
// --- TimestampLogger ---
//   [APP] started
//   [timestamp]   [APP] processing
