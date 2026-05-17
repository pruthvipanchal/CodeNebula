// CodeNebula - C++98 Example: Pointers
// Compile: g++ -std=c++98 -Wall -Wextra -o example pointers.cpp

// Demonstrates pointer fundamentals in C++98: declaration, address-of operator,
// dereferencing, pointer arithmetic, null pointers, pointers to pointers,
// const pointers, and dynamic memory with new/delete.

#include <iostream>

// Swap using pointers (classic C-style)
void swapValues(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Pointer declaration and basic operations
    // ------------------------------------------------------------------
    std::cout << "=== Pointer Basics ===" << std::endl;

    int value = 42;
    int* ptr = &value;          // ptr holds the address of value

    std::cout << "  value          : " << value << std::endl;
    std::cout << "  &value (addr)  : " << &value << std::endl;
    std::cout << "  ptr            : " << ptr << " (same as &value)" << std::endl;
    std::cout << "  *ptr (deref)   : " << *ptr << " (same as value)" << std::endl;

    // Modify value through pointer
    *ptr = 99;
    std::cout << "  After *ptr = 99:" << std::endl;
    std::cout << "  value          : " << value << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Null pointer (use NULL or 0 in C++98, NOT nullptr)
    // ------------------------------------------------------------------
    std::cout << "=== Null Pointer ===" << std::endl;

    int* nullPtr = NULL;
    std::cout << "  nullPtr = NULL : " << nullPtr << std::endl;

    if (nullPtr == NULL) {
        std::cout << "  Pointer is null - safe to check before dereferencing" << std::endl;
    }

    int* zeroPtr = 0;  // Also valid in C++98
    if (zeroPtr == NULL) {
        std::cout << "  0 and NULL are equivalent in C++98" << std::endl;
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Pointer arithmetic
    // ------------------------------------------------------------------
    std::cout << "=== Pointer Arithmetic ===" << std::endl;

    int arr[] = {10, 20, 30, 40, 50};
    int* p = arr;       // points to arr[0]

    std::cout << "  Array: {10, 20, 30, 40, 50}" << std::endl;
    std::cout << "  p = arr (points to first element)" << std::endl;

    for (int i = 0; i < 5; ++i) {
        std::cout << "  *(p + " << i << ") = " << *(p + i)
                  << "  address: " << (p + i) << std::endl;
    }

    // Increment pointer to walk through array
    std::cout << std::endl;
    std::cout << "  Walking with p++:" << std::endl;
    p = arr;
    for (int i = 0; i < 5; ++i) {
        std::cout << "    *p = " << *p << std::endl;
        ++p;
    }

    // Pointer difference
    int* first = &arr[0];
    int* last  = &arr[4];
    std::cout << "  Distance (last - first) = " << (last - first)
              << " elements" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Pointers and arrays
    // ------------------------------------------------------------------
    std::cout << "=== Pointers and Arrays ===" << std::endl;

    // Array name decays to a pointer to first element
    std::cout << "  arr      = " << arr << std::endl;
    std::cout << "  &arr[0]  = " << &arr[0] << " (same address)" << std::endl;

    // Subscript operator works on pointers too
    int* arrPtr = arr;
    std::cout << "  arrPtr[2] = " << arrPtr[2] << " (same as *(arrPtr+2))" << std::endl;
    std::cout << "  2[arrPtr] = " << 2[arrPtr] << " (obscure but valid!)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Passing pointers to functions
    // ------------------------------------------------------------------
    std::cout << "=== Swap via Pointers ===" << std::endl;

    int a = 10, b = 20;
    std::cout << "  Before swap: a=" << a << ", b=" << b << std::endl;
    swapValues(&a, &b);
    std::cout << "  After swap:  a=" << a << ", b=" << b << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 6. Pointer to pointer
    // ------------------------------------------------------------------
    std::cout << "=== Pointer to Pointer ===" << std::endl;

    int val = 77;
    int* pVal = &val;
    int** ppVal = &pVal;

    std::cout << "  val            : " << val << std::endl;
    std::cout << "  *pVal          : " << *pVal << std::endl;
    std::cout << "  **ppVal        : " << **ppVal << std::endl;
    std::cout << "  pVal  (addr)   : " << pVal << std::endl;
    std::cout << "  *ppVal (addr)  : " << *ppVal << " (same as pVal)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 7. const and pointers
    // ------------------------------------------------------------------
    std::cout << "=== const and Pointers ===" << std::endl;

    int x = 10, y = 20;

    // Pointer to const int: can't modify *pc, but can reassign pc
    const int* pc = &x;
    std::cout << "  const int* pc = &x;  *pc = " << *pc << std::endl;
    pc = &y;        // OK: pointer itself can change
    std::cout << "  pc = &y;             *pc = " << *pc << std::endl;
    // *pc = 30;    // ERROR: can't modify value through pointer-to-const

    // const pointer to int: can modify *cp, but can't reassign cp
    int* const cp = &x;
    *cp = 100;      // OK: can modify the value
    std::cout << "  int* const cp = &x;  *cp = " << *cp << std::endl;
    // cp = &y;     // ERROR: can't change where const pointer points

    // const pointer to const int
    const int* const cpc = &y;
    std::cout << "  const int* const cpc = &y;  *cpc = " << *cpc << std::endl;
    // *cpc = 5;    // ERROR
    // cpc = &x;    // ERROR
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 8. Dynamic memory allocation (new / delete)
    // ------------------------------------------------------------------
    std::cout << "=== Dynamic Memory ===" << std::endl;

    int* dynInt = new int(42);
    std::cout << "  new int(42): *dynInt = " << *dynInt << std::endl;
    delete dynInt;
    dynInt = NULL;      // good practice: set to NULL after delete

    // Dynamic array
    int size = 5;
    int* dynArr = new int[size];
    for (int i = 0; i < size; ++i) {
        dynArr[i] = (i + 1) * 10;
    }

    std::cout << "  Dynamic array: ";
    for (int i = 0; i < size; ++i) {
        std::cout << dynArr[i] << " ";
    }
    std::cout << std::endl;

    delete[] dynArr;    // use delete[] for arrays
    dynArr = NULL;

    // ------------------------------------------------------------------
    // 9. void pointer (generic pointer)
    // ------------------------------------------------------------------
    std::cout << std::endl;
    std::cout << "=== void Pointer ===" << std::endl;

    int    intVar = 5;
    double dblVar = 3.14;

    void* vp = &intVar;
    std::cout << "  void* pointing to int:    "
              << *static_cast<int*>(vp) << std::endl;

    vp = &dblVar;
    std::cout << "  void* pointing to double: "
              << *static_cast<double*>(vp) << std::endl;

    std::cout << "  (Must cast void* before dereferencing)" << std::endl;

    return 0;
}

/*
Expected output (addresses will vary):

=== Pointer Basics ===
  value          : 42
  &value (addr)  : 0x7ffd...
  ptr            : 0x7ffd... (same as &value)
  *ptr (deref)   : 42
  After *ptr = 99:
  value          : 99

=== Null Pointer ===
  nullPtr = NULL : 0
  Pointer is null - safe to check before dereferencing
  0 and NULL are equivalent in C++98

=== Pointer Arithmetic ===
  Array: {10, 20, 30, 40, 50}
  p = arr (points to first element)
  *(p + 0) = 10  address: 0x...
  *(p + 1) = 20  address: 0x...
  *(p + 2) = 30  address: 0x...
  *(p + 3) = 40  address: 0x...
  *(p + 4) = 50  address: 0x...

  Walking with p++:
    *p = 10
    *p = 20
    *p = 30
    *p = 40
    *p = 50
  Distance (last - first) = 4 elements

=== Pointers and Arrays ===
  arr      = 0x...
  &arr[0]  = 0x... (same address)
  arrPtr[2] = 30 (same as *(arrPtr+2))
  2[arrPtr] = 30 (obscure but valid!)

=== Swap via Pointers ===
  Before swap: a=10, b=20
  After swap:  a=20, b=10

=== Pointer to Pointer ===
  val            : 77
  *pVal          : 77
  **ppVal        : 77
  pVal  (addr)   : 0x...
  *ppVal (addr)  : 0x... (same as pVal)

=== const and Pointers ===
  const int* pc = &x;  *pc = 10
  pc = &y;             *pc = 20
  int* const cp = &x;  *cp = 100
  const int* const cpc = &y;  *cpc = 20

=== Dynamic Memory ===
  new int(42): *dynInt = 42
  Dynamic array: 10 20 30 40 50

=== void Pointer ===
  void* pointing to int:    5
  void* pointing to double: 3.14
  (Must cast void* before dereferencing)
*/
