// CodeNebula - C++98 Example: Default Arguments
// Compile: g++ -std=c++98 -Wall -Wextra -o example default_arguments.cpp

// Demonstrates default arguments in C++98: functions with default parameter
// values, rules for placement, combining with overloading, and practical uses.

#include <iostream>
#include <cstring>

// ------------------------------------------------------------------
// 1. Simple function with default arguments
//    Default arguments must be at the END of the parameter list.
// ------------------------------------------------------------------
void printLine(char ch = '-', int length = 40)
{
    for (int i = 0; i < length; ++i) {
        std::cout << ch;
    }
    std::cout << std::endl;
}

// ------------------------------------------------------------------
// 2. Function with some defaults and some required
// ------------------------------------------------------------------
void displayMessage(const char* message, int indent = 0, bool uppercase = false)
{
    // Print indentation
    for (int i = 0; i < indent; ++i) {
        std::cout << ' ';
    }

    if (uppercase) {
        // Print each char in uppercase
        for (int i = 0; message[i] != '\0'; ++i) {
            char c = message[i];
            if (c >= 'a' && c <= 'z') {
                c = c - 'a' + 'A';
            }
            std::cout << c;
        }
    } else {
        std::cout << message;
    }
    std::cout << std::endl;
}

// ------------------------------------------------------------------
// 3. Power function with default exponent
// ------------------------------------------------------------------
double power(double base, int exponent = 2)
{
    double result = 1.0;
    bool negative = (exponent < 0);
    int exp = negative ? -exponent : exponent;

    for (int i = 0; i < exp; ++i) {
        result *= base;
    }

    return negative ? 1.0 / result : result;
}

// ------------------------------------------------------------------
// 4. Default arguments in a "configuration" style function
// ------------------------------------------------------------------
void createWindow(const char* title,
                  int width = 800,
                  int height = 600,
                  bool fullscreen = false,
                  bool resizable = true)
{
    std::cout << "  Window created:" << std::endl;
    std::cout << "    Title      : " << title << std::endl;
    std::cout << "    Size       : " << width << "x" << height << std::endl;
    std::cout << "    Fullscreen : " << (fullscreen ? "yes" : "no") << std::endl;
    std::cout << "    Resizable  : " << (resizable ? "yes" : "no") << std::endl;
}

// ------------------------------------------------------------------
// 5. Default arguments with pointer parameters
// ------------------------------------------------------------------
void logMessage(const char* msg, const char* prefix = "INFO", int level = 0)
{
    std::cout << "  [" << prefix << "]";
    if (level > 0) {
        std::cout << "(L" << level << ")";
    }
    std::cout << " " << msg << std::endl;
}

// ------------------------------------------------------------------
// 6. Default argument using a previous declaration
//    Defaults are specified in the declaration (prototype), not definition.
// ------------------------------------------------------------------

// Forward declaration with defaults:
int clamp(int value, int low = 0, int high = 100);

// Definition WITHOUT repeating the defaults:
int clamp(int value, int low, int high)
{
    if (value < low)  return low;
    if (value > high) return high;
    return value;
}

// ------------------------------------------------------------------
// 7. Practical example: formatted number output
// ------------------------------------------------------------------
void printNumber(int value, int width = 0, char fill = ' ')
{
    // Simple right-aligned number printing
    // First, calculate number of digits
    int temp = (value < 0) ? -value : value;
    int digits = 0;
    if (temp == 0) {
        digits = 1;
    } else {
        int t = temp;
        while (t > 0) {
            ++digits;
            t /= 10;
        }
    }
    if (value < 0) ++digits; // for minus sign

    // Print fill characters
    for (int i = digits; i < width; ++i) {
        std::cout << fill;
    }
    std::cout << value;
}

