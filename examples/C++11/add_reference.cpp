// CodeNebula - C++11 Example: add_reference
// Compile: g++ -std=c++11 -Wall -Wextra -o example add_reference.cpp

// Demonstrates std::add_lvalue_reference and std::add_rvalue_reference.
// These follow reference collapsing rules: T& + & = T&, T& + && = T&.

#include <iostream>
#include <type_traits>

int main() {
    std::cout << "=== std::add_lvalue_reference / add_rvalue_reference ===" << std::endl;

    // add_lvalue_reference adds &
    using LRef = std::add_lvalue_reference<int>::type;
    using LRefFromRef = std::add_lvalue_reference<int&>::type;
    using LRefFromRRef = std::add_lvalue_reference<int&&>::type;

    static_assert(std::is_same<LRef, int&>::value, "int -> int&");
    static_assert(std::is_same<LRefFromRef, int&>::value, "int& -> int&");
    static_assert(std::is_same<LRefFromRRef, int&>::value, "int&& -> int& (collapse)");

    std::cout << "add_lvalue_reference<int>   is int&: "
              << std::is_same<LRef, int&>::value << std::endl;
    std::cout << "add_lvalue_reference<int&>  is int&: "
              << std::is_same<LRefFromRef, int&>::value << std::endl;
    std::cout << "add_lvalue_reference<int&&> is int&: "
              << std::is_same<LRefFromRRef, int&>::value << std::endl;

    // add_rvalue_reference adds &&
    using RRef = std::add_rvalue_reference<int>::type;
    using RRefFromLRef = std::add_rvalue_reference<int&>::type;
    using RRefFromRRef = std::add_rvalue_reference<int&&>::type;

    static_assert(std::is_same<RRef, int&&>::value, "int -> int&&");
    static_assert(std::is_same<RRefFromLRef, int&>::value, "int& -> int& (collapse)");
    static_assert(std::is_same<RRefFromRRef, int&&>::value, "int&& -> int&&");

    std::cout << "\nadd_rvalue_reference<int>   is int&&: "
              << std::is_same<RRef, int&&>::value << std::endl;
    std::cout << "add_rvalue_reference<int&>  is int&:  "
              << std::is_same<RRefFromLRef, int&>::value << std::endl;
    std::cout << "add_rvalue_reference<int&&> is int&&: "
              << std::is_same<RRefFromRRef, int&&>::value << std::endl;

    // void is special: references to void are not formed
    std::cout << "\nadd_lvalue_reference<void> is void: "
              << std::is_same<std::add_lvalue_reference<void>::type, void>::value << std::endl;

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::add_lvalue_reference / add_rvalue_reference ===
// add_lvalue_reference<int>   is int&: 1
// add_lvalue_reference<int&>  is int&: 1
// add_lvalue_reference<int&&> is int&: 1
//
// add_rvalue_reference<int>   is int&&: 1
// add_rvalue_reference<int&>  is int&:  1
// add_rvalue_reference<int&&> is int&&: 1
//
// add_lvalue_reference<void> is void: 1
//
// All checks passed!
