// CodeNebula - C++11 Example: std::piecewise_construct
// Compile: g++ -std=c++11 -Wall -Wextra -o example piecewise_construct.cpp

// std::piecewise_construct is a tag used with std::pair's constructor
// to forward separate argument tuples to the constructors of each
// element. Essential for in-place construction in maps.

#include <iostream>
#include <utility>
#include <tuple>
#include <map>
#include <string>

struct Point {
    double x, y;
    Point(double x_, double y_) : x(x_), y(y_) {
        std::cout << "  Point(" << x << ", " << y << ") constructed" << std::endl;
    }
    // No default constructor -- must use piecewise_construct
    Point(const Point& o) : x(o.x), y(o.y) {
        std::cout << "  Point copied" << std::endl;
    }
};

struct Label {
    std::string text;
    int priority;
    Label(std::string t, int p) : text(std::move(t)), priority(p) {
        std::cout << "  Label(\"" << text << "\", " << priority << ") constructed" << std::endl;
    }
    Label(const Label& o) : text(o.text), priority(o.priority) {
        std::cout << "  Label copied" << std::endl;
    }
};

int main() {
    // Piecewise construct a pair of complex types
    std::cout << "Creating pair with piecewise_construct:" << std::endl;
    std::pair<Point, Label> item(
        std::piecewise_construct,
        std::forward_as_tuple(3.0, 4.0),       // args for Point
        std::forward_as_tuple("origin", 1)      // args for Label
    );
    std::cout << "Result: Point(" << item.first.x << ", " << item.first.y
              << ") Label(\"" << item.second.text << "\", "
              << item.second.priority << ")\n" << std::endl;

    // Primary use case: map::emplace with non-copyable keys or values
    std::cout << "Emplacing into map:" << std::endl;
    std::map<std::string, Point> locations;
    locations.emplace(
        std::piecewise_construct,
        std::forward_as_tuple("home"),
        std::forward_as_tuple(1.0, 2.0)
    );
    locations.emplace(
        std::piecewise_construct,
        std::forward_as_tuple("work"),
        std::forward_as_tuple(5.0, 6.0)
    );

    std::cout << "\nMap contents:" << std::endl;
    for (const auto& kv : locations) {
        std::cout << "  " << kv.first << " -> ("
                  << kv.second.x << ", " << kv.second.y << ")" << std::endl;
    }

    // Multi-map with complex key and value
    std::cout << "\nMultimap emplace:" << std::endl;
    std::multimap<int, Label> tasks;
    tasks.emplace(
        std::piecewise_construct,
        std::forward_as_tuple(1),
        std::forward_as_tuple("urgent task", 10)
    );
    tasks.emplace(
        std::piecewise_construct,
        std::forward_as_tuple(2),
        std::forward_as_tuple("normal task", 5)
    );

    std::cout << "\nTasks:" << std::endl;
    for (const auto& kv : tasks) {
        std::cout << "  [" << kv.first << "] " << kv.second.text
                  << " (priority " << kv.second.priority << ")" << std::endl;
    }

    return 0;
}

// Expected output:
// Creating pair with piecewise_construct:
//   Point(3, 4) constructed
//   Label("origin", 1) constructed
// Result: Point(3, 4) Label("origin", 1)
//
// Emplacing into map:
//   Point(1, 2) constructed
//   Point(5, 6) constructed
//
// Map contents:
//   home -> (1, 2)
//   work -> (5, 6)
//
// Multimap emplace:
//   Label("urgent task", 10) constructed
//   Label("normal task", 5) constructed
//
// Tasks:
//   [1] urgent task (priority 10)
//   [2] normal task (priority 5)
