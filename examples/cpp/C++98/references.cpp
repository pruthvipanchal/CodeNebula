// CodeNebula - C++98 Example: References
// Compile: g++ -std=c++98 -Wall -Wextra -o example references.cpp

// Demonstrates references in C++98: declaration, aliasing behavior,
// pass-by-reference, const references, references vs pointers, and
// returning references from functions.

#include <iostream>
#include <string>

// ------------------------------------------------------------------
// Pass by value - makes a copy, original is unchanged
// ------------------------------------------------------------------
void incrementByValue(int x)
{
    ++x;
    std::cout << "    Inside incrementByValue: x = " << x << std::endl;
}

// ------------------------------------------------------------------
// Pass by reference - modifies the original
// ------------------------------------------------------------------
void incrementByRef(int& x)
{
    ++x;
    std::cout << "    Inside incrementByRef: x = " << x << std::endl;
}

// ------------------------------------------------------------------
// Pass by pointer (for comparison)
// ------------------------------------------------------------------
void incrementByPtr(int* x)
{
    ++(*x);
    std::cout << "    Inside incrementByPtr: *x = " << *x << std::endl;
}

// ------------------------------------------------------------------
// Swap using references (cleaner than pointer version)
// ------------------------------------------------------------------
void swapRefs(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

// ------------------------------------------------------------------
// const reference: avoids copy without allowing modification
// ------------------------------------------------------------------
void printLargeObject(const std::string& str)
{
    std::cout << "    String (length " << str.size() << "): " << str << std::endl;
    // str += "x";  // ERROR: const reference prevents modification
}

// ------------------------------------------------------------------
// Returning a reference (allows chaining and l-value use)
// ------------------------------------------------------------------
int globalArray[] = {100, 200, 300, 400, 500};

int& getElement(int index)
{
    return globalArray[index];
}

// ------------------------------------------------------------------
// Demonstrating reference in a struct
// ------------------------------------------------------------------
struct Wrapper {
    int& ref;

    // Constructor must initialize reference (references can't be default-constructed)
    Wrapper(int& r) : ref(r) {}
};

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic reference declaration and aliasing
    // ------------------------------------------------------------------
    std::cout << "=== Reference Basics ===" << std::endl;

    int original = 42;
    int& alias = original;      // alias IS original (not a copy)

    std::cout << "  original : " << original << std::endl;
    std::cout << "  alias    : " << alias << std::endl;
    std::cout << "  &original: " << &original << std::endl;
    std::cout << "  &alias   : " << &alias << " (same address!)" << std::endl;

    // Modifying alias modifies original
    alias = 100;
    std::cout << "  After alias = 100:" << std::endl;
    std::cout << "  original : " << original << std::endl;

    // Modifying original is visible through alias
    original = 200;
    std::cout << "  After original = 200:" << std::endl;
    std::cout << "  alias    : " << alias << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. References must be initialized and cannot be reseated
    // ------------------------------------------------------------------
    std::cout << "=== References Cannot Be Reseated ===" << std::endl;

    int a = 10, b = 20;
    int& ref = a;

    std::cout << "  ref -> a, a = " << a << std::endl;

    // This does NOT make ref point to b. It copies b's value into a.
    ref = b;
    std::cout << "  After ref = b:" << std::endl;
    std::cout << "  a = " << a << " (a now holds b's value)" << std::endl;
    std::cout << "  b = " << b << " (unchanged)" << std::endl;
    std::cout << "  ref still aliases a: &ref=" << &ref
              << " &a=" << &a << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Pass by value vs reference vs pointer
    // ------------------------------------------------------------------
    std::cout << "=== Pass by Value vs Reference vs Pointer ===" << std::endl;

    int val = 10;

    std::cout << "  Starting value: " << val << std::endl;
    incrementByValue(val);
    std::cout << "  After incrementByValue: val = " << val
              << " (unchanged)" << std::endl;

    incrementByRef(val);
    std::cout << "  After incrementByRef:   val = " << val
              << " (modified!)" << std::endl;

    incrementByPtr(&val);
    std::cout << "  After incrementByPtr:   val = " << val
              << " (modified!)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Swap via references
    // ------------------------------------------------------------------
    std::cout << "=== Swap via References ===" << std::endl;

    int x = 10, y = 20;
    std::cout << "  Before: x=" << x << ", y=" << y << std::endl;
    swapRefs(x, y);
    std::cout << "  After:  x=" << x << ", y=" << y << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. const reference
    // ------------------------------------------------------------------
    std::cout << "=== const Reference ===" << std::endl;

    // const reference to a variable
    int number = 42;
    const int& cref = number;
    std::cout << "  number = " << number << std::endl;
    std::cout << "  cref   = " << cref << std::endl;
    number = 50;    // OK: modify through original name
    std::cout << "  After number = 50, cref = " << cref << std::endl;
    // cref = 60;   // ERROR: can't modify through const reference

    // const reference can bind to a temporary (extends its lifetime)
    const int& temp = 100 + 200;
    std::cout << "  const int& temp = 100 + 200: " << temp << std::endl;

    // Pass string by const reference (avoids expensive copy)
    std::string longString = "This is a long string that we avoid copying";
    printLargeObject(longString);
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 6. Returning a reference
    // ------------------------------------------------------------------
    std::cout << "=== Returning References ===" << std::endl;

    std::cout << "  globalArray[2] before: " << globalArray[2] << std::endl;

    // getElement returns a reference, so we can assign to it
    getElement(2) = 999;
    std::cout << "  After getElement(2) = 999: " << globalArray[2] << std::endl;

    // Can also read through returned reference
    int& elemRef = getElement(0);
    std::cout << "  elemRef = getElement(0): " << elemRef << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 7. Reference as a struct member
    // ------------------------------------------------------------------
    std::cout << "=== Reference in Struct ===" << std::endl;

    int source = 77;
    Wrapper w(source);

    std::cout << "  source = " << source << std::endl;
    std::cout << "  w.ref  = " << w.ref << std::endl;

    w.ref = 88;
    std::cout << "  After w.ref = 88:" << std::endl;
    std::cout << "  source = " << source << " (modified through struct ref)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 8. References vs Pointers summary
    // ------------------------------------------------------------------
    std::cout << "=== References vs Pointers ===" << std::endl;
    std::cout << "  References:" << std::endl;
    std::cout << "    - Must be initialized at declaration" << std::endl;
    std::cout << "    - Cannot be null" << std::endl;
    std::cout << "    - Cannot be reseated to another object" << std::endl;
    std::cout << "    - No explicit dereferencing needed" << std::endl;
    std::cout << "    - Cleaner syntax" << std::endl;
    std::cout << "  Pointers:" << std::endl;
    std::cout << "    - Can be declared without initialization" << std::endl;
    std::cout << "    - Can be null (NULL / 0)" << std::endl;
    std::cout << "    - Can be reassigned to point elsewhere" << std::endl;
    std::cout << "    - Support pointer arithmetic" << std::endl;
    std::cout << "    - Can have pointer-to-pointer" << std::endl;

    return 0;
}

