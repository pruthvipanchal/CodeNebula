// CodeNebula - C++98 Example: Arrays
// Compile: g++ -std=c++98 -Wall -Wextra -o example arrays.cpp

// Demonstrates arrays in C++98: declaration, initialization, iteration,
// multidimensional arrays, arrays as function parameters, and common
// array operations.

#include <iostream>
#include <cstring>

// ------------------------------------------------------------------
// Arrays decay to pointers when passed to functions.
// The size information is lost, so we must pass it separately.
// ------------------------------------------------------------------
void printArray(const int arr[], int size)
{
    std::cout << "  [";
    for (int i = 0; i < size; ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << arr[i];
    }
    std::cout << "]" << std::endl;
}

// Sum elements of an array
int sumArray(const int arr[], int size)
{
    int total = 0;
    for (int i = 0; i < size; ++i) {
        total += arr[i];
    }
    return total;
}

// Reverse an array in place
void reverseArray(int arr[], int size)
{
    for (int i = 0; i < size / 2; ++i) {
        int temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

// Print a 2D matrix (fixed column count in C++98)
void printMatrix(const int mat[][4], int rows)
{
    for (int r = 0; r < rows; ++r) {
        std::cout << "    ";
        for (int c = 0; c < 4; ++c) {
            std::cout << mat[r][c] << "\t";
        }
        std::cout << std::endl;
    }
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Declaration and initialization
    // ------------------------------------------------------------------
    std::cout << "=== Array Declaration ===" << std::endl;

    // Explicit size, all elements initialized
    int a[5] = {10, 20, 30, 40, 50};
    std::cout << "  int a[5] = {10,20,30,40,50}: ";
    printArray(a, 5);

    // Size deduced from initializer
    int b[] = {1, 2, 3};
    int bSize = sizeof(b) / sizeof(b[0]);
    std::cout << "  int b[] = {1,2,3} (size=" << bSize << "): ";
    printArray(b, bSize);

    // Partial initialization - remaining elements are zero
    int c[5] = {1, 2};
    std::cout << "  int c[5] = {1,2} (rest are 0): ";
    printArray(c, 5);

    // Zero initialization
    int d[5] = {0};
    std::cout << "  int d[5] = {0} (all zeros): ";
    printArray(d, 5);

    // Uninitialized (values are indeterminate)
    int e[3];
    e[0] = 100;
    e[1] = 200;
    e[2] = 300;
    std::cout << "  int e[3] (manually set): ";
    printArray(e, 3);
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Accessing elements
    // ------------------------------------------------------------------
    std::cout << "=== Element Access ===" << std::endl;

    std::cout << "  a[0] = " << a[0] << std::endl;
    std::cout << "  a[4] = " << a[4] << std::endl;

    // Modify elements
    a[2] = 999;
    std::cout << "  After a[2] = 999: ";
    printArray(a, 5);
    a[2] = 30;  // restore
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Iterating with for loop (index-based, C++98 style)
    // ------------------------------------------------------------------
    std::cout << "=== Iteration ===" << std::endl;

    std::cout << "  Forward:  ";
    for (int i = 0; i < 5; ++i) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "  Backward: ";
    for (int i = 4; i >= 0; --i) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;

    // Using pointer iteration
    std::cout << "  Pointer:  ";
    for (int* p = a; p != a + 5; ++p) {
        std::cout << *p << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Array operations
    // ------------------------------------------------------------------
    std::cout << "=== Array Operations ===" << std::endl;

    std::cout << "  Sum of a: " << sumArray(a, 5) << std::endl;

    int toReverse[] = {1, 2, 3, 4, 5};
    std::cout << "  Before reverse: ";
    printArray(toReverse, 5);
    reverseArray(toReverse, 5);
    std::cout << "  After reverse:  ";
    printArray(toReverse, 5);

    // Linear search
    int target = 30;
    int foundIndex = -1;
    for (int i = 0; i < 5; ++i) {
        if (a[i] == target) {
            foundIndex = i;
            break;
        }
    }
    std::cout << "  Search for " << target << " in a: "
              << (foundIndex >= 0 ? "found at index " : "not found")
              << (foundIndex >= 0 ? foundIndex : 0) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Character arrays (C-strings)
    // ------------------------------------------------------------------
    std::cout << "=== Character Arrays (C-Strings) ===" << std::endl;

    char greeting[] = "Hello, World!";
    std::cout << "  greeting: " << greeting << std::endl;
    std::cout << "  strlen:   " << std::strlen(greeting) << std::endl;
    std::cout << "  sizeof:   " << sizeof(greeting) << " (includes '\\0')" << std::endl;

    // Individual characters
    std::cout << "  Characters: ";
    for (int i = 0; greeting[i] != '\0'; ++i) {
        std::cout << greeting[i] << ' ';
    }
    std::cout << std::endl;

    // Copy a string
    char copy[50];
    std::strcpy(copy, greeting);
    std::cout << "  Copy: " << copy << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 6. Multidimensional arrays
    // ------------------------------------------------------------------
    std::cout << "=== 2D Array (Matrix) ===" << std::endl;

    int matrix[3][4] = {
        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12}
    };

    std::cout << "  3x4 Matrix:" << std::endl;
    printMatrix(matrix, 3);

    std::cout << "  matrix[1][2] = " << matrix[1][2] << std::endl;
    std::cout << "  sizeof(matrix)       = " << sizeof(matrix) << std::endl;
    std::cout << "  sizeof(matrix[0])    = " << sizeof(matrix[0])
              << " (one row)" << std::endl;
    std::cout << "  Rows = " << sizeof(matrix) / sizeof(matrix[0]) << std::endl;
    std::cout << "  Cols = " << sizeof(matrix[0]) / sizeof(matrix[0][0]) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 7. 3D array
    // ------------------------------------------------------------------
    std::cout << "=== 3D Array ===" << std::endl;

    int cube[2][3][2] = {
        { {1, 2}, {3, 4}, {5, 6} },
        { {7, 8}, {9, 10}, {11, 12} }
    };

    std::cout << "  2x3x2 Cube:" << std::endl;
    for (int i = 0; i < 2; ++i) {
        std::cout << "    Layer " << i << ": ";
        for (int j = 0; j < 3; ++j) {
            std::cout << "[";
            for (int k = 0; k < 2; ++k) {
                if (k > 0) std::cout << ",";
                std::cout << cube[i][j][k];
            }
            std::cout << "] ";
        }
        std::cout << std::endl;
    }
    std::cout << "  sizeof(cube) = " << sizeof(cube)
              << " bytes (" << sizeof(cube) / sizeof(int) << " ints)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 8. Array of structures
    // ------------------------------------------------------------------
    std::cout << "=== Array of Structs ===" << std::endl;

    struct Student {
        char name[20];
        int  grade;
    };

    Student students[3];
    std::strcpy(students[0].name, "Alice");   students[0].grade = 95;
    std::strcpy(students[1].name, "Bob");     students[1].grade = 87;
    std::strcpy(students[2].name, "Charlie"); students[2].grade = 92;

    for (int i = 0; i < 3; ++i) {
        std::cout << "  " << students[i].name << ": " << students[i].grade << std::endl;
    }

    return 0;
}

/*
Expected output:

=== Array Declaration ===
  int a[5] = {10,20,30,40,50}: [10, 20, 30, 40, 50]
  int b[] = {1,2,3} (size=3): [1, 2, 3]
  int c[5] = {1,2} (rest are 0): [1, 2, 0, 0, 0]
  int d[5] = {0} (all zeros): [0, 0, 0, 0, 0]
  int e[3] (manually set): [100, 200, 300]

=== Element Access ===
  a[0] = 10
  a[4] = 50
  After a[2] = 999: [10, 20, 999, 40, 50]

=== Iteration ===
  Forward:  10 20 30 40 50
  Backward: 50 40 30 20 10
  Pointer:  10 20 30 40 50

=== Array Operations ===
  Sum of a: 150
  Before reverse: [1, 2, 3, 4, 5]
  After reverse:  [5, 4, 3, 2, 1]
  Search for 30 in a: found at index 2

=== Character Arrays (C-Strings) ===
  greeting: Hello, World!
  strlen:   13
  sizeof:   14 (includes '\0')
  Characters: H e l l o ,   W o r l d !
  Copy: Hello, World!

=== 2D Array (Matrix) ===
  3x4 Matrix:
    1	2	3	4
    5	6	7	8
    9	10	11	12
  matrix[1][2] = 7
  sizeof(matrix)       = 48
  sizeof(matrix[0])    = 16 (one row)
  Rows = 3
  Cols = 4

=== 3D Array ===
  2x3x2 Cube:
    Layer 0: [1,2] [3,4] [5,6]
    Layer 1: [7,8] [9,10] [11,12]
  sizeof(cube) = 48 bytes (12 ints)

=== Array of Structs ===
  Alice: 95
  Bob: 87
  Charlie: 92
*/
