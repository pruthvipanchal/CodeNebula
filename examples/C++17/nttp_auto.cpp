// CodeNebula - C++17 Example: auto Non-Type Template Parameters
// Compile: g++ -std=c++17 -Wall -Wextra -o example nttp_auto.cpp

// Demonstrates C++17's auto for non-type template parameters. Instead of
// specifying the exact type (int, char, bool, etc.), you use auto and the
// compiler deduces it. This simplifies generic code that works with any
// compile-time constant.

#include <iostream>
#include <type_traits>
#include <string>
#include <array>

// ------------------------------------------------------------------
// 1. Basic auto NTTP: type is deduced from the argument
// ------------------------------------------------------------------
template <auto Value>
struct Constant {
    using type = decltype(Value);

    static void print() {
        std::cout << "  Value = " << Value
                  << ", type = " << typeid(type).name() << std::endl;
    }
};

// ------------------------------------------------------------------
// 2. auto NTTP for compile-time dispatch
// ------------------------------------------------------------------
template <auto N>
constexpr auto doubled() {
    return N + N;  // works for int, char, bool, etc.
}

// ------------------------------------------------------------------
// 3. Heterogeneous compile-time list using auto...
// ------------------------------------------------------------------
template <auto... Values>
struct ValueList {
    static constexpr std::size_t size = sizeof...(Values);

    static void print() {
        std::cout << "  [";
        ((std::cout << " " << Values), ...);
        std::cout << " ] (size=" << size << ")" << std::endl;
    }
};

// ------------------------------------------------------------------
// 4. auto NTTP for function pointers
// ------------------------------------------------------------------
int add(int a, int b) { return a + b; }
int multiply(int a, int b) { return a * b; }

template <auto Func>
int apply(int a, int b) {
    return Func(a, b);
}

// ------------------------------------------------------------------
// 5. auto NTTP for member pointers
// ------------------------------------------------------------------
struct Config {
    int width = 800;
    int height = 600;
    bool fullscreen = false;
};

template <auto MemberPtr>
auto get_member(const Config& cfg) {
    return cfg.*MemberPtr;
}

// ------------------------------------------------------------------
// 6. Compile-time factorial with auto NTTP
// ------------------------------------------------------------------
template <auto N>
constexpr auto factorial() {
    if constexpr (N <= 1) return decltype(N){1};
    else return N * factorial<N - 1>();
}

int main()
{
    // 1. Basic auto NTTP
    std::cout << "=== auto NTTP basics ===" << std::endl;
    Constant<42>::print();        // int
    Constant<'A'>::print();       // char
    Constant<true>::print();      // bool
    Constant<100UL>::print();     // unsigned long

    // 2. Doubled with auto NTTP
    std::cout << "\n=== doubled<N>() ===" << std::endl;
    std::cout << "  doubled<21>()   = " << doubled<21>() << std::endl;
    std::cout << "  doubled<'A'>()  = " << static_cast<char>(doubled<'A'>()) << std::endl;
    std::cout << "  doubled<true>() = " << doubled<true>() << std::endl;

    // 3. Heterogeneous value list (auto...)
    std::cout << "\n=== ValueList<auto...> ===" << std::endl;
    ValueList<1, 2, 3, 4, 5>::print();
    ValueList<'x', 'y', 'z'>::print();

    // 4. Function pointer as NTTP
    std::cout << "\n=== function pointer NTTP ===" << std::endl;
    std::cout << "  apply<add>(3, 4)      = " << apply<add>(3, 4) << std::endl;
    std::cout << "  apply<multiply>(3, 4) = " << apply<multiply>(3, 4) << std::endl;

    // 5. Member pointer as NTTP
    std::cout << "\n=== member pointer NTTP ===" << std::endl;
    Config cfg;
    std::cout << "  width:  " << get_member<&Config::width>(cfg) << std::endl;
    std::cout << "  height: " << get_member<&Config::height>(cfg) << std::endl;

    // 6. Compile-time factorial
    std::cout << "\n=== compile-time factorial ===" << std::endl;
    std::cout << "  5!  = " << factorial<5>() << std::endl;
    std::cout << "  10! = " << factorial<10>() << std::endl;

    return 0;
}

/*
Expected output (type names are compiler-dependent):

=== auto NTTP basics ===
  Value = 42, type = i
  Value = A, type = c
  Value = 1, type = b
  Value = 100, type = m

=== doubled<N>() ===
  doubled<21>()   = 42
  doubled<'A'>()  = (char with value 130, displayed as a character)
  doubled<true>() = 2

=== ValueList<auto...> ===
  [ 1 2 3 4 5 ] (size=5)
  [ x y z ] (size=3)

=== function pointer NTTP ===
  apply<add>(3, 4)      = 7
  apply<multiply>(3, 4) = 12

=== member pointer NTTP ===
  width:  800
  height: 600

=== compile-time factorial ===
  5!  = 120
  10! = 3628800
*/
