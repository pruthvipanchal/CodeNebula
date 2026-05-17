// CodeNebula - C++98 Example: Function Overloading
// Compile: g++ -std=c++98 -Wall -Wextra -o example function_overloading.cpp

// Demonstrates function overloading in C++98: same function name with different
// parameter types, different parameter counts, overloading with const, and
// how the compiler resolves which overload to call.

#include <iostream>
#include <cstring>
#include <cmath>

// ------------------------------------------------------------------
// 1. Overloading by parameter TYPE
//    Same name "print", different parameter types.
// ------------------------------------------------------------------
void print(int value)
{
    std::cout << "  print(int):     " << value << std::endl;
}

void print(double value)
{
    std::cout << "  print(double):  " << value << std::endl;
}

void print(char value)
{
    std::cout << "  print(char):    '" << value << "'" << std::endl;
}

void print(const char* value)
{
    std::cout << "  print(char*):   \"" << value << "\"" << std::endl;
}

void print(bool value)
{
    std::cout << "  print(bool):    " << (value ? "true" : "false") << std::endl;
}

// ------------------------------------------------------------------
// 2. Overloading by NUMBER of parameters
// ------------------------------------------------------------------
int add(int a, int b)
{
    return a + b;
}

int add(int a, int b, int c)
{
    return a + b + c;
}

double add(double a, double b)
{
    return a + b;
}

// ------------------------------------------------------------------
// 3. Overloading: area calculation for different shapes
//    A practical example showing how overloading makes APIs intuitive.
// ------------------------------------------------------------------
double area(double radius)                      // Circle
{
    const double PI = 3.14159265358979;
    return PI * radius * radius;
}

double area(double length, double width)        // Rectangle
{
    return length * width;
}

