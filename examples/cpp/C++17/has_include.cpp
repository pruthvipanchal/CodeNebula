// CodeNebula - C++17 Example: __has_include Preprocessor Check
// Compile: g++ -std=c++17 -Wall -Wextra -o example has_include.cpp

// Demonstrates __has_include(), a C++17 preprocessor feature that checks whether
// a header is available before including it. This is invaluable for writing
// portable code that adapts to available libraries.

#include <iostream>

// ------------------------------------------------------------------
// 1. Check for C++17 headers
// ------------------------------------------------------------------
#if __has_include(<optional>)
    #include <optional>
    #define HAS_OPTIONAL 1
#else
    #define HAS_OPTIONAL 0
#endif

#if __has_include(<filesystem>)
    #define HAS_FILESYSTEM 1
#else
    #define HAS_FILESYSTEM 0
#endif

#if __has_include(<variant>)
    #include <variant>
    #define HAS_VARIANT 1
#else
    #define HAS_VARIANT 0
#endif

#if __has_include(<any>)
    #define HAS_ANY 1
#else
    #define HAS_ANY 0
#endif

// ------------------------------------------------------------------
// 2. Check for a header that likely does not exist
// ------------------------------------------------------------------
#if __has_include(<nonexistent_header.h>)
    #define HAS_NONEXISTENT 1
#else
    #define HAS_NONEXISTENT 0
#endif

// ------------------------------------------------------------------
// 3. Platform-specific header detection
// ------------------------------------------------------------------
#if __has_include(<unistd.h>)
    #define HAS_UNISTD 1
#else
    #define HAS_UNISTD 0
#endif

#if __has_include(<windows.h>)
    #define HAS_WINDOWS 1
#else
    #define HAS_WINDOWS 0
#endif

// ------------------------------------------------------------------
// 4. Conditional functionality based on available headers
// ------------------------------------------------------------------
#if HAS_OPTIONAL
std::optional<int> safe_divide(int a, int b) {
    if (b == 0) return std::nullopt;
    return a / b;
}
#else
int safe_divide(int a, int b) {
    return (b != 0) ? a / b : -1;  // fallback: return -1 on error
}
#endif

int main()
{
    std::cout << "=== C++17 header availability ===" << std::endl;
    std::cout << "  <optional>  : " << (HAS_OPTIONAL   ? "available" : "not found") << std::endl;
    std::cout << "  <filesystem>: " << (HAS_FILESYSTEM  ? "available" : "not found") << std::endl;
    std::cout << "  <variant>   : " << (HAS_VARIANT     ? "available" : "not found") << std::endl;
    std::cout << "  <any>       : " << (HAS_ANY         ? "available" : "not found") << std::endl;

    std::cout << "\n=== non-existent header ===" << std::endl;
    std::cout << "  <nonexistent_header.h>: "
              << (HAS_NONEXISTENT ? "available" : "not found") << std::endl;

    std::cout << "\n=== platform headers ===" << std::endl;
    std::cout << "  <unistd.h> : " << (HAS_UNISTD  ? "available" : "not found") << std::endl;
    std::cout << "  <windows.h>: " << (HAS_WINDOWS ? "available" : "not found") << std::endl;

    std::cout << "\n=== conditional functionality ===" << std::endl;
#if HAS_OPTIONAL
    auto result = safe_divide(10, 3);
    std::cout << "  10 / 3 = " << result.value_or(-1) << " (using std::optional)" << std::endl;
    auto bad = safe_divide(10, 0);
    std::cout << "  10 / 0 = " << (bad.has_value() ? std::to_string(*bad) : "nullopt") << std::endl;
#else
    std::cout << "  10 / 3 = " << safe_divide(10, 3) << " (fallback)" << std::endl;
#endif

    return 0;
}

/*
Expected output (may vary by platform):

=== C++17 header availability ===
  <optional>  : available
  <filesystem>: available
  <variant>   : available
  <any>       : available

=== non-existent header ===
  <nonexistent_header.h>: not found

=== platform headers ===
  <unistd.h> : available (or not found on Windows without MSYS)
  <windows.h>: not found (or available on Windows)

=== conditional functionality ===
  10 / 3 = 3 (using std::optional)
  10 / 0 = nullopt
*/
