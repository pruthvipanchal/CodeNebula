// CodeNebula - C++20 Example: Abbreviated Function Templates
// Compile: g++ -std=c++20 -Wall -Wextra -o example abbreviated_function_templates.cpp

// Demonstrates the void f(auto x) shorthand for function templates,
// constrained auto parameters, and multiple auto parameters.

#include <iostream>
#include <concepts>
#include <string>
#include <vector>

// ------------------------------------------------------------------
// 1. Basic abbreviated function template: auto parameter
// ------------------------------------------------------------------
void print_value(auto val) {
    std::cout << "  " << val << std::endl;
}

// ------------------------------------------------------------------
// 2. Multiple auto parameters (each independently deduced)
// ------------------------------------------------------------------
void print_pair(auto first, auto second) {
    std::cout << "  (" << first << ", " << second << ")" << std::endl;
}

// ------------------------------------------------------------------
// 3. auto return type with auto parameter
// ------------------------------------------------------------------
auto triple(auto x) {
    return x + x + x;
}

// ------------------------------------------------------------------
// 4. Constrained auto - concept applied to auto
// ------------------------------------------------------------------
void add_and_print(std::integral auto a, std::integral auto b) {
    std::cout << "  " << a << " + " << b << " = " << (a + b) << std::endl;
}

double half(std::floating_point auto x) {
    return x / 2.0;
}

// ------------------------------------------------------------------
// 5. Abbreviated template with container-like auto
// ------------------------------------------------------------------
void print_size(const auto& container) {
    std::cout << "  Size: " << container.size() << ", elements:";
    for (const auto& e : container)
        std::cout << " " << e;
    std::cout << std::endl;
}

// ------------------------------------------------------------------
// 6. Mixing abbreviated and explicit template parameters
// ------------------------------------------------------------------
template <typename Result>
Result convert_and_add(auto a, auto b) {
    return static_cast<Result>(a) + static_cast<Result>(b);
}

// ------------------------------------------------------------------
// 7. Abbreviated with lambda comparison
// ------------------------------------------------------------------
void sort_and_print(auto& vec, auto comparator) {
    std::sort(vec.begin(), vec.end(), comparator);
    std::cout << "  Sorted:";
    for (const auto& e : vec)
        std::cout << " " << e;
    std::cout << std::endl;
}

int main()
{
    std::cout << "=== Basic auto Parameter ===" << std::endl;
    print_value(42);
    print_value(3.14);
    print_value(std::string("hello"));

    std::cout << "\n=== Multiple auto Parameters ===" << std::endl;
    print_pair(1, "one");
    print_pair(3.14, 42);
    print_pair(std::string("key"), 100);

    std::cout << "\n=== auto Return + auto Param ===" << std::endl;
    std::cout << "  triple(5) = " << triple(5) << std::endl;
    std::cout << "  triple(1.5) = " << triple(1.5) << std::endl;
    std::cout << "  triple(\"ab\") = " << triple(std::string("ab")) << std::endl;

    std::cout << "\n=== Constrained auto ===" << std::endl;
    add_and_print(10, 20);
    add_and_print(short(3), long(7));
    std::cout << "  half(9.0) = " << half(9.0) << std::endl;
    std::cout << "  half(5.0f) = " << half(5.0f) << std::endl;

    std::cout << "\n=== Container auto ===" << std::endl;
    print_size(std::vector<int>{1, 2, 3, 4, 5});
    print_size(std::string("C++20"));

    std::cout << "\n=== Mixed Template + auto ===" << std::endl;
    std::cout << "  int result: " << convert_and_add<int>(3.7, 2.1) << std::endl;
    std::cout << "  double result: " << convert_and_add<double>(3, 4) << std::endl;

    std::cout << "\n=== auto Comparator ===" << std::endl;
    std::vector<int> nums = {5, 3, 8, 1, 9};
    sort_and_print(nums, [](int a, int b) { return a > b; });

    return 0;
}

/*
Expected output:

=== Basic auto Parameter ===
  42
  3.14
  hello

=== Multiple auto Parameters ===
  (1, one)
  (3.14, 42)
  (key, 100)

=== auto Return + auto Param ===
  triple(5) = 15
  triple(1.5) = 4.5
  triple("ab") = ababab

=== Constrained auto ===
  10 + 20 = 30
  3 + 7 = 10
  half(9.0) = 4.5
  half(5.0f) = 2.5

=== Container auto ===
  Size: 5, elements: 1 2 3 4 5
  Size: 5, elements: C + + 2 0

=== Mixed Template + auto ===
  int result: 5
  double result: 7

=== auto Comparator ===
  Sorted: 9 8 5 3 1
*/
