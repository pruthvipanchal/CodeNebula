// CodeNebula - C++20 Example: Template Lambdas
// Compile: g++ -std=c++20 -Wall -Wextra -o example template_lambdas.cpp

// Demonstrates the C++20 template lambda syntax []<typename T>(T x) {}
// which gives lambdas explicit template parameters for precise type control.

#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <numeric>

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic template lambda with single type parameter
    // ------------------------------------------------------------------
    std::cout << "=== Basic Template Lambda ===" << std::endl;
    auto type_info = []<typename T>(T val) {
        std::cout << "  Value: " << val
                  << "  (size=" << sizeof(T) << ")" << std::endl;
    };
    type_info(42);
    type_info(3.14f);
    type_info(std::string("hello"));

    // ------------------------------------------------------------------
    // 2. Template lambda to enforce same-type arguments
    // ------------------------------------------------------------------
    std::cout << "\n=== Same-Type Enforcement ===" << std::endl;
    auto add_same = []<typename T>(T a, T b) -> T {
        return a + b;
    };
    std::cout << "  int: " << add_same(3, 4) << std::endl;
    std::cout << "  double: " << add_same(1.5, 2.5) << std::endl;
    std::cout << "  string: " << add_same(std::string("ab"), std::string("cd"))
              << std::endl;
    // add_same(1, 2.0);  // Error: T deduced as both int and double

    // ------------------------------------------------------------------
    // 3. Template lambda with container deduction
    // ------------------------------------------------------------------
    std::cout << "\n=== Container Template Lambda ===" << std::endl;
    auto sum_vec = []<typename T>(const std::vector<T>& v) -> T {
        return std::accumulate(v.begin(), v.end(), T{});
    };
    std::cout << "  sum(int):    " << sum_vec(std::vector<int>{1, 2, 3, 4, 5})
              << std::endl;
    std::cout << "  sum(double): " << sum_vec(std::vector<double>{0.1, 0.2, 0.3})
              << std::endl;

    // ------------------------------------------------------------------
    // 4. Template lambda with non-type template parameter
    // ------------------------------------------------------------------
    std::cout << "\n=== Non-Type Template Parameter ===" << std::endl;
    auto repeat = []<int N>(const std::string& s) {
        std::string result;
        for (int i = 0; i < N; ++i) result += s;
        return result;
    };
    std::cout << "  " << repeat.operator()<3>("Ha") << std::endl;
    std::cout << "  " << repeat.operator()<5>("*") << std::endl;

    // ------------------------------------------------------------------
    // 5. Template lambda with constexpr if
    // ------------------------------------------------------------------
    std::cout << "\n=== Template Lambda with if constexpr ===" << std::endl;
    auto describe = []<typename T>(T val) {
        if constexpr (std::is_integral_v<T>)
            std::cout << "  " << val << " is an integer" << std::endl;
        else if constexpr (std::is_floating_point_v<T>)
            std::cout << "  " << val << " is a float" << std::endl;
        else if constexpr (std::is_same_v<T, std::string>)
            std::cout << "  \"" << val << "\" is a string" << std::endl;
        else
            std::cout << "  unknown type" << std::endl;
    };
    describe(42);
    describe(2.71828);
    describe(std::string("C++20"));

    // ------------------------------------------------------------------
    // 6. Multiple template parameters
    // ------------------------------------------------------------------
    std::cout << "\n=== Multiple Template Parameters ===" << std::endl;
    auto convert = []<typename To, typename From>(From val) -> To {
        return static_cast<To>(val);
    };
    int i = convert.operator()<int>(3.7);
    double d = convert.operator()<double>(42);
    std::cout << "  3.7 -> int: " << i << std::endl;
    std::cout << "  42 -> double: " << d << std::endl;

    // ------------------------------------------------------------------
    // 7. Template lambda stored in auto variable
    // ------------------------------------------------------------------
    std::cout << "\n=== Reusable Template Lambda ===" << std::endl;
    auto max_of = []<typename T>(T a, T b) { return (a > b) ? a : b; };
    std::cout << "  max(3, 7) = " << max_of(3, 7) << std::endl;
    std::cout << "  max(9.1, 2.5) = " << max_of(9.1, 2.5) << std::endl;
    std::cout << "  max(ab, cd) = "
              << max_of(std::string("ab"), std::string("cd")) << std::endl;

    return 0;
}

/*
Expected output:

=== Basic Template Lambda ===
  Value: 42  (size=4)
  Value: 3.14  (size=4)
  Value: hello  (size=32)

=== Same-Type Enforcement ===
  int: 7
  double: 4
  string: abcd

=== Container Template Lambda ===
  sum(int):    15
  sum(double): 0.6

=== Non-Type Template Parameter ===
  HaHaHa
  *****

=== Template Lambda with if constexpr ===
  42 is an integer
  2.71828 is a float
  "C++20" is a string

=== Multiple Template Parameters ===
  3.7 -> int: 3
  42 -> double: 42

=== Reusable Template Lambda ===
  max(3, 7) = 7
  max(9.1, 2.5) = 9.1
  max(ab, cd) = cd
*/
