// CodeNebula - C++98 Example: generate
// Compile: g++ -std=c++98 -Wall -Wextra -o example generate.cpp

// std::generate assigns the result of calling a generator function to each
// element in [first, last). The generator takes no arguments and returns a value.

#include <iostream>
#include <vector>
#include <algorithm>

int counter_value = 0;

int counter() {
    return ++counter_value;
}

struct Fibonacci {
    int a, b;
    Fibonacci() : a(0), b(1) {}
    int operator()() {
        int result = a;
        int next = a + b;
        a = b;
        b = next;
        return result;
    }
};

int main() {
    // Generate sequential numbers using a free function
    std::vector<int> v(6);
    counter_value = 0;
    std::generate(v.begin(), v.end(), counter);

    std::cout << "Counter:   ";
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Generate Fibonacci numbers using a functor
    std::vector<int> fib(8);
    std::generate(fib.begin(), fib.end(), Fibonacci());

    std::cout << "Fibonacci: ";
    for (std::vector<int>::iterator it = fib.begin(); it != fib.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Counter:   1 2 3 4 5 6
// Fibonacci: 0 1 1 2 3 5 8 13
