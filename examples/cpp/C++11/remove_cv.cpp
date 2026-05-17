// CodeNebula - C++11 Example: remove_cv
// Compile: g++ -std=c++11 -Wall -Wextra -o example remove_cv.cpp

// Demonstrates std::remove_cv, std::remove_const, and std::remove_volatile
// to strip const and/or volatile qualifiers from types.

#include <iostream>
#include <type_traits>

template<typename T>
void check_qualifiers(const char* name) {
    std::cout << name << ":" << std::endl;
    std::cout << "  is_const:    " << std::is_const<T>::value << std::endl;
    std::cout << "  is_volatile: " << std::is_volatile<T>::value << std::endl;
}

int main() {
    std::cout << "=== std::remove_cv / remove_const / remove_volatile ===" << std::endl;

    // remove_const strips const
    static_assert(std::is_same<std::remove_const<const int>::type, int>::value,
                  "remove_const: const int -> int");
    // remove_volatile strips volatile
    static_assert(std::is_same<std::remove_volatile<volatile int>::type, int>::value,
                  "remove_volatile: volatile int -> int");
    // remove_cv strips both
    static_assert(std::is_same<std::remove_cv<const volatile int>::type, int>::value,
                  "remove_cv: const volatile int -> int");

    check_qualifiers<int>("int");
    check_qualifiers<const int>("const int");
    check_qualifiers<volatile int>("volatile int");
    check_qualifiers<const volatile int>("const volatile int");

    std::cout << "\nAfter remove_const<const int>:       is int? "
              << std::is_same<std::remove_const<const int>::type, int>::value << std::endl;
    std::cout << "After remove_volatile<volatile int>:  is int? "
              << std::is_same<std::remove_volatile<volatile int>::type, int>::value << std::endl;
    std::cout << "After remove_cv<const volatile int>:  is int? "
              << std::is_same<std::remove_cv<const volatile int>::type, int>::value << std::endl;

    // Note: only top-level qualifiers are removed
    std::cout << "\nremove_const<const int*> is int*: "
              << std::is_same<std::remove_const<const int*>::type, int*>::value << std::endl;
    std::cout << "remove_const<int* const> is int*: "
              << std::is_same<std::remove_const<int* const>::type, int*>::value << std::endl;

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::remove_cv / remove_const / remove_volatile ===
// int:
//   is_const:    0
//   is_volatile: 0
// const int:
//   is_const:    1
//   is_volatile: 0
// volatile int:
//   is_const:    0
//   is_volatile: 1
// const volatile int:
//   is_const:    1
//   is_volatile: 1
//
// After remove_const<const int>:       is int? 1
// After remove_volatile<volatile int>:  is int? 1
// After remove_cv<const volatile int>:  is int? 1
//
// remove_const<const int*> is int*: 0
// remove_const<int* const> is int*: 1
//
// All checks passed!
