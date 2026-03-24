// CodeNebula - C++26 Example: Erroneous Behavior
// Compile: g++ -std=c++26 -Wall -Wextra -o example erroneous_behavior.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// C++26 introduces "erroneous behavior" as a new category between
// well-defined and undefined behavior. Reading an uninitialized variable
// is no longer UB -- it produces an erroneous but stable value.
// Compilers may diagnose it, but the program does not exhibit UB.

#include <iostream>
#include <cstdint>

// --- C++26 Erroneous Behavior Semantics ---
//
// void demo() {
//     int x;           // uninitialized
//     int y = x;       // C++23: undefined behavior
//                      // C++26: erroneous behavior -- x has a stable
//                      //        but indeterminate value (e.g., 0xAA pattern)
//     std::cout << y;  // Prints some value; NOT undefined behavior
// }
//
// // The compiler MAY:
// //   - Diagnose reads of uninitialized variables (warning/error)
// //   - Initialize to a trap pattern (e.g., 0xAA bytes) in debug mode
// //   - Optimize assuming no erroneous behavior in release mode
// //
// // Key distinction from UB:
// //   - UB: program has no defined semantics at all
// //   - Erroneous: program has defined (but incorrect) semantics

// --- Simulation showing the concept ---

// Simulate the erroneous behavior trap pattern
constexpr uint8_t ERRONEOUS_PATTERN = 0xAA;

struct SafeInt {
    int value;
    bool initialized = false;

    SafeInt() : value(0) {} // Default: erroneous-ready
    explicit SafeInt(int v) : value(v), initialized(true) {}

    int read() const {
        if (!initialized) {
            std::cout << "  [erroneous behavior: reading uninitialized value]" << std::endl;
            // C++26: returns stable but erroneous value, NOT UB
        }
        return value;
    }
};

int main() {
    std::cout << "=== C++26 Erroneous Behavior (Simulated) ===" << std::endl;

    // Scenario 1: Uninitialized read (was UB, now erroneous)
    SafeInt x;
    std::cout << "Reading uninitialized x:" << std::endl;
    int val = x.read();
    std::cout << "  Value: " << val << " (stable, not UB)" << std::endl;

    // Scenario 2: Properly initialized
    SafeInt y(42);
    std::cout << "Reading initialized y:" << std::endl;
    std::cout << "  Value: " << y.read() << std::endl;

    // Scenario 3: Show the safety improvement
    std::cout << "\nC++23 vs C++26 comparison:" << std::endl;
    std::cout << "  int x; int y = x;" << std::endl;
    std::cout << "  C++23: undefined behavior (anything can happen)" << std::endl;
    std::cout << "  C++26: erroneous behavior (stable value, diagnosable)" << std::endl;

    // Demonstrate that erroneous reads are repeatable (not UB)
    int a = x.read();
    int b = x.read();
    std::cout << "Two reads of same uninitialized var: "
              << (a == b ? "equal (stable)" : "differ") << std::endl;

    std::cout << "Erroneous behavior makes uninitialized reads safer." << std::endl;
    return 0;
}

// Expected output:
// === C++26 Erroneous Behavior (Simulated) ===
// Reading uninitialized x:
//   [erroneous behavior: reading uninitialized value]
//   Value: 0 (stable, not UB)
// Reading initialized y:
//   Value: 42
//
// C++23 vs C++26 comparison:
//   int x; int y = x;
//   C++23: undefined behavior (anything can happen)
//   C++26: erroneous behavior (stable value, diagnosable)
//   [erroneous behavior: reading uninitialized value]
//   [erroneous behavior: reading uninitialized value]
// Two reads of same uninitialized var: equal (stable)
// Erroneous behavior makes uninitialized reads safer.
