// CodeNebula - C++20 Example: Modules
// Compile: g++ -std=c++20 -Wall -Wextra -o example modules.cpp
//
// NOTE: C++20 modules require special compiler support and build steps.
// This file demonstrates module SYNTAX via comments, then provides
// a compilable fallback that illustrates the same organizational pattern.
//
// === How a real module would look ===
//
// --- File: math_utils.cppm (module interface unit) ---
//   export module math_utils;          // declare and export module
//
//   export int add(int a, int b) {     // exported function
//       return a + b;
//   }
//
//   export int multiply(int a, int b) { // exported function
//       return a * b;
//   }
//
//   export namespace constants {        // exported namespace
//       inline constexpr double pi = 3.14159265358979;
//       inline constexpr double e  = 2.71828182845905;
//   }
//
// --- File: main.cpp ---
//   import math_utils;                 // import the module
//   #include <iostream>
//   int main() {
//       std::cout << add(3, 4) << "\n";
//       std::cout << constants::pi << "\n";
//   }
//
// === Key advantages of modules ===
// 1. No header files needed — no include guards, no multiple definitions
// 2. Faster compilation — modules are parsed once, not per translation unit
// 3. No macro leakage — macros in a module don't affect importers
// 4. Explicit export control — only exported names are visible

#include <iostream>

// Fallback: simulate module pattern with a namespace
namespace math_utils {
    int add(int a, int b) { return a + b; }
    int multiply(int a, int b) { return a * b; }

    namespace constants {
        inline constexpr double pi = 3.14159265358979;
        inline constexpr double e  = 2.71828182845905;
    }
}

int main() {
    // This is how you would use an imported module:
    //   import math_utils;
    // Here we use the namespace simulation instead.

    std::cout << "=== C++20 Modules (simulated with namespace) ===\n";
    std::cout << "add(3, 4)      = " << math_utils::add(3, 4) << "\n";
    std::cout << "multiply(5, 6) = " << math_utils::multiply(5, 6) << "\n";
    std::cout << "pi             = " << math_utils::constants::pi << "\n";
    std::cout << "e              = " << math_utils::constants::e << "\n";

    std::cout << "\nModule benefits over #include:\n";
    std::cout << "  - Parsed once, not per translation unit\n";
    std::cout << "  - No header guards or pragma once needed\n";
    std::cout << "  - No macro leakage between modules\n";
    std::cout << "  - Only exported symbols are visible\n";

    return 0;
}

// Expected output:
// === C++20 Modules (simulated with namespace) ===
// add(3, 4)      = 7
// multiply(5, 6) = 30
// pi             = 3.14159
// e              = 2.71828
//
// Module benefits over #include:
//   - Parsed once, not per translation unit
//   - No header guards or pragma once needed
//   - No macro leakage between modules
//   - Only exported symbols are visible
