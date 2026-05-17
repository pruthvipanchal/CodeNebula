// CodeNebula - C++98 Example: std::bad_alloc
// Compile: g++ -std=c++98 -Wall -Wextra -o example bad_alloc.cpp

#include <iostream>
#include <new>
#include <cstddef>

int main() {
    // Attempt to allocate an enormous amount of memory
    try {
        std::cout << "Attempting huge allocation..." << std::endl;
        // Request an absurdly large amount to trigger bad_alloc
        std::size_t huge = static_cast<std::size_t>(-1) / 2;
        int* p = new int[huge];
        // If it somehow succeeds (unlikely), clean up
        delete[] p;
        std::cout << "Allocation succeeded (unexpected)" << std::endl;
    } catch (const std::bad_alloc& e) {
        std::cout << "bad_alloc caught: " << e.what() << std::endl;
    }

    // nothrow version returns NULL instead of throwing
    int* q = new(std::nothrow) int[1000000000UL];
    if (q == NULL) {
        std::cout << "nothrow allocation returned NULL" << std::endl;
    } else {
        std::cout << "nothrow allocation succeeded" << std::endl;
        delete[] q;
    }

    // Normal allocation still works after catching bad_alloc
    try {
        int* small = new int[10];
        small[0] = 42;
        std::cout << "Small allocation works: " << small[0] << std::endl;
        delete[] small;
    } catch (const std::bad_alloc& e) {
        std::cout << "Unexpected: " << e.what() << std::endl;
    }

    return 0;
}

// Expected output (may vary by platform):
// Attempting huge allocation...
// bad_alloc caught: std::bad_alloc
// nothrow allocation returned NULL
// Small allocation works: 42
