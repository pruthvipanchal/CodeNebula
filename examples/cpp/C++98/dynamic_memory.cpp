// CodeNebula - C++98 Example: Dynamic Memory Management
// Compile: g++ -std=c++98 -Wall -Wextra -o example dynamic_memory.cpp

// Dynamic memory in C++98 uses new/delete for single objects and
// new[]/delete[] for arrays. Unlike stack allocation, dynamic memory
// persists until explicitly freed. This example demonstrates allocation
// patterns, RAII, and common pitfalls.

#include <iostream>
#include <string>
#include <cstring>

// ------------------------------------------------------------------
// A class that tracks its construction/destruction
// ------------------------------------------------------------------
class Resource {
private:
    std::string name;
    int id;
    static int nextId;

public:
    Resource(const std::string& n) : name(n), id(nextId++) {
        std::cout << "  [Resource #" << id << " \"" << name << "\" constructed]" << std::endl;
    }

    ~Resource() {
        std::cout << "  [Resource #" << id << " \"" << name << "\" destroyed]" << std::endl;
    }

    void use() const {
        std::cout << "  Using Resource #" << id << " \"" << name << "\"" << std::endl;
    }
};

int Resource::nextId = 1;

// ------------------------------------------------------------------
// Simple RAII wrapper (C++98 style smart pointer)
// Demonstrates the principle behind std::auto_ptr
// ------------------------------------------------------------------
class IntPtr {
private:
    int* ptr;

    // Prevent copying (C++98 style: declare private, don't define)
    IntPtr(const IntPtr&);
    IntPtr& operator=(const IntPtr&);

public:
    explicit IntPtr(int* p = 0) : ptr(p) {}

    ~IntPtr() {
        std::cout << "  IntPtr destructor: deleting pointer" << std::endl;
        delete ptr;
    }

    int& operator*() const { return *ptr; }
    int* get() const { return ptr; }
};

// ------------------------------------------------------------------
// Dynamic string buffer class (manages char array)
// ------------------------------------------------------------------
class DynString {
private:
    char* data;
    int length;

public:
    DynString(const char* str) {
        length = std::strlen(str);
        data = new char[length + 1];
        std::strcpy(data, str);
        std::cout << "  DynString allocated " << (length + 1) << " bytes" << std::endl;
    }

    // Copy constructor (deep copy)
    DynString(const DynString& other) {
        length = other.length;
        data = new char[length + 1];
        std::strcpy(data, other.data);
        std::cout << "  DynString copy: allocated " << (length + 1) << " bytes" << std::endl;
    }

    // Assignment operator (deep copy)
    DynString& operator=(const DynString& other) {
        if (this != &other) {
            delete[] data;  // Free old memory first
            length = other.length;
            data = new char[length + 1];
            std::strcpy(data, other.data);
            std::cout << "  DynString assign: reallocated " << (length + 1) << " bytes" << std::endl;
        }
        return *this;
    }

    ~DynString() {
        std::cout << "  DynString freed " << (length + 1) << " bytes" << std::endl;
        delete[] data;
    }

    void print() const {
        std::cout << "  \"" << data << "\" (len=" << length << ")" << std::endl;
    }
};

