// CodeNebula - C++26 Example: std::function_ref
// Compile: g++ -std=c++26 -Wall -Wextra -o example function_ref.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// C++26 introduces std::function_ref as a lightweight, non-owning
// reference to a callable. Unlike std::function, it never allocates
// and never copies the callable -- it just references it.

#include <iostream>
#include <functional>
#include <string>
#include <vector>

// --- C++26 std::function_ref Syntax ---
//
// #include <functional>
//
// void apply(std::function_ref<int(int)> fn, int x) {
//     std::cout << fn(x);  // Calls the referenced callable
// }
//
// auto lambda = [](int x) { return x * 2; };
// apply(lambda, 5);  // No copy, no allocation
//
// // Key properties:
// // - Non-owning: does NOT extend lifetime of the callable
// // - Trivially copyable: just a pointer + function pointer internally
// // - Perfect for callback parameters where ownership isn't needed

// --- Simulation using raw function pointers + templates ---

// Simulate function_ref with a lightweight type-erased wrapper
template<typename Sig>
class function_ref_sim;

template<typename R, typename... Args>
class function_ref_sim<R(Args...)> {
    void* obj_ = nullptr;
    R (*invoke_)(void*, Args...) = nullptr;

public:
    // From function pointer
    function_ref_sim(R (*fn)(Args...))
        : obj_(reinterpret_cast<void*>(fn))
        , invoke_([](void* o, Args... args) -> R {
            return reinterpret_cast<R(*)(Args...)>(o)(args...);
        }) {}

    // From any callable (lambda, functor)
    template<typename F>
    function_ref_sim(F& f)
        : obj_(const_cast<void*>(static_cast<const void*>(&f)))
        , invoke_([](void* o, Args... args) -> R {
            return (*static_cast<F*>(o))(args...);
        }) {}

    R operator()(Args... args) const {
        return invoke_(obj_, args...);
    }
};

// A function that takes a non-owning callable reference
void apply_and_print(function_ref_sim<int(int)> fn, int x) {
    std::cout << "  fn(" << x << ") = " << fn(x) << std::endl;
}

int square(int x) { return x * x; }
int negate(int x) { return -x; }

int main() {
    std::cout << "=== C++26 std::function_ref (Simulated) ===" << std::endl;

    // With function pointers
    std::cout << "Function pointers:" << std::endl;
    apply_and_print(square, 5);
    apply_and_print(negate, 3);

    // With lambdas (no allocation, just a reference)
    auto doubler = [](int x) { return x * 2; };
    auto adder = [offset = 100](int x) { return x + offset; };
    std::cout << "Lambdas:" << std::endl;
    apply_and_print(doubler, 7);
    apply_and_print(adder, 5);

    // Show it's non-owning: sizeof is tiny
    std::cout << "\nsizeof(function_ref_sim): " << sizeof(function_ref_sim<int(int)>)
              << " bytes (2 pointers)" << std::endl;
    std::cout << "sizeof(std::function):    " << sizeof(std::function<int(int)>)
              << " bytes" << std::endl;

    std::cout << "\nfunction_ref: zero-overhead non-owning callable reference." << std::endl;
    return 0;
}

// Expected output:
// === C++26 std::function_ref (Simulated) ===
// Function pointers:
//   fn(5) = 25
//   fn(3) = -3
// Lambdas:
//   fn(7) = 14
//   fn(5) = 105
//
// sizeof(function_ref_sim): 16 bytes (2 pointers)
// sizeof(std::function):    32 bytes
//
// function_ref: zero-overhead non-owning callable reference.