int main()
{
    // ------------------------------------------------------------------
    // Demo 1: Function with all defaults
    // ------------------------------------------------------------------
    std::cout << "=== printLine with Defaults ===" << std::endl;

    printLine();                // uses both defaults: '-', 40
    printLine('=');             // uses default length: 40
    printLine('*', 20);        // no defaults used
    printLine('#', 10);
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 2: Mix of required and default parameters
    // ------------------------------------------------------------------
    std::cout << "=== displayMessage ===" << std::endl;

    displayMessage("Hello, World!");                  // indent=0, uppercase=false
    displayMessage("Indented message", 4);            // uppercase=false
    displayMessage("loud message", 0, true);          // all specified
    displayMessage("indented and loud", 8, true);
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 3: Power function
    // ------------------------------------------------------------------
    std::cout << "=== power with Default Exponent ===" << std::endl;

    std::cout << "  power(5)      = " << power(5) << " (default exponent=2)" << std::endl;
    std::cout << "  power(5, 2)   = " << power(5, 2) << std::endl;
    std::cout << "  power(5, 3)   = " << power(5, 3) << std::endl;
    std::cout << "  power(2, 10)  = " << power(2, 10) << std::endl;
    std::cout << "  power(2, -3)  = " << power(2, -3) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 4: Configuration-style function
    // ------------------------------------------------------------------
    std::cout << "=== createWindow ===" << std::endl;

    std::cout << "  With all defaults:" << std::endl;
    createWindow("My App");

    std::cout << "  Custom size:" << std::endl;
    createWindow("Editor", 1024, 768);

    std::cout << "  Fullscreen:" << std::endl;
    createWindow("Game", 1920, 1080, true, false);
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 5: Logging with defaults
    // ------------------------------------------------------------------
    std::cout << "=== logMessage ===" << std::endl;

    logMessage("Application started");                   // prefix="INFO", level=0
    logMessage("File not found", "WARN");                // level=0
    logMessage("Null pointer dereference", "ERROR", 3);  // all specified
    logMessage("Connection established", "DEBUG", 1);
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 6: Defaults specified in declaration
    // ------------------------------------------------------------------
    std::cout << "=== clamp ===" << std::endl;

    std::cout << "  clamp(150)        = " << clamp(150)        << " (clamped to 0..100)" << std::endl;
    std::cout << "  clamp(-10)        = " << clamp(-10)        << " (clamped to 0..100)" << std::endl;
    std::cout << "  clamp(50)         = " << clamp(50)         << " (within range)" << std::endl;
    std::cout << "  clamp(50, 0, 40)  = " << clamp(50, 0, 40) << " (custom range)" << std::endl;
    std::cout << "  clamp(50, 60, 100)= " << clamp(50, 60, 100) << " (below custom range)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 7: Formatted number output
    // ------------------------------------------------------------------
    std::cout << "=== printNumber ===" << std::endl;

    std::cout << "  Default:   [";
    printNumber(42);
    std::cout << "]" << std::endl;

    std::cout << "  Width 8:   [";
    printNumber(42, 8);
    std::cout << "]" << std::endl;

    std::cout << "  Width 8 0: [";
    printNumber(42, 8, '0');
    std::cout << "]" << std::endl;

    std::cout << "  Negative:  [";
    printNumber(-7, 6, '.');
    std::cout << "]" << std::endl;

    // Right-aligned table
    std::cout << std::endl;
    std::cout << "  Formatted table:" << std::endl;
    int values[] = {1, 23, 456, 7890, 12};
    for (int i = 0; i < 5; ++i) {
        std::cout << "    ";
        printNumber(values[i], 6);
        std::cout << std::endl;
    }

    return 0;
}

/*
Expected output:

=== printLine with Defaults ===
----------------------------------------
========================================
********************
##########

=== displayMessage ===
Hello, World!
    Indented message
LOUD MESSAGE
        INDENTED AND LOUD

=== power with Default Exponent ===
  power(5)      = 25 (default exponent=2)
  power(5, 2)   = 25
  power(5, 3)   = 125
  power(2, 10)  = 1024
  power(2, -3)  = 0.125

=== createWindow ===
  With all defaults:
  Window created:
    Title      : My App
    Size       : 800x600
    Fullscreen : no
    Resizable  : yes
  Custom size:
  Window created:
    Title      : Editor
    Size       : 1024x768
    Fullscreen : no
    Resizable  : yes
  Fullscreen:
  Window created:
    Title      : Game
    Size       : 1920x1080
    Fullscreen : yes
    Resizable  : no

=== logMessage ===
  [INFO] Application started
  [WARN] File not found
  [ERROR](L3) Null pointer dereference
  [DEBUG](L1) Connection established

=== clamp ===
  clamp(150)        = 100 (clamped to 0..100)
  clamp(-10)        = 0 (clamped to 0..100)
  clamp(50)         = 50 (within range)
  clamp(50, 0, 40)  = 40 (custom range)
  clamp(50, 60, 100)= 60 (below custom range)

=== printNumber ===
  Default:   [42]
  Width 8:   [      42]
  Width 8 0: [00000042]
  Negative:  [....-7]

  Formatted table:
         1
        23
       456
      7890
        12
*/
