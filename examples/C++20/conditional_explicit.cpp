// CodeNebula - C++20 Example: Conditional explicit (explicit(bool))
// Compile: g++ -std=c++20 -Wall -Wextra -o example conditional_explicit.cpp

// C++20 allows explicit(bool-expression) to conditionally make a
// constructor or conversion explicit. This is useful in wrapper types
// that should mirror the implicit/explicit behavior of the wrapped type.

#include <iostream>
#include <type_traits>
#include <string>

// A wrapper that is implicitly convertible only when T is
// implicitly convertible from the argument type
template <typename T>
struct Wrapper {
    T value;

    // If U is implicitly convertible to T, this constructor is implicit.
    // Otherwise, it is explicit.
    template <typename U>
    explicit(!std::is_convertible_v<U, T>)
    Wrapper(U&& val) : value(std::forward<U>(val)) {}

    friend std::ostream& operator<<(std::ostream& os, const Wrapper& w) {
        os << w.value;
        return os;
    }
};

// A pair type where explicitness depends on BOTH element types
template <typename T1, typename T2>
struct MyPair {
    T1 first;
    T2 second;

    template <typename U1, typename U2>
    explicit(!std::is_convertible_v<U1, T1> || !std::is_convertible_v<U2, T2>)
    MyPair(U1&& a, U2&& b)
        : first(std::forward<U1>(a)), second(std::forward<U2>(b)) {}
};

// Demonstrate with a type that has an explicit-only constructor
struct StrictInt {
    int value;
    explicit StrictInt(int v) : value(v) {}  // no implicit conversion from int
};

// A numeric type with conditional explicit conversion operator
template <typename T>
struct Number {
    T val;

    Number(T v) : val(v) {}

    // Implicit conversion to U only if T is implicitly convertible to U
    template <typename U>
    explicit(!std::is_convertible_v<T, U>)
    operator U() const { return static_cast<U>(val); }
};

void takes_wrapper_int(Wrapper<int> w) {
    std::cout << "  Wrapper<int>: " << w << "\n";
}

void takes_wrapper_string(Wrapper<std::string> w) {
    std::cout << "  Wrapper<string>: " << w << "\n";
}

int main() {
    std::cout << "=== explicit(bool) — Conditional Explicit ===\n\n";

    // --- Wrapper examples ---
    // int -> int is implicit, so Wrapper<int> from int is implicit
    Wrapper<int> w1 = 42;             // OK: implicit
    std::cout << "Wrapper<int> from int: " << w1 << "\n";

    // const char* -> std::string is implicit
    Wrapper<std::string> w2 = "hello"; // OK: implicit
    std::cout << "Wrapper<string> from const char*: " << w2 << "\n";

    // double -> int is narrowing but convertible
    Wrapper<int> w3 = 3.14;           // OK: double is convertible to int
    std::cout << "Wrapper<int> from double: " << w3 << "\n\n";

    // --- Function call demonstrates implicit conversion ---
    std::cout << "Implicit conversions in function calls:\n";
    takes_wrapper_int(100);            // OK: int -> Wrapper<int> is implicit
    takes_wrapper_string("world");     // OK: const char* -> string is implicit
    std::cout << "\n";

    // --- MyPair examples ---
    // Both conversions are implicit -> MyPair is implicit
    MyPair<int, double> p1 = {1, 2.5};
    std::cout << "MyPair<int,double>: " << p1.first << ", " << p1.second << "\n";

    // --- Number conversion ---
    Number<int> n{42};
    double d = n;     // int -> double is implicit, so this works
    std::cout << "Number<int> to double: " << d << "\n";

    // int -> std::string is NOT convertible, so this would fail:
    // std::string s = n;  // ERROR: explicit conversion required

    std::cout << "\nKey insight: explicit(condition) lets generic wrappers\n"
              << "mirror the implicit/explicit behavior of their contents.\n";

    return 0;
}

// Expected output:
// === explicit(bool) — Conditional Explicit ===
//
// Wrapper<int> from int: 42
// Wrapper<string> from const char*: hello
// Wrapper<int> from double: 3
//
// Implicit conversions in function calls:
//   Wrapper<int>: 100
//   Wrapper<string>: world
//
// MyPair<int,double>: 1, 2.5
// Number<int> to double: 42
//
// Key insight: explicit(condition) lets generic wrappers
// mirror the implicit/explicit behavior of their contents.
