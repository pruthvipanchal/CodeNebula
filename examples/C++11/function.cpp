// CodeNebula - C++11 Example: std::function
// Compile: g++ -std=c++11 -Wall -Wextra -o example function.cpp

// std::function is a general-purpose polymorphic function wrapper.
// It can store, copy, and invoke any callable target: functions,
// lambda expressions, bind expressions, or other function objects.

#include <iostream>
#include <functional>

// A regular function
int add(int a, int b) { return a + b; }

// A functor (function object)
struct Multiplier {
    int factor;
    int operator()(int x) const { return x * factor; }
};

// A function returning a std::function
std::function<int(int)> make_adder(int n) {
    return [n](int x) { return x + n; };
}

int main() {
    // Wrap a regular function
    std::function<int(int, int)> func1 = add;
    std::cout << "add(3, 4) = " << func1(3, 4) << std::endl;

    // Wrap a lambda
    std::function<int(int, int)> func2 = [](int a, int b) { return a - b; };
    std::cout << "lambda(10, 3) = " << func2(10, 3) << std::endl;

    // Wrap a functor
    std::function<int(int)> func3 = Multiplier{5};
    std::cout << "Multiplier{5}(6) = " << func3(6) << std::endl;

    // Factory returning std::function
    auto add10 = make_adder(10);
    std::cout << "add10(25) = " << add10(25) << std::endl;

    // Check if function is empty
    std::function<void()> empty_func;
    std::cout << "empty_func is " << (empty_func ? "set" : "empty") << std::endl;

    // Reassign to a new callable
    empty_func = []() { std::cout << "Now I'm set!" << std::endl; };
    std::cout << "empty_func is " << (empty_func ? "set" : "empty") << std::endl;
    empty_func();

    // Store in a variable and swap
    std::function<int(int)> fa = [](int x) { return x * 2; };
    std::function<int(int)> fb = [](int x) { return x * 3; };
    std::cout << "Before swap: fa(5)=" << fa(5) << " fb(5)=" << fb(5) << std::endl;
    fa.swap(fb);
    std::cout << "After swap:  fa(5)=" << fa(5) << " fb(5)=" << fb(5) << std::endl;

    return 0;
}

// Expected output:
// add(3, 4) = 7
// lambda(10, 3) = 7
// Multiplier{5}(6) = 30
// add10(25) = 35
// empty_func is empty
// empty_func is set
// Now I'm set!
// Before swap: fa(5)=10 fb(5)=15
// After swap:  fa(5)=15 fb(5)=10
