// CodeNebula - C++20 Example: std::assignable_from Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example assignable_from.cpp

// std::assignable_from<LHS, RHS> checks that an expression of type RHS
// can be assigned to an lvalue of type LHS. The LHS must be an lvalue
// reference type.

#include <concepts>
#include <iostream>
#include <string>
#include <vector>

// Generic assign function constrained by assignable_from
template <typename T, typename U>
    requires std::assignable_from<T&, U>
void assign_to(T& target, U&& source) {
    target = std::forward<U>(source);
    std::cout << "Assignment successful\n";
}

// Fill a container element if assignment is valid
template <typename Container, typename Value>
    requires std::assignable_from<typename Container::reference, Value>
void fill_first(Container& c, Value&& val) {
    if (!c.empty()) {
        c.front() = std::forward<Value>(val);
        std::cout << "Filled first element\n";
    }
}

// Compile-time checks
template <typename LHS, typename RHS>
void check_assignable(const char* lhs_name, const char* rhs_name) {
    std::cout << lhs_name << " = " << rhs_name << ": "
              << std::assignable_from<LHS, RHS> << "\n";
}

int main() {
    // Basic assignment
    int x = 0;
    assign_to(x, 42);
    std::cout << "x = " << x << "\n";

    // String assignment from const char*
    std::string s = "hello";
    assign_to(s, "world");
    std::cout << "s = " << s << "\n";

    // Fill first element of vector
    std::vector<int> v = {1, 2, 3};
    fill_first(v, 99);
    std::cout << "v[0] = " << v[0] << "\n";

    // Check various assignability relationships
    std::cout << "\nAssignability checks:\n";
    check_assignable<int&, int>("int&", "int");
    check_assignable<int&, double>("int&", "double");
    check_assignable<std::string&, const char*>("string&", "const char*");
    check_assignable<double&, int>("double&", "int");
    check_assignable<std::string&, int>("string&", "int");
    check_assignable<int&, std::string>("int&", "string");

    return 0;
}

// Expected output:
// Assignment successful
// x = 42
// Assignment successful
// s = world
// Filled first element
// v[0] = 99
//
// Assignability checks:
// int& = int: 1
// int& = double: 1
// string& = const char*: 1
// double& = int: 1
// string& = int: 0
// int& = string: 0
