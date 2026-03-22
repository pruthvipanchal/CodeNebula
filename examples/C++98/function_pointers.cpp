// CodeNebula - C++98 Example: Function Pointers
// Compile: g++ -std=c++98 -Wall -Wextra -o example function_pointers.cpp

// Demonstrates function pointers in C++98: declaration, assignment, calling
// through pointers, arrays of function pointers, callback patterns, and
// practical uses like sorting with custom comparators.

#include <iostream>
#include <cstdlib>
#include <cstring>

// ------------------------------------------------------------------
// 1. Simple functions to point to
// ------------------------------------------------------------------
int add(int a, int b)      { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b)   { return (b != 0) ? a / b : 0; }

// ------------------------------------------------------------------
// 2. Functions for callback demonstration
// ------------------------------------------------------------------
void greetEnglish(const char* name) { std::cout << "  Hello, " << name << "!" << std::endl; }
void greetSpanish(const char* name) { std::cout << "  Hola, " << name << "!" << std::endl; }
void greetFrench(const char* name)  { std::cout << "  Bonjour, " << name << "!" << std::endl; }
void greetGerman(const char* name)  { std::cout << "  Hallo, " << name << "!" << std::endl; }

// ------------------------------------------------------------------
// 3. Callback pattern: a function that accepts a function pointer
// ------------------------------------------------------------------
typedef int (*BinaryOp)(int, int);

int applyOperation(int a, int b, BinaryOp op)
{
    return op(a, b);
}

// ------------------------------------------------------------------
// 4. Transform array using a function pointer (map pattern)
// ------------------------------------------------------------------
typedef int (*TransformFunc)(int);

int doubleIt(int x) { return x * 2; }
int squareIt(int x) { return x * x; }
int negate(int x)   { return -x; }
int increment(int x){ return x + 1; }

void transformArray(int arr[], int size, TransformFunc fn)
{
    for (int i = 0; i < size; ++i) {
        arr[i] = fn(arr[i]);
    }
}

void printArray(const int arr[], int size)
{
    std::cout << "[";
    for (int i = 0; i < size; ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << arr[i];
    }
    std::cout << "]";
}

// ------------------------------------------------------------------
// 5. Filter pattern using function pointer as predicate
// ------------------------------------------------------------------
typedef bool (*Predicate)(int);

bool isEven(int x) { return x % 2 == 0; }
bool isOdd(int x)  { return x % 2 != 0; }
bool isPositive(int x) { return x > 0; }

int filterArray(const int src[], int srcSize, int dest[], Predicate pred)
{
    int count = 0;
    for (int i = 0; i < srcSize; ++i) {
        if (pred(src[i])) {
            dest[count++] = src[i];
        }
    }
    return count;
}

// ------------------------------------------------------------------
// 6. Comparison function for qsort (C library callback)
// ------------------------------------------------------------------
int compareAscending(const void* a, const void* b)
{
    return (*(const int*)a) - (*(const int*)b);
}

int compareDescending(const void* a, const void* b)
{
    return (*(const int*)b) - (*(const int*)a);
}

