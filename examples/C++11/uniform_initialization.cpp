// CodeNebula - C++11 Example: Uniform Initialization (Brace Initialization)
// Compile: g++ -std=c++11 -Wall -Wextra -o example uniform_initialization.cpp

// Demonstrates uniform initialization with braces {}. This syntax works
// everywhere (variables, members, aggregates, containers), prevents
// narrowing conversions, and avoids the "most vexing parse" ambiguity.

#include <iostream>
#include <vector>
#include <map>
#include <string>

// Aggregate type (no user-declared constructors)
struct Point {
    double x;
    double y;
};

// Class with constructor
class Circle {
    Point center_;
    double radius_;
public:
    Circle(Point c, double r) : center_{c}, radius_{r} {}

    void print() const
    {
        std::cout << "  Circle at (" << center_.x << ", " << center_.y
                  << ") r=" << radius_ << std::endl;
    }
};

// Default member initializers + brace init
class Config {
public:
    int width{800};
    int height{600};
    std::string title{"Untitled"};
    bool fullscreen{false};

    void print() const
    {
        std::cout << "  " << title << " (" << width << "x" << height << ")"
                  << (fullscreen ? " [fullscreen]" : "") << std::endl;
    }
};

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic uniform initialization
    // ------------------------------------------------------------------
    int a{42};
    double b{3.14};
    char c{'X'};

    std::cout << "=== Basic brace init ===" << std::endl;
    std::cout << "  int a{42}    : " << a << std::endl;
    std::cout << "  double b{3.14}: " << b << std::endl;
    std::cout << "  char c{'X'}  : " << c << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Narrowing conversion prevention
    // ------------------------------------------------------------------
    // int narrow{3.14};     // ERROR: narrowing double -> int
    // char ch{300};         // ERROR: narrowing, 300 > CHAR_MAX
    int safe{100};           // OK: 100 fits in int

    std::cout << "=== Narrowing prevention ===" << std::endl;
    std::cout << "  int safe{100}: " << safe << std::endl;
    std::cout << "  (int{3.14} and char{300} would fail to compile)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Aggregate initialization
    // ------------------------------------------------------------------
    Point p1{1.0, 2.0};
    Point p2{};             // zero-initialized: {0.0, 0.0}

    std::cout << "=== Aggregate init ===" << std::endl;
    std::cout << "  p1: (" << p1.x << ", " << p1.y << ")" << std::endl;
    std::cout << "  p2: (" << p2.x << ", " << p2.y << ")" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Class constructor with braces
    // ------------------------------------------------------------------
    Circle circ{{5.0, 3.0}, 2.5};

    std::cout << "=== Class brace init ===" << std::endl;
    circ.print();
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Container initialization
    // ------------------------------------------------------------------
    std::vector<int> nums{1, 2, 3, 4, 5};
    std::map<std::string, int> ages{{"Alice", 30}, {"Bob", 25}};

    std::cout << "=== Container init ===" << std::endl;
    std::cout << "  vector: ";
    for (auto n : nums) std::cout << n << " ";
    std::cout << std::endl;
    for (const auto& p : ages) {
        std::cout << "  " << p.first << ": " << p.second << std::endl;
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 6. Avoiding most vexing parse
    // ------------------------------------------------------------------
    // Config cfg();     // WRONG: declares a function, not an object!
    Config cfg{};        // CORRECT: value-initializes a Config object

    std::cout << "=== Avoid most vexing parse ===" << std::endl;
    cfg.print();

    Config custom{1920, 1080, "My App", true};
    custom.print();

    return 0;
}

/*
Expected output:

=== Basic brace init ===
  int a{42}    : 42
  double b{3.14}: 3.14
  char c{'X'}  : X

=== Narrowing prevention ===
  int safe{100}: 100
  (int{3.14} and char{300} would fail to compile)

=== Aggregate init ===
  p1: (1, 2)
  p2: (0, 0)

=== Class brace init ===
  Circle at (5, 3) r=2.5

=== Container init ===
  vector: 1 2 3 4 5
  Alice: 30
  Bob: 25

=== Avoid most vexing parse ===
  Untitled (800x600)
  My App (1920x1080) [fullscreen]
*/
