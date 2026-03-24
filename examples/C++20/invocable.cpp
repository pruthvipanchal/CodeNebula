// CodeNebula - C++20 Example: std::invocable Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example invocable.cpp

// std::invocable<F, Args...> checks that F can be called with Args...
// using std::invoke. It accepts functions, lambdas, function objects,
// and member function pointers.

#include <concepts>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

// Free function
int square(int x) { return x * x; }

// Function object
struct Multiplier {
    int factor;
    int operator()(int x) const { return x * factor; }
};

// Apply a callable to each element and print results
template <typename F, typename T>
    requires std::invocable<F, T>
void apply_and_print(F&& func, const std::vector<T>& items) {
    for (const auto& item : items) {
        std::cout << std::invoke(func, item) << " ";
    }
    std::cout << "\n";
}

// Apply a binary callable
template <typename F, typename T, typename U>
    requires std::invocable<F, T, U>
auto apply_binary(F&& func, T a, U b) {
    return std::invoke(std::forward<F>(func), a, b);
}

// Repeat a no-arg callable N times
template <std::invocable F>
void repeat(F&& func, int n) {
    for (int i = 0; i < n; ++i) {
        std::invoke(func);
    }
}

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};

    // Apply free function
    std::cout << "Squared: ";
    apply_and_print(square, nums);

    // Apply lambda
    std::cout << "Doubled: ";
    apply_and_print([](int x) { return x * 2; }, nums);

    // Apply function object
    std::cout << "Times 3: ";
    apply_and_print(Multiplier{3}, nums);

    // Binary callable
    auto sum = apply_binary(std::plus<>{}, 10, 20);
    std::cout << "\n10 + 20 = " << sum << "\n";

    auto product = apply_binary([](int a, int b) { return a * b; }, 6, 7);
    std::cout << "6 * 7 = " << product << "\n";

    // Repeat a void callable
    int counter = 0;
    std::cout << "\nCounting: ";
    repeat([&counter]() { std::cout << ++counter << " "; }, 5);
    std::cout << "\n";

    // Concept checks
    std::cout << "\nInvocable checks:\n";
    std::cout << "square(int): " << std::invocable<decltype(square), int> << "\n";
    std::cout << "Multiplier(int): " << std::invocable<Multiplier, int> << "\n";
    std::cout << "plus<>(int,int): " << std::invocable<std::plus<>, int, int> << "\n";
    std::cout << "square(): " << std::invocable<decltype(square)> << "\n";

    return 0;
}

// Expected output:
// Squared: 1 4 9 16 25
// Doubled: 2 4 6 8 10
// Times 3: 3 6 9 12 15
//
// 10 + 20 = 30
// 6 * 7 = 42
//
// Counting: 1 2 3 4 5
//
// Invocable checks:
// square(int): 1
// Multiplier(int): 1
// plus<>(int,int): 1
// square(): 0
