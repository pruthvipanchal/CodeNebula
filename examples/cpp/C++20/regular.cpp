// CodeNebula - C++20 Example: std::regular Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example regular.cpp

// std::regular<T> requires semiregular plus equality_comparable. A regular
// type behaves like a built-in type: default constructible, copyable,
// movable, and equality comparable. Think of int, string, vector.

#include <concepts>
#include <iostream>
#include <string>
#include <vector>

// A well-behaved regular type
struct Fraction {
    int num, den;
    Fraction() : num(0), den(1) {}
    Fraction(int n, int d) : num(n), den(d) {}
    bool operator==(const Fraction&) const = default;
};

std::ostream& operator<<(std::ostream& os, const Fraction& f) {
    return os << f.num << "/" << f.den;
}

// A non-regular type (no operator==)
struct Opaque {
    int data;
    Opaque() : data(0) {}
};

// Container that requires regular element type
template <std::regular T>
class SimpleCache {
    std::vector<T> items_;
public:
    void store(const T& item) {
        for (const auto& i : items_)
            if (i == item) return;  // needs equality_comparable
        items_.push_back(item);     // needs copy_constructible
    }
    std::size_t size() const { return items_.size(); }
    void show() const {
        for (const auto& i : items_) std::cout << "  " << i << "\n";
    }
};

template <typename T>
void check_regular(const char* name) {
    std::cout << name << " - regular: " << std::regular<T>
              << ", semiregular: " << std::semiregular<T> << "\n";
}

int main() {
    // Use SimpleCache with regular types
    SimpleCache<int> int_cache;
    int_cache.store(10);
    int_cache.store(20);
    int_cache.store(10);  // duplicate, not added
    std::cout << "Int cache (" << int_cache.size() << " items):\n";
    int_cache.show();

    SimpleCache<std::string> str_cache;
    str_cache.store("hello");
    str_cache.store("world");
    str_cache.store("hello");  // duplicate
    std::cout << "String cache (" << str_cache.size() << " items):\n";
    str_cache.show();

    SimpleCache<Fraction> frac_cache;
    frac_cache.store({1, 2});
    frac_cache.store({3, 4});
    frac_cache.store({1, 2});  // duplicate
    std::cout << "Fraction cache (" << frac_cache.size() << " items):\n";
    frac_cache.show();

    // Concept checks
    std::cout << "Regularity checks:\n";
    check_regular<int>("int");
    check_regular<std::string>("string");
    check_regular<Fraction>("Fraction");
    check_regular<std::vector<int>>("vector<int>");
    check_regular<Opaque>("Opaque");

    return 0;
}

// Expected output:
// Int cache (2 items):
//   10
//   20
// String cache (2 items):
//   hello
//   world
// Fraction cache (2 items):
//   1/2
//   3/4
// Regularity checks:
// int - regular: 1, semiregular: 1
// string - regular: 1, semiregular: 1
// Fraction - regular: 1, semiregular: 1
// vector<int> - regular: 1, semiregular: 1
// Opaque - regular: 0, semiregular: 1
