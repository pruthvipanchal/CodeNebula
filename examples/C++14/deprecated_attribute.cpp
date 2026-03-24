// CodeNebula - C++14 Example: [[deprecated]] Attribute
// Compile: g++ -std=c++14 -Wall -Wextra -o example deprecated_attribute.cpp

// Demonstrates the [[deprecated]] and [[deprecated("message")]] attributes
// introduced in C++14. These generate compiler warnings when deprecated
// entities are used. Real-world use: API evolution, gradual migration from
// old interfaces, and communicating intended replacements to users.

#include <iostream>
#include <string>

// ------------------------------------------------------------------
// 1. Deprecated function (no message)
// ------------------------------------------------------------------
[[deprecated]]
int old_calculate(int x, int y)
{
    return x + y;
}

// ------------------------------------------------------------------
// 2. Deprecated function with replacement message
// ------------------------------------------------------------------
[[deprecated("Use fast_process() instead - 3x faster")]]
void slow_process(const std::string& data)
{
    std::cout << "  [slow_process] Processing: " << data << std::endl;
}

void fast_process(const std::string& data)
{
    std::cout << "  [fast_process] Processing: " << data << std::endl;
}

// ------------------------------------------------------------------
// 3. Deprecated class
// ------------------------------------------------------------------
class [[deprecated("Use ModernLogger instead")]] OldLogger
{
public:
    void log(const std::string& msg)
    {
        std::cout << "  [OldLogger] " << msg << std::endl;
    }
};

class ModernLogger
{
public:
    void log(const std::string& msg)
    {
        std::cout << "  [ModernLogger] " << msg << std::endl;
    }
};

// ------------------------------------------------------------------
// 4. Deprecated typedef / type alias
// ------------------------------------------------------------------
using Size = std::size_t;
[[deprecated("Use Size instead of LegacySize")]]
typedef std::size_t LegacySize;

// ------------------------------------------------------------------
// 5. Deprecated enum value
// ------------------------------------------------------------------
enum class Color
{
    Red,
    Green,
    Blue,
    Yellow [[deprecated("Yellow is removed in v3.0; use Gold")]] ,
    Gold
};

// ------------------------------------------------------------------
// 6. Deprecated variable
// ------------------------------------------------------------------
[[deprecated("Use MAX_CONNECTIONS_V2 instead")]]
constexpr int MAX_CONNECTIONS = 100;

constexpr int MAX_CONNECTIONS_V2 = 500;

int main()
{
    // Note: Using deprecated entities will produce compiler WARNINGS.
    // The code still compiles and runs. Warnings are the point!

    std::cout << "=== Deprecated Function (no message) ===" << std::endl;
    // Uncommenting the next line would trigger: warning: 'old_calculate' is deprecated
    // int result = old_calculate(3, 4);
    std::cout << "  (old_calculate skipped to avoid warning)" << std::endl;
    std::cout << std::endl;

    std::cout << "=== Deprecated Function (with message) ===" << std::endl;
    // Uncommenting: warning: 'slow_process' is deprecated: Use fast_process() instead
    // slow_process("data.csv");
    fast_process("data.csv");     // use the replacement
    std::cout << std::endl;

    std::cout << "=== Deprecated Class ===" << std::endl;
    // Uncommenting: warning: 'OldLogger' is deprecated: Use ModernLogger instead
    // OldLogger old_log;
    // old_log.log("hello");
    ModernLogger modern_log;
    modern_log.log("hello from modern logger");
    std::cout << std::endl;

    std::cout << "=== Deprecated Enum Value ===" << std::endl;
    Color c = Color::Gold;   // preferred
    // Color y = Color::Yellow;  // would warn: Yellow is removed in v3.0
    std::cout << "  Using Color::Gold (value " << static_cast<int>(c) << ")" << std::endl;
    std::cout << std::endl;

    std::cout << "=== Deprecated Variable ===" << std::endl;
    // int max = MAX_CONNECTIONS;  // would warn
    int max_v2 = MAX_CONNECTIONS_V2;
    std::cout << "  MAX_CONNECTIONS_V2 = " << max_v2 << std::endl;
    std::cout << std::endl;

    std::cout << "=== Summary ===" << std::endl;
    std::cout << "  [[deprecated]] generates compiler warnings, not errors." << std::endl;
    std::cout << "  It works on: functions, classes, typedefs, enums, variables." << std::endl;
    std::cout << "  Use the message form to guide users to replacements." << std::endl;

    return 0;
}

/*
Expected output:

=== Deprecated Function (no message) ===
  (old_calculate skipped to avoid warning)

=== Deprecated Function (with message) ===
  [fast_process] Processing: data.csv

=== Deprecated Class ===
  [ModernLogger] hello from modern logger

=== Deprecated Enum Value ===
  Using Color::Gold (value 4)

=== Deprecated Variable ===
  MAX_CONNECTIONS_V2 = 500

=== Summary ===
  [[deprecated]] generates compiler warnings, not errors.
  It works on: functions, classes, typedefs, enums, variables.
  Use the message form to guide users to replacements.
*/
