// CodeNebula - C++23 Example: std::stacktrace
// Compile: g++ -std=c++23 -Wall -Wextra -lstdc++_libbacktrace -o example stacktrace.cpp
// Note: Requires GCC 12+ / Clang 19+ / MSVC 19.34+
//       GCC needs -lstdc++_libbacktrace; MSVC links automatically.
//       Compile with -g for meaningful function names and line numbers.

// std::stacktrace captures the current call stack at runtime.
// Useful for debugging, error reporting, and logging.

#include <iostream>
#include <stacktrace>
#include <string>

void print_trace(const std::string& label) {
    std::cout << "--- " << label << " ---" << std::endl;
    auto trace = std::stacktrace::current();
    std::cout << "Stack depth: " << trace.size() << " frames" << std::endl;

    for (std::size_t i = 0; i < trace.size() && i < 5; ++i) {
        const auto& entry = trace[i];
        std::cout << "  [" << i << "] ";
        if (!entry.description().empty())
            std::cout << entry.description();
        else
            std::cout << "(no description)";
        std::cout << std::endl;

        // source_file and source_line may be empty without debug info
        if (!entry.source_file().empty()) {
            std::cout << "       at " << entry.source_file()
                      << ":" << entry.source_line() << std::endl;
        }
    }
    std::cout << std::endl;
}

void function_c() {
    print_trace("Inside function_c");
}

void function_b() {
    function_c();
}

void function_a() {
    function_b();
}

// Capture stacktrace in an exception-like error report
struct ErrorReport {
    std::string message;
    std::stacktrace trace;

    ErrorReport(const std::string& msg)
        : message(msg), trace(std::stacktrace::current()) {}

    void print() const {
        std::cout << "ERROR: " << message << std::endl;
        std::cout << "Captured " << trace.size() << " frames" << std::endl;
        // Print top 3 frames
        for (std::size_t i = 0; i < trace.size() && i < 3; ++i) {
            std::cout << "  [" << i << "] " << trace[i].description() << std::endl;
        }
    }
};

void risky_operation() {
    ErrorReport err("something went wrong in risky_operation");
    err.print();
}

int main() {
    std::cout << "=== std::stacktrace ===" << std::endl;

    // Capture current stacktrace
    auto here = std::stacktrace::current();
    std::cout << "Current stack has " << here.size() << " frame(s)" << std::endl;

    // Nested call to show stack depth
    std::cout << "\n=== Nested calls ===" << std::endl;
    function_a();

    // Stacktrace in error reporting
    std::cout << "=== Error reporting with stacktrace ===" << std::endl;
    risky_operation();

    // Convert to string
    std::cout << "\n=== to_string ===" << std::endl;
    auto trace = std::stacktrace::current();
    std::string trace_str = std::to_string(trace);
    std::cout << "Trace as string (first 120 chars):" << std::endl;
    std::cout << trace_str.substr(0, 120) << "..." << std::endl;

    return 0;
}

/*
Expected output (exact frames vary by platform and compiler):
=== std::stacktrace ===
Current stack has N frame(s)

=== Nested calls ===
--- Inside function_c ---
Stack depth: N frames
  [0] print_trace(...)
  [1] function_c()
  [2] function_b()
  [3] function_a()
  [4] main

=== Error reporting with stacktrace ===
ERROR: something went wrong in risky_operation
Captured N frames
  [0] risky_operation()
  [1] main
  ...

=== to_string ===
Trace as string (first 120 chars):
(platform-dependent stack trace text)...
*/
