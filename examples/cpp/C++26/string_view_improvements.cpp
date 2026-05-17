// CodeNebula - C++26 Example: string_view Improvements
// Compile: g++ -std=c++26 -Wall -Wextra -o example string_view_improvements.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// C++26 improves std::string_view with additional member functions,
// better constexpr support, and improved interoperability with
// std::string and other string-like types.

#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>

// --- C++26 string_view Improvements ---
//
// // C++26 adds contains() (already in C++23), and improves:
// std::string_view sv = "Hello, World!";
//
// // Improved constexpr support for all operations
// constexpr std::string_view csv = "compile-time";
// static_assert(csv.contains("time"));
// static_assert(csv.starts_with("comp"));
// static_assert(csv.ends_with("time"));
//
// // Better conversion and construction from ranges
// // C++26: string_view from contiguous ranges directly
// std::vector<char> chars = {'h', 'i'};
// std::string_view from_range(chars);  // C++26 range constructor

// --- Simulation using C++20 features ---

// Helper: simple contains for pre-C++23
bool sv_contains(std::string_view haystack, std::string_view needle) {
    return haystack.find(needle) != std::string_view::npos;
}

int main() {
    std::cout << "=== C++26 string_view Improvements (Simulated) ===" << std::endl;

    std::string_view sv = "Hello, C++26 World!";

    // Basic operations
    std::cout << "View: \"" << sv << "\"" << std::endl;
    std::cout << "Length: " << sv.length() << std::endl;
    std::cout << "Substr(7,4): \"" << sv.substr(7, 4) << "\"" << std::endl;

    // Prefix/suffix checks
    std::cout << "starts_with(\"Hello\"): " << std::boolalpha
              << sv.starts_with("Hello") << std::endl;
    std::cout << "ends_with(\"World!\"): " << sv.ends_with("World!") << std::endl;

    // Contains (C++23+)
    std::cout << "contains(\"C++26\"): " << sv_contains(sv, "C++26") << std::endl;
    std::cout << "contains(\"C++23\"): " << sv_contains(sv, "C++23") << std::endl;

    // Constexpr operations (demonstrate at compile time)
    constexpr std::string_view csv = "constexpr-string-view";
    static_assert(csv.size() == 21);
    static_assert(csv.starts_with("constexpr"));
    static_assert(csv[0] == 'c');
    std::cout << "\nconstexpr checks passed for: \"" << csv << "\"" << std::endl;

    // remove_prefix / remove_suffix
    std::string_view trimmed = sv;
    trimmed.remove_prefix(7);  // Remove "Hello, "
    trimmed.remove_suffix(1);  // Remove "!"
    std::cout << "After trim: \"" << trimmed << "\"" << std::endl;

    // Find operations
    auto pos = sv.find("C++26");
    std::cout << "\"C++26\" found at position: " << pos << std::endl;

    std::cout << "string_view: lightweight, non-owning string reference." << std::endl;
    return 0;
}

// Expected output:
// === C++26 string_view Improvements (Simulated) ===
// View: "Hello, C++26 World!"
// Length: 19
// Substr(7,4): "C++2"
// starts_with("Hello"): true
// ends_with("World!"): true
// contains("C++26"): true
// contains("C++23"): false
//
// constexpr checks passed for: "constexpr-string-view"
// After trim: "C++26 World"
// "C++26" found at position: 7
// string_view: lightweight, non-owning string reference.
