// CodeNebula - C++11 Example: nullptr vs NULL
// Compile: g++ -std=c++11 -Wall -Wextra -o example nullptr.cpp

// Demonstrates nullptr, the type-safe null pointer constant introduced in
// C++11. Unlike NULL (which is typically 0), nullptr has its own type
// (std::nullptr_t) and resolves overload ambiguities correctly.

#include <iostream>
#include <cstddef>   // for std::nullptr_t

// Real-world scenario: overloaded functions where NULL causes ambiguity
void process(int value)
{
    std::cout << "  process(int): " << value << std::endl;
}

void process(int* ptr)
{
    if (ptr) {
        std::cout << "  process(int*): points to " << *ptr << std::endl;
    } else {
        std::cout << "  process(int*): null pointer" << std::endl;
    }
}

void process(std::nullptr_t)
{
    std::cout << "  process(nullptr_t): received nullptr" << std::endl;
}

// Template function that detects null pointers
template <typename T>
void checkPointer(T ptr)
{
    if (ptr == nullptr) {
        std::cout << "  Pointer is null" << std::endl;
    } else {
        std::cout << "  Pointer is valid" << std::endl;
    }
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic nullptr usage
    // ------------------------------------------------------------------
    int* p1 = nullptr;
    double* p2 = nullptr;

    std::cout << "=== Basic nullptr ===" << std::endl;
    std::cout << "  p1 is null: " << (p1 == nullptr ? "yes" : "no") << std::endl;
    std::cout << "  p2 is null: " << (p2 == nullptr ? "yes" : "no") << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Overload resolution: nullptr vs NULL
    // ------------------------------------------------------------------
    int val = 42;

    std::cout << "=== Overload resolution ===" << std::endl;
    process(0);             // calls process(int)
    process(&val);          // calls process(int*)
    process(nullptr);       // calls process(nullptr_t) -- unambiguous!
    // process(NULL);       // would be ambiguous on many compilers
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. nullptr in boolean contexts
    // ------------------------------------------------------------------
    int* ptr = nullptr;

    std::cout << "=== Boolean context ===" << std::endl;
    if (!ptr) {
        std::cout << "  ptr is null (boolean false)" << std::endl;
    }

    ptr = &val;
    if (ptr) {
        std::cout << "  ptr is valid (boolean true), value: " << *ptr << std::endl;
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. nullptr with templates
    // ------------------------------------------------------------------
    int num = 7;
    int* validPtr = &num;

    std::cout << "=== Templates with nullptr ===" << std::endl;
    checkPointer(validPtr);
    checkPointer(static_cast<int*>(nullptr));
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. nullptr_t as a type
    // ------------------------------------------------------------------
    std::nullptr_t np = nullptr;    // variable of type nullptr_t

    std::cout << "=== nullptr_t type ===" << std::endl;
    std::cout << "  sizeof(nullptr)  : " << sizeof(nullptr) << std::endl;
    std::cout << "  sizeof(nullptr_t): " << sizeof(np) << std::endl;
    std::cout << "  nullptr == 0     : " << (nullptr == 0 ? "true" : "false") << std::endl;

    return 0;
}

/*
Expected output:

=== Basic nullptr ===
  p1 is null: yes
  p2 is null: yes

=== Overload resolution ===
  process(int): 0
  process(int*): points to 42
  process(nullptr_t): received nullptr

=== Boolean context ===
  ptr is null (boolean false)
  ptr is valid (boolean true), value: 42

=== Templates with nullptr ===
  Pointer is valid
  Pointer is null

=== nullptr_t type ===
  sizeof(nullptr)  : 8
  sizeof(nullptr_t): 8
  nullptr == 0     : true
*/
