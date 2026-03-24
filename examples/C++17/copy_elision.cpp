// CodeNebula - C++17 Example: Guaranteed Copy Elision
// Compile: g++ -std=c++17 -Wall -Wextra -o example copy_elision.cpp

// Demonstrates guaranteed copy elision (also called "mandatory RVO"). In C++17,
// returning a prvalue from a function directly initializes the target object.
// No copy/move constructor is even required to exist for prvalue returns.

#include <iostream>
#include <string>

// ------------------------------------------------------------------
// 1. Non-movable type: works in C++17 due to guaranteed elision
// ------------------------------------------------------------------
struct NonMovable {
    int value;

    explicit NonMovable(int v) : value(v) {
        std::cout << "  NonMovable(" << v << ") constructed" << std::endl;
    }

    // Deleted copy and move -- only legal in C++17 for prvalue returns
    NonMovable(const NonMovable&) = delete;
    NonMovable(NonMovable&&) = delete;
    NonMovable& operator=(const NonMovable&) = delete;
    NonMovable& operator=(NonMovable&&) = delete;
};

// Returns a prvalue -- no copy/move needed in C++17
NonMovable make_non_movable(int v) {
    return NonMovable{v};  // guaranteed: directly constructs at call site
}

// ------------------------------------------------------------------
// 2. Tracking type: shows that no copy/move actually occurs
// ------------------------------------------------------------------
struct Tracker {
    std::string name;

    explicit Tracker(std::string n) : name(std::move(n)) {
        std::cout << "  Tracker(\"" << name << "\") constructed" << std::endl;
    }
    Tracker(const Tracker& o) : name(o.name + " [copy]") {
        std::cout << "  Tracker(\"" << name << "\") COPIED" << std::endl;
    }
    Tracker(Tracker&& o) noexcept : name(std::move(o.name) + " [move]") {
        std::cout << "  Tracker(\"" << name << "\") MOVED" << std::endl;
    }
    ~Tracker() {
        std::cout << "  ~Tracker(\"" << name << "\")" << std::endl;
    }
};

Tracker make_tracker(const std::string& n) {
    return Tracker{n};  // prvalue return: guaranteed no copy/move
}

Tracker make_tracker_named() {
    Tracker t{"named"};  // NRVO: named return value optimization (not guaranteed)
    return t;            // compiler may or may not elide
}

// ------------------------------------------------------------------
// 3. Chained prvalue: elision through multiple layers
// ------------------------------------------------------------------
Tracker make_outer() {
    return make_tracker("chained");  // prvalue chain: still guaranteed
}

int main()
{
    std::cout << "=== guaranteed elision: non-movable type ===" << std::endl;
    NonMovable nm = make_non_movable(42);
    std::cout << "  nm.value = " << nm.value << std::endl;
    // Without guaranteed elision, this would fail to compile (deleted move ctor)

    std::cout << "\n=== guaranteed elision: prvalue return ===" << std::endl;
    Tracker t1 = make_tracker("direct");
    std::cout << "  t1.name = " << t1.name << std::endl;
    // Expected: only ONE construction, no copy/move

    std::cout << "\n=== NRVO: named return (may or may not elide) ===" << std::endl;
    Tracker t2 = make_tracker_named();
    std::cout << "  t2.name = " << t2.name << std::endl;

    std::cout << "\n=== chained prvalue elision ===" << std::endl;
    Tracker t3 = make_outer();
    std::cout << "  t3.name = " << t3.name << std::endl;

    std::cout << "\n=== destructors ===" << std::endl;
    return 0;
}

/*
Expected output (with guaranteed copy elision):

=== guaranteed elision: non-movable type ===
  NonMovable(42) constructed
  nm.value = 42

=== guaranteed elision: prvalue return ===
  Tracker("direct") constructed
  t1.name = direct

=== NRVO: named return (may or may not elide) ===
  Tracker("named") constructed
  t2.name = named

=== chained prvalue elision ===
  Tracker("chained") constructed
  t3.name = chained

=== destructors ===
  ~Tracker("chained")
  ~Tracker("named")
  ~Tracker("direct")
*/
