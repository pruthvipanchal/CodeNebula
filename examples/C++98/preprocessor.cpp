// CodeNebula - C++98 Example: Preprocessor Directives
// Compile: g++ -std=c++98 -Wall -Wextra -o example preprocessor.cpp

// The C/C++ preprocessor runs BEFORE compilation, performing text
// substitution. Key directives:
//   #define      - Define macros (object-like and function-like)
//   #undef       - Undefine a macro
//   #ifdef/#ifndef/#if/#elif/#else/#endif - Conditional compilation
//   #include     - Include files (with include guards)
//   #pragma      - Compiler-specific instructions
//   #error       - Emit a compile-time error
//   #line        - Override line numbering
//   Predefined macros: __FILE__, __LINE__, __DATE__, __TIME__

#include <iostream>
#include <cstring>

// ==================================================================
// 1. Include guards (typically in header files)
// ==================================================================
// In a header file (myheader.h), you would write:
//
// #ifndef MYHEADER_H
// #define MYHEADER_H
//   ... declarations ...
// #endif // MYHEADER_H
//
// This prevents double inclusion.

// ==================================================================
// 2. Object-like macros (constants)
// ==================================================================
#define PI 3.14159265358979
#define MAX_BUFFER_SIZE 1024
#define APP_NAME "CodeNebula Preprocessor Demo"
#define VERSION_MAJOR 1
#define VERSION_MINOR 0

// ==================================================================
// 3. Function-like macros (with arguments)
// ==================================================================
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(x) ((x) >= 0 ? (x) : -(x))
#define CLAMP(val, lo, hi) (MIN(MAX((val), (lo)), (hi)))

// Multi-line macro using backslash continuation
#define PRINT_VAR(var) \
    std::cout << "  " << #var << " = " << (var) << std::endl

// ==================================================================
// 4. Stringification (#) and token pasting (##)
// ==================================================================
// # turns a macro argument into a string literal
#define STRINGIFY(x) #x
#define TO_STRING(x) STRINGIFY(x)

// ## pastes two tokens together
#define MAKE_VAR(prefix, num) prefix##num
#define MAKE_FUNC(name) void print_##name() { \
    std::cout << "  Function: print_" << #name << "()" << std::endl; \
}

// Generate functions using token pasting
MAKE_FUNC(hello)
MAKE_FUNC(world)

// ==================================================================
// 5. Conditional compilation
// ==================================================================
#define DEBUG_MODE
#define PLATFORM_WINDOWS

// Logging macro that compiles away in release mode
#ifdef DEBUG_MODE
    #define DEBUG_LOG(msg) std::cout << "[DEBUG] " << msg << std::endl
#else
    #define DEBUG_LOG(msg)  /* nothing - compiles to empty */
#endif

// Platform-specific code
#ifdef PLATFORM_WINDOWS
    #define PATH_SEPARATOR '\\'
    #define PLATFORM_NAME "Windows"
#elif defined(PLATFORM_LINUX)
    #define PATH_SEPARATOR '/'
    #define PLATFORM_NAME "Linux"
#else
    #define PATH_SEPARATOR '/'
    #define PLATFORM_NAME "Unknown"
#endif

// ==================================================================
// 6. Feature toggles
// ==================================================================
#define FEATURE_LOGGING 1
#define FEATURE_METRICS 0

// ==================================================================
// 7. Variadic-style workaround (C++98 doesn't have __VA_ARGS__)
// ==================================================================
#define ASSERT_MSG(cond, msg) \
    do { \
        if (!(cond)) { \
            std::cerr << "ASSERTION FAILED: " << msg \
                      << " at " << __FILE__ << ":" << __LINE__ << std::endl; \
        } \
    } while (0)

// ==================================================================
// 8. do-while(0) idiom for safe multi-statement macros
// ==================================================================
#define SAFE_DELETE(ptr) \
    do { \
        delete (ptr); \
        (ptr) = 0; \
    } while (0)

