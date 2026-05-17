// CodeNebula - C++98 Example: generate_n
// Compile: g++ -std=c++98 -Wall -Wextra -o example generate_n.cpp

// std::generate_n assigns the result of calling a generator to the first N
// elements starting from an iterator.

#include <iostream>
#include <vector>
#include <algorithm>

struct PowersOfTwo {
    int current;
    PowersOfTwo() : current(1) {}
    int operator()() {
        int result = current;
        current *= 2;
        return result;
    }
};

struct Countdown {
    int n;
    Countdown(int start) : n(start) {}
    int operator()() { return n--; }
};

int main() {
    // Generate 8 powers of two
    std::vector<int> powers(8, 0);
    std::generate_n(powers.begin(), 8, PowersOfTwo());

    std::cout << "Powers of 2: ";
    for (std::vector<int>::iterator it = powers.begin(); it != powers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Generate a countdown into part of a vector
    std::vector<int> v(10, 0);
    std::generate_n(v.begin() + 2, 5, Countdown(5));

    std::cout << "Countdown:   ";
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Generate zero elements (no-op)
    std::generate_n(v.begin(), 0, PowersOfTwo());
    std::cout << "After no-op: ";
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Powers of 2: 1 2 4 8 16 32 64 128
// Countdown:   0 0 5 4 3 2 1 0 0 0
// After no-op: 0 0 5 4 3 2 1 0 0 0
