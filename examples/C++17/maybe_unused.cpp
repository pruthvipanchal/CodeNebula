// CodeNebula - C++17 Example: [[maybe_unused]] Attribute
// Compile: g++ -std=c++17 -Wall -Wextra -o example maybe_unused.cpp

// Demonstrates [[maybe_unused]], which suppresses compiler warnings for
// entities that may intentionally go unused. Useful for debug-only variables,
// platform-specific code, and callback parameters.

#include <iostream>
#include <string>
#include <cassert>

// ------------------------------------------------------------------
// 1. [[maybe_unused]] on function parameters
// ------------------------------------------------------------------
void event_handler([[maybe_unused]] int event_id,
                   [[maybe_unused]] const std::string& source,
                   int priority) {
    // In release mode, event_id and source might only be used in asserts
    assert(event_id > 0);
    assert(!source.empty());

    std::cout << "  Handling event with priority: " << priority << std::endl;
}

// ------------------------------------------------------------------
// 2. [[maybe_unused]] on local variables
// ------------------------------------------------------------------
void process_data(int value) {
    [[maybe_unused]] int debug_copy = value;  // used only in debug builds
    [[maybe_unused]] auto start_time = 0;     // placeholder for timing

    // In release: debug_copy and start_time are unused -- no warning
    std::cout << "  Processing value: " << value << std::endl;

    #ifndef NDEBUG
    std::cout << "  [DEBUG] debug_copy = " << debug_copy << std::endl;
    #endif
}

// ------------------------------------------------------------------
// 3. [[maybe_unused]] on a function
// ------------------------------------------------------------------
[[maybe_unused]] static void internal_helper() {
    // This function might not be called in all configurations
    std::cout << "  internal_helper called" << std::endl;
}

// ------------------------------------------------------------------
// 4. [[maybe_unused]] on typedef / using
// ------------------------------------------------------------------
[[maybe_unused]] typedef unsigned long ulong_t;
using size_type [[maybe_unused]] = std::size_t;

// ------------------------------------------------------------------
// 5. [[maybe_unused]] on an enum / class
// ------------------------------------------------------------------
enum class [[maybe_unused]] DebugLevel { Off, Low, Medium, High };

struct [[maybe_unused]] DebugInfo {
    int line;
    const char* file;
};

// ------------------------------------------------------------------
// 6. Practical pattern: platform-specific code
// ------------------------------------------------------------------
void platform_init() {
    [[maybe_unused]] bool gpu_available = false;

    #ifdef _WIN32
    gpu_available = true;   // Windows GPU init
    #elif defined(__linux__)
    gpu_available = true;   // Linux GPU init
    #endif

    // gpu_available might be unused on unsupported platforms
    std::cout << "  Platform init complete" << std::endl;
}

int main()
{
    std::cout << "=== [[maybe_unused]] on parameters ===" << std::endl;
    event_handler(1, "keyboard", 5);

    std::cout << "\n=== [[maybe_unused]] on local variables ===" << std::endl;
    process_data(42);

    std::cout << "\n=== [[maybe_unused]] on function ===" << std::endl;
    internal_helper();  // called here, but might not be in other configs

    std::cout << "\n=== [[maybe_unused]] platform-specific ===" << std::endl;
    platform_init();

    std::cout << "\n=== summary ===" << std::endl;
    std::cout << "  All examples compiled without unused-variable warnings." << std::endl;
    std::cout << "  [[maybe_unused]] tells the compiler: 'this may be" << std::endl;
    std::cout << "  intentionally unused -- do not warn.'" << std::endl;

    return 0;
}

/*
Expected output:

=== [[maybe_unused]] on parameters ===
  Handling event with priority: 5

=== [[maybe_unused]] on local variables ===
  Processing value: 42

=== [[maybe_unused]] on function ===
  internal_helper called

=== [[maybe_unused]] platform-specific ===
  Platform init complete

=== summary ===
  All examples compiled without unused-variable warnings.
  [[maybe_unused]] tells the compiler: 'this may be
  intentionally unused -- do not warn.'
*/
