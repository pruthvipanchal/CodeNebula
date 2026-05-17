// CodeNebula - C++17 Example: std::invoke
// Compile: g++ -std=c++17 -Wall -Wextra -o example invoke.cpp

// Demonstrates std::invoke, a uniform interface for calling any callable:
// free functions, member functions, member data pointers, lambdas, and
// function objects -- all through the same syntax.

#include <iostream>
#include <functional>
#include <string>

int add(int a, int b) { return a + b; }

struct Widget {
    std::string name;
    int value;

    void print() const {
        std::cout << "  Widget{" << name << ", " << value << "}" << std::endl;
    }

    int doubled() const { return value * 2; }
};

struct Functor {
    std::string operator()(const std::string& s) const {
        return "[" + s + "]";
    }
};

int main()
{
    // ------------------------------------------------------------------
    // 1. Invoke a free function
    // ------------------------------------------------------------------
    std::cout << "=== Free Function ===" << std::endl;
    int sum = std::invoke(add, 3, 4);
    std::cout << "  add(3, 4) = " << sum << std::endl;

    // ------------------------------------------------------------------
    // 2. Invoke a member function on an object
    // ------------------------------------------------------------------
    Widget w{"Gear", 21};
    std::cout << "\n=== Member Function ===" << std::endl;
    std::invoke(&Widget::print, w);

    int d = std::invoke(&Widget::doubled, w);
    std::cout << "  doubled() = " << d << std::endl;

    // ------------------------------------------------------------------
    // 3. Invoke a pointer-to-member-data (reads the member)
    // ------------------------------------------------------------------
    std::cout << "\n=== Member Data Pointer ===" << std::endl;
    std::string& n = std::invoke(&Widget::name, w);
    std::cout << "  name = " << n << std::endl;

    int& v = std::invoke(&Widget::value, w);
    std::cout << "  value = " << v << std::endl;

    // ------------------------------------------------------------------
    // 4. Invoke a lambda
    // ------------------------------------------------------------------
    auto square = [](int x) { return x * x; };
    std::cout << "\n=== Lambda ===" << std::endl;
    std::cout << "  square(9) = " << std::invoke(square, 9) << std::endl;

    // ------------------------------------------------------------------
    // 5. Invoke a function object
    // ------------------------------------------------------------------
    Functor fmt;
    std::cout << "\n=== Function Object ===" << std::endl;
    std::cout << "  fmt(\"hello\") = " << std::invoke(fmt, "hello") << std::endl;

    // ------------------------------------------------------------------
    // 6. Invoke with a pointer to the object
    // ------------------------------------------------------------------
    Widget* pw = &w;
    std::cout << "\n=== Via Pointer ===" << std::endl;
    std::invoke(&Widget::print, pw);

    return 0;
}

/*
Expected output:

=== Free Function ===
  add(3, 4) = 7

=== Member Function ===
  Widget{Gear, 21}
  doubled() = 42

=== Member Data Pointer ===
  name = Gear
  value = 21

=== Lambda ===
  square(9) = 81

=== Function Object ===
  fmt("hello") = [hello]

=== Via Pointer ===
  Widget{Gear, 21}
*/