/*
Expected output:

=== Reference Basics ===
  original : 42
  alias    : 42
  &original: 0x7ffd...
  &alias   : 0x7ffd... (same address!)
  After alias = 100:
  original : 100
  After original = 200:
  alias    : 200

=== References Cannot Be Reseated ===
  ref -> a, a = 10
  After ref = b:
  a = 20 (a now holds b's value)
  b = 20 (unchanged)
  ref still aliases a: &ref=0x... &a=0x...

=== Pass by Value vs Reference vs Pointer ===
  Starting value: 10
    Inside incrementByValue: x = 11
  After incrementByValue: val = 10 (unchanged)
    Inside incrementByRef: x = 11
  After incrementByRef:   val = 11 (modified!)
    Inside incrementByPtr: *x = 12
  After incrementByPtr:   val = 12 (modified!)

=== Swap via References ===
  Before: x=10, y=20
  After:  x=20, y=10

=== const Reference ===
  number = 42
  cref   = 42
  After number = 50, cref = 50
  const int& temp = 100 + 200: 300
    String (length 44): This is a long string that we avoid copying

=== Returning References ===
  globalArray[2] before: 300
  After getElement(2) = 999: 999
  elemRef = getElement(0): 100

=== Reference in Struct ===
  source = 77
  w.ref  = 77
  After w.ref = 88:
  source = 88 (modified through struct ref)

=== References vs Pointers ===
  References:
    - Must be initialized at declaration
    - Cannot be null
    - Cannot be reseated to another object
    - No explicit dereferencing needed
    - Cleaner syntax
  Pointers:
    - Can be declared without initialization
    - Can be null (NULL / 0)
    - Can be reassigned to point elsewhere
    - Support pointer arithmetic
    - Can have pointer-to-pointer
*/
