// CodeNebula - C++26 Example: std::copyable_function
// Compile: g++ -std=c++26 -Wall -Wextra -o example copyable_function.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// C++26 introduces std::copyable_function as a complement to C++23's
// std::move_only_function. It is a type-erased callable wrapper that
// is both movable and copyable, with const-correctness guarantees
// that std::function lacks.

#include <iostream>
#include <functional>
#include <string>
#include <vector>

// --- C++26 std::copyable_function Syntax ---
//
// #include <functional>
//
// // Unlike std::function, copyable_function enforces const correctness
// std::copyable_function<int(int) const> f = [](int x) { return x * 2; };
//
// // Can be copied (unlike move_only_function)
// auto g = f;  // OK: copyable
//
// // Comparison with other function wrappers:
// // std::function<int(int)>            -- copyable, but no const enforcement
// // std::move_only_function<int(int)>  -- move-only, const-correct (C++23)
// // std::copyable_function<int(int)>   -- copyable AND const-correct (C++26)

// --- Simulation using std::function (C++20) ---

// std::function already supports copying; we simulate the const-correct aspect
template<typename Sig>
using copyable_function_sim = std::function<Sig>;

int multiply(int x, int y) { return x * y; }

int main() {
    std::cout << "=== C++26 std::copyable_function (Simulated) ===" << std::endl;

    // Basic usage: type-erased callable
    copyable_function_sim<int(int)> doubler = [](int x) { return x * 2; };
    std::cout << "doubler(5) = " << doubler(5) << std::endl;

    // Copy semantics (the key feature vs move_only_function)
    auto doubler_copy = doubler;
    std::cout << "doubler_copy(7) = " << doubler_copy(7) << std::endl;

    // Works with function pointers
    copyable_function_sim<int(int, int)> mul = multiply;
    std::cout << "multiply(3, 4) = " << mul(3, 4) << std::endl;

    // Works with stateful lambdas
    int offset = 100;
    copyable_function_sim<int(int)> adder = [offset](int x) { return x + offset; };
    auto adder_copy = adder;
    std::cout << "adder(5) = " << adder(5) << std::endl;
    std::cout << "adder_copy(5) = " << adder_copy(5) << std::endl;

    // Store in containers (requires copyability)
    std::vector<copyable_function_sim<int(int)>> transforms;
    transforms.push_back([](int x) { return x + 1; });
    transforms.push_back([](int x) { return x * 3; });
    transforms.push_back([](int x) { return x - 10; });

    int val = 5;
    std::cout << "Chained transforms on " << val << ": ";
    for (const auto& fn : transforms) {
        val = fn(val);
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Key difference table
    std::cout << "\nFunction wrapper comparison:" << std::endl;
    std::cout << "  std::function:            copyable, no const safety" << std::endl;
    std::cout << "  std::move_only_function:  move-only, const-correct" << std::endl;
    std::cout << "  std::copyable_function:   copyable + const-correct" << std::endl;

    return 0;
}

// Expected output:
// === C++26 std::copyable_function (Simulated) ===
// doubler(5) = 10
// doubler_copy(7) = 14
// multiply(3, 4) = 12
// adder(5) = 105
// adder_copy(5) = 105
// Chained transforms on 5: 6 18 8
//
// Function wrapper comparison:
//   std::function:            copyable, no const safety
//   std::move_only_function:  move-only, const-correct
//   std::copyable_function:   copyable + const-correct