int main()
{
    // ------------------------------------------------------------------
    // Demo 1: Basic function pointer declaration and use
    // ------------------------------------------------------------------
    std::cout << "=== Basic Function Pointers ===" << std::endl;

    // Declare a function pointer: pointer to function taking two ints, returning int
    int (*operation)(int, int);

    // Assign and call
    operation = add;
    std::cout << "  operation = add:      " << operation(10, 3) << std::endl;

    operation = subtract;
    std::cout << "  operation = subtract: " << operation(10, 3) << std::endl;

    operation = multiply;
    std::cout << "  operation = multiply: " << operation(10, 3) << std::endl;

    operation = divide;
    std::cout << "  operation = divide:   " << operation(10, 3) << std::endl;

    // Can also use address-of operator (both forms are valid)
    operation = &add;
    std::cout << "  Using &add:           " << operation(5, 7) << std::endl;

    // Can dereference explicitly (both forms are valid)
    std::cout << "  Using (*operation):   " << (*operation)(5, 7) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 2: Using typedef for cleaner syntax
    // ------------------------------------------------------------------
    std::cout << "=== Typedef for Function Pointers ===" << std::endl;

    // BinaryOp is typedef'd above as: int (*)(int, int)
    BinaryOp op = multiply;
    std::cout << "  BinaryOp op = multiply; op(6, 7) = " << op(6, 7) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 3: Array of function pointers
    // ------------------------------------------------------------------
    std::cout << "=== Array of Function Pointers ===" << std::endl;

    BinaryOp operations[] = { add, subtract, multiply, divide };
    const char* opNames[] = { "add", "subtract", "multiply", "divide" };

    int a = 20, b = 4;
    for (int i = 0; i < 4; ++i) {
        std::cout << "  " << opNames[i] << "(" << a << ", " << b << ") = "
                  << operations[i](a, b) << std::endl;
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 4: Callback pattern
    // ------------------------------------------------------------------
    std::cout << "=== Callback Pattern ===" << std::endl;

    std::cout << "  applyOperation(10, 5, add)      = "
              << applyOperation(10, 5, add) << std::endl;
    std::cout << "  applyOperation(10, 5, subtract)  = "
              << applyOperation(10, 5, subtract) << std::endl;
    std::cout << "  applyOperation(10, 5, multiply)  = "
              << applyOperation(10, 5, multiply) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 5: Greeting callbacks (strategy pattern)
    // ------------------------------------------------------------------
    std::cout << "=== Greeting Callbacks ===" << std::endl;

    typedef void (*GreetFunc)(const char*);

    GreetFunc greeters[] = { greetEnglish, greetSpanish, greetFrench, greetGerman };
    const char* languages[] = { "English", "Spanish", "French", "German" };

    for (int i = 0; i < 4; ++i) {
        std::cout << "  " << languages[i] << ": ";
        greeters[i]("Alice");
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 6: Transform array (map pattern)
    // ------------------------------------------------------------------
    std::cout << "=== Transform Array (Map) ===" << std::endl;

    int data[] = {1, 2, 3, 4, 5};
    int size = 5;

    std::cout << "  Original:  ";
    printArray(data, size);
    std::cout << std::endl;

    int copy1[] = {1, 2, 3, 4, 5};
    transformArray(copy1, size, doubleIt);
    std::cout << "  doubled:   ";
    printArray(copy1, size);
    std::cout << std::endl;

    int copy2[] = {1, 2, 3, 4, 5};
    transformArray(copy2, size, squareIt);
    std::cout << "  squared:   ";
    printArray(copy2, size);
    std::cout << std::endl;

    int copy3[] = {1, 2, 3, 4, 5};
    transformArray(copy3, size, negate);
    std::cout << "  negated:   ";
    printArray(copy3, size);
    std::cout << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 7: Filter array (filter pattern)
    // ------------------------------------------------------------------
    std::cout << "=== Filter Array ===" << std::endl;

    int source[] = {-3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
    int srcSize = 10;
    int filtered[10];
    int count;

    std::cout << "  Source: ";
    printArray(source, srcSize);
    std::cout << std::endl;

    count = filterArray(source, srcSize, filtered, isEven);
    std::cout << "  Even:     ";
    printArray(filtered, count);
    std::cout << std::endl;

    count = filterArray(source, srcSize, filtered, isOdd);
    std::cout << "  Odd:      ";
    printArray(filtered, count);
    std::cout << std::endl;

    count = filterArray(source, srcSize, filtered, isPositive);
    std::cout << "  Positive: ";
    printArray(filtered, count);
    std::cout << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 8: qsort with function pointer callback (C library)
    // ------------------------------------------------------------------
    std::cout << "=== qsort with Callback ===" << std::endl;

    int unsorted[] = {42, 17, 93, 5, 28, 61, 3, 84};
    int arrSize = sizeof(unsorted) / sizeof(unsorted[0]);

    std::cout << "  Unsorted:   ";
    printArray(unsorted, arrSize);
    std::cout << std::endl;

    std::qsort(unsorted, arrSize, sizeof(int), compareAscending);
    std::cout << "  Ascending:  ";
    printArray(unsorted, arrSize);
    std::cout << std::endl;

    std::qsort(unsorted, arrSize, sizeof(int), compareDescending);
    std::cout << "  Descending: ";
    printArray(unsorted, arrSize);
    std::cout << std::endl;

    return 0;
}

/*
Expected output:

=== Basic Function Pointers ===
  operation = add:      13
  operation = subtract: 7
  operation = multiply: 30
  operation = divide:   3
  Using &add:           12
  Using (*operation):   12

=== Typedef for Function Pointers ===
  BinaryOp op = multiply; op(6, 7) = 42

=== Array of Function Pointers ===
  add(20, 4) = 24
  subtract(20, 4) = 16
  multiply(20, 4) = 80
  divide(20, 4) = 5

=== Callback Pattern ===
  applyOperation(10, 5, add)      = 15
  applyOperation(10, 5, subtract)  = 5
  applyOperation(10, 5, multiply)  = 50

=== Greeting Callbacks ===
  English:   Hello, Alice!
  Spanish:   Hola, Alice!
  French:   Bonjour, Alice!
  German:   Hallo, Alice!

=== Transform Array (Map) ===
  Original:  [1, 2, 3, 4, 5]
  doubled:   [2, 4, 6, 8, 10]
  squared:   [1, 4, 9, 16, 25]
  negated:   [-1, -2, -3, -4, -5]

=== Filter Array ===
  Source: [-3, -2, -1, 0, 1, 2, 3, 4, 5, 6]
  Even:     [-2, 0, 2, 4, 6]
  Odd:      [-3, -1, 1, 3, 5]
  Positive: [1, 2, 3, 4, 5, 6]

=== qsort with Callback ===
  Unsorted:   [42, 17, 93, 5, 28, 61, 3, 84]
  Ascending:  [3, 5, 17, 28, 42, 61, 84, 93]
  Descending: [93, 84, 61, 42, 28, 17, 5, 3]
*/
