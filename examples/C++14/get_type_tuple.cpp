// CodeNebula - C++14 Example: std::get<Type>() for Tuples
// Compile: g++ -std=c++14 -Wall -Wextra -o example get_type_tuple.cpp

// Demonstrates accessing tuple elements by type instead of index using
// std::get<Type>(). The type must appear exactly once in the tuple.
// Real-world use: named-like access to tuple fields, clearer code when
// tuple element types are distinct, and reducing index-based errors.

#include <iostream>
#include <tuple>
#include <string>
#include <utility>

// ------------------------------------------------------------------
// Type aliases for clarity in multi-type tuples
// ------------------------------------------------------------------
struct Name   { std::string value; };
struct Age    { int value; };
struct Salary { double value; };

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic get-by-type (each type appears once)
    // ------------------------------------------------------------------
    auto record = std::make_tuple(42, 3.14, std::string("hello"));

    std::cout << "=== Basic get<Type> ===" << std::endl;
    std::cout << "  get<int>    : " << std::get<int>(record) << std::endl;
    std::cout << "  get<double> : " << std::get<double>(record) << std::endl;
    std::cout << "  get<string> : " << std::get<std::string>(record) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Comparison: index-based vs type-based access
    // ------------------------------------------------------------------
    using Config = std::tuple<std::string, int, bool>;
    Config cfg{"localhost", 8080, true};

    std::cout << "=== Index vs Type Access ===" << std::endl;
    std::cout << "  By index: get<0> = " << std::get<0>(cfg) << std::endl;
    std::cout << "  By type:  get<string> = " << std::get<std::string>(cfg) << std::endl;
    std::cout << "  By index: get<1> = " << std::get<1>(cfg) << std::endl;
    std::cout << "  By type:  get<int> = " << std::get<int>(cfg) << std::endl;
    std::cout << "  By index: get<2> = " << std::boolalpha << std::get<2>(cfg) << std::endl;
    std::cout << "  By type:  get<bool> = " << std::get<bool>(cfg) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Modifying through get<Type>
    // ------------------------------------------------------------------
    std::cout << "=== Modification via get<Type> ===" << std::endl;
    std::cout << "  Before: port = " << std::get<int>(cfg) << std::endl;
    std::get<int>(cfg) = 9090;
    std::cout << "  After:  port = " << std::get<int>(cfg) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. With std::pair (pairs are 2-element tuples)
    // ------------------------------------------------------------------
    std::pair<std::string, int> item{"widget", 99};

    std::cout << "=== get<Type> with std::pair ===" << std::endl;
    std::cout << "  get<string> : " << std::get<std::string>(item) << std::endl;
    std::cout << "  get<int>    : " << std::get<int>(item) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Wrapper structs for duplicate underlying types
    // ------------------------------------------------------------------
    // If you need two ints, wrap them in distinct types:
    auto employee = std::make_tuple(Name{"Alice"}, Age{30}, Salary{75000.0});

    std::cout << "=== Wrapper Types for Distinct Access ===" << std::endl;
    std::cout << "  Name   : " << std::get<Name>(employee).value << std::endl;
    std::cout << "  Age    : " << std::get<Age>(employee).value << std::endl;
    std::cout << "  Salary : " << std::get<Salary>(employee).value << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 6. With const and rvalue references
    // ------------------------------------------------------------------
    const auto& cfg_ref = cfg;

    std::cout << "=== Const Reference Access ===" << std::endl;
    std::cout << "  const get<string> : " << std::get<std::string>(cfg_ref) << std::endl;
    // std::get<std::string>(cfg_ref) = "x";  // Error: const reference

    // Move semantics
    auto moved = std::get<std::string>(std::make_tuple(std::string("moved!")));
    std::cout << "  rvalue get<string>: " << moved << std::endl;

    return 0;
}

/*
Expected output:

=== Basic get<Type> ===
  get<int>    : 42
  get<double> : 3.14
  get<string> : hello

=== Index vs Type Access ===
  By index: get<0> = localhost
  By type:  get<string> = localhost
  By index: get<1> = 8080
  By type:  get<int> = 8080
  By index: get<2> = true
  By type:  get<bool> = true

=== Modification via get<Type> ===
  Before: port = 8080
  After:  port = 9090

=== get<Type> with std::pair ===
  get<string> : widget
  get<int>    : 99

=== Wrapper Types for Distinct Access ===
  Name   : Alice
  Age    : 30
  Salary : 75000

=== Const Reference Access ===
  const get<string> : localhost
  rvalue get<string>: moved!
*/
