// CodeNebula - C++98 Example: sizeof Operator
// Compile: g++ -std=c++98 -Wall -Wextra -o example sizeof_operator.cpp

// Demonstrates the sizeof operator on fundamental types, arrays, structs,
// classes, pointers, and expressions. Shows struct padding/alignment effects.

#include <iostream>

// ------------------------------------------------------------------
// Structs to demonstrate padding and alignment
// ------------------------------------------------------------------

// Poorly ordered struct (likely has padding)
struct Padded {
    char   a;     // 1 byte  + 3 bytes padding (to align next int)
    int    b;     // 4 bytes
    char   c;     // 1 byte  + 3 bytes padding (to align struct size)
};

// Well-ordered struct (minimal padding)
struct Compact {
    int    b;     // 4 bytes
    char   a;     // 1 byte
    char   c;     // 1 byte  + 2 bytes padding (to align struct size)
};

// Struct with mixed types
struct Mixed {
    double d;     // 8 bytes
    int    i;     // 4 bytes
    short  s;     // 2 bytes
    char   c;     // 1 byte + 1 byte padding
};

// Empty struct (guaranteed at least 1 byte in C++)
struct Empty {};

// Struct containing an array
struct WithArray {
    int    id;
    char   name[20];
    double score;
};

// Class with virtual function (has vtable pointer)
class Base {
public:
    int x;
    virtual void foo() {}
};

class Derived : public Base {
public:
    int y;
};

int main()
{
    // ------------------------------------------------------------------
    // 1. sizeof on fundamental types
    // ------------------------------------------------------------------
    std::cout << "=== Fundamental Types ===" << std::endl;
    std::cout << "  sizeof(bool)       : " << sizeof(bool)        << std::endl;
    std::cout << "  sizeof(char)       : " << sizeof(char)        << std::endl;
    std::cout << "  sizeof(short)      : " << sizeof(short)       << std::endl;
    std::cout << "  sizeof(int)        : " << sizeof(int)         << std::endl;
    std::cout << "  sizeof(long)       : " << sizeof(long)        << std::endl;
    std::cout << "  sizeof(float)      : " << sizeof(float)       << std::endl;
    std::cout << "  sizeof(double)     : " << sizeof(double)      << std::endl;
    std::cout << "  sizeof(long double): " << sizeof(long double) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. sizeof on pointers (all pointers are the same size)
    // ------------------------------------------------------------------
    std::cout << "=== Pointer Types ===" << std::endl;
    std::cout << "  sizeof(char*)     : " << sizeof(char*)       << std::endl;
    std::cout << "  sizeof(int*)      : " << sizeof(int*)        << std::endl;
    std::cout << "  sizeof(double*)   : " << sizeof(double*)     << std::endl;
    std::cout << "  sizeof(void*)     : " << sizeof(void*)       << std::endl;
    std::cout << "  sizeof(Padded*)   : " << sizeof(Padded*)     << std::endl;
    std::cout << "  (All pointers are the same size on a given platform)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. sizeof on arrays
    // ------------------------------------------------------------------
    std::cout << "=== Arrays ===" << std::endl;

    int arr[10];
    char str[] = "Hello";           // 6 chars including '\0'
    double matrix[3][4];

    std::cout << "  int arr[10]:" << std::endl;
    std::cout << "    sizeof(arr)          : " << sizeof(arr)
              << " (" << sizeof(arr) / sizeof(arr[0]) << " elements)" << std::endl;
    std::cout << "    sizeof(arr[0])       : " << sizeof(arr[0]) << std::endl;

    std::cout << "  char str[] = \"Hello\":" << std::endl;
    std::cout << "    sizeof(str)          : " << sizeof(str)
              << " (includes null terminator)" << std::endl;

    std::cout << "  double matrix[3][4]:" << std::endl;
    std::cout << "    sizeof(matrix)       : " << sizeof(matrix) << std::endl;
    std::cout << "    sizeof(matrix[0])    : " << sizeof(matrix[0])
              << " (one row = 4 doubles)" << std::endl;
    std::cout << "    sizeof(matrix[0][0]) : " << sizeof(matrix[0][0]) << std::endl;
    std::cout << "    Total elements       : "
              << sizeof(matrix) / sizeof(matrix[0][0]) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. sizeof on structs (padding and alignment)
    // ------------------------------------------------------------------
    std::cout << "=== Struct Padding ===" << std::endl;

    std::cout << "  struct Padded { char a; int b; char c; }:" << std::endl;
    std::cout << "    sizeof(Padded) : " << sizeof(Padded)
              << " (expected 6, but padding makes it larger)" << std::endl;

    std::cout << "  struct Compact { int b; char a; char c; }:" << std::endl;
    std::cout << "    sizeof(Compact): " << sizeof(Compact)
              << " (better member ordering)" << std::endl;

    std::cout << "  struct Mixed { double; int; short; char; }:" << std::endl;
    std::cout << "    sizeof(Mixed)  : " << sizeof(Mixed) << std::endl;

    std::cout << "  struct Empty {}:" << std::endl;
    std::cout << "    sizeof(Empty)  : " << sizeof(Empty)
              << " (C++ guarantees at least 1)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. sizeof on struct with array member
    // ------------------------------------------------------------------
    std::cout << "=== Struct With Array ===" << std::endl;
    std::cout << "  struct WithArray { int id; char name[20]; double score; }:" << std::endl;
    std::cout << "    sizeof(WithArray): " << sizeof(WithArray) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 6. sizeof on class with virtual functions (vtable pointer)
    // ------------------------------------------------------------------
    std::cout << "=== Classes with Virtual Functions ===" << std::endl;
    std::cout << "  sizeof(Base)    : " << sizeof(Base)
              << " (int + vtable pointer)" << std::endl;
    std::cout << "  sizeof(Derived) : " << sizeof(Derived)
              << " (Base + int y)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 7. sizeof on expressions (evaluated at compile time, no side effects)
    // ------------------------------------------------------------------
    std::cout << "=== sizeof on Expressions ===" << std::endl;

    int x = 5;
    std::cout << "  sizeof(x)     : " << sizeof(x)     << std::endl;
    std::cout << "  sizeof(x + 1) : " << sizeof(x + 1) << std::endl;
    std::cout << "  sizeof(x + 1.0): " << sizeof(x + 1.0)
              << " (promoted to double)" << std::endl;

    char ch = 'A';
    std::cout << "  sizeof(ch)    : " << sizeof(ch) << std::endl;
    std::cout << "  sizeof(ch + 1): " << sizeof(ch + 1)
              << " (char promoted to int in expression)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 8. Common idiom: compute array length with sizeof
    // ------------------------------------------------------------------
    std::cout << "=== Array Length Idiom ===" << std::endl;
    int data[] = {10, 20, 30, 40, 50, 60, 70};
    int length = sizeof(data) / sizeof(data[0]);
    std::cout << "  int data[] = {10,20,30,40,50,60,70};" << std::endl;
    std::cout << "  Array length = sizeof(data)/sizeof(data[0]) = "
              << length << std::endl;

    return 0;
}

