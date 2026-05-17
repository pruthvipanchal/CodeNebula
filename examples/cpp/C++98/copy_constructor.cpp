// CodeNebula - C++98 Example: Copy Constructor
// Compile: g++ -std=c++98 -Wall -Wextra -o example copy_constructor.cpp
//
// This example demonstrates:
// - Default (shallow) copy vs custom (deep) copy constructors
// - Why deep copy is essential when a class manages heap memory
// - How the copy constructor is invoked (direct init, pass-by-value, return)

#include <iostream>
#include <cstring>

// ============================================================
// ShallowArray - uses the compiler-generated copy constructor
// (dangerous when the class owns heap memory)
// ============================================================
class ShallowArray {
public:
    int* data;
    int  size;

    ShallowArray(int n) : data(new int[n]), size(n) {
        for (int i = 0; i < size; ++i) {
            data[i] = i * 10;
        }
        std::cout << "  ShallowArray constructed, data @ " << data << std::endl;
    }

    // No custom copy constructor -- compiler generates a member-wise
    // (shallow) copy.  Both objects will point to the SAME memory!

    ~ShallowArray() {
        std::cout << "  ShallowArray destructor, freeing data @ " << data << std::endl;
        delete[] data;
    }

    void print() const {
        std::cout << "  [";
        for (int i = 0; i < size; ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << data[i];
        }
        std::cout << "]" << std::endl;
    }
};

// ============================================================
// DeepArray - provides a proper deep-copying copy constructor
// ============================================================
class DeepArray {
private:
    int* data;
    int  size;

public:
    // Regular constructor
    DeepArray(int n) : data(new int[n]), size(n) {
        for (int i = 0; i < size; ++i) {
            data[i] = i * 10;
        }
        std::cout << "  DeepArray constructed, data @ " << data << std::endl;
    }

    // ---- Custom copy constructor (deep copy) ----
    DeepArray(const DeepArray& other) : data(new int[other.size]), size(other.size) {
        // Allocate fresh memory and copy element-by-element
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        std::cout << "  DeepArray COPY constructed, new data @ " << data
                  << " (source was @ " << other.data << ")" << std::endl;
    }

    ~DeepArray() {
        std::cout << "  DeepArray destructor, freeing data @ " << data << std::endl;
        delete[] data;
    }

    void set(int index, int value) {
        if (index >= 0 && index < size) {
            data[index] = value;
        }
    }

    void print() const {
        std::cout << "  [";
        for (int i = 0; i < size; ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << data[i];
        }
        std::cout << "]" << std::endl;
    }
};

// Helper: receives a DeepArray by value (triggers copy constructor)
void passByValue(DeepArray arr) {
    std::cout << "  Inside passByValue, array contains:";
    arr.print();
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "1. SHALLOW COPY PROBLEM (dangerous!)" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Creating original ShallowArray of size 3:" << std::endl;

    // We intentionally limit scope so we can see the double-free issue
    // described in comments, but avoid actual undefined behaviour in
    // this demo by only constructing ONE ShallowArray.
    {
        ShallowArray original(3);
        original.print();
        std::cout << "\n  NOTE: If we copied 'original' with the default copy" << std::endl;
        std::cout << "  constructor, BOTH objects would share the same pointer." << std::endl;
        std::cout << "  When they destruct, the memory is freed TWICE -> undefined behaviour!" << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "2. DEEP COPY SOLUTION" << std::endl;
    std::cout << "========================================" << std::endl;

    std::cout << "\n-- Creating original DeepArray of size 4 --" << std::endl;
    DeepArray original(4);
    original.print();

    std::cout << "\n-- Copy-constructing 'copy' from 'original' --" << std::endl;
    DeepArray copy(original);           // invokes copy constructor
    copy.print();

    std::cout << "\n-- Modifying copy (setting index 0 to 999) --" << std::endl;
    copy.set(0, 999);

    std::cout << "  original: ";
    original.print();
    std::cout << "  copy:     ";
    copy.print();
    std::cout << "  (original is unchanged -- deep copy works!)" << std::endl;

    std::cout << "\n========================================" << std::endl;
    std::cout << "3. COPY CONSTRUCTOR VIA PASS-BY-VALUE" << std::endl;
    std::cout << "========================================" << std::endl;
    passByValue(original);

    std::cout << "\n========================================" << std::endl;
    std::cout << "4. DESTRUCTORS RUN (reverse order)" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}

// Expected output (addresses will vary):
// ========================================
// 1. SHALLOW COPY PROBLEM (dangerous!)
// ========================================
// Creating original ShallowArray of size 3:
//   ShallowArray constructed, data @ 0x...
//   [0, 10, 20]
//
//   NOTE: If we copied 'original' with the default copy
//   constructor, BOTH objects would share the same pointer.
//   When they destruct, the memory is freed TWICE -> undefined behaviour!
//   ShallowArray destructor, freeing data @ 0x...
//
// ========================================
// 2. DEEP COPY SOLUTION
// ========================================
//
// -- Creating original DeepArray of size 4 --
//   DeepArray constructed, data @ 0x...
//   [0, 10, 20, 30]
//
// -- Copy-constructing 'copy' from 'original' --
//   DeepArray COPY constructed, new data @ 0x... (source was @ 0x...)
//   [0, 10, 20, 30]
//
// -- Modifying copy (setting index 0 to 999) --
//   original:   [0, 10, 20, 30]
//   copy:       [999, 10, 20, 30]
//   (original is unchanged -- deep copy works!)
//
// ========================================
// 3. COPY CONSTRUCTOR VIA PASS-BY-VALUE
// ========================================
//   DeepArray COPY constructed, new data @ 0x... (source was @ 0x...)
//   Inside passByValue, array contains:  [0, 10, 20, 30]
//   DeepArray destructor, freeing data @ 0x...
//
// ========================================
// 4. DESTRUCTORS RUN (reverse order)
// ========================================
//   DeepArray destructor, freeing data @ 0x...
//   DeepArray destructor, freeing data @ 0x...
