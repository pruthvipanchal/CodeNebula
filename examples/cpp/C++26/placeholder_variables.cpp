// CodeNebula - C++26 Example: Placeholder Variables
// Compile: g++ -std=c++26 -Wall -Wextra -o example placeholder_variables.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// C++26 allows using _ as a placeholder variable name multiple times
// in the same scope. Each _ is a unique unnamed variable. This is useful
// for ignoring values in structured bindings, locks, RAII guards, etc.

#include <iostream>
#include <tuple>
#include <map>
#include <mutex>

// --- C++26 Placeholder Syntax ---
//
// auto [_, value, _] = std::tuple{1, "hello", 3.14};
// // Both _ are separate unnamed variables; only 'value' is usable
//
// std::lock_guard _(mutex1);  // unnamed lock
// std::lock_guard _(mutex2);  // another unnamed lock, same scope!
//
// for (auto [_, v] : my_map) { /* use v, ignore key */ }

// --- Simulation using C++20 features ---

// In C++20, we must use unique names or [[maybe_unused]]
struct Point3D { int x; int y; int z; };

int main() {
    std::cout << "=== C++26 Placeholder Variables (Simulated) ===" << std::endl;

    // C++26: auto [_, value, _] = std::tuple{1, "hello", 3.14};
    // Simulation: use unique placeholder names
    auto [_1, value, _2] = std::tuple{1, std::string("hello"), 3.14};
    (void)_1; (void)_2; // suppress unused warnings
    std::cout << "Extracted value: " << value << std::endl;

    // C++26: for (auto [_, v] : map) { ... }
    std::map<int, std::string> colors{{1, "red"}, {2, "green"}, {3, "blue"}};
    std::cout << "Map values (keys ignored):" << std::endl;
    for (auto [_key, v] : colors) {
        (void)_key;
        std::cout << "  " << v << std::endl;
    }

    // C++26: multiple RAII guards with _ name
    std::mutex m1, m2;
    {
        // C++26: std::lock_guard _(m1); std::lock_guard _(m2);
        std::lock_guard lock1(m1); // Simulation: unique names
        std::lock_guard lock2(m2);
        std::cout << "Both mutexes locked (two _ guards in C++26)" << std::endl;
    }

    // C++26: auto [x, _, _] = Point3D{10, 20, 30};
    auto [x, _y, _z] = Point3D{10, 20, 30};
    (void)_y; (void)_z;
    std::cout << "Point3D x only: " << x << std::endl;

    std::cout << "Placeholder _ reduces noise for intentionally unused variables."
              << std::endl;
    return 0;
}

// Expected output:
// === C++26 Placeholder Variables (Simulated) ===
// Extracted value: hello
// Map values (keys ignored):
//   red
//   green
//   blue
// Both mutexes locked (two _ guards in C++26)
// Point3D x only: 10
// Placeholder _ reduces noise for intentionally unused variables.
