// CodeNebula - C++11 Example: std::unique_ptr
// Compile: g++ -std=c++11 -Wall -Wextra -o example unique_ptr.cpp
//
// This example demonstrates:
// - std::unique_ptr for exclusive ownership of heap objects
// - Automatic cleanup when unique_ptr goes out of scope
// - std::move to transfer ownership
// - unique_ptr with arrays
// - Custom deleters
// - unique_ptr in containers and as function return values

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ============================================================
// 1. Trackable resource
// ============================================================
class Widget {
    std::string name_;
    int id_;
public:
    Widget(const std::string& name, int id) : name_(name), id_(id) {
        std::cout << "  Widget(" << name_ << ", " << id_ << ") created" << std::endl;
    }

    ~Widget() {
        std::cout << "  Widget(" << name_ << ", " << id_ << ") destroyed" << std::endl;
    }

    void doWork() const {
        std::cout << "  Widget " << name_ << " working (id=" << id_ << ")" << std::endl;
    }
};

// ============================================================
// 2. Factory function returning unique_ptr
// ============================================================
std::unique_ptr<Widget> createWidget(const std::string& name, int id) {
    return std::unique_ptr<Widget>(new Widget(name, id));
    // In C++14, use: return std::make_unique<Widget>(name, id);
}

// ============================================================
// 3. Function taking ownership via unique_ptr
// ============================================================
void consumeWidget(std::unique_ptr<Widget> w) {
    std::cout << "  consumeWidget: took ownership" << std::endl;
    w->doWork();
    // Widget destroyed when function returns
}

// ============================================================
// 4. Polymorphism with unique_ptr
// ============================================================
class Shape {
public:
    virtual ~Shape() {}
    virtual void draw() const = 0;
};

class Circle : public Shape {
    double radius_;
public:
    Circle(double r) : radius_(r) {}
    void draw() const override {
        std::cout << "  Drawing circle (r=" << radius_ << ")" << std::endl;
    }
};

class Square : public Shape {
    double side_;
public:
    Square(double s) : side_(s) {}
    void draw() const override {
        std::cout << "  Drawing square (s=" << side_ << ")" << std::endl;
    }
};

int main() {
    std::cout << "=== std::unique_ptr ===" << std::endl;

    // Basic creation and automatic cleanup
    std::cout << "\n--- Basic usage ---" << std::endl;
    {
        std::unique_ptr<Widget> w(new Widget("Basic", 1));
        w->doWork();
        // Automatically destroyed at end of scope
    }

    // Factory function
    std::cout << "\n--- Factory function ---" << std::endl;
    {
        auto w = createWidget("Factory", 2);
        w->doWork();
    }

    // Transfer ownership with std::move
    std::cout << "\n--- Move semantics ---" << std::endl;
    {
        auto w1 = createWidget("Movable", 3);
        std::cout << "  w1 valid: " << (w1 ? "yes" : "no") << std::endl;

        std::unique_ptr<Widget> w2 = std::move(w1);
        std::cout << "  After move: w1 valid: " << (w1 ? "yes" : "no") << std::endl;
        std::cout << "  After move: w2 valid: " << (w2 ? "yes" : "no") << std::endl;
        w2->doWork();
    }

    // Transfer to function (consuming)
    std::cout << "\n--- Transfer to function ---" << std::endl;
    {
        auto w = createWidget("Consumed", 4);
        consumeWidget(std::move(w));
        std::cout << "  After consume: w valid: " << (w ? "yes" : "no") << std::endl;
    }

    // unique_ptr with arrays
    std::cout << "\n--- Array unique_ptr ---" << std::endl;
    {
        std::unique_ptr<int[]> arr(new int[5]);
        for (int i = 0; i < 5; ++i) {
            arr[i] = i * 10;
        }
        std::cout << "  Array: ";
        for (int i = 0; i < 5; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    // Container of unique_ptrs (polymorphism)
    std::cout << "\n--- Container of unique_ptr (polymorphism) ---" << std::endl;
    {
        std::vector<std::unique_ptr<Shape>> shapes;
        shapes.push_back(std::unique_ptr<Shape>(new Circle(5.0)));
        shapes.push_back(std::unique_ptr<Shape>(new Square(3.0)));
        shapes.push_back(std::unique_ptr<Shape>(new Circle(1.5)));

        for (const auto& s : shapes) {
            s->draw();
        }
    }

    // Release and reset
    std::cout << "\n--- release() and reset() ---" << std::endl;
    {
        auto w = createWidget("Released", 5);
        Widget* raw = w.release();  // Give up ownership
        std::cout << "  After release: w valid: " << (w ? "yes" : "no") << std::endl;
        raw->doWork();
        delete raw;  // Must manually delete now

        auto w2 = createWidget("Resetable", 6);
        w2.reset();  // Explicitly destroy
        std::cout << "  After reset: w2 valid: " << (w2 ? "yes" : "no") << std::endl;
    }

    return 0;
}

// Expected output:
// === std::unique_ptr ===
//
// --- Basic usage ---
//   Widget(Basic, 1) created
//   Widget Basic working (id=1)
//   Widget(Basic, 1) destroyed
//
// --- Factory function ---
//   Widget(Factory, 2) created
//   Widget Factory working (id=2)
//   Widget(Factory, 2) destroyed
//
// --- Move semantics ---
//   Widget(Movable, 3) created
//   w1 valid: yes
//   After move: w1 valid: no
//   After move: w2 valid: yes
//   Widget Movable working (id=3)
//   Widget(Movable, 3) destroyed
//
// --- Transfer to function ---
//   Widget(Consumed, 4) created
//   consumeWidget: took ownership
//   Widget Consumed working (id=4)
//   Widget(Consumed, 4) destroyed
//   After consume: w valid: no
//
// --- Array unique_ptr ---
//   Array: 0 10 20 30 40
//
// --- Container of unique_ptr (polymorphism) ---
//   Drawing circle (r=5)
//   Drawing square (s=3)
//   Drawing circle (r=1.5)
//
// --- release() and reset() ---
//   Widget(Released, 5) created
//   After release: w valid: no
//   Widget Released working (id=5)
//   Widget(Released, 5) destroyed
//   Widget(Resetable, 6) created
//   Widget(Resetable, 6) destroyed
//   After reset: w2 valid: no
