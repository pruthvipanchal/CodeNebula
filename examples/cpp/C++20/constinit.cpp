// CodeNebula - C++20 Example: constinit
// Compile: g++ -std=c++20 -Wall -Wextra -o example constinit.cpp

// Demonstrates the constinit keyword: ensures a variable is initialized at
// compile time (constant initialization), preventing the "static init order
// fiasco" while still allowing runtime modification (unlike constexpr).

#include <iostream>

// ------------------------------------------------------------------
// 1. constinit for global/static variables
// ------------------------------------------------------------------
constinit int globalCounter = 0;          // Initialized at compile time
constinit const char* appName = "MyApp";  // Pointer initialized at compile time
constinit double pi = 3.14159265358979;

// ------------------------------------------------------------------
// 2. constinit with constexpr function
// ------------------------------------------------------------------
constexpr int compute_initial_value() {
    return 42;
}

constinit int computed = compute_initial_value();

// ------------------------------------------------------------------
// 3. constinit vs constexpr comparison
// ------------------------------------------------------------------
// constexpr int ceVal = 100;  // Cannot be modified after init
constinit int ciVal = 100;     // Can be modified after init!

// ------------------------------------------------------------------
// 4. constinit with thread_local
// ------------------------------------------------------------------
constinit thread_local int threadId = 0;

// ------------------------------------------------------------------
// 5. constinit in a class with static members
// ------------------------------------------------------------------
struct AppConfig {
    static constinit int maxConnections;
    static constinit bool debugMode;
    static constinit const char* version;
};

constinit int AppConfig::maxConnections = 10;
constinit bool AppConfig::debugMode = false;
constinit const char* AppConfig::version = "1.0.0";

// ------------------------------------------------------------------
// 6. constexpr helper for constinit arrays
// ------------------------------------------------------------------
constexpr int square(int x) { return x * x; }

constinit int squares[] = {
    square(0), square(1), square(2), square(3), square(4)
};

int main()
{
    std::cout << "=== constinit Global Variables ===" << std::endl;
    std::cout << "  globalCounter = " << globalCounter << std::endl;
    std::cout << "  appName = " << appName << std::endl;
    std::cout << "  pi = " << pi << std::endl;

    std::cout << "\n=== constinit with constexpr Function ===" << std::endl;
    std::cout << "  computed = " << computed << std::endl;

    std::cout << "\n=== constinit is Mutable (unlike constexpr) ===" << std::endl;
    std::cout << "  ciVal before: " << ciVal << std::endl;
    ciVal = 200;  // OK! constinit only constrains initialization
    std::cout << "  ciVal after:  " << ciVal << std::endl;

    globalCounter++;
    globalCounter++;
    std::cout << "  globalCounter after 2 increments: " << globalCounter << std::endl;

    std::cout << "\n=== constinit thread_local ===" << std::endl;
    std::cout << "  threadId = " << threadId << std::endl;
    threadId = 1;  // Can modify at runtime
    std::cout << "  threadId after assignment: " << threadId << std::endl;

    std::cout << "\n=== constinit Static Class Members ===" << std::endl;
    std::cout << "  maxConnections: " << AppConfig::maxConnections << std::endl;
    std::cout << "  debugMode: " << AppConfig::debugMode << std::endl;
    std::cout << "  version: " << AppConfig::version << std::endl;

    AppConfig::debugMode = true;
    AppConfig::maxConnections = 50;
    std::cout << "  After runtime changes:" << std::endl;
    std::cout << "  maxConnections: " << AppConfig::maxConnections << std::endl;
    std::cout << "  debugMode: " << AppConfig::debugMode << std::endl;

    std::cout << "\n=== constinit Array ===" << std::endl;
    std::cout << "  squares:";
    for (int s : squares) std::cout << " " << s;
    std::cout << std::endl;

    return 0;
}

/*
Expected output:

=== constinit Global Variables ===
  globalCounter = 0
  appName = MyApp
  pi = 3.14159

=== constinit with constexpr Function ===
  computed = 42

=== constinit is Mutable (unlike constexpr) ===
  ciVal before: 100
  ciVal after:  200
  globalCounter after 2 increments: 2

=== constinit thread_local ===
  threadId = 0
  threadId after assignment: 1

=== constinit Static Class Members ===
  maxConnections: 10
  debugMode: 0
  version: 1.0.0
  After runtime changes:
  maxConnections: 50
  debugMode: 1

=== constinit Array ===
  squares: 0 1 4 9 16
*/
