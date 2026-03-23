// CodeNebula - C++11 Example: Trailing Return Types
// Compile: g++ -std=c++11 -Wall -Wextra -o example trailing_return_types.cpp
//
// This example demonstrates:
// - The auto f() -> ReturnType syntax introduced in C++11
// - Trailing return types with decltype for deduced return types
// - Use cases where trailing return types simplify template code
// - Combining trailing return types with lambdas

#include <iostream>
#include <string>
#include <vector>

// ============================================================
// 1. Basic trailing return type syntax
// ============================================================
auto add(int a, int b) -> int {
    return a + b;
}

auto greet(const std::string& name) -> std::string {
    return "Hello, " + name + "!";
}

// ============================================================
// 2. Trailing return type with decltype (deduced return)
// ============================================================
template <typename T, typename U>
auto multiply(T a, U b) -> decltype(a * b) {
    return a * b;
}

// Without trailing return type, you cannot refer to parameters
// in the return type position. This solves that problem.

// ============================================================
// 3. Trailing return type depending on class member
// ============================================================
class Container {
    std::vector<double> data_;
public:
    Container(std::initializer_list<double> vals) : data_(vals) {}

    auto size() const -> std::vector<double>::size_type {
        return data_.size();
    }

    auto front() const -> const double& {
        return data_.front();
    }

    auto begin() -> std::vector<double>::iterator { return data_.begin(); }
    auto end() -> std::vector<double>::iterator { return data_.end(); }
};

// ============================================================
// 4. Function pointer with trailing return type
// ============================================================
auto getOperation(char op) -> int(*)(int, int) {
    switch (op) {
        case '+': return [](int a, int b) -> int { return a + b; };
        case '-': return [](int a, int b) -> int { return a - b; };
        default:  return [](int a, int b) -> int { return a * b; };
    }
}

int main() {
    std::cout << "=== Trailing Return Types ===" << std::endl;

    // Basic usage
    std::cout << "add(3, 4) = " << add(3, 4) << std::endl;
    std::cout << "greet(\"C++11\") = " << greet("C++11") << std::endl;

    // Template with decltype
    std::cout << "multiply(3, 4.5) = " << multiply(3, 4.5) << std::endl;
    std::cout << "multiply(2.0f, 3) = " << multiply(2.0f, 3) << std::endl;

    // Class members
    Container c{1.1, 2.2, 3.3};
    std::cout << "Container size: " << c.size() << std::endl;
    std::cout << "Container front: " << c.front() << std::endl;

    // Function pointer
    auto op = getOperation('+');
    std::cout << "getOperation('+')(10, 5) = " << op(10, 5) << std::endl;
    op = getOperation('-');
    std::cout << "getOperation('-')(10, 5) = " << op(10, 5) << std::endl;

    // Lambda with trailing return type
    auto divide = [](double a, double b) -> double {
        return (b != 0.0) ? a / b : 0.0;
    };
    std::cout << "divide(10.0, 3.0) = " << divide(10.0, 3.0) << std::endl;

    return 0;
}

// Expected output:
// === Trailing Return Types ===
// add(3, 4) = 7
// greet("C++11") = Hello, C++11!
// multiply(3, 4.5) = 13.5
// multiply(2.0f, 3) = 6
// Container size: 3
// Container front: 1.1
// getOperation('+')(10, 5) = 15
// getOperation('-')(10, 5) = 5
// divide(10.0, 3.0) = 3.33333
