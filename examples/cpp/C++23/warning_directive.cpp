// CodeNebula - C++23 Example: #warning Preprocessor Directive
// Compile: g++ -std=c++23 -Wall -Wextra -o example warning_directive.cpp
// Note: Requires GCC 13+ / Clang 17+ / MSVC 19.34+
//       (Many compilers already supported #warning as an extension)

// C++23 standardizes the #warning preprocessor directive.
// Unlike #error (which stops compilation), #warning emits a diagnostic
// message but allows compilation to continue.

#include <iostream>

// Common use case: deprecation notices during compilation
#define LIBRARY_VERSION 2

#if LIBRARY_VERSION < 3
#warning "Library version < 3: some features may be missing"
#endif

// Use case: platform-specific reminders
#ifdef _WIN32
#warning "Windows build: ensure winsock2 is linked for networking"
#endif

// Use case: TODO reminders that show up during compilation
#warning "TODO: Replace placeholder algorithm before release"

// Use case: feature-flag reminders
#define USE_EXPERIMENTAL_FEATURE 1
#if USE_EXPERIMENTAL_FEATURE
#warning "Experimental feature enabled - not for production use"
#endif

int main() {
    std::cout << "=== #warning Preprocessor Directive ===" << std::endl;
    std::cout << "This program compiled successfully despite #warning." << std::endl;
    std::cout << std::endl;

    std::cout << "Key points about #warning:" << std::endl;
    std::cout << "  1. Standardized in C++23 (was a common extension before)" << std::endl;
    std::cout << "  2. Emits a compiler warning message" << std::endl;
    std::cout << "  3. Does NOT stop compilation (unlike #error)" << std::endl;
    std::cout << "  4. Useful for TODOs, deprecation, platform notes" << std::endl;

    std::cout << "\n=== Comparison ===" << std::endl;
    std::cout << "  #warning \"msg\"  -> warns, continues compiling" << std::endl;
    std::cout << "  #error   \"msg\"  -> stops compilation entirely" << std::endl;

    std::cout << "\nLibrary version: " << LIBRARY_VERSION << std::endl;
    std::cout << "Program ran successfully." << std::endl;

    return 0;
}

/*
During compilation, you will see warnings like:
  warning: Library version < 3: some features may be missing
  warning: TODO: Replace placeholder algorithm before release
  warning: Experimental feature enabled - not for production use

Expected program output:
=== #warning Preprocessor Directive ===
This program compiled successfully despite #warning.

Key points about #warning:
  1. Standardized in C++23 (was a common extension before)
  2. Emits a compiler warning message
  3. Does NOT stop compilation (unlike #error)
  4. Useful for TODOs, deprecation, platform notes

=== Comparison ===
  #warning "msg"  -> warns, continues compiling
  #error   "msg"  -> stops compilation entirely

Library version: 2
Program ran successfully.
*/
