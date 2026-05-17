// CodeNebula - C++17 Example: std::is_invocable
// Compile: g++ -std=c++17 -Wall -Wextra -o example is_invocable.cpp

// Demonstrates std::is_invocable and related traits for compile-time
// checking whether a callable can be invoked with given argument types.
// Includes is_invocable_r (with return type check) and is_nothrow_invocable.

#include <iostream>
#include <type_traits>
#include <string>
#include <functional>

int add(int a, int b) { return a + b; }
void greet(const std::string& name) { (void)name; }
int safe_div(int a, int b) noexcept { return b != 0 ? a / b : 0; }

struct Functor {
    double operator()(double x) const { return x * 2.0; }
};

struct Widget {
    int value;
    int get() const { return value; }
};

int main()
{
    // ------------------------------------------------------------------
    // 1. is_invocable: can we call F with these argument types?
    // ------------------------------------------------------------------
    std::cout << "=== std::is_invocable ===" << std::endl;
    std::cout << "  add(int, int)       : "
              << std::is_invocable_v<decltype(add), int, int> << std::endl;
    std::cout << "  add(int)            : "
              << std::is_invocable_v<decltype(add), int> << std::endl;
    std::cout << "  greet(string)       : "
              << std::is_invocable_v<decltype(greet), std::string> << std::endl;
    std::cout << "  Functor(double)     : "
              << std::is_invocable_v<Functor, double> << std::endl;
    std::cout << "  Functor(string)     : "
              << std::is_invocable_v<Functor, std::string> << std::endl;

    // ------------------------------------------------------------------
    // 2. is_invocable_r: can we call F and get return type R?
    // ------------------------------------------------------------------
    std::cout << "\n=== std::is_invocable_r ===" << std::endl;
    std::cout << "  add(int,int)->int   : "
              << std::is_invocable_r_v<int, decltype(add), int, int> << std::endl;
    std::cout << "  add(int,int)->double: "
              << std::is_invocable_r_v<double, decltype(add), int, int> << std::endl;
    std::cout << "  add(int,int)->string: "
              << std::is_invocable_r_v<std::string, decltype(add), int, int> << std::endl;

    // ------------------------------------------------------------------
    // 3. is_nothrow_invocable: noexcept check
    // ------------------------------------------------------------------
    std::cout << "\n=== std::is_nothrow_invocable ===" << std::endl;
    std::cout << "  safe_div(int,int)   : "
              << std::is_nothrow_invocable_v<decltype(safe_div), int, int> << std::endl;
    std::cout << "  add(int,int)        : "
              << std::is_nothrow_invocable_v<decltype(add), int, int> << std::endl;

    // ------------------------------------------------------------------
    // 4. Member function and member data pointers
    // ------------------------------------------------------------------
    std::cout << "\n=== Member Pointers ===" << std::endl;
    std::cout << "  Widget::get(Widget) : "
              << std::is_invocable_v<decltype(&Widget::get), Widget> << std::endl;
    std::cout << "  Widget::value(Widget): "
              << std::is_invocable_v<decltype(&Widget::value), Widget> << std::endl;

    // ------------------------------------------------------------------
    // 5. Practical: SFINAE-friendly template
    // ------------------------------------------------------------------
    auto try_call = [](auto&& fn, auto&&... args) {
        if constexpr (std::is_invocable_v<decltype(fn), decltype(args)...>) {
            std::cout << "  Callable -> result: " << fn(args...) << std::endl;
        } else {
            std::cout << "  Not callable with these args" << std::endl;
        }
    };

    std::cout << "\n=== Practical if-constexpr ===" << std::endl;
    try_call(add, 5, 10);
    try_call(add, "hello", "world");

    return 0;
}

/*
Expected output:

=== std::is_invocable ===
  add(int, int)       : 1
  add(int)            : 0
  greet(string)       : 1
  Functor(double)     : 1
  Functor(string)     : 0

=== std::is_invocable_r ===
  add(int,int)->int   : 1
  add(int,int)->double: 1
  add(int,int)->string: 0

=== std::is_nothrow_invocable ===
  safe_div(int,int)   : 1
  add(int,int)        : 0

=== Member Pointers ===
  Widget::get(Widget) : 1
  Widget::value(Widget): 1

=== Practical if-constexpr ===
  Callable -> result: 15
  Not callable with these args
*/