int main() {
    std::cout << "=== C++98 Dynamic Memory ===" << std::endl;

    // --- 1. new / delete for single objects ---
    std::cout << "\n--- 1. new/delete (single object) ---" << std::endl;
    int* pi = new int(42);
    std::cout << "Allocated int: " << *pi << std::endl;
    // Expected: Allocated int: 42

    double* pd = new double(3.14);
    std::cout << "Allocated double: " << *pd << std::endl;
    // Expected: Allocated double: 3.14

    delete pi;
    delete pd;
    std::cout << "Single objects deleted." << std::endl;

    // Set pointers to NULL after delete (good practice in C++98)
    pi = 0;
    pd = 0;

    // --- 2. new[] / delete[] for arrays ---
    std::cout << "\n--- 2. new[]/delete[] (arrays) ---" << std::endl;
    int size = 5;
    int* arr = new int[size];

    // Initialize the array
    for (int i = 0; i < size; ++i) {
        arr[i] = (i + 1) * 10;
    }

    // Print the array
    std::cout << "Dynamic array: ";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i];
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    // Expected: Dynamic array: 10, 20, 30, 40, 50

    delete[] arr;  // MUST use delete[] for arrays, not delete
    arr = 0;
    std::cout << "Array deleted." << std::endl;

    // --- 3. Dynamic objects with constructors/destructors ---
    std::cout << "\n--- 3. Dynamic objects ---" << std::endl;
    Resource* r1 = new Resource("Database");
    Resource* r2 = new Resource("Network");

    r1->use();
    r2->use();

    delete r1;  // Destructor called here
    delete r2;

    // --- 4. Array of objects ---
    std::cout << "\n--- 4. Array of objects ---" << std::endl;
    {
        // new[] calls default constructor for each element
        // (Resource needs a default constructor for this, so we use pointers)
        const int N = 3;
        Resource* resources[N];
        resources[0] = new Resource("File");
        resources[1] = new Resource("Socket");
        resources[2] = new Resource("Timer");

        for (int i = 0; i < N; ++i) {
            resources[i]->use();
        }

        // Must delete each one
        for (int i = 0; i < N; ++i) {
            delete resources[i];
        }
    }

    // --- 5. RAII pattern ---
    std::cout << "\n--- 5. RAII wrapper ---" << std::endl;
    {
        IntPtr smart(new int(99));
        std::cout << "Smart pointer holds: " << *smart << std::endl;
        // Expected: Smart pointer holds: 99

        // No need to call delete -- IntPtr destructor handles it
    }
    // Expected: IntPtr destructor: deleting pointer
    std::cout << "After RAII scope: memory automatically freed." << std::endl;

    // --- 6. Deep copy with dynamic memory ---
    std::cout << "\n--- 6. Deep copy (DynString) ---" << std::endl;
    {
        DynString s1("Hello, C++98!");
        s1.print();

        // Copy constructor
        DynString s2(s1);
        s2.print();

        // Assignment operator
        DynString s3("temporary");
        s3 = s1;
        s3.print();
    }
    // All DynStrings destroyed here, each freeing its own memory

    // --- 7. Checking for NULL before delete (safe) ---
    std::cout << "\n--- 7. Safe delete patterns ---" << std::endl;
    int* maybe = 0;
    delete maybe;  // Deleting NULL/0 is safe and does nothing
    std::cout << "Deleting null pointer is safe (no-op)." << std::endl;

    // --- 8. 2D dynamic array ---
    std::cout << "\n--- 8. 2D dynamic array ---" << std::endl;
    int rows = 3, cols = 4;

    // Allocate array of row pointers
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }

    // Fill with values
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = i * cols + j + 1;
        }
    }

    // Print
    std::cout << "2D array:" << std::endl;
    for (int i = 0; i < rows; ++i) {
        std::cout << "  ";
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[i][j];
            if (j < cols - 1) std::cout << "\t";
        }
        std::cout << std::endl;
    }

    // Free in reverse order
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    std::cout << "2D array freed." << std::endl;

    return 0;
}

/*
Expected Output:
=== C++98 Dynamic Memory ===

--- 1. new/delete (single object) ---
Allocated int: 42
Allocated double: 3.14
Single objects deleted.

--- 2. new[]/delete[] (arrays) ---
Dynamic array: 10, 20, 30, 40, 50
Array deleted.

--- 3. Dynamic objects ---
  [Resource #1 "Database" constructed]
  [Resource #2 "Network" constructed]
  Using Resource #1 "Database"
  Using Resource #2 "Network"
  [Resource #1 "Database" destroyed]
  [Resource #2 "Network" destroyed]

--- 4. Array of objects ---
  [Resource #3 "File" constructed]
  [Resource #4 "Socket" constructed]
  [Resource #5 "Timer" constructed]
  Using Resource #3 "File"
  Using Resource #4 "Socket"
  Using Resource #5 "Timer"
  [Resource #3 "File" destroyed]
  [Resource #4 "Socket" destroyed]
  [Resource #5 "Timer" destroyed]

--- 5. RAII wrapper ---
Smart pointer holds: 99
  IntPtr destructor: deleting pointer
After RAII scope: memory automatically freed.

--- 6. Deep copy (DynString) ---
  DynString allocated 14 bytes
  "Hello, C++98!" (len=13)
  DynString copy: allocated 14 bytes
  "Hello, C++98!" (len=13)
  DynString allocated 10 bytes
  DynString assign: reallocated 14 bytes
  "Hello, C++98!" (len=13)
  DynString freed 14 bytes
  DynString freed 14 bytes
  DynString freed 14 bytes

--- 7. Safe delete patterns ---
Deleting null pointer is safe (no-op).

--- 8. 2D dynamic array ---
2D array:
  1	2	3	4
  5	6	7	8
  9	10	11	12
2D array freed.
*/
