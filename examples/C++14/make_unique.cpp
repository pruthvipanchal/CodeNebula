// CodeNebula - C++14 Example: std::make_unique
// Compile: g++ -std=c++14 -Wall -Wextra -o example make_unique.cpp

// Demonstrates std::make_unique for safe unique_ptr creation. This was a
// notable omission from C++11 (which had make_shared but not make_unique).
// Real-world use: exception-safe memory allocation, factory functions,
// avoiding raw 'new', and building ownership-clear APIs.

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ------------------------------------------------------------------
// Sample classes for demonstration
// ------------------------------------------------------------------
class Widget
{
    std::string name_;
    int value_;
public:
    Widget(std::string name, int value)
        : name_(std::move(name)), value_(value)
    {
        std::cout << "  Widget(" << name_ << ", " << value_ << ") constructed" << std::endl;
    }

    ~Widget() { std::cout << "  Widget(" << name_ << ") destroyed" << std::endl; }

    void show() const
    {
        std::cout << "  Widget: " << name_ << " = " << value_ << std::endl;
    }
};

class Base
{
public:
    virtual ~Base() = default;
    virtual std::string type() const { return "Base"; }
};

class Derived : public Base
{
public:
    std::string type() const override { return "Derived"; }
};

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic make_unique (replaces: unique_ptr<T>(new T(...)))
    // ------------------------------------------------------------------
    std::cout << "=== Basic make_unique ===" << std::endl;
    auto w1 = std::make_unique<Widget>("Alpha", 42);
    w1->show();
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. make_unique with no arguments (default construction)
    // ------------------------------------------------------------------
    std::cout << "=== Default Construction ===" << std::endl;
    auto num = std::make_unique<int>();       // value-initialized to 0
    auto str = std::make_unique<std::string>();
    std::cout << "  *num = " << *num << std::endl;
    std::cout << "  *str = \"" << *str << "\" (empty)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. make_unique for arrays
    // ------------------------------------------------------------------
    std::cout << "=== Array make_unique ===" << std::endl;
    auto arr = std::make_unique<int[]>(5);    // array of 5 ints
    for (int i = 0; i < 5; ++i)
        arr[i] = (i + 1) * 10;
    std::cout << "  Array contents:";
    for (int i = 0; i < 5; ++i)
        std::cout << " " << arr[i];
    std::cout << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Polymorphism with make_unique
    // ------------------------------------------------------------------
    std::cout << "=== Polymorphic make_unique ===" << std::endl;
    std::unique_ptr<Base> base_ptr = std::make_unique<Derived>();
    std::cout << "  Type: " << base_ptr->type() << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Storing in containers
    // ------------------------------------------------------------------
    std::cout << "=== Container of unique_ptrs ===" << std::endl;
    std::vector<std::unique_ptr<Widget>> widgets;
    widgets.push_back(std::make_unique<Widget>("Beta", 10));
    widgets.push_back(std::make_unique<Widget>("Gamma", 20));
    widgets.push_back(std::make_unique<Widget>("Delta", 30));

    std::cout << "  All widgets:" << std::endl;
    for (const auto& w : widgets)
        w->show();
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 6. Exception safety advantage
    // ------------------------------------------------------------------
    std::cout << "=== Exception Safety Note ===" << std::endl;
    std::cout << "  // Dangerous (C++11): may leak if second new throws" << std::endl;
    std::cout << "  // func(unique_ptr<A>(new A), unique_ptr<B>(new B));" << std::endl;
    std::cout << "  // Safe (C++14):" << std::endl;
    std::cout << "  // func(make_unique<A>(), make_unique<B>());" << std::endl;
    std::cout << std::endl;

    std::cout << "=== Automatic Cleanup ===" << std::endl;

    return 0;
}

/*
Expected output:

=== Basic make_unique ===
  Widget(Alpha, 42) constructed
  Widget: Alpha = 42

=== Default Construction ===
  *num = 0
  *str = "" (empty)

=== Array make_unique ===
  Array contents: 10 20 30 40 50

=== Polymorphic make_unique ===
  Type: Derived

=== Container of unique_ptrs ===
  Widget(Beta, 10) constructed
  Widget(Gamma, 20) constructed
  Widget(Delta, 30) constructed
  All widgets:
  Widget: Beta = 10
  Widget: Gamma = 20
  Widget: Delta = 30

=== Exception Safety Note ===
  // Dangerous (C++11): may leak if second new throws
  // func(unique_ptr<A>(new A), unique_ptr<B>(new B));
  // Safe (C++14):
  // func(make_unique<A>(), make_unique<B>());

=== Automatic Cleanup ===
  Widget(Delta) destroyed
  Widget(Gamma) destroyed
  Widget(Beta) destroyed
  Widget(Alpha) destroyed
*/
