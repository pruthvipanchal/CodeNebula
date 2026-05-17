// CodeNebula - C++23 Example: std::invoke_r
// Compile: g++ -std=c++23 -Wall -Wextra -o example invoke_r.cpp
// Note: Requires GCC 13+ / Clang 17+

#include <functional>
#include <iostream>
#include <string>

// std::invoke_r<R>(f, args...) invokes a callable and converts the
// result to type R. Useful for explicit return type control, including
// invoking callables that return void when you need a specific type.

int add(int a, int b) { return a + b; }

struct Multiplier {
    double factor;
    double operator()(double x) const { return x * factor; }
};

struct Widget {
    int value;
    int get_value() const { return value; }
};

// A function returning int that we want to use as returning double
int compute() { return 42; }

// Void-returning function: invoke_r<void> discards any return value
int side_effect_func() {
    std::cout << "  (side effect executed)\n";
    return 999;  // Return value will be discarded by invoke_r<void>
}

int main() {
    std::cout << "=== std::invoke_r with explicit return type ===\n\n";

    // Basic: invoke free function, convert int result to double
    double result = std::invoke_r<double>(add, 3, 4);
    std::cout << "invoke_r<double>(add, 3, 4) = " << result << "\n";
    std::cout << "Type is double? "
              << std::is_same_v<decltype(result), double> << "\n\n";

    // Invoke function object
    Multiplier mul{2.5};
    double product = std::invoke_r<double>(mul, 4.0);
    std::cout << "invoke_r<double>(Multiplier{2.5}, 4.0) = " << product << "\n\n";

    // Invoke member function
    Widget w{100};
    long val = std::invoke_r<long>(&Widget::get_value, w);
    std::cout << "invoke_r<long>(&Widget::get_value, w) = " << val << "\n\n";

    // Invoke lambda with return type conversion
    auto lambda = [](int x) { return x * x; };
    double sq = std::invoke_r<double>(lambda, 7);
    std::cout << "invoke_r<double>(square_lambda, 7) = " << sq << "\n\n";

    // invoke_r<void> discards the return value
    std::cout << "invoke_r<void> discards return value:\n";
    std::invoke_r<void>(side_effect_func);
    std::cout << "  (return value was discarded)\n\n";

    // Convert int to bool
    auto is_positive = [](int x) { return x; };
    bool positive = std::invoke_r<bool>(is_positive, 5);
    std::cout << "invoke_r<bool>(is_positive, 5) = "
              << std::boolalpha << positive << "\n";

    return 0;
}

// Expected output:
// === std::invoke_r with explicit return type ===
//
// invoke_r<double>(add, 3, 4) = 7
// Type is double? 1
//
// invoke_r<double>(Multiplier{2.5}, 4.0) = 10
//
// invoke_r<long>(&Widget::get_value, w) = 100
//
// invoke_r<double>(square_lambda, 7) = 49
//
// invoke_r<void> discards return value:
//   (side effect executed)
//   (return value was discarded)
//
// invoke_r<bool>(is_positive, 5) = true
