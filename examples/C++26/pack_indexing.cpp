// CodeNebula - C++26 Example: Pack Indexing
// Compile: g++ -std=c++26 -Wall -Wextra -o example pack_indexing.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// C++26 pack indexing allows direct access to a specific element in a
// parameter pack using T...[I] syntax, eliminating recursive templates
// and std::tuple tricks for simple element access.

#include <iostream>
#include <string>
#include <tuple>

// --- C++26 Pack Indexing Syntax (not yet compilable) ---
//
// // Access the Ith type in a parameter pack
// template<std::size_t I, typename... Ts>
// using nth_type = Ts...[I];   // Direct type indexing!
//
// // Access the Ith value in a parameter pack
// template<std::size_t I, typename... Args>
// auto get_nth(Args... args) {
//     return args...[I];        // Direct value indexing!
// }
//
// // First and last element access
// template<typename... Ts>
// auto first(Ts... args) { return args...[0]; }
//
// template<typename... Ts>
// auto last(Ts... args) { return args...[sizeof...(Ts) - 1]; }

// --- Simulation using C++20 features ---

// Simulate nth type access with std::tuple_element
template<std::size_t I, typename... Ts>
using nth_type = std::tuple_element_t<I, std::tuple<Ts...>>;

// Simulate nth value access using std::get on a tuple
template<std::size_t I, typename... Args>
auto get_nth(Args... args) {
    return std::get<I>(std::make_tuple(args...));
}

template<typename... Ts>
auto first(Ts... args) {
    return std::get<0>(std::make_tuple(args...));
}

template<typename... Ts>
auto last(Ts... args) {
    return std::get<sizeof...(Ts) - 1>(std::make_tuple(args...));
}

int main() {
    std::cout << "=== C++26 Pack Indexing (Simulated) ===" << std::endl;

    // Value indexing
    std::cout << "get_nth<0>(10,20,30) = " << get_nth<0>(10, 20, 30) << std::endl;
    std::cout << "get_nth<2>(10,20,30) = " << get_nth<2>(10, 20, 30) << std::endl;

    std::cout << "first(1,2,3) = " << first(1, 2, 3) << std::endl;
    std::cout << "last(1,2,3)  = " << last(1, 2, 3) << std::endl;

    // Type indexing
    static_assert(std::is_same_v<nth_type<0, int, double, char>, int>);
    static_assert(std::is_same_v<nth_type<1, int, double, char>, double>);
    std::cout << "nth_type<0, int,double,char> is int:    true" << std::endl;
    std::cout << "nth_type<1, int,double,char> is double: true" << std::endl;

    // Mixed types
    auto val = get_nth<1>(42, std::string("hello"), 3.14);
    std::cout << "get_nth<1>(42, \"hello\", 3.14) = " << val << std::endl;

    std::cout << "Pack indexing replaces recursive templates with T...[I]." << std::endl;
    return 0;
}

// Expected output:
// === C++26 Pack Indexing (Simulated) ===
// get_nth<0>(10,20,30) = 10
// get_nth<2>(10,20,30) = 30
// first(1,2,3) = 1
// last(1,2,3)  = 3
// nth_type<0, int,double,char> is int:    true
// nth_type<1, int,double,char> is double: true
// get_nth<1>(42, "hello", 3.14) = hello
// Pack indexing replaces recursive templates with T...[I].
