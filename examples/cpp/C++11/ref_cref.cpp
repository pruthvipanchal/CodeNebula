// CodeNebula - C++11 Example: std::ref and std::cref
// Compile: g++ -std=c++11 -Wall -Wextra -o example ref_cref.cpp

// std::ref and std::cref create reference_wrapper objects that allow
// passing references where copies would normally be made. Essential
// when using std::bind or std::thread with reference arguments.

#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

void increment(int& value) {
    ++value;
}

void print_value(const int& value) {
    std::cout << "Value: " << value << std::endl;
}

struct Counter {
    int count = 0;
    void tick() { ++count; }
};

int main() {
    // Problem: std::bind copies by default
    int x = 10;
    auto bound_copy = std::bind(increment, x);       // copies x
    auto bound_ref = std::bind(increment, std::ref(x)); // references x
    bound_copy();
    std::cout << "After bound_copy(): x = " << x << std::endl;  // unchanged
    bound_ref();
    std::cout << "After bound_ref():  x = " << x << std::endl;  // incremented

    // std::cref for const references
    int y = 42;
    auto bound_print = std::bind(print_value, std::cref(y));
    y = 99;
    bound_print();  // prints updated value

    // reference_wrapper in containers (vectors can't hold references)
    int a = 1, b = 2, c = 3;
    std::vector<std::reference_wrapper<int>> refs = {
        std::ref(a), std::ref(b), std::ref(c)
    };

    // Modify through the reference wrapper
    for (auto& r : refs) {
        r.get() *= 10;
    }
    std::cout << "a=" << a << " b=" << b << " c=" << c << std::endl;

    // Sort original values through reference wrappers
    int p = 30, q = 10, r = 20;
    std::vector<std::reference_wrapper<int>> sortable = {
        std::ref(p), std::ref(q), std::ref(r)
    };
    std::sort(sortable.begin(), sortable.end());
    std::cout << "Sorted refs: ";
    for (auto& ref : sortable) std::cout << ref.get() << " ";
    std::cout << std::endl;

    // reference_wrapper with function objects
    Counter counter;
    auto ref_counter = std::ref(counter);
    ref_counter.get().tick();
    ref_counter.get().tick();
    ref_counter.get().tick();
    std::cout << "Counter: " << counter.count << std::endl;

    return 0;
}

// Expected output:
// After bound_copy(): x = 10
// After bound_ref():  x = 11
// Value: 99
// a=10 b=20 c=30
// Sorted refs: 10 20 30
// Counter: 3
