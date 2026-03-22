// CodeNebula - C++98 Example: Function Templates
// Compile: g++ -std=c++98 -Wall -Wextra -o example function_templates.cpp

// Function templates allow writing a single function definition that works
// with many types. The compiler generates type-specific code at compile time.
// This example shows template max, swap, print_array, and template specialization.

#include <iostream>
#include <string>
#include <cstring>

// ------------------------------------------------------------------
// Basic function template: myMax
// Works with any type that supports operator<
// ------------------------------------------------------------------
template <typename T>
T myMax(T a, T b) {
    return (a > b) ? a : b;
}

// ------------------------------------------------------------------
// Function template: mySwap
// Swaps two values of the same type using a temporary
// ------------------------------------------------------------------
template <typename T>
void mySwap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// ------------------------------------------------------------------
// Function template with a non-type parameter: printArray
// Prints the contents of an array of known size
// ------------------------------------------------------------------
template <typename T>
void printArray(const T arr[], int size) {
    std::cout << "[ ";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i];
        if (i < size - 1) {
            std::cout << ", ";
        }
    }
    std::cout << " ]" << std::endl;
}

// ------------------------------------------------------------------
// Template with two different type parameters
// Compares values of different types (both must support comparison)
// ------------------------------------------------------------------
template <typename T, typename U>
bool isEqual(T a, U b) {
    return a == b;
}

// ------------------------------------------------------------------
// Explicit (full) template specialization for const char*
// The generic myMax does pointer comparison; we want string comparison.
// ------------------------------------------------------------------
template <>
const char* myMax<const char*>(const char* a, const char* b) {
    // Compare the actual string contents, not addresses
    return (std::strcmp(a, b) > 0) ? a : b;
}

// ------------------------------------------------------------------
// Function template: clamp a value between lo and hi
// ------------------------------------------------------------------
template <typename T>
T clamp(T value, T lo, T hi) {
    if (value < lo) return lo;
    if (value > hi) return hi;
    return value;
}

int main() {
    std::cout << "=== C++98 Function Templates ===" << std::endl;

    // --- myMax with different types ---
    std::cout << "\n--- myMax ---" << std::endl;
    std::cout << "myMax(3, 7)       = " << myMax(3, 7) << std::endl;
    // Expected: 7
    std::cout << "myMax(3.14, 2.72) = " << myMax(3.14, 2.72) << std::endl;
    // Expected: 3.14
    std::cout << "myMax('a', 'z')   = " << myMax('a', 'z') << std::endl;
    // Expected: z

    // Using the specialization for C-strings
    const char* s1 = "apple";
    const char* s2 = "banana";
    std::cout << "myMax(\"apple\",\"banana\") = "
              << myMax(s1, s2) << std::endl;
    // Expected: banana (lexicographic)

    // Explicit type specification
    std::cout << "myMax<double>(3, 7.5) = " << myMax<double>(3, 7.5) << std::endl;
    // Expected: 7.5

    // --- mySwap ---
    std::cout << "\n--- mySwap ---" << std::endl;
    int x = 10, y = 20;
    std::cout << "Before swap: x=" << x << ", y=" << y << std::endl;
    mySwap(x, y);
    std::cout << "After swap:  x=" << x << ", y=" << y << std::endl;
    // Expected: x=20, y=10

    double p = 1.1, q = 9.9;
    std::cout << "Before swap: p=" << p << ", q=" << q << std::endl;
    mySwap(p, q);
    std::cout << "After swap:  p=" << p << ", q=" << q << std::endl;
    // Expected: p=9.9, q=1.1

    std::string sa = "hello", sb = "world";
    std::cout << "Before swap: sa=" << sa << ", sb=" << sb << std::endl;
    mySwap(sa, sb);
    std::cout << "After swap:  sa=" << sa << ", sb=" << sb << std::endl;
    // Expected: sa=world, sb=hello

    // --- printArray ---
    std::cout << "\n--- printArray ---" << std::endl;
    int ints[] = {10, 20, 30, 40, 50};
    std::cout << "int array:    ";
    printArray(ints, 5);
    // Expected: [ 10, 20, 30, 40, 50 ]

    double dbls[] = {1.1, 2.2, 3.3};
    std::cout << "double array: ";
    printArray(dbls, 3);
    // Expected: [ 1.1, 2.2, 3.3 ]

    // --- isEqual with two types ---
    std::cout << "\n--- isEqual (two type params) ---" << std::endl;
    std::cout << "isEqual(5, 5.0)  = " << (isEqual(5, 5.0) ? "true" : "false") << std::endl;
    // Expected: true
    std::cout << "isEqual(5, 5.1)  = " << (isEqual(5, 5.1) ? "true" : "false") << std::endl;
    // Expected: false

    // --- clamp ---
    std::cout << "\n--- clamp ---" << std::endl;
    std::cout << "clamp(15, 0, 10)   = " << clamp(15, 0, 10) << std::endl;
    // Expected: 10
    std::cout << "clamp(-5, 0, 10)   = " << clamp(-5, 0, 10) << std::endl;
    // Expected: 0
    std::cout << "clamp(5, 0, 10)    = " << clamp(5, 0, 10) << std::endl;
    // Expected: 5
    std::cout << "clamp(3.7, 1.0, 3.5) = " << clamp(3.7, 1.0, 3.5) << std::endl;
    // Expected: 3.5

    return 0;
}

/*
Expected Output:
=== C++98 Function Templates ===

--- myMax ---
myMax(3, 7)       = 7
myMax(3.14, 2.72) = 3.14
myMax('a', 'z')   = z
myMax("apple","banana") = banana
myMax<double>(3, 7.5) = 7.5

--- mySwap ---
Before swap: x=10, y=20
After swap:  x=20, y=10
Before swap: p=1.1, q=9.9
After swap:  p=9.9, q=1.1
Before swap: sa=hello, sb=world
After swap:  sa=world, sb=hello

--- printArray ---
int array:    [ 10, 20, 30, 40, 50 ]
double array: [ 1.1, 2.2, 3.3 ]

--- isEqual (two type params) ---
isEqual(5, 5.0)  = true
isEqual(5, 5.1)  = false

--- clamp ---
clamp(15, 0, 10)   = 10
clamp(-5, 0, 10)   = 0
clamp(5, 0, 10)    = 5
clamp(3.7, 1.0, 3.5) = 3.5
*/