double area(double a, double b, double c)       // Triangle (Heron's formula)
{
    double s = (a + b + c) / 2.0;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

// ------------------------------------------------------------------
// 4. Overloading with reference and const reference
// ------------------------------------------------------------------
void inspect(int& x)
{
    std::cout << "  inspect(int&):       " << x << " (non-const ref)" << std::endl;
    x = x + 1;  // Can modify
}

void inspect(const int& x)
{
    std::cout << "  inspect(const int&): " << x << " (const ref)" << std::endl;
    // x = x + 1;  // ERROR: const reference
}

// ------------------------------------------------------------------
// 5. Overloading: max function for different types
// ------------------------------------------------------------------
int maxOf(int a, int b)
{
    std::cout << "  maxOf(int, int): ";
    return (a > b) ? a : b;
}

double maxOf(double a, double b)
{
    std::cout << "  maxOf(double, double): ";
    return (a > b) ? a : b;
}

const char* maxOf(const char* a, const char* b)
{
    std::cout << "  maxOf(char*, char*): ";
    return (std::strcmp(a, b) > 0) ? a : b;
}

// ------------------------------------------------------------------
// 6. Overloading: array operations
// ------------------------------------------------------------------
void fill(int arr[], int size, int value)
{
    for (int i = 0; i < size; ++i) {
        arr[i] = value;
    }
}

void fill(double arr[], int size, double value)
{
    for (int i = 0; i < size; ++i) {
        arr[i] = value;
    }
}

void fill(char arr[], int size, char value)
{
    for (int i = 0; i < size; ++i) {
        arr[i] = value;
    }
}

int main()
{
    // ------------------------------------------------------------------
    // Demo 1: Overloading by parameter type
    // ------------------------------------------------------------------
    std::cout << "=== Overloading by Type ===" << std::endl;

    print(42);              // calls print(int)
    print(3.14);            // calls print(double)
    print('X');             // calls print(char)
    print("Hello");         // calls print(const char*)
    print(true);            // calls print(bool)
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 2: Overloading by number of parameters
    // ------------------------------------------------------------------
    std::cout << "=== Overloading by Parameter Count ===" << std::endl;

    std::cout << "  add(3, 4)      = " << add(3, 4) << std::endl;
    std::cout << "  add(3, 4, 5)   = " << add(3, 4, 5) << std::endl;
    std::cout << "  add(1.5, 2.5)  = " << add(1.5, 2.5) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 3: Shape area calculation
    // ------------------------------------------------------------------
    std::cout << "=== Area Overloading ===" << std::endl;

    std::cout << "  Circle (r=5):         " << area(5.0) << std::endl;
    std::cout << "  Rectangle (4x6):      " << area(4.0, 6.0) << std::endl;
    std::cout << "  Triangle (3,4,5):     " << area(3.0, 4.0, 5.0) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 4: const vs non-const reference overload
    // ------------------------------------------------------------------
    std::cout << "=== const vs non-const Overloads ===" << std::endl;

    int mutable_val = 10;
    const int const_val = 20;

    inspect(mutable_val);   // calls inspect(int&) - non-const
    inspect(const_val);     // calls inspect(const int&) - const
    std::cout << "  mutable_val after inspect: " << mutable_val
              << " (was modified)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 5: max function overloads
    // ------------------------------------------------------------------
    std::cout << "=== maxOf Overloads ===" << std::endl;

    std::cout << maxOf(10, 20) << std::endl;
    std::cout << maxOf(3.14, 2.72) << std::endl;
    std::cout << maxOf("apple", "banana") << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 6: fill overloads for different array types
    // ------------------------------------------------------------------
    std::cout << "=== fill Overloads ===" << std::endl;

    int intArr[5];
    fill(intArr, 5, 42);
    std::cout << "  int array filled with 42:    ";
    for (int i = 0; i < 5; ++i) std::cout << intArr[i] << " ";
    std::cout << std::endl;

    double dblArr[4];
    fill(dblArr, 4, 3.14);
    std::cout << "  double array filled with 3.14: ";
    for (int i = 0; i < 4; ++i) std::cout << dblArr[i] << " ";
    std::cout << std::endl;

    char charArr[6];
    fill(charArr, 5, '*');
    charArr[5] = '\0';
    std::cout << "  char array filled with '*':  " << charArr << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Note on overload resolution rules
    // ------------------------------------------------------------------
    std::cout << "=== Overload Resolution Notes ===" << std::endl;
    std::cout << "  The compiler picks the best match based on:" << std::endl;
    std::cout << "  1. Exact match (no conversion needed)" << std::endl;
    std::cout << "  2. Promotion (char->int, float->double)" << std::endl;
    std::cout << "  3. Standard conversion (int->double, etc.)" << std::endl;
    std::cout << "  4. User-defined conversion" << std::endl;
    std::cout << "  If ambiguous, the compiler reports an error." << std::endl;

    return 0;
}

/*
Expected output:

=== Overloading by Type ===
  print(int):     42
  print(double):  3.14
  print(char):    'X'
  print(char*):   "Hello"
  print(bool):    true

=== Overloading by Parameter Count ===
  add(3, 4)      = 7
  add(3, 4, 5)   = 12
  add(1.5, 2.5)  = 4

=== Area Overloading ===
  Circle (r=5):         78.5398
  Rectangle (4x6):      24
  Triangle (3,4,5):     6

=== const vs non-const Overloads ===
  inspect(int&):       10 (non-const ref)
  inspect(const int&): 20 (const ref)
  mutable_val after inspect: 11 (was modified)

=== maxOf Overloads ===
  maxOf(int, int): 20
  maxOf(double, double): 3.14
  maxOf(char*, char*): banana

=== fill Overloads ===
  int array filled with 42:    42 42 42 42 42
  double array filled with 3.14: 3.14 3.14 3.14 3.14
  char array filled with '*':  *****

=== Overload Resolution Notes ===
  The compiler picks the best match based on:
  1. Exact match (no conversion needed)
  2. Promotion (char->int, float->double)
  3. Standard conversion (int->double, etc.)
  4. User-defined conversion
  If ambiguous, the compiler reports an error.
*/