int main() {
    std::cout << "=== C++98 Preprocessor Directives ===" << std::endl;

    // --- 1. Object-like macros ---
    std::cout << "\n--- 1. Object-like macros ---" << std::endl;
    std::cout << "  App: " << APP_NAME << std::endl;
    std::cout << "  Version: " << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;
    std::cout << "  PI = " << PI << std::endl;
    std::cout << "  MAX_BUFFER_SIZE = " << MAX_BUFFER_SIZE << std::endl;

    // --- 2. Function-like macros ---
    std::cout << "\n--- 2. Function-like macros ---" << std::endl;
    std::cout << "  SQUARE(5) = " << SQUARE(5) << std::endl;
    // Expected: 25
    std::cout << "  SQUARE(2+3) = " << SQUARE(2+3) << std::endl;
    // Expected: 25 (parentheses protect against precedence issues)

    std::cout << "  MAX(10, 20) = " << MAX(10, 20) << std::endl;
    // Expected: 20
    std::cout << "  MIN(10, 20) = " << MIN(10, 20) << std::endl;
    // Expected: 10
    std::cout << "  ABS(-7) = " << ABS(-7) << std::endl;
    // Expected: 7
    std::cout << "  CLAMP(150, 0, 100) = " << CLAMP(150, 0, 100) << std::endl;
    // Expected: 100

    // PRINT_VAR uses stringification (#)
    int score = 95;
    double temperature = 23.5;
    PRINT_VAR(score);
    // Expected: score = 95
    PRINT_VAR(temperature);
    // Expected: temperature = 23.5
    PRINT_VAR(3 + 4);
    // Expected: 3 + 4 = 7

    // --- 3. Stringification (#) ---
    std::cout << "\n--- 3. Stringification ---" << std::endl;
    std::cout << "  STRINGIFY(hello) = " << STRINGIFY(hello) << std::endl;
    // Expected: hello
    std::cout << "  STRINGIFY(3 + 4) = " << STRINGIFY(3 + 4) << std::endl;
    // Expected: 3 + 4 (as a string, not evaluated)
    std::cout << "  TO_STRING(VERSION_MAJOR) = " << TO_STRING(VERSION_MAJOR) << std::endl;
    // Expected: 1 (expanded first, then stringified)

    // --- 4. Token pasting (##) ---
    std::cout << "\n--- 4. Token pasting ---" << std::endl;
    int MAKE_VAR(value, 1) = 100;  // Creates: int value1 = 100;
    int MAKE_VAR(value, 2) = 200;  // Creates: int value2 = 200;
    std::cout << "  value1 = " << value1 << std::endl;
    std::cout << "  value2 = " << value2 << std::endl;

    // Call generated functions
    print_hello();
    print_world();

    // --- 5. Conditional compilation ---
    std::cout << "\n--- 5. Conditional compilation ---" << std::endl;
    DEBUG_LOG("This only appears in debug mode");
    // Expected: [DEBUG] This only appears in debug mode

    std::cout << "  Platform: " << PLATFORM_NAME << std::endl;
    std::cout << "  Path separator: '" << PATH_SEPARATOR << "'" << std::endl;

#ifdef DEBUG_MODE
    std::cout << "  DEBUG_MODE is defined" << std::endl;
#endif

#ifndef RELEASE_MODE
    std::cout << "  RELEASE_MODE is NOT defined" << std::endl;
#endif

    // --- 6. #if with expressions ---
    std::cout << "\n--- 6. #if with expressions ---" << std::endl;

#if FEATURE_LOGGING
    std::cout << "  Logging feature is ENABLED" << std::endl;
#else
    std::cout << "  Logging feature is DISABLED" << std::endl;
#endif

#if FEATURE_METRICS
    std::cout << "  Metrics feature is ENABLED" << std::endl;
#else
    std::cout << "  Metrics feature is DISABLED" << std::endl;
#endif

#if VERSION_MAJOR >= 1 && VERSION_MINOR >= 0
    std::cout << "  Version check passed (>= 1.0)" << std::endl;
#endif

    // --- 7. Predefined macros ---
    std::cout << "\n--- 7. Predefined macros ---" << std::endl;
    std::cout << "  __FILE__ = " << __FILE__ << std::endl;
    std::cout << "  __LINE__ = " << __LINE__ << std::endl;
    std::cout << "  __DATE__ = " << __DATE__ << std::endl;
    std::cout << "  __TIME__ = " << __TIME__ << std::endl;
#ifdef __cplusplus
    std::cout << "  __cplusplus = " << __cplusplus << std::endl;
    // Expected: 199711 for C++98
#endif

    // --- 8. ASSERT_MSG macro ---
    std::cout << "\n--- 8. Assert macro ---" << std::endl;
    int x = 10;
    ASSERT_MSG(x > 0, "x must be positive");
    // Expected: no output (assertion passes)

    ASSERT_MSG(x > 100, "x must be greater than 100");
    // Expected: ASSERTION FAILED: x must be greater than 100 at file:line

    // --- 9. SAFE_DELETE macro (do-while(0) idiom) ---
    std::cout << "\n--- 9. Safe delete macro ---" << std::endl;
    int* ptr = new int(42);
    std::cout << "  Before: *ptr = " << *ptr << std::endl;
    SAFE_DELETE(ptr);
    std::cout << "  After: ptr is " << (ptr == 0 ? "NULL" : "not NULL") << std::endl;
    // Expected: ptr is NULL

    // --- 10. #undef ---
    std::cout << "\n--- 10. #undef ---" << std::endl;
#define TEMP_MACRO 999
    std::cout << "  TEMP_MACRO = " << TEMP_MACRO << std::endl;
#undef TEMP_MACRO
    // TEMP_MACRO is now undefined; using it would cause an error
    std::cout << "  TEMP_MACRO has been undefined" << std::endl;

    // Redefine with a different value
#define TEMP_MACRO 111
    std::cout << "  TEMP_MACRO redefined = " << TEMP_MACRO << std::endl;
#undef TEMP_MACRO

    std::cout << "\nPreprocessor demo complete." << std::endl;

    return 0;
}

