// CodeNebula - C++17 Example: Fold Expressions
// Compile: g++ -std=c++17 -Wall -Wextra -o example fold_expressions.cpp

// Demonstrates fold expressions over parameter packs. C++17 supports four forms:
//   Unary right fold: (args op ...)     -> a1 op (a2 op (a3 op a4))
//   Unary left fold:  (... op args)     -> ((a1 op a2) op a3) op a4
//   Binary right fold: (args op ... op init)
//   Binary left fold:  (init op ... op args)

#include <iostream>
#include <string>

// ------------------------------------------------------------------
// 1. Unary right fold: sum all arguments  (args + ...)
// ------------------------------------------------------------------
template <typename... Args>
auto sum(Args... args) {
    return (args + ...);  // a1 + (a2 + (a3 + a4))
}

// ------------------------------------------------------------------
// 2. Unary left fold: subtract left-to-right  (... - args)
// ------------------------------------------------------------------
template <typename... Args>
auto subtract_left(Args... args) {
    return (... - args);  // ((a1 - a2) - a3) - a4
}

// ------------------------------------------------------------------
// 3. Binary left fold with init: product with initial value
// ------------------------------------------------------------------
template <typename... Args>
auto product(Args... args) {
    return (1 * ... * args);  // ((1 * a1) * a2) * a3
}

// ------------------------------------------------------------------
// 4. Fold with comma operator: print all arguments
// ------------------------------------------------------------------
template <typename... Args>
void print_all(Args... args) {
    ((std::cout << "  " << args << std::endl), ...);
}

// ------------------------------------------------------------------
// 5. Fold with logical AND: all positive?
// ------------------------------------------------------------------
template <typename... Args>
bool all_positive(Args... args) {
    return ((args > 0) && ...);
}

// ------------------------------------------------------------------
// 6. Fold with logical OR: any negative?
// ------------------------------------------------------------------
template <typename... Args>
bool any_negative(Args... args) {
    return ((args < 0) || ...);
}

// ------------------------------------------------------------------
// 7. Binary fold for string concatenation with separator
// ------------------------------------------------------------------
template <typename... Args>
std::string join(Args... args) {
    return (std::string{} + ... + (std::string(", ") + args));
}

int main()
{
    std::cout << "=== unary right fold (sum) ===" << std::endl;
    std::cout << "  sum(1,2,3,4): " << sum(1, 2, 3, 4) << std::endl;
    std::cout << "  sum(1.5, 2.5): " << sum(1.5, 2.5) << std::endl;

    std::cout << "\n=== unary left fold (subtract) ===" << std::endl;
    std::cout << "  subtract_left(100,20,5,3): " << subtract_left(100, 20, 5, 3) << std::endl;

    std::cout << "\n=== binary left fold (product) ===" << std::endl;
    std::cout << "  product(2,3,4): " << product(2, 3, 4) << std::endl;
    std::cout << "  product(): " << product() << std::endl;  // empty pack, returns init (1)

    std::cout << "\n=== comma fold (print_all) ===" << std::endl;
    print_all(42, "hello", 3.14, 'X');

    std::cout << "\n=== logical AND fold ===" << std::endl;
    std::cout << "  all_positive(1,2,3): " << std::boolalpha << all_positive(1, 2, 3) << std::endl;
    std::cout << "  all_positive(1,-2,3): " << all_positive(1, -2, 3) << std::endl;

    std::cout << "\n=== logical OR fold ===" << std::endl;
    std::cout << "  any_negative(1,2,3): " << std::boolalpha << any_negative(1, 2, 3) << std::endl;
    std::cout << "  any_negative(1,-2,3): " << any_negative(1, -2, 3) << std::endl;

    std::cout << "\n=== string join fold ===" << std::endl;
    std::cout << "  " << join("Alice", "Bob", "Carol") << std::endl;

    return 0;
}

/*
Expected output:

=== unary right fold (sum) ===
  sum(1,2,3,4): 10
  sum(1.5, 2.5): 4

=== unary left fold (subtract) ===
  subtract_left(100,20,5,3): 72

=== binary left fold (product) ===
  product(2,3,4): 24
  product(): 1

=== comma fold (print_all) ===
  42
  hello
  3.14
  X

=== logical AND fold ===
  all_positive(1,2,3): true
  all_positive(1,-2,3): false

=== logical OR fold ===
  any_negative(1,2,3): false
  any_negative(1,-2,3): true

=== string join fold ===
  , Alice, Bob, Carol
*/
