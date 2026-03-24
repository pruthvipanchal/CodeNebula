// CodeNebula - C++20 Example: Lambda Enhancements
// Compile: g++ -std=c++20 -Wall -Wextra -o example lambda_enhancements.cpp

// Demonstrates C++20 lambda improvements: template parameters, default
// constructible stateless lambdas, lambdas in unevaluated contexts,
// pack expansion captures, and implicit this capture deprecation.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <type_traits>

int main()
{
    // ------------------------------------------------------------------
    // 1. Template lambdas: []<typename T>(T x)
    // ------------------------------------------------------------------
    std::cout << "=== Template Lambdas ===" << std::endl;
    auto typed_print = []<typename T>(const T& val) {
        if constexpr (std::is_integral_v<T>)
            std::cout << "  Integer: " << val << std::endl;
        else if constexpr (std::is_floating_point_v<T>)
            std::cout << "  Float: " << val << std::endl;
        else
            std::cout << "  Other: " << val << std::endl;
    };
    typed_print(42);
    typed_print(3.14);
    typed_print(std::string("hello"));

    // ------------------------------------------------------------------
    // 2. Template lambda with explicit type
    // ------------------------------------------------------------------
    std::cout << "\n=== Template Lambda with Vector ===" << std::endl;
    auto print_vec = []<typename T>(const std::vector<T>& v) {
        std::cout << "  [";
        for (std::size_t i = 0; i < v.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << v[i];
        }
        std::cout << "]" << std::endl;
    };
    print_vec(std::vector<int>{1, 2, 3});
    print_vec(std::vector<std::string>{"a", "b", "c"});

    // ------------------------------------------------------------------
    // 3. Stateless lambdas are default constructible
    // ------------------------------------------------------------------
    std::cout << "\n=== Default Constructible Lambdas ===" << std::endl;
    auto cmp = [](int a, int b) { return a > b; };
    using CmpType = decltype(cmp);

    // Can default-construct the same lambda type
    CmpType cmp2{};
    std::vector<int> nums = {5, 2, 8, 1, 9};
    std::sort(nums.begin(), nums.end(), cmp2);
    std::cout << "  Sorted desc:";
    for (int n : nums) std::cout << " " << n;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Lambda in unevaluated contexts (decltype, sizeof)
    // ------------------------------------------------------------------
    std::cout << "\n=== Lambda in Unevaluated Context ===" << std::endl;
    using AddType = decltype([](int a, int b) { return a + b; });
    AddType adder;  // Default construct from unevaluated lambda type
    std::cout << "  adder(3, 4) = " << adder(3, 4) << std::endl;

    // ------------------------------------------------------------------
    // 5. Pack expansion in lambda init-captures
    // ------------------------------------------------------------------
    std::cout << "\n=== Pack Expansion Capture ===" << std::endl;
    auto make_tuple_printer = [](auto... args) {
        return [... captured = args]() {
            ((std::cout << "  " << captured << std::endl), ...);
        };
    };
    auto printer = make_tuple_printer(1, 2.5, "three");
    printer();

    // ------------------------------------------------------------------
    // 6. Lambdas with constexpr and consteval
    // ------------------------------------------------------------------
    std::cout << "\n=== Constexpr Lambda ===" << std::endl;
    constexpr auto square = [](int x) { return x * x; };
    constexpr int result = square(7);
    std::cout << "  square(7) = " << result << std::endl;

    static_assert(square(5) == 25, "compile-time check");
    std::cout << "  static_assert(square(5) == 25) passed" << std::endl;

    // ------------------------------------------------------------------
    // 7. Lambda with explicit return type and template
    // ------------------------------------------------------------------
    std::cout << "\n=== Template Lambda with Explicit Return ===" << std::endl;
    auto safe_div = []<typename T>(T a, T b) -> T {
        return (b != T{}) ? a / b : T{};
    };
    std::cout << "  10 / 3 = " << safe_div(10, 3) << std::endl;
    std::cout << "  10.0 / 3.0 = " << safe_div(10.0, 3.0) << std::endl;
    std::cout << "  5 / 0 = " << safe_div(5, 0) << std::endl;

    return 0;
}

/*
Expected output:

=== Template Lambdas ===
  Integer: 42
  Float: 3.14
  Other: hello

=== Template Lambda with Vector ===
  [1, 2, 3]
  [a, b, c]

=== Default Constructible Lambdas ===
  Sorted desc: 9 8 5 2 1

=== Lambda in Unevaluated Context ===
  adder(3, 4) = 7

=== Pack Expansion Capture ===
  1
  2.5
  three

=== Constexpr Lambda ===
  square(7) = 49
  static_assert(square(5) == 25) passed

=== Template Lambda with Explicit Return ===
  10 / 3 = 3
  10.0 / 3.0 = 3.33333
  5 / 0 = 0
*/
