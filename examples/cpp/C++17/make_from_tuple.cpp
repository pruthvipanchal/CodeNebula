// CodeNebula - C++17 Example: std::make_from_tuple
// Compile: g++ -std=c++17 -Wall -Wextra -o example make_from_tuple.cpp

// Demonstrates std::make_from_tuple, which constructs an object of type T
// by unpacking a tuple as constructor arguments. This is the construction
// counterpart to std::apply (which calls a callable with tuple args).

#include <iostream>
#include <tuple>
#include <string>
#include <array>

struct Point {
    double x, y;
    Point(double x, double y) : x(x), y(y) {
        std::cout << "  Point(" << x << ", " << y << ") constructed" << std::endl;
    }
};

struct Person {
    std::string name;
    int age;
    double height;
    Person(std::string n, int a, double h)
        : name(std::move(n)), age(a), height(h) {}

    void print() const {
        std::cout << "  " << name << ", age " << age
                  << ", height " << height << "m" << std::endl;
    }
};

struct Widget {
    int id;
    std::string label;
    bool active;
    Widget(int i, std::string l, bool a)
        : id(i), label(std::move(l)), active(a) {}

    void print() const {
        std::cout << "  Widget #" << id << " \"" << label
                  << "\" active=" << active << std::endl;
    }
};

// Factory function that creates objects from stored tuple configs
template <typename T, typename Tuple>
T create(const Tuple& args) {
    return std::make_from_tuple<T>(args);
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic construction from a tuple
    // ------------------------------------------------------------------
    std::cout << "=== Basic Construction ===" << std::endl;
    auto point_args = std::make_tuple(3.0, 4.0);
    auto p = std::make_from_tuple<Point>(point_args);
    std::cout << "  Result: (" << p.x << ", " << p.y << ")" << std::endl;

    // ------------------------------------------------------------------
    // 2. Mixed types
    // ------------------------------------------------------------------
    std::cout << "\n=== Mixed Types ===" << std::endl;
    auto person_args = std::make_tuple(std::string("Alice"), 30, 1.68);
    auto alice = std::make_from_tuple<Person>(person_args);
    alice.print();

    // ------------------------------------------------------------------
    // 3. Constructing from an inline tuple
    // ------------------------------------------------------------------
    std::cout << "\n=== Inline Tuple ===" << std::endl;
    auto w = std::make_from_tuple<Widget>(
        std::make_tuple(42, std::string("gear"), true)
    );
    w.print();

    // ------------------------------------------------------------------
    // 4. Using std::array (which is tuple-like)
    // ------------------------------------------------------------------
    std::cout << "\n=== From std::array ===" << std::endl;
    std::array<double, 2> coords = {7.5, 2.3};
    auto p2 = std::make_from_tuple<Point>(coords);
    std::cout << "  Result: (" << p2.x << ", " << p2.y << ")" << std::endl;

    // ------------------------------------------------------------------
    // 5. Generic factory pattern
    // ------------------------------------------------------------------
    std::cout << "\n=== Factory Pattern ===" << std::endl;
    auto cfg1 = std::make_tuple(std::string("Bob"), 25, 1.80);
    auto cfg2 = std::make_tuple(99, std::string("motor"), false);

    auto bob = create<Person>(cfg1);
    bob.print();

    auto motor = create<Widget>(cfg2);
    motor.print();

    // ------------------------------------------------------------------
    // 6. With std::pair (also tuple-like)
    // ------------------------------------------------------------------
    std::cout << "\n=== From std::pair ===" << std::endl;
    std::pair<double, double> xy{1.0, 9.0};
    auto p3 = std::make_from_tuple<Point>(xy);
    std::cout << "  Result: (" << p3.x << ", " << p3.y << ")" << std::endl;

    return 0;
}

/*
Expected output:

=== Basic Construction ===
  Point(3, 4) constructed
  Result: (3, 4)

=== Mixed Types ===
  Alice, age 30, height 1.68m

=== Inline Tuple ===
  Widget #42 "gear" active=1

=== From std::array ===
  Point(7.5, 2.3) constructed
  Result: (7.5, 2.3)

=== Factory Pattern ===
  Bob, age 25, height 1.8m
  Widget #99 "motor" active=0

=== From std::pair ===
  Point(1, 9) constructed
  Result: (1, 9)
*/