/*
Expected Output:
=== C++98 Preprocessor Directives ===

--- 1. Object-like macros ---
  App: CodeNebula Preprocessor Demo
  Version: 1.0
  PI = 3.14159
  MAX_BUFFER_SIZE = 1024

--- 2. Function-like macros ---
  SQUARE(5) = 25
  SQUARE(2+3) = 25
  MAX(10, 20) = 20
  MIN(10, 20) = 10
  ABS(-7) = 7
  CLAMP(150, 0, 100) = 100
  score = 95
  temperature = 23.5
  3 + 4 = 7

--- 3. Stringification ---
  STRINGIFY(hello) = hello
  STRINGIFY(3 + 4) = 3 + 4
  TO_STRING(VERSION_MAJOR) = 1

--- 4. Token pasting ---
  value1 = 100
  value2 = 200
  Function: print_hello()
  Function: print_world()

--- 5. Conditional compilation ---
[DEBUG] This only appears in debug mode
  Platform: Windows
  Path separator: '\'
  DEBUG_MODE is defined
  RELEASE_MODE is NOT defined

--- 6. #if with expressions ---
  Logging feature is ENABLED
  Metrics feature is DISABLED
  Version check passed (>= 1.0)

--- 7. Predefined macros ---
  __FILE__ = preprocessor.cpp
  __LINE__ = <line number>
  __DATE__ = <compilation date>
  __TIME__ = <compilation time>
  __cplusplus = 199711

--- 8. Assert macro ---
ASSERTION FAILED: x must be greater than 100 at preprocessor.cpp:<line>

--- 9. Safe delete macro ---
  Before: *ptr = 42
  After: ptr is NULL

--- 10. #undef ---
  TEMP_MACRO = 999
  TEMP_MACRO has been undefined
  TEMP_MACRO redefined = 111

Preprocessor demo complete.
*/
