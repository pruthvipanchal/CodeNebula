// CodeNebula - C++23 Example: std::string::contains / std::string_view::contains
// Compile: g++ -std=c++23 -Wall -Wextra -o example string_contains.cpp
// Note: Requires GCC 13+ / Clang 17+

#include <iostream>
#include <string>
#include <string_view>

// C++23 adds contains() to std::string and std::string_view.
// It checks if a substring or character is present, replacing
// the verbose (str.find(x) != std::string::npos) pattern.

int main() {
    std::cout << "=== std::string::contains / std::string_view::contains ===\n\n";

    std::string text = "The quick brown fox jumps over the lazy dog";

    // contains(string_view)
    std::cout << "Text: \"" << text << "\"\n\n";
    std::cout << "contains(\"fox\"):    " << text.contains("fox") << "\n";
    std::cout << "contains(\"cat\"):    " << text.contains("cat") << "\n";
    std::cout << "contains(\"quick\"): " << text.contains("quick") << "\n\n";

    // contains(char)
    std::cout << "contains('z'): " << text.contains('z') << "\n";
    std::cout << "contains('Z'): " << text.contains('Z') << "\n\n";

    // string_view::contains
    std::string_view sv = "Hello, World!";
    std::cout << "string_view \"" << sv << "\":\n";
    std::cout << "  contains(\"World\"): " << sv.contains("World") << "\n";
    std::cout << "  contains(\"world\"): " << sv.contains("world") << "\n";
    std::cout << "  contains(','):     " << sv.contains(',') << "\n\n";

    // Practical example: filtering strings
    std::cout << "--- Filtering filenames ---\n";
    std::string files[] = {
        "main.cpp", "header.h", "readme.md",
        "config.json", "test.cpp", "build.sh"
    };

    std::cout << "C++ files: ";
    for (const auto& f : files) {
        if (f.contains(".cpp") || f.contains(".h")) {
            std::cout << f << " ";
        }
    }
    std::cout << "\n";

    // Comparison with the old approach
    std::cout << "\nOld: str.find(x) != npos  ->  New: str.contains(x)\n";
    std::cout << "Much more readable!\n";

    return 0;
}

// Expected output:
// === std::string::contains / std::string_view::contains ===
//
// Text: "The quick brown fox jumps over the lazy dog"
//
// contains("fox"):    1
// contains("cat"):    0
// contains("quick"): 1
//
// contains('z'): 1
// contains('Z'): 0
//
// string_view "Hello, World!":
//   contains("World"): 1
//   contains("world"): 0
//   contains(','):     1
//
// --- Filtering filenames ---
// C++ files: main.cpp header.h test.cpp
//
// Old: str.find(x) != npos  ->  New: str.contains(x)
// Much more readable!
