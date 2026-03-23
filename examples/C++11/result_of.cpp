// CodeNebula - C++11 Example: result_of
// Compile: g++ -std=c++11 -Wall -Wextra -o example result_of.cpp

// Demonstrates std::result_of to deduce the return type of a callable.
// Note: std::result_of is deprecated in C++17; use std::invoke_result instead.

#include <iostream>
#include <type_traits>
#include <functional>

int add(int a, int b) { return a + b; }
double multiply(double a, double b) { return a * b; }

struct Functor {
    std::string operator()(int n) const {
        return std::to_string(n);
    }
};

// Use result_of to deduce return type in a wrapper
template<typename F, typename Arg>
typename std::result_of<F(Arg)>::type
apply(F f, Arg a) {
    return f(a);
}

int main() {
    std::cout << "=== std::result_of ===" << std::endl;

    // Deduce return types of various callables
    using AddResult = std::result_of<decltype(add)&(int, int)>::type;
    using MulResult = std::result_of<decltype(multiply)&(double, double)>::type;
    using FuncResult = std::result_of<Functor(int)>::type;

    std::cout << "add returns int:        "
              << std::is_same<AddResult, int>::value << std::endl;
    std::cout << "multiply returns double: "
              << std::is_same<MulResult, double>::value << std::endl;
    std::cout << "Functor returns string:  "
              << std::is_same<FuncResult, std::string>::value << std::endl;

    // Lambda result type
    auto lambda = [](int x) -> double { return x * 1.5; };
    using LambdaResult = std::result_of<decltype(lambda)(int)>::type;
    std::cout << "lambda returns double:   "
              << std::is_same<LambdaResult, double>::value << std::endl;

    // Practical wrapper usage
    Functor f;
    auto result = apply(f, 42);
    std::cout << "\napply(Functor, 42) = \"" << result << "\"" << std::endl;
    std::cout << "Result is string: "
              << std::is_same<decltype(result), std::string>::value << std::endl;

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::result_of ===
// add returns int:        1
// multiply returns double: 1
// Functor returns string:  1
// lambda returns double:   1
//
// apply(Functor, 42) = "42"
// Result is string: 1
//
// All checks passed!
