// CodeNebula - C++14 Example: decltype(auto)
// Compile: g++ -std=c++14 -Wall -Wextra -o example decltype_auto.cpp

// Demonstrates decltype(auto) which preserves the exact type including
// references and cv-qualifiers. Unlike plain 'auto' which strips references,
// decltype(auto) deduces the type exactly as decltype would. Real-world use:
// perfect forwarding of return types in wrapper/proxy functions.

#include <iostream>
#include <string>
#include <vector>

// ------------------------------------------------------------------
// Global data for reference examples
// ------------------------------------------------------------------
std::vector<int> global_data = {10, 20, 30, 40, 50};
std::string global_name = "CodeNebula";

// ------------------------------------------------------------------
// 1. auto strips references; decltype(auto) preserves them
// ------------------------------------------------------------------
auto get_copy(std::vector<int>& v)
{
    return v[0];            // returns int (copy)
}

decltype(auto) get_ref(std::vector<int>& v)
{
    return v[0];            // returns int& (reference!)
}

// ------------------------------------------------------------------
// 2. decltype(auto) with const references
// ------------------------------------------------------------------
decltype(auto) get_const_ref(const std::string& s)
{
    return s;               // returns const string&
}

// ------------------------------------------------------------------
// 3. Perfect return type forwarding in a wrapper
// ------------------------------------------------------------------
template<typename Container>
decltype(auto) front(Container& c)
{
    return c.front();       // preserves whatever front() returns
}

// ------------------------------------------------------------------
// 4. decltype(auto) variables (less common but valid)
// ------------------------------------------------------------------
void demonstrate_variables()
{
    int x = 42;
    int& rx = x;

    auto a = rx;              // int  (reference stripped)
    decltype(auto) b = rx;    // int& (reference preserved)

    b = 100;    // modifies x through the reference

    std::cout << "  auto a = rx       -> a = " << a
              << " (copy, x unchanged by a)" << std::endl;
    std::cout << "  decltype(auto) b  -> b = " << b
              << " (reference, x changed to 100)" << std::endl;
    std::cout << "  x after b = 100   -> x = " << x << std::endl;
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Reference preservation
    // ------------------------------------------------------------------
    std::cout << "=== auto vs decltype(auto) Return ===" << std::endl;
    std::cout << "  Original v[0]     : " << global_data[0] << std::endl;

    auto copy = get_copy(global_data);
    copy = 999;
    std::cout << "  After copy = 999  : v[0] = " << global_data[0]
              << " (unchanged, was a copy)" << std::endl;

    decltype(auto) ref = get_ref(global_data);
    ref = 999;
    std::cout << "  After ref = 999   : v[0] = " << global_data[0]
              << " (changed, was a reference)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Const reference preservation
    // ------------------------------------------------------------------
    std::cout << "=== Const Reference Preservation ===" << std::endl;
    decltype(auto) name_ref = get_const_ref(global_name);
    std::cout << "  name_ref: " << name_ref << std::endl;
    // name_ref = "other";  // Would fail: const reference
    std::cout << "  (const ref - cannot modify)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Perfect forwarding with containers
    // ------------------------------------------------------------------
    std::cout << "=== Perfect Return Forwarding ===" << std::endl;
    std::vector<double> doubles = {1.1, 2.2, 3.3};
    front(doubles) = 9.9;  // works because front() returns a reference
    std::cout << "  After front(doubles) = 9.9 : " << doubles[0] << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Variable declarations
    // ------------------------------------------------------------------
    std::cout << "=== decltype(auto) Variables ===" << std::endl;
    demonstrate_variables();

    return 0;
}

/*
Expected output:

=== auto vs decltype(auto) Return ===
  Original v[0]     : 10
  After copy = 999  : v[0] = 10 (unchanged, was a copy)
  After ref = 999   : v[0] = 999 (changed, was a reference)

=== Const Reference Preservation ===
  name_ref: CodeNebula
  (const ref - cannot modify)

=== Perfect Return Forwarding ===
  After front(doubles) = 9.9 : 9.9

=== decltype(auto) Variables ===
  auto a = rx       -> a = 42 (copy, x unchanged by a)
  decltype(auto) b  -> b = 100 (reference, x changed to 100)
  x after b = 100   -> x = 100
*/
