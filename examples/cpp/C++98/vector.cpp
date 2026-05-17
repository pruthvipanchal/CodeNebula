// CodeNebula - C++98 Example: vector
// Compile: g++ -std=c++98 -Wall -Wextra -o example vector.cpp

// std::vector is a dynamic array that manages its own memory.
// It provides random access, automatic resizing, and contiguous storage.

#include <iostream>
#include <vector>

int main() {
    // --- Construction ---
    std::vector<int> v;
    std::cout << "=== Construction ===" << std::endl;
    std::cout << "Empty vector size: " << v.size() << std::endl;
    std::cout << "Empty vector capacity: " << v.capacity() << std::endl;

    // Construct with a specific size and default value
    std::vector<int> v2(5, 42);
    std::cout << "v2 (5 elements of 42): ";
    for (std::vector<int>::iterator it = v2.begin(); it != v2.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // --- push_back and capacity growth ---
    std::cout << "\n=== push_back and capacity ===" << std::endl;
    for (int i = 1; i <= 8; ++i) {
        v.push_back(i * 10);
        std::cout << "After push_back(" << i * 10 << "): "
                  << "size=" << v.size()
                  << ", capacity=" << v.capacity() << std::endl;
    }

    // --- Element access ---
    std::cout << "\n=== Element access ===" << std::endl;
    std::cout << "v[0] = " << v[0] << std::endl;
    std::cout << "v.at(3) = " << v.at(3) << std::endl;
    std::cout << "v.front() = " << v.front() << std::endl;
    std::cout << "v.back() = " << v.back() << std::endl;

    // --- Iteration with iterators ---
    std::cout << "\n=== Forward iteration ===" << std::endl;
    std::cout << "Elements: ";
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // --- Reverse iteration ---
    std::cout << "\n=== Reverse iteration ===" << std::endl;
    std::cout << "Reversed: ";
    for (std::vector<int>::reverse_iterator rit = v.rbegin(); rit != v.rend(); ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;

    // --- Const iteration ---
    std::cout << "\n=== Const iteration ===" << std::endl;
    const std::vector<int>& cv = v;
    std::cout << "Const elements: ";
    for (std::vector<int>::const_iterator it = cv.begin(); it != cv.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // --- Modifying elements ---
    std::cout << "\n=== Modifying elements ===" << std::endl;
    v[0] = 100;
    v.at(1) = 200;
    std::cout << "After modifying v[0]=100, v.at(1)=200: ";
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // --- Insert and erase ---
    std::cout << "\n=== Insert and erase ===" << std::endl;
    v.insert(v.begin() + 2, 999);
    std::cout << "After insert 999 at position 2: ";
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    v.erase(v.begin() + 2);
    std::cout << "After erase at position 2: ";
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // --- reserve and resize ---
    std::cout << "\n=== reserve and resize ===" << std::endl;
    v.reserve(100);
    std::cout << "After reserve(100): capacity=" << v.capacity() << std::endl;

    v.resize(4);
    std::cout << "After resize(4): size=" << v.size() << ", elements: ";
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // --- clear and empty ---
    std::cout << "\n=== clear and empty ===" << std::endl;
    std::cout << "Before clear: empty=" << (v.empty() ? "true" : "false") << std::endl;
    v.clear();
    std::cout << "After clear: size=" << v.size()
              << ", empty=" << (v.empty() ? "true" : "false") << std::endl;

    // --- swap ---
    std::cout << "\n=== swap ===" << std::endl;
    std::vector<int> a(3, 1);
    std::vector<int> b(5, 9);
    std::cout << "Before swap: a.size=" << a.size() << ", b.size=" << b.size() << std::endl;
    a.swap(b);
    std::cout << "After swap:  a.size=" << a.size() << ", b.size=" << b.size() << std::endl;

    return 0;
}

/*
Expected output:
=== Construction ===
Empty vector size: 0
Empty vector capacity: 0
v2 (5 elements of 42): 42 42 42 42 42

=== push_back and capacity ===
After push_back(10): size=1, capacity=1
After push_back(20): size=2, capacity=2
After push_back(30): size=3, capacity=4
After push_back(40): size=4, capacity=4
After push_back(50): size=5, capacity=8
After push_back(60): size=6, capacity=8
After push_back(70): size=7, capacity=8
After push_back(80): size=8, capacity=8

=== Element access ===
v[0] = 10
v.at(3) = 40
v.front() = 10
v.back() = 80

=== Forward iteration ===
Elements: 10 20 30 40 50 60 70 80

=== Reverse iteration ===
Reversed: 80 70 60 50 40 30 20 10

=== Const iteration ===
Const elements: 10 20 30 40 50 60 70 80

=== Modifying elements ===
After modifying v[0]=100, v.at(1)=200: 100 200 30 40 50 60 70 80

=== Insert and erase ===
After insert 999 at position 2: 100 200 999 30 40 50 60 70 80
After erase at position 2: 100 200 30 40 50 60 70 80

=== reserve and resize ===
After reserve(100): capacity=100
After resize(4): size=4, elements: 100 200 30 40

=== clear and empty ===
Before clear: empty=false
After clear: size=0, empty=true

=== swap ===
Before swap: a.size=3, b.size=5
After swap:  a.size=5, b.size=3
*/
