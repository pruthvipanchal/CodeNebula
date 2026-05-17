// CodeNebula - C++98 Example: Functions
// Compile: g++ -std=c++98 -Wall -Wextra -o example functions.cpp

// Demonstrates functions in C++98: declaration vs definition, pass-by-value,
// pass-by-reference, pass-by-pointer, return values, returning multiple values
// via reference parameters, and recursive functions.

#include <iostream>
#include <cmath>

// ------------------------------------------------------------------
// 1. Function declarations (prototypes) - declare before main, define after
// ------------------------------------------------------------------
int add(int a, int b);
double circleArea(double radius);
void greet(const char* name);
void modifyByValue(int x);
void modifyByReference(int& x);
void modifyByPointer(int* x);
void getMinMax(const int arr[], int size, int& outMin, int& outMax);
int factorial(int n);
void printStars(int n);

int main()
{
    // ------------------------------------------------------------------
    // Demo 1: Basic function calls with return values
    // ------------------------------------------------------------------
    std::cout << "=== Basic Functions ===" << std::endl;

    int sum = add(3, 4);
    std::cout << "  add(3, 4) = " << sum << std::endl;

    double area = circleArea(5.0);
    std::cout << "  circleArea(5.0) = " << area << std::endl;

    greet("Alice");
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 2: Pass by value - original is not modified
    // ------------------------------------------------------------------
    std::cout << "=== Pass by Value ===" << std::endl;

    int val = 10;
    std::cout << "  Before modifyByValue: val = " << val << std::endl;
    modifyByValue(val);
    std::cout << "  After modifyByValue:  val = " << val
              << " (unchanged)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 3: Pass by reference - original IS modified
    // ------------------------------------------------------------------
    std::cout << "=== Pass by Reference ===" << std::endl;

    int refVal = 10;
    std::cout << "  Before modifyByReference: refVal = " << refVal << std::endl;
    modifyByReference(refVal);
    std::cout << "  After modifyByReference:  refVal = " << refVal
              << " (modified!)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 4: Pass by pointer - original IS modified
    // ------------------------------------------------------------------
    std::cout << "=== Pass by Pointer ===" << std::endl;

    int ptrVal = 10;
    std::cout << "  Before modifyByPointer: ptrVal = " << ptrVal << std::endl;
    modifyByPointer(&ptrVal);
    std::cout << "  After modifyByPointer:  ptrVal = " << ptrVal
              << " (modified!)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 5: Returning multiple values via reference parameters
    // ------------------------------------------------------------------
    std::cout << "=== Multiple Return Values (via reference) ===" << std::endl;

    int data[] = {34, 12, 78, 5, 56, 91, 23};
    int dataSize = sizeof(data) / sizeof(data[0]);
    int minVal = 0, maxVal = 0;

    getMinMax(data, dataSize, minVal, maxVal);
    std::cout << "  Array: {34, 12, 78, 5, 56, 91, 23}" << std::endl;
    std::cout << "  Min = " << minVal << std::endl;
    std::cout << "  Max = " << maxVal << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 6: Recursive function
    // ------------------------------------------------------------------
    std::cout << "=== Recursion ===" << std::endl;

    for (int i = 0; i <= 10; ++i) {
        std::cout << "  " << i << "! = " << factorial(i) << std::endl;
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 7: void function (performs action, returns nothing)
    // ------------------------------------------------------------------
    std::cout << "=== void Function ===" << std::endl;

    for (int i = 1; i <= 5; ++i) {
        std::cout << "  ";
        printStars(i);
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 8: Functions with array parameters
    // ------------------------------------------------------------------
    std::cout << "=== Array Parameters ===" << std::endl;

    // When you pass an array, you always need the size
    int scores[] = {85, 92, 78, 96, 88};
    int numScores = sizeof(scores) / sizeof(scores[0]);

    // Calculate average using array parameter
    int total = 0;
    for (int i = 0; i < numScores; ++i) {
        total += scores[i];
    }
    double average = static_cast<double>(total) / numScores;
    std::cout << "  Scores: {85, 92, 78, 96, 88}" << std::endl;
    std::cout << "  Average: " << average << std::endl;

    return 0;
}

// ------------------------------------------------------------------
// Function definitions
// ------------------------------------------------------------------

// Simple function returning a value
int add(int a, int b)
{
    return a + b;
}

// Function with double parameter and return
double circleArea(double radius)
{
    const double PI = 3.14159265358979;
    return PI * radius * radius;
}

// Function returning void (no return value)
void greet(const char* name)
{
    std::cout << "  Hello, " << name << "!" << std::endl;
}

// Pass by value: x is a copy; changes are local only
void modifyByValue(int x)
{
    x = x * 2;
    std::cout << "    Inside function: x = " << x << std::endl;
}

// Pass by reference: x IS the caller's variable
void modifyByReference(int& x)
{
    x = x * 2;
    std::cout << "    Inside function: x = " << x << std::endl;
}

// Pass by pointer: *x accesses the caller's variable
void modifyByPointer(int* x)
{
    *x = *x * 2;
    std::cout << "    Inside function: *x = " << *x << std::endl;
}

// Return multiple values through reference parameters
void getMinMax(const int arr[], int size, int& outMin, int& outMax)
{
    if (size <= 0) return;

    outMin = arr[0];
    outMax = arr[0];

    for (int i = 1; i < size; ++i) {
        if (arr[i] < outMin) outMin = arr[i];
        if (arr[i] > outMax) outMax = arr[i];
    }
}

// Classic recursive function
int factorial(int n)
{
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// Print n stars followed by newline
void printStars(int n)
{
    for (int i = 0; i < n; ++i) {
        std::cout << "*";
    }
    std::cout << std::endl;
}

/*
Expected output:

=== Basic Functions ===
  add(3, 4) = 7
  circleArea(5.0) = 78.5398
  Hello, Alice!

=== Pass by Value ===
  Before modifyByValue: val = 10
    Inside function: x = 20
  After modifyByValue:  val = 10 (unchanged)

=== Pass by Reference ===
  Before modifyByReference: refVal = 10
    Inside function: x = 20
  After modifyByReference:  refVal = 20 (modified!)

=== Pass by Pointer ===
  Before modifyByPointer: ptrVal = 10
    Inside function: *x = 20
  After modifyByPointer:  ptrVal = 20 (modified!)

=== Multiple Return Values (via reference) ===
  Array: {34, 12, 78, 5, 56, 91, 23}
  Min = 5
  Max = 91

=== Recursion ===
  0! = 1
  1! = 1
  2! = 2
  3! = 6
  4! = 24
  5! = 120
  6! = 720
  7! = 5040
  8! = 40320
  9! = 362880
  10! = 3628800

=== void Function ===
  *
  **
  ***
  ****
  *****

=== Array Parameters ===
  Scores: {85, 92, 78, 96, 88}
  Average: 87.8
*/
