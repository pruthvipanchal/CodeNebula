// CodeNebula - C++17 Example: Class Template Argument Deduction (CTAD)
// Compile: g++ -std=c++17 -Wall -Wextra -o example template_argument_deduction.cpp

// Demonstrates class template argument deduction (CTAD). In C++17, the compiler
// can deduce template arguments from constructor arguments, so you can write
// std::pair{1, 2.0} instead of std::pair<int, double>{1, 2.0}.

#include <iostream>
#include <vector>
#include <tuple>
#include <array>
#include <mutex>
#include <functional>
#include <string>

int main()
{
    // ------------------------------------------------------------------
    // 1. std::pair - no need for std::make_pair or explicit types
    // ------------------------------------------------------------------
    std::pair p{42, 3.14};   // deduced as std::pair<int, double>
    std::cout << "=== std::pair CTAD ===" << std::endl;
    std::cout << "  p = {" << p.first << ", " << p.second << "}" << std::endl;

    // ------------------------------------------------------------------
    // 2. std::tuple - replaces std::make_tuple
    // ------------------------------------------------------------------
    std::tuple t{1, "hello", 2.5};  // std::tuple<int, const char*, double>
    std::cout << "\n=== std::tuple CTAD ===" << std::endl;
    std::cout << "  t = {" << std::get<0>(t) << ", " << std::get<1>(t)
              << ", " << std::get<2>(t) << "}" << std::endl;

    // ------------------------------------------------------------------
    // 3. std::vector - deduced from initializer list
    // ------------------------------------------------------------------
    std::vector v{1, 2, 3, 4, 5};   // std::vector<int>
    std::cout << "\n=== std::vector CTAD ===" << std::endl;
    std::cout << "  v = {";
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << v[i];
    }
    std::cout << "}" << std::endl;

    // ------------------------------------------------------------------
    // 4. std::array - deduced element type and size
    // ------------------------------------------------------------------
    std::array a{10, 20, 30};  // std::array<int, 3>
    std::cout << "\n=== std::array CTAD ===" << std::endl;
    std::cout << "  a = {";
    for (std::size_t i = 0; i < a.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << a[i];
    }
    std::cout << "}, size = " << a.size() << std::endl;

    // ------------------------------------------------------------------
    // 5. std::lock_guard - mutex type deduced
    // ------------------------------------------------------------------
    std::mutex mtx;
    {
        std::lock_guard lock(mtx);  // std::lock_guard<std::mutex>
        std::cout << "\n=== std::lock_guard CTAD ===" << std::endl;
        std::cout << "  Lock acquired (type deduced)" << std::endl;
    }

    // ------------------------------------------------------------------
    // 6. std::function - deduced from lambda/function pointer
    // ------------------------------------------------------------------
    std::function f = [](int x) { return x * x; };
    std::cout << "\n=== std::function CTAD ===" << std::endl;
    std::cout << "  f(7) = " << f(7) << std::endl;

    // ------------------------------------------------------------------
    // 7. std::optional via CTAD
    // ------------------------------------------------------------------
    std::optional opt{std::string("C++17")};  // std::optional<std::string>
    std::cout << "\n=== std::optional CTAD ===" << std::endl;
    std::cout << "  opt = " << opt.value() << std::endl;

    return 0;
}

/*
Expected output:

=== std::pair CTAD ===
  p = {42, 3.14}

=== std::tuple CTAD ===
  t = {1, hello, 2.5}

=== std::vector CTAD ===
  v = {1, 2, 3, 4, 5}

=== std::array CTAD ===
  a = {10, 20, 30}, size = 3

=== std::lock_guard CTAD ===
  Lock acquired (type deduced)

=== std::function CTAD ===
  f(7) = 49

=== std::optional CTAD ===
  opt = C++17
*/
