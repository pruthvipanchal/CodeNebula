// CodeNebula - C++20 Example: Constraints and Requires
// Compile: g++ -std=c++20 -Wall -Wextra -o example constraints_requires.cpp

// Demonstrates requires clauses and requires expressions: simple requirements,
// type requirements, compound requirements, and nested requirements.

#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <concepts>

// ------------------------------------------------------------------
// 1. Simple requires clause on a function template
// ------------------------------------------------------------------
template <typename T>
    requires std::integral<T>
T gcd(T a, T b) {
    while (b != 0) {
        T temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// ------------------------------------------------------------------
// 2. Requires expression - ad-hoc constraint
// ------------------------------------------------------------------
template <typename T>
    requires requires(T a, T b) {
        { a + b } -> std::convertible_to<T>;
        { a * b } -> std::convertible_to<T>;
    }
T multiply_and_add(T a, T b, T c) {
    return a * b + c;
}

// ------------------------------------------------------------------
// 3. Requires expression with type requirements
// ------------------------------------------------------------------
template <typename Container>
    requires requires(Container c) {
        typename Container::value_type;
        typename Container::iterator;
        { c.size() } -> std::convertible_to<std::size_t>;
        { c.begin() } -> std::same_as<typename Container::iterator>;
    }
void print_container(const Container& c) {
    std::cout << "  [";
    bool first = true;
    for (const auto& elem : c) {
        if (!first) std::cout << ", ";
        std::cout << elem;
        first = false;
    }
    std::cout << "] (size=" << c.size() << ")" << std::endl;
}

// ------------------------------------------------------------------
// 4. Nested requires - constraint within a constraint
// ------------------------------------------------------------------
template <typename T>
    requires requires(T val) {
        requires std::is_arithmetic_v<T>;
        requires sizeof(T) >= 4;
    }
T safe_divide(T a, T b) {
    if (b == T{}) return T{};
    return a / b;
}

// ------------------------------------------------------------------
// 5. Trailing requires clause on member function
// ------------------------------------------------------------------
template <typename T>
struct Wrapper {
    T value;

    void print() const requires requires(std::ostream& os, T v) {
        os << v;
    } {
        std::cout << "  Wrapper(" << value << ")" << std::endl;
    }

    T doubled() const requires std::integral<T> || std::floating_point<T> {
        return value + value;
    }
};

int main()
{
    std::cout << "=== Requires Clause (gcd) ===" << std::endl;
    std::cout << "  gcd(12, 8) = " << gcd(12, 8) << std::endl;
    std::cout << "  gcd(100, 75) = " << gcd(100, 75) << std::endl;

    std::cout << "\n=== Requires Expression (multiply_and_add) ===" << std::endl;
    std::cout << "  3*4+5 = " << multiply_and_add(3, 4, 5) << std::endl;
    std::cout << "  1.5*2.0+0.5 = " << multiply_and_add(1.5, 2.0, 0.5) << std::endl;

    std::cout << "\n=== Type Requirements (print_container) ===" << std::endl;
    print_container(std::vector<int>{10, 20, 30});
    print_container(std::vector<std::string>{"a", "b", "c"});

    std::cout << "\n=== Nested Requires (safe_divide) ===" << std::endl;
    std::cout << "  10 / 3 = " << safe_divide(10, 3) << std::endl;
    std::cout << "  7.5 / 2.5 = " << safe_divide(7.5, 2.5) << std::endl;
    std::cout << "  5 / 0 = " << safe_divide(5, 0) << std::endl;

    std::cout << "\n=== Trailing Requires (Wrapper) ===" << std::endl;
    Wrapper<int> wi{42};
    wi.print();
    std::cout << "  Doubled: " << wi.doubled() << std::endl;

    Wrapper<std::string> ws{"hello"};
    ws.print();

    return 0;
}

/*
Expected output:

=== Requires Clause (gcd) ===
  gcd(12, 8) = 4
  gcd(100, 75) = 25

=== Requires Expression (multiply_and_add) ===
  3*4+5 = 17
  1.5*2.0+0.5 = 3.5

=== Type Requirements (print_container) ===
  [10, 20, 30] (size=3)
  [a, b, c] (size=3)

=== Nested Requires (safe_divide) ===
  10 / 3 = 3
  7.5 / 2.5 = 3
  5 / 0 = 0

=== Trailing Requires (Wrapper) ===
  Wrapper(42)
  Doubled: 84
  Wrapper(hello)
*/
