// CodeNebula - C++17 Example: std::as_const
// Compile: g++ -std=c++17 -Wall -Wextra -o example as_const.cpp

// Demonstrates std::as_const, a utility that adds a const qualifier to an
// lvalue reference. Useful for forcing const overload selection without
// writing a verbose const_cast or separate const reference variable.

#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <set>

// A class with const and non-const overloads
class Container {
    std::vector<int> data_ = {10, 20, 30};
public:
    // Non-const: returns mutable reference
    std::vector<int>& items() {
        std::cout << "  [non-const overload]" << std::endl;
        return data_;
    }

    // Const: returns const reference
    const std::vector<int>& items() const {
        std::cout << "  [const overload]" << std::endl;
        return data_;
    }
};

// Template that behaves differently based on const-ness
template <typename T>
void inspect(T& val) { std::cout << "  non-const ref" << std::endl; }

template <typename T>
void inspect(const T& val) { std::cout << "  const ref" << std::endl; (void)val; }

int main()
{
    // ------------------------------------------------------------------
    // 1. Forcing const overload selection
    // ------------------------------------------------------------------
    Container c;
    std::cout << "=== Overload Selection ===" << std::endl;
    std::cout << "  c.items():" << std::endl;
    c.items();  // Calls non-const

    std::cout << "  std::as_const(c).items():" << std::endl;
    std::as_const(c).items();  // Calls const

    // ------------------------------------------------------------------
    // 2. Range-based for without accidental mutation
    // ------------------------------------------------------------------
    std::vector<std::string> names = {"Alice", "Bob", "Charlie"};

    std::cout << "\n=== Safe Iteration ===" << std::endl;
    // Without as_const, auto& could accidentally allow mutation
    for (const auto& name : std::as_const(names)) {
        std::cout << "  " << name << std::endl;
    }

    // ------------------------------------------------------------------
    // 3. Template overload resolution
    // ------------------------------------------------------------------
    int x = 42;
    std::cout << "\n=== Template Overload ===" << std::endl;
    std::cout << "  inspect(x):               ";
    inspect(x);
    std::cout << "  inspect(std::as_const(x)):";
    inspect(std::as_const(x));

    // ------------------------------------------------------------------
    // 4. Preventing set element mutation through iterator
    // ------------------------------------------------------------------
    std::set<int> s = {1, 2, 3, 4, 5};

    std::cout << "\n=== Const Set Iteration ===" << std::endl;
    std::cout << "  Elements: ";
    for (auto it = std::as_const(s).begin(); it != std::as_const(s).end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Type verification
    // ------------------------------------------------------------------
    std::cout << "\n=== Type Properties ===" << std::endl;
    std::cout << "  x is const?           : "
              << std::is_const_v<std::remove_reference_t<decltype(x)>> << std::endl;
    std::cout << "  as_const(x) is const? : "
              << std::is_const_v<std::remove_reference_t<decltype(std::as_const(x))>>
              << std::endl;

    return 0;
}

/*
Expected output:

=== Overload Selection ===
  c.items():
  [non-const overload]
  std::as_const(c).items():
  [const overload]

=== Safe Iteration ===
  Alice
  Bob
  Charlie

=== Template Overload ===
  inspect(x):               non-const ref
  inspect(std::as_const(x)):  const ref

=== Const Set Iteration ===
  Elements: 1 2 3 4 5

=== Type Properties ===
  x is const?           : 0
  as_const(x) is const? : 1
*/
