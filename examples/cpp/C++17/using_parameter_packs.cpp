// CodeNebula - C++17 Example: Using-declaration for Parameter Packs
// Compile: g++ -std=c++17 -Wall -Wextra -o example using_parameter_packs.cpp

// Demonstrates C++17's ability to expand parameter packs in using-declarations.
// This allows inheriting constructors or operators from multiple bases in a
// single using statement: using Bases::operator()...;

#include <iostream>
#include <string>
#include <variant>

// ------------------------------------------------------------------
// 1. Overloaded callable: the classic "overloaded" pattern
// ------------------------------------------------------------------
// Each lambda becomes a base class; we inherit all operator() overloads.
template <typename... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;  // C++17: pack expansion in using-declaration
};

// Deduction guide (C++17 CTAD)
template <typename... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

// ------------------------------------------------------------------
// 2. Multiple base classes with different named methods
// ------------------------------------------------------------------
struct Printer {
    void print(const std::string& msg) const {
        std::cout << "  [Printer] " << msg << std::endl;
    }
};

struct Logger {
    void log(const std::string& msg) const {
        std::cout << "  [Logger] " << msg << std::endl;
    }
};

struct Alerter {
    void alert(const std::string& msg) const {
        std::cout << "  [Alerter] " << msg << std::endl;
    }
};

// Combine all three into one class, bringing in all methods
template <typename... Bases>
struct CombinedService : Bases... {
    using Bases::print...;    // Not applicable here since names differ,
    // but we can use constructor inheritance:
    // using Bases::Bases...;  // would bring in all base constructors
};

// ------------------------------------------------------------------
// 3. Inheriting constructors from multiple bases
// ------------------------------------------------------------------
struct FromInt {
    int value;
    FromInt(int v) : value(v) {}
};

struct FromString {
    std::string text;
    FromString(std::string s) : text(std::move(s)) {}
};

struct FromDouble {
    double number;
    FromDouble(double d) : number(d) {}
};

template <typename... Bases>
struct MultiConstructor : Bases... {
    using Bases::Bases...;   // C++17: inherit all constructors from all bases
};

int main()
{
    // ------------------------------------------------------------------
    // 1. Overloaded pattern with std::variant
    // ------------------------------------------------------------------
    std::cout << "=== overloaded visitor (using...pack) ===" << std::endl;

    std::variant<int, double, std::string> v1 = 42;
    std::variant<int, double, std::string> v2 = 3.14;
    std::variant<int, double, std::string> v3 = std::string("hello");

    auto visitor = overloaded{
        [](int i)               { std::cout << "  int: " << i << std::endl; },
        [](double d)            { std::cout << "  double: " << d << std::endl; },
        [](const std::string& s){ std::cout << "  string: " << s << std::endl; }
    };

    std::visit(visitor, v1);
    std::visit(visitor, v2);
    std::visit(visitor, v3);

    // ------------------------------------------------------------------
    // 2. Inline visitor with overloaded
    // ------------------------------------------------------------------
    std::cout << "\n=== inline visitor ===" << std::endl;
    std::variant<int, std::string> data = std::string("C++17");

    std::visit(overloaded{
        [](int n)               { std::cout << "  number: " << n << std::endl; },
        [](const std::string& s){ std::cout << "  text: " << s << std::endl; }
    }, data);

    // ------------------------------------------------------------------
    // 3. Inheriting constructors from multiple bases
    // ------------------------------------------------------------------
    std::cout << "\n=== inherited constructors (using Bases::Bases...) ===" << std::endl;

    using Multi = MultiConstructor<FromInt, FromString, FromDouble>;

    Multi m1(42);                       // calls FromInt(int)
    Multi m2(std::string("test"));      // calls FromString(string)
    Multi m3(2.718);                    // calls FromDouble(double)

    std::cout << "  From int:    " << m1.value << std::endl;
    std::cout << "  From string: " << m2.text << std::endl;
    std::cout << "  From double: " << m3.number << std::endl;

    return 0;
}

/*
Expected output:

=== overloaded visitor (using...pack) ===
  int: 42
  double: 3.14
  string: hello

=== inline visitor ===
  text: C++17

=== inherited constructors (using Bases::Bases...) ===
  From int:    42
  From string: test
  From double: 2.718
*/
