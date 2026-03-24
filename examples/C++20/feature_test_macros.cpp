// CodeNebula - C++20 Example: Feature Test Macros
// Compile: g++ -std=c++20 -Wall -Wextra -o example feature_test_macros.cpp

// C++20 standardizes feature test macros that let you check at compile
// time whether a specific language or library feature is available.
// Language features use __cpp_* macros; library features use __cpp_lib_*.

#include <iostream>
#include <version>  // C++20: defines all __cpp_lib_* macros in one place

// Helper macro to check and print feature availability
#define CHECK_FEATURE(name) \
    do { \
        std::cout << "  " #name ": "; \
        if constexpr (name > 0) \
            std::cout << name << " (supported)\n"; \
        else \
            std::cout << "not supported\n"; \
    } while (0)

// Safe check for macros that may not be defined
#define CHECK_MAYBE(name, macro_val) \
    std::cout << "  " name ": " << macro_val << "\n"

int main() {
    std::cout << "=== C++20 Feature Test Macros ===\n\n";

    // --- Core language features ---
    std::cout << "Core language features:\n";

#ifdef __cpp_concepts
    CHECK_MAYBE("__cpp_concepts", __cpp_concepts);
#else
    std::cout << "  __cpp_concepts: not defined\n";
#endif

#ifdef __cpp_coroutines
    CHECK_MAYBE("__cpp_coroutines", __cpp_coroutines);
#else
    std::cout << "  __cpp_coroutines: not defined\n";
#endif

#ifdef __cpp_modules
    CHECK_MAYBE("__cpp_modules", __cpp_modules);
#else
    std::cout << "  __cpp_modules: not defined\n";
#endif

#ifdef __cpp_consteval
    CHECK_MAYBE("__cpp_consteval", __cpp_consteval);
#else
    std::cout << "  __cpp_consteval: not defined\n";
#endif

#ifdef __cpp_constexpr
    CHECK_MAYBE("__cpp_constexpr", __cpp_constexpr);
#else
    std::cout << "  __cpp_constexpr: not defined\n";
#endif

#ifdef __cpp_constinit
    CHECK_MAYBE("__cpp_constinit", __cpp_constinit);
#else
    std::cout << "  __cpp_constinit: not defined\n";
#endif

#ifdef __cpp_aggregate_paren_init
    CHECK_MAYBE("__cpp_aggregate_paren_init", __cpp_aggregate_paren_init);
#else
    std::cout << "  __cpp_aggregate_paren_init: not defined\n";
#endif

    // --- Library features ---
    std::cout << "\nLibrary features:\n";

#ifdef __cpp_lib_ranges
    CHECK_MAYBE("__cpp_lib_ranges", __cpp_lib_ranges);
#else
    std::cout << "  __cpp_lib_ranges: not defined\n";
#endif

#ifdef __cpp_lib_format
    CHECK_MAYBE("__cpp_lib_format", __cpp_lib_format);
#else
    std::cout << "  __cpp_lib_format: not defined\n";
#endif

#ifdef __cpp_lib_concepts
    CHECK_MAYBE("__cpp_lib_concepts", __cpp_lib_concepts);
#else
    std::cout << "  __cpp_lib_concepts: not defined\n";
#endif

#ifdef __cpp_lib_coroutine
    CHECK_MAYBE("__cpp_lib_coroutine", __cpp_lib_coroutine);
#else
    std::cout << "  __cpp_lib_coroutine: not defined\n";
#endif

#ifdef __cpp_lib_three_way_comparison
    CHECK_MAYBE("__cpp_lib_three_way_comparison", __cpp_lib_three_way_comparison);
#else
    std::cout << "  __cpp_lib_three_way_comparison: not defined\n";
#endif

#ifdef __cpp_lib_span
    CHECK_MAYBE("__cpp_lib_span", __cpp_lib_span);
#else
    std::cout << "  __cpp_lib_span: not defined\n";
#endif

    // --- Conditional compilation using feature test macros ---
    std::cout << "\nConditional compilation example:\n";

#if defined(__cpp_concepts) && __cpp_concepts >= 202002L
    std::cout << "  Concepts available — using constrained templates\n";
#else
    std::cout << "  Concepts not available — using SFINAE fallback\n";
#endif

#if defined(__cpp_lib_ranges) && __cpp_lib_ranges >= 202110L
    std::cout << "  Full ranges support available\n";
#elif defined(__cpp_lib_ranges)
    std::cout << "  Basic ranges support available\n";
#else
    std::cout << "  Ranges not available\n";
#endif

    std::cout << "\nTip: #include <version> defines all __cpp_lib_* macros.\n";

    return 0;
}

// Expected output (varies by compiler):
// === C++20 Feature Test Macros ===
//
// Core language features:
//   __cpp_concepts: 202002 (or similar)
//   __cpp_coroutines: ... (or not defined)
//   __cpp_modules: ... (or not defined)
//   __cpp_consteval: ...
//   __cpp_constexpr: ...
//   __cpp_constinit: ...
//   __cpp_aggregate_paren_init: ...
//
// Library features:
//   __cpp_lib_ranges: ...
//   __cpp_lib_format: ...
//   __cpp_lib_concepts: ...
//   (etc.)
//
// Conditional compilation example:
//   Concepts available — using constrained templates
//   ...
