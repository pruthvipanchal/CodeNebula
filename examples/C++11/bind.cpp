// CodeNebula - C++11 Example: std::bind
// Compile: g++ -std=c++11 -Wall -Wextra -o example bind.cpp

// std::bind creates a forwarding call wrapper that binds arguments
// to a callable. Placeholders (_1, _2, ...) mark positions for
// arguments supplied at call time.

#include <iostream>
#include <functional>

using namespace std::placeholders;

int subtract(int a, int b) { return a - b; }

double power(double base, int exp) {
    double result = 1.0;
    for (int i = 0; i < exp; ++i) result *= base;
    return result;
}

struct Calculator {
    int value;
    int add(int x) const { return value + x; }
    int multiply(int x) const { return value * x; }
};

int main() {
    // Bind all arguments (no placeholders)
    auto five_minus_three = std::bind(subtract, 5, 3);
    std::cout << "5 - 3 = " << five_minus_three() << std::endl;

    // Bind first argument, leave second as placeholder
    auto subtract_from_10 = std::bind(subtract, 10, _1);
    std::cout << "10 - 4 = " << subtract_from_10(4) << std::endl;

    // Reorder arguments using placeholders
    auto reversed = std::bind(subtract, _2, _1);
    std::cout << "reversed(3, 10) = 10-3 = " << reversed(3, 10) << std::endl;

    // Bind with partial application
    auto square = std::bind(power, _1, 2);
    auto cube = std::bind(power, _1, 3);
    std::cout << "square(5) = " << square(5.0) << std::endl;
    std::cout << "cube(3) = " << cube(3.0) << std::endl;

    // Bind member functions
    Calculator calc{100};
    auto add_to_calc = std::bind(&Calculator::add, &calc, _1);
    auto mul_by_calc = std::bind(&Calculator::multiply, &calc, _1);
    std::cout << "calc.add(20) = " << add_to_calc(20) << std::endl;
    std::cout << "calc.multiply(3) = " << mul_by_calc(3) << std::endl;

    // Nested bind: bind result used as argument
    auto sub5 = std::bind(subtract, _1, 5);
    std::cout << "sub5(12) = " << sub5(12) << std::endl;

    // Store bind result in std::function
    std::function<int(int)> func = std::bind(subtract, _1, 1);
    std::cout << "func(10) = " << func(10) << std::endl;

    return 0;
}

// Expected output:
// 5 - 3 = 2
// 10 - 4 = 6
// reversed(3, 10) = 10-3 = 7
// square(5) = 25
// cube(3) = 27
// calc.add(20) = 120
// calc.multiply(3) = 300
// sub5(12) = 7
// func(10) = 9
