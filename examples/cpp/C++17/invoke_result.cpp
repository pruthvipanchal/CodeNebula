// CodeNebula - C++17 Example: std::invoke_result
// Compile: g++ -std=c++17 -Wall -Wextra -o example invoke_result.cpp

// Demonstrates std::invoke_result, the C++17 replacement for the deprecated
// std::result_of. It deduces the return type of invoking a callable with
// given argument types, and is SFINAE-friendly (no hard error on failure).

#include <iostream>
#include <type_traits>
#include <string>
#include <functional>

int add(int a, int b) { return a + b; }
double half(double x) { return x / 2.0; }

struct Converter {
    std::string operator()(int n) const { return std::to_string(n); }
    int operator()(const std::string& s) const { return static_cast<int>(s.size()); }
};

struct Widget {
    int value;
    int get() const { return value; }
};

// Helper to print the deduced type name
template <typename T>
constexpr const char* type_name();
template <> constexpr const char* type_name<int>()         { return "int"; }
template <> constexpr const char* type_name<double>()      { return "double"; }
template <> constexpr const char* type_name<std::string>() { return "std::string"; }

int main()
{
    // ------------------------------------------------------------------
    // 1. Deducing return types of free functions
    // ------------------------------------------------------------------
    using AddResult  = std::invoke_result_t<decltype(add), int, int>;
    using HalfResult = std::invoke_result_t<decltype(half), double>;

    std::cout << "=== Free Functions ===" << std::endl;
    std::cout << "  add(int,int)  -> " << type_name<AddResult>() << std::endl;
    std::cout << "  half(double)  -> " << type_name<HalfResult>() << std::endl;

    // ------------------------------------------------------------------
    // 2. Overloaded function object
    // ------------------------------------------------------------------
    using ConvIntResult = std::invoke_result_t<Converter, int>;
    using ConvStrResult = std::invoke_result_t<Converter, std::string>;

    std::cout << "\n=== Overloaded Functor ===" << std::endl;
    std::cout << "  Converter(int)    -> " << type_name<ConvIntResult>() << std::endl;
    std::cout << "  Converter(string) -> " << type_name<ConvStrResult>() << std::endl;

    // ------------------------------------------------------------------
    // 3. Member function and data pointers
    // ------------------------------------------------------------------
    using GetResult = std::invoke_result_t<decltype(&Widget::get), Widget>;
    using ValResult = std::invoke_result_t<decltype(&Widget::value), Widget>;

    std::cout << "\n=== Member Pointers ===" << std::endl;
    std::cout << "  Widget::get()  -> " << type_name<GetResult>() << std::endl;
    std::cout << "  Widget::value  -> " << type_name<ValResult>() << std::endl;

    // ------------------------------------------------------------------
    // 4. Lambda return type deduction
    // ------------------------------------------------------------------
    auto square = [](int x) { return x * x; };
    using SqResult = std::invoke_result_t<decltype(square), int>;

    std::cout << "\n=== Lambda ===" << std::endl;
    std::cout << "  square(int)   -> " << type_name<SqResult>() << std::endl;

    // ------------------------------------------------------------------
    // 5. Practical: generic wrapper using invoke_result_t
    // ------------------------------------------------------------------
    auto call_and_report = [](auto fn, auto... args) {
        using R = std::invoke_result_t<decltype(fn), decltype(args)...>;
        R result = std::invoke(fn, args...);
        std::cout << "  Result = " << result << std::endl;
    };

    std::cout << "\n=== Generic Wrapper ===" << std::endl;
    call_and_report(add, 100, 200);
    call_and_report(half, 9.0);

    return 0;
}

/*
Expected output:

=== Free Functions ===
  add(int,int)  -> int
  half(double)  -> double

=== Overloaded Functor ===
  Converter(int)    -> std::string
  Converter(string) -> int

=== Member Pointers ===
  Widget::get()  -> int
  Widget::value  -> int

=== Lambda ===
  square(int)   -> int

=== Generic Wrapper ===
  Result = 300
  Result = 4.5
*/