/*
Expected output (typical 64-bit platform, sizes may vary):

=== Fundamental Types ===
  sizeof(bool)       : 1
  sizeof(char)       : 1
  sizeof(short)      : 2
  sizeof(int)        : 4
  sizeof(long)       : 4
  sizeof(float)      : 4
  sizeof(double)     : 8
  sizeof(long double): 12

=== Pointer Types ===
  sizeof(char*)     : 8
  sizeof(int*)      : 8
  sizeof(double*)   : 8
  sizeof(void*)     : 8
  sizeof(Padded*)   : 8
  (All pointers are the same size on a given platform)

=== Arrays ===
  int arr[10]:
    sizeof(arr)          : 40 (10 elements)
    sizeof(arr[0])       : 4
  char str[] = "Hello":
    sizeof(str)          : 6 (includes null terminator)
  double matrix[3][4]:
    sizeof(matrix)       : 96
    sizeof(matrix[0])    : 32 (one row = 4 doubles)
    sizeof(matrix[0][0]) : 8
    Total elements       : 12

=== Struct Padding ===
  struct Padded { char a; int b; char c; }:
    sizeof(Padded) : 12 (expected 6, but padding makes it larger)
  struct Compact { int b; char a; char c; }:
    sizeof(Compact): 8 (better member ordering)
  struct Mixed { double; int; short; char; }:
    sizeof(Mixed)  : 16
  struct Empty {}:
    sizeof(Empty)  : 1 (C++ guarantees at least 1)

=== Struct With Array ===
  struct WithArray { int id; char name[20]; double score; }:
    sizeof(WithArray): 32

=== Classes with Virtual Functions ===
  sizeof(Base)    : 16 (int + vtable pointer)
  sizeof(Derived) : 16 (Base + int y)

=== sizeof on Expressions ===
  sizeof(x)     : 4
  sizeof(x + 1) : 4
  sizeof(x + 1.0): 8 (promoted to double)
  sizeof(ch)    : 1
  sizeof(ch + 1): 4 (char promoted to int in expression)

=== Array Length Idiom ===
  int data[] = {10,20,30,40,50,60,70};
  Array length = sizeof(data)/sizeof(data[0]) = 7
*/
