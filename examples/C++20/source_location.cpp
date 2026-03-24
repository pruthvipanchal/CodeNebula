// CodeNebula - C++20 Example: std::source_location
// Compile: g++ -std=c++20 -Wall -Wextra -o example source_location.cpp

// std::source_location captures call-site information (file, line, column,
// function name) at compile time. It replaces the __FILE__, __LINE__,
// and __func__ macros with a type-safe, composable alternative.

#include <iostream>
#include <source_location>
#include <string_view>

// A logging function that automatically captures the caller's location
void log(std::string_view message,
         const std::source_location& loc = std::source_location::current()) {
    std::cout << loc.file_name() << ":"
              << loc.line() << ":"
              << loc.column() << " ["
              << loc.function_name() << "] "
              << message << "\n";
}

// A debug-level logger with severity
enum class LogLevel { INFO, WARN, ERROR };

void log_with_level(LogLevel level, std::string_view message,
                    const std::source_location& loc = std::source_location::current()) {
    const char* level_str = "INFO";
    if (level == LogLevel::WARN)  level_str = "WARN";
    if (level == LogLevel::ERROR) level_str = "ERROR";

    std::cout << "[" << level_str << "] "
              << loc.file_name() << ":" << loc.line()
              << " in " << loc.function_name()
              << " - " << message << "\n";
}

// An assertion replacement using source_location
void my_assert(bool condition, std::string_view expr,
               const std::source_location& loc = std::source_location::current()) {
    if (!condition) {
        std::cout << "ASSERTION FAILED: " << expr << "\n"
                  << "  at " << loc.file_name() << ":" << loc.line()
                  << " in " << loc.function_name() << "\n";
    }
}

void helper_function() {
    log("Called from helper_function");
    log_with_level(LogLevel::WARN, "Something looks suspicious");
}

void demonstrate_assert() {
    int x = 5;
    my_assert(x > 0, "x > 0");       // passes
    my_assert(x > 10, "x > 10");     // fails — prints location info
}

int main() {
    std::cout << "=== std::source_location for Logging ===\n\n";

    // Direct usage
    auto loc = std::source_location::current();
    std::cout << "Current location:\n";
    std::cout << "  File:     " << loc.file_name() << "\n";
    std::cout << "  Line:     " << loc.line() << "\n";
    std::cout << "  Column:   " << loc.column() << "\n";
    std::cout << "  Function: " << loc.function_name() << "\n\n";

    // Logging with automatic location capture
    log("Starting application");
    log("Processing data");

    // Log from a different function
    helper_function();

    // Leveled logging
    std::cout << "\n";
    log_with_level(LogLevel::INFO, "Initialization complete");
    log_with_level(LogLevel::ERROR, "Connection failed");

    // Custom assert
    std::cout << "\n";
    demonstrate_assert();

    return 0;
}

// Expected output (file paths and exact line/column numbers will vary):
// === std::source_location for Logging ===
//
// Current location:
//   File:     source_location.cpp
//   Line:     55
//   Column:   ...
//   Function: main
//
// ... (log messages with file:line:column [function] format)
// ... ASSERTION FAILED: x > 10 ...
