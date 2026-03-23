// CodeNebula - C++11 Example: Defaulted and Deleted Functions
// Compile: g++ -std=c++11 -Wall -Wextra -o example defaulted_deleted_functions.cpp
//
// This example demonstrates:
// - =default to explicitly request compiler-generated functions
// - =delete to explicitly prevent function usage
// - Controlling copy/move semantics
// - Preventing implicit conversions with =delete

#include <iostream>
#include <string>

// ============================================================
// 1. =default: Explicit compiler-generated special members
// ============================================================
class Point {
    double x_, y_;
public:
    Point(double x, double y) : x_(x), y_(y) {}

    // Explicitly request defaults (would be suppressed by user constructor)
    Point() = default;   // Default constructor restored
    ~Point() = default;  // Default destructor

    // Explicitly defaulted copy operations
    Point(const Point&) = default;
    Point& operator=(const Point&) = default;

    // Explicitly defaulted move operations
    Point(Point&&) = default;
    Point& operator=(Point&&) = default;

    void print() const {
        std::cout << "(" << x_ << ", " << y_ << ")";
    }
};

// ============================================================
// 2. =delete: Non-copyable class (move-only)
// ============================================================
class UniqueResource {
    std::string name_;
    int handle_;
public:
    UniqueResource(const std::string& name, int handle)
        : name_(name), handle_(handle) {
        std::cout << "  Acquired: " << name_ << std::endl;
    }

    ~UniqueResource() {
        std::cout << "  Released: " << name_ << std::endl;
    }

    // Delete copy operations
    UniqueResource(const UniqueResource&) = delete;
    UniqueResource& operator=(const UniqueResource&) = delete;

    // Allow move operations
    UniqueResource(UniqueResource&& other)
        : name_(std::move(other.name_)), handle_(other.handle_) {
        other.handle_ = -1;
        other.name_ = "(moved)";
    }

    UniqueResource& operator=(UniqueResource&& other) {
        if (this != &other) {
            name_ = std::move(other.name_);
            handle_ = other.handle_;
            other.handle_ = -1;
            other.name_ = "(moved)";
        }
        return *this;
    }

    void describe() const {
        std::cout << "  Resource: " << name_ << " [handle=" << handle_ << "]" << std::endl;
    }
};

// ============================================================
// 3. =delete to prevent implicit conversions
// ============================================================
class SafeInt {
    int value_;
public:
    explicit SafeInt(int v) : value_(v) {}

    // Delete constructors for types that would implicitly convert
    SafeInt(double) = delete;
    SafeInt(bool) = delete;
    SafeInt(char) = delete;

    int get() const { return value_; }
};

// ============================================================
// 4. =delete on free functions to prevent overloads
// ============================================================
void processInt(int value) {
    std::cout << "  processInt(" << value << ")" << std::endl;
}

void processInt(double) = delete;   // Prevent double -> int conversion
void processInt(bool) = delete;     // Prevent bool -> int conversion

// ============================================================
// 5. Non-heap-allocatable class (delete operator new)
// ============================================================
class StackOnly {
    int value_;
public:
    StackOnly(int v) : value_(v) {}
    int get() const { return value_; }

    // Prevent heap allocation
    void* operator new(std::size_t) = delete;
    void* operator new[](std::size_t) = delete;
};

int main() {
    std::cout << "=== Defaulted and Deleted Functions ===" << std::endl;

    // Defaulted functions
    std::cout << "\n--- =default ---" << std::endl;
    Point p1;            // Uses defaulted default constructor
    Point p2(3.0, 4.0);
    Point p3 = p2;       // Uses defaulted copy constructor
    p1 = p3;             // Uses defaulted copy assignment
    std::cout << "  p1 = "; p1.print(); std::cout << std::endl;
    std::cout << "  p2 = "; p2.print(); std::cout << std::endl;

    Point p4 = std::move(p2);  // Uses defaulted move constructor
    std::cout << "  p4 (moved from p2) = "; p4.print(); std::cout << std::endl;

    // Non-copyable, move-only resource
    std::cout << "\n--- =delete (move-only) ---" << std::endl;
    UniqueResource r1("Database", 1);
    r1.describe();

    // UniqueResource r2 = r1;  // ERROR: copy deleted
    UniqueResource r2 = std::move(r1);  // OK: move allowed
    r1.describe();
    r2.describe();

    // Deleted implicit conversions
    std::cout << "\n--- =delete (prevent conversions) ---" << std::endl;
    SafeInt si(42);
    std::cout << "  SafeInt(42) = " << si.get() << std::endl;
    // SafeInt bad(3.14);  // ERROR: deleted
    // SafeInt bad(true);  // ERROR: deleted
    std::cout << "  SafeInt(double) = deleted" << std::endl;
    std::cout << "  SafeInt(bool) = deleted" << std::endl;

    // Deleted overloads
    std::cout << "\n--- =delete (prevent overloads) ---" << std::endl;
    processInt(42);
    // processInt(3.14);  // ERROR: deleted
    // processInt(true);  // ERROR: deleted

    // Stack-only object
    std::cout << "\n--- =delete (stack-only) ---" << std::endl;
    StackOnly s(100);
    std::cout << "  StackOnly on stack: " << s.get() << std::endl;
    // StackOnly* p = new StackOnly(1);  // ERROR: deleted

    return 0;
}

// Expected output:
// === Defaulted and Deleted Functions ===
//
// --- =default ---
//   p1 = (3, 4)
//   p2 = (3, 4)
//   p4 (moved from p2) = (3, 4)
//
// --- =delete (move-only) ---
//   Acquired: Database
//   Resource: Database [handle=1]
//   Resource: (moved) [handle=-1]
//   Resource: Database [handle=1]
//
// --- =delete (prevent conversions) ---
//   SafeInt(42) = 42
//   SafeInt(double) = deleted
//   SafeInt(bool) = deleted
//
// --- =delete (prevent overloads) ---
//   processInt(42)
//
// --- =delete (stack-only) ---
//   StackOnly on stack: 100
//   Released: Database
//   Released: (moved)
