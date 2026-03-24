// CodeNebula - C++23 Example: std::ranges::as_rvalue_view
// Compile: g++ -std=c++23 -Wall -Wextra -o example as_rvalue_view.cpp
// Note: Requires GCC 13+ / Clang 17+

// std::ranges::as_rvalue_view casts each element of a range to an rvalue
// reference, enabling efficient move semantics when consuming elements.
// Equivalent to applying std::move to each element during iteration.

#include <iostream>
#include <ranges>
#include <vector>
#include <string>

int main() {
    // Demonstrate moving strings from one container to another
    std::vector<std::string> source = {"Hello", "World", "from", "C++23", "rvalues"};

    std::cout << "=== Before move ===" << std::endl;
    std::cout << "  Source: ";
    for (const auto& s : source) std::cout << "\"" << s << "\" ";
    std::cout << std::endl;

    // Move all strings to a new vector using as_rvalue_view
    std::vector<std::string> dest;
    for (auto&& s : source | std::views::as_rvalue) {
        dest.push_back(std::move(s));
    }

    std::cout << "\n=== After move ===" << std::endl;
    std::cout << "  Source (moved-from): ";
    for (const auto& s : source) std::cout << "\"" << s << "\" ";
    std::cout << std::endl;
    std::cout << "  Dest: ";
    for (const auto& s : dest) std::cout << "\"" << s << "\" ";
    std::cout << std::endl;

    // Selective move: only move long strings
    std::vector<std::string> words = {"Hi", "Supercalifragilistic", "OK", "Extraordinary"};
    std::vector<std::string> long_words;

    std::cout << "\n=== Selective move (words > 5 chars) ===" << std::endl;
    for (auto&& w : words | std::views::filter([](const std::string& s) {
                        return s.size() > 5;
                    }) | std::views::as_rvalue) {
        long_words.push_back(std::move(w));
    }
    std::cout << "  Moved long words: ";
    for (const auto& w : long_words) std::cout << "\"" << w << "\" ";
    std::cout << std::endl;

    // Show that as_rvalue works with any range
    std::vector<std::vector<int>> nested = {{1, 2}, {3, 4, 5}, {6}};
    std::vector<std::vector<int>> moved_vecs;
    std::cout << "\n=== Moving nested vectors ===" << std::endl;
    for (auto&& v : nested | std::views::as_rvalue) {
        moved_vecs.push_back(std::move(v));
    }
    std::cout << "  Moved " << moved_vecs.size() << " inner vectors" << std::endl;
    std::cout << "  Contents: ";
    for (const auto& v : moved_vecs) {
        std::cout << "[";
        for (size_t i = 0; i < v.size(); ++i) {
            if (i > 0) std::cout << ",";
            std::cout << v[i];
        }
        std::cout << "] ";
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// === Before move ===
//   Source: "Hello" "World" "from" "C++23" "rvalues"
//
// === After move ===
//   Source (moved-from): "" "" "" "" ""
//   Dest: "Hello" "World" "from" "C++23" "rvalues"
//
// === Selective move (words > 5 chars) ===
//   Moved long words: "Supercalifragilistic" "Extraordinary"
//
// === Moving nested vectors ===
//   Moved 3 inner vectors
//   Contents: [1,2] [3,4,5] [6]
