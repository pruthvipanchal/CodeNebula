// CodeNebula - C++17 Example: Inline Variables
// Compile: g++ -std=c++17 -Wall -Wextra -o example inline_variables.cpp

// Demonstrates inline variables and inline static data members. Before C++17,
// static data members required a separate out-of-class definition. Now, inline
// allows definition directly in the class, and inline global variables can appear
// in headers without ODR violations.

#include <iostream>
#include <string>

// ------------------------------------------------------------------
// 1. inline variable at namespace scope (safe to put in a header)
// ------------------------------------------------------------------
inline const int kMaxConnections = 100;
inline const std::string kAppName = "CodeNebula";

// ------------------------------------------------------------------
// 2. Class with inline static data members (no out-of-class definition needed)
// ------------------------------------------------------------------
struct Config {
    inline static int version = 3;
    inline static std::string mode = "release";
    inline static constexpr double pi = 3.14159265358979;  // constexpr implies inline

    static void print() {
        std::cout << "  version: " << version << std::endl;
        std::cout << "  mode   : " << mode << std::endl;
        std::cout << "  pi     : " << pi << std::endl;
    }
};

// ------------------------------------------------------------------
// 3. Template with inline static member
// ------------------------------------------------------------------
template <typename T>
struct TypeInfo {
    inline static int instance_count = 0;

    TypeInfo()  { ++instance_count; }
    ~TypeInfo() { --instance_count; }
};

// ------------------------------------------------------------------
// 4. inline constexpr for compile-time constants
// ------------------------------------------------------------------
inline constexpr int BUFFER_SIZE = 1024;
inline constexpr char DELIMITER = ',';

int main()
{
    // Namespace-scope inline variables
    std::cout << "=== inline namespace-scope variables ===" << std::endl;
    std::cout << "  kMaxConnections: " << kMaxConnections << std::endl;
    std::cout << "  kAppName       : " << kAppName << std::endl;

    // Class inline static members
    std::cout << "\n=== inline static class members ===" << std::endl;
    Config::print();

    // Modify inline static members
    Config::version = 4;
    Config::mode = "debug";
    std::cout << "\n=== after modification ===" << std::endl;
    Config::print();

    // Template inline static members (each specialization gets its own copy)
    std::cout << "\n=== template inline static members ===" << std::endl;
    TypeInfo<int> a, b, c;
    TypeInfo<double> d;
    std::cout << "  TypeInfo<int>::instance_count   : " << TypeInfo<int>::instance_count << std::endl;
    std::cout << "  TypeInfo<double>::instance_count: " << TypeInfo<double>::instance_count << std::endl;

    // inline constexpr
    std::cout << "\n=== inline constexpr ===" << std::endl;
    std::cout << "  BUFFER_SIZE: " << BUFFER_SIZE << std::endl;
    std::cout << "  DELIMITER  : '" << DELIMITER << "'" << std::endl;

    return 0;
}

/*
Expected output:

=== inline namespace-scope variables ===
  kMaxConnections: 100
  kAppName       : CodeNebula

=== inline static class members ===
  version: 3
  mode   : release
  pi     : 3.14159

=== after modification ===
  version: 4
  mode   : debug
  pi     : 3.14159

=== template inline static members ===
  TypeInfo<int>::instance_count   : 3
  TypeInfo<double>::instance_count: 1

=== inline constexpr ===
  BUFFER_SIZE: 1024
  DELIMITER  : ','
*/
