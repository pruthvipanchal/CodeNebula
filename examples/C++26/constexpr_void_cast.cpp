// CodeNebula - C++26 Example: constexpr Cast from void*
// Compile: g++ -std=c++26 -Wall -Wextra -o example constexpr_void_cast.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// C++26 allows static_cast from void* in constexpr contexts. Previously,
// casting from void* was forbidden at compile time, making constexpr
// memory management and type-erasure patterns impossible.

#include <iostream>
#include <type_traits>

// --- C++26 constexpr void* Cast Syntax ---
//
// constexpr int test() {
//     int x = 42;
//     void* vp = &x;                   // OK in constexpr since C++20
//     int* ip = static_cast<int*>(vp); // NEW in C++26: allowed in constexpr!
//     return *ip;
// }
//
// static_assert(test() == 42); // Passes at compile time in C++26
//
// // Enables constexpr type-erasure and allocator patterns
// constexpr auto make_and_recover() {
//     double d = 3.14;
//     void* erased = &d;
//     double* recovered = static_cast<double*>(erased);
//     return *recovered;
// }

// --- Simulation using C++20 runtime equivalents ---

// Runtime version of what C++26 allows at compile time
int runtime_void_cast_demo() {
    int x = 42;
    void* vp = &x;
    int* ip = static_cast<int*>(vp); // Fine at runtime, not constexpr pre-C++26
    return *ip;
}

double type_erasure_demo() {
    double d = 3.14;
    void* erased = &d;
    double* recovered = static_cast<double*>(erased);
    return *recovered;
}

// Simple constexpr type-erasure storage (simulated concept)
template<typename T>
struct constexpr_box {
    T value;
    constexpr const T& get() const { return value; }
    // In C++26: could store as void* and cast back in constexpr
};

int main() {
    std::cout << "=== C++26 constexpr void* Cast (Simulated) ===" << std::endl;

    std::cout << "void* -> int*:    " << runtime_void_cast_demo() << std::endl;
    std::cout << "void* -> double*: " << type_erasure_demo() << std::endl;

    constexpr constexpr_box<int> box{99};
    static_assert(box.get() == 99);
    std::cout << "constexpr_box<int>: " << box.get() << std::endl;

    // Demonstrate the pattern that C++26 enables at compile time
    int arr[] = {10, 20, 30};
    void* base = arr;
    int* typed = static_cast<int*>(base);
    std::cout << "Array via void*: " << typed[0] << ", " << typed[1]
              << ", " << typed[2] << std::endl;

    std::cout << "C++26 allows static_cast<T*>(void*) in constexpr." << std::endl;
    return 0;
}

// Expected output:
// === C++26 constexpr void* Cast (Simulated) ===
// void* -> int*:    42
// void* -> double*: 3.14
// constexpr_box<int>: 99
// Array via void*: 10, 20, 30
// C++26 allows static_cast<T*>(void*) in constexpr.
