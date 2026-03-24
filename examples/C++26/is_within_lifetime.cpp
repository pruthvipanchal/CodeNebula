// CodeNebula - C++26 Example: std::is_within_lifetime
// Compile: g++ -std=c++26 -Wall -Wextra -o example is_within_lifetime.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// C++26 introduces std::is_within_lifetime to check at compile time
// whether a pointer/reference refers to an object whose lifetime has
// begun and not yet ended. This enables safe constexpr union access.

#include <iostream>
#include <type_traits>
#include <variant>
#include <string>

// --- C++26 std::is_within_lifetime Syntax ---
//
// #include <type_traits>
//
// union IntOrFloat {
//     int i;
//     float f;
// };
//
// consteval bool test_union() {
//     IntOrFloat u;
//     u.i = 42;
//     // Check which member is active at compile time
//     if (std::is_within_lifetime(&u.i))  // true: i is active
//         return true;
//     if (std::is_within_lifetime(&u.f))  // false: f is NOT active
//         return false;
//     return false;
// }
//
// static_assert(test_union()); // Passes: i is the active member

// --- Simulation using C++20 features ---

// Simulate with a tagged union that tracks the active member
template<typename T1, typename T2>
struct SafeUnion {
    enum class Active { First, Second, None } active = Active::None;
    union { T1 first; T2 second; };

    void set_first(const T1& v)  { first = v; active = Active::First; }
    void set_second(const T2& v) { second = v; active = Active::Second; }

    bool is_first_active() const  { return active == Active::First; }
    bool is_second_active() const { return active == Active::Second; }

    // Simulates std::is_within_lifetime for first member
    const T1& get_first() const {
        if (!is_first_active())
            throw std::runtime_error("first member not within lifetime");
        return first;
    }
    const T2& get_second() const {
        if (!is_second_active())
            throw std::runtime_error("second member not within lifetime");
        return second;
    }
};

int main() {
    std::cout << "=== C++26 std::is_within_lifetime (Simulated) ===" << std::endl;

    SafeUnion<int, float> u;

    // Set int member
    u.set_first(42);
    std::cout << "After set_first(42):" << std::endl;
    std::cout << "  is_first_active:  " << std::boolalpha << u.is_first_active() << std::endl;
    std::cout << "  is_second_active: " << u.is_second_active() << std::endl;
    std::cout << "  value: " << u.get_first() << std::endl;

    // Switch to float member
    u.set_second(3.14f);
    std::cout << "After set_second(3.14):" << std::endl;
    std::cout << "  is_first_active:  " << u.is_first_active() << std::endl;
    std::cout << "  is_second_active: " << u.is_second_active() << std::endl;
    std::cout << "  value: " << u.get_second() << std::endl;

    // Accessing inactive member is caught
    try {
        u.get_first(); // first is no longer active
    } catch (const std::exception& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    std::cout << "is_within_lifetime enables safe constexpr union access." << std::endl;
    return 0;
}

// Expected output:
// === C++26 std::is_within_lifetime (Simulated) ===
// After set_first(42):
//   is_first_active:  true
//   is_second_active: false
//   value: 42
// After set_second(3.14):
//   is_first_active:  false
//   is_second_active: true
//   value: 3.14
// Caught: first member not within lifetime
// is_within_lifetime enables safe constexpr union access.
