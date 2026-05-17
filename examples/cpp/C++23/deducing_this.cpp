// CodeNebula - C++23 Example: Deducing This
// Compile: g++ -std=c++23 -Wall -Wextra -o example deducing_this.cpp
// Note: Requires GCC 14+ / Clang 18+ / MSVC 19.37+

// C++23 allows an explicit object parameter using "this auto& self",
// replacing CRTP patterns and simplifying overload sets for const/non-const.

#include <iostream>
#include <string>

struct TextBox {
    std::string text = "Hello, C++23!";

    // Single function replaces const and non-const overloads
    // 'self' deduces to TextBox& or const TextBox& based on call context
    auto&& get_text(this auto&& self) {
        std::cout << "  (called on "
                  << (std::is_const_v<std::remove_reference_t<decltype(self)>>
                      ? "const" : "mutable")
                  << " object)" << std::endl;
        return self.text;
    }

    // Recursive lambda-like pattern with explicit this
    void print_chars(this const TextBox& self) {
        std::cout << "Characters: ";
        for (char c : self.text) std::cout << c << ' ';
        std::cout << std::endl;
    }
};

// CRTP replacement: no template base class needed
struct Counter {
    int value = 0;

    // Chaining returns the derived type automatically
    auto& increment(this auto& self) {
        ++self.value;
        return self;
    }
};

struct NamedCounter : Counter {
    std::string name = "MyCounter";
};

int main() {
    std::cout << "=== Deducing This ===" << std::endl;

    TextBox box;
    std::cout << "Mutable access:" << std::endl;
    std::cout << "  text = " << box.get_text() << std::endl;

    const TextBox cbox;
    std::cout << "Const access:" << std::endl;
    std::cout << "  text = " << cbox.get_text() << std::endl;

    std::cout << "\n=== Recursive-style member ===" << std::endl;
    box.print_chars();

    std::cout << "\n=== CRTP Replacement ===" << std::endl;
    NamedCounter nc;
    nc.increment().increment().increment();
    std::cout << "NamedCounter '" << nc.name << "' value: " << nc.value << std::endl;

    return 0;
}

/*
Expected output:
=== Deducing This ===
Mutable access:
  (called on mutable object)
  text = Hello, C++23!
Const access:
  (called on const object)
  text = Hello, C++23!

=== Recursive-style member ===
Characters: H e l l o ,   C + + 2 3 !

=== CRTP Replacement ===
NamedCounter 'MyCounter' value: 3
*/
