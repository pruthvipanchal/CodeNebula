// CodeNebula - C++20 Example: CTAD Enhancements
// Compile: g++ -std=c++20 -Wall -Wextra -o example ctad_enhancements.cpp

// C++20 enhances Class Template Argument Deduction (CTAD):
//   1. CTAD for aggregates — no deduction guides needed
//   2. CTAD for alias templates — aliases can deduce too
//   3. Improvements to deduction guides

#include <iostream>
#include <vector>
#include <array>
#include <tuple>
#include <string>
#include <functional>
#include <memory>

// --- 1. CTAD for aggregates (C++20) ---
// In C++17, aggregates needed explicit deduction guides.
// C++20 deduces template parameters from aggregate init automatically.

template <typename T, typename U>
struct Pair {
    T first;
    U second;
};

template <typename T>
struct Holder {
    T value;
    int count;
};

template <typename T, int N>
struct FixedArray {
    T data[N];
};

// --- 2. CTAD for alias templates (C++20) ---
// Aliases can now participate in CTAD

template <typename T>
using Vec = std::vector<T>;

template <typename T>
using MyPair = Pair<T, T>;  // alias restricts both to same type

// --- 3. A class with custom deduction guide ---
template <typename T>
struct Wrapper {
    T value;

    Wrapper(T v) : value(v) {}
    Wrapper(T v, int) : value(v) {}  // second overload
};

// Deduction guide: const char* -> std::string
Wrapper(const char*) -> Wrapper<std::string>;

// --- Helper printer ---
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const Pair<T, U>& p) {
    return os << "{" << p.first << ", " << p.second << "}";
}

int main() {
    std::cout << "=== C++20 CTAD Enhancements ===\n\n";

    // --- Aggregate CTAD ---
    std::cout << "1. CTAD for aggregates:\n";

    // Deduces Pair<int, double>
    Pair p1{42, 3.14};
    std::cout << "   Pair{42, 3.14}       = " << p1 << "\n";

    // Deduces Pair<std::string, int>
    Pair p2{std::string("hello"), 5};
    std::cout << "   Pair{\"hello\", 5}     = " << p2 << "\n";

    // Deduces Holder<double>
    Holder h{2.718, 3};
    std::cout << "   Holder{2.718, 3}      = {" << h.value << ", " << h.count << "}\n";

    std::cout << "\n";

    // --- Alias template CTAD ---
    std::cout << "2. CTAD for alias templates:\n";

    // Vec deduces to std::vector<int>
    Vec v1{1, 2, 3, 4, 5};
    std::cout << "   Vec{1,2,3,4,5}:        ";
    for (int x : v1) std::cout << x << " ";
    std::cout << "\n";

    // MyPair deduces both types as the same
    MyPair mp{10, 20};  // Pair<int, int>
    std::cout << "   MyPair{10, 20}        = " << mp << "\n";

    std::cout << "\n";

    // --- Standard library CTAD improvements ---
    std::cout << "3. Standard library CTAD:\n";

    // std::array CTAD
    std::array arr{1, 2, 3, 4};  // deduces std::array<int, 4>
    std::cout << "   std::array{1,2,3,4}:   ";
    for (int x : arr) std::cout << x << " ";
    std::cout << "(size=" << arr.size() << ")\n";

    // std::tuple CTAD
    std::tuple tup{42, 3.14, std::string("abc")};
    std::cout << "   std::tuple{42,3.14,\"abc\"}: ("
              << std::get<0>(tup) << ", "
              << std::get<1>(tup) << ", "
              << std::get<2>(tup) << ")\n";

    // std::pair CTAD
    std::pair sp{100, "text"};
    std::cout << "   std::pair{100,\"text\"}: ("
              << sp.first << ", " << sp.second << ")\n";

    std::cout << "\n";

    // --- Custom deduction guide ---
    std::cout << "4. Custom deduction guides:\n";

    Wrapper w1{42};          // Wrapper<int>
    Wrapper w2{"hello"};     // Wrapper<std::string> via deduction guide
    std::cout << "   Wrapper{42}:      " << w1.value << "\n";
    std::cout << "   Wrapper{\"hello\"}: " << w2.value << "\n";

    return 0;
}

// Expected output:
// === C++20 CTAD Enhancements ===
//
// 1. CTAD for aggregates:
//    Pair{42, 3.14}       = {42, 3.14}
//    Pair{"hello", 5}     = {hello, 5}
//    Holder{2.718, 3}      = {2.718, 3}
//
// 2. CTAD for alias templates:
//    Vec{1,2,3,4,5}:        1 2 3 4 5
//    MyPair{10, 20}        = {10, 20}
//
// 3. Standard library CTAD:
//    std::array{1,2,3,4}:   1 2 3 4 (size=4)
//    std::tuple{42,3.14,"abc"}: (42, 3.14, abc)
//    std::pair{100,"text"}: (100, text)
//
// 4. Custom deduction guides:
//    Wrapper{42}:      42
//    Wrapper{"hello"}: hello
