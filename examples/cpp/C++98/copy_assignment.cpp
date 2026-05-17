// CodeNebula - C++98 Example: Copy Assignment Operator
// Compile: g++ -std=c++98 -Wall -Wextra -o example copy_assignment.cpp
//
// This example demonstrates:
// - Overloading operator= for deep-copy assignment
// - Self-assignment check (critical for correctness)
// - The difference between copy construction and copy assignment
// - The "Rule of Three": if you need one of {copy ctor, operator=, destructor},
//   you likely need all three

#include <iostream>
#include <cstring>

class String {
private:
    char* data;
    int   length;

    void cleanup() {
        delete[] data;
        data = NULL;
        length = 0;
    }

public:
    // Default constructor
    String() : data(NULL), length(0) {
        std::cout << "  [String] Default constructed (empty)" << std::endl;
    }

    // Parameterised constructor
    String(const char* str) : data(NULL), length(0) {
        if (str) {
            length = std::strlen(str);
            data = new char[length + 1];
            std::strcpy(data, str);
        }
        std::cout << "  [String] Constructed: \"" << (data ? data : "(null)")
                  << "\"" << std::endl;
    }

    // Copy constructor (deep copy)
    String(const String& other) : data(NULL), length(other.length) {
        if (other.data) {
            data = new char[length + 1];
            std::strcpy(data, other.data);
        }
        std::cout << "  [String] Copy constructed: \"" << (data ? data : "(null)")
                  << "\"" << std::endl;
    }

    // ---- Copy assignment operator (deep copy) ----
    String& operator=(const String& other) {
        std::cout << "  [String] operator= called" << std::endl;

        // 1. Self-assignment check
        if (this == &other) {
            std::cout << "    -> Self-assignment detected, skipping" << std::endl;
            return *this;
        }

        // 2. Free existing resource
        delete[] data;

        // 3. Deep-copy from source
        length = other.length;
        if (other.data) {
            data = new char[length + 1];
            std::strcpy(data, other.data);
        } else {
            data = NULL;
        }

        std::cout << "    -> Assigned: \"" << (data ? data : "(null)") << "\"" << std::endl;

        // 4. Return *this to allow chaining: a = b = c;
        return *this;
    }

    // Destructor
    ~String() {
        std::cout << "  [String] Destructor: \"" << (data ? data : "(null)")
                  << "\"" << std::endl;
        delete[] data;
    }

    // Utility
    void print(const char* label) const {
        std::cout << "  " << label << " = \""
                  << (data ? data : "(null)") << "\"" << std::endl;
    }

    void set(const char* str) {
        delete[] data;
        if (str) {
            length = std::strlen(str);
            data = new char[length + 1];
            std::strcpy(data, str);
        } else {
            data = NULL;
            length = 0;
        }
    }
};

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "1. COPY CONSTRUCTION vs COPY ASSIGNMENT" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        String a("Hello");           // parameterised ctor
        String b(a);                 // copy CONSTRUCTOR (not assignment)
        String c;                    // default ctor
        c = a;                       // copy ASSIGNMENT (operator=)

        a.print("a");
        b.print("b");
        c.print("c");
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "2. SELF-ASSIGNMENT CHECK" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        String s("World");
        s = s;                       // self-assignment -- must be safe!
        s.print("s (after self-assign)");
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "3. DEEP COPY VERIFICATION" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        String x("Original");
        String y;
        y = x;                       // deep copy via operator=

        x.print("x before mutation");
        y.print("y before mutation");

        x.set("Modified-X");
        x.print("x after mutation");
        y.print("y after mutation");
        std::cout << "  (y is unchanged -- deep copy works!)" << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "4. CHAINED ASSIGNMENT  a = b = c" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        String a, b, c("Chain");
        a = b = c;                   // works because operator= returns *this
        a.print("a");
        b.print("b");
        c.print("c");
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "5. RULE OF THREE SUMMARY" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "  If your class manages a resource (heap memory, file handle, etc.)," << std::endl;
    std::cout << "  you should define ALL THREE:" << std::endl;
    std::cout << "    1. Copy constructor    - String(const String&)" << std::endl;
    std::cout << "    2. Copy assignment     - String& operator=(const String&)" << std::endl;
    std::cout << "    3. Destructor          - ~String()" << std::endl;
    std::cout << "  Omitting any one leads to shallow copies or resource leaks." << std::endl;

    return 0;
}

// Expected output:
// ========================================
// 1. COPY CONSTRUCTION vs COPY ASSIGNMENT
// ========================================
//   [String] Constructed: "Hello"
//   [String] Copy constructed: "Hello"
//   [String] Default constructed (empty)
//   [String] operator= called
//     -> Assigned: "Hello"
//   a = "Hello"
//   b = "Hello"
//   c = "Hello"
//   [String] Destructor: "Hello"
//   [String] Destructor: "Hello"
//   [String] Destructor: "Hello"
//
// ========================================
// 2. SELF-ASSIGNMENT CHECK
// ========================================
//   [String] Constructed: "World"
//   [String] operator= called
//     -> Self-assignment detected, skipping
//   s (after self-assign) = "World"
//   [String] Destructor: "World"
//
// ========================================
// 3. DEEP COPY VERIFICATION
// ========================================
//   [String] Constructed: "Original"
//   [String] Default constructed (empty)
//   [String] operator= called
//     -> Assigned: "Original"
//   x before mutation = "Original"
//   y before mutation = "Original"
//   x after mutation = "Modified-X"
//   y after mutation = "Original"
//   (y is unchanged -- deep copy works!)
//   [String] Destructor: "Original"
//   [String] Destructor: "Modified-X"
//
// ========================================
// 4. CHAINED ASSIGNMENT  a = b = c
// ========================================
//   [String] Default constructed (empty)
//   [String] Default constructed (empty)
//   [String] Constructed: "Chain"
//   [String] operator= called
//     -> Assigned: "Chain"
//   [String] operator= called
//     -> Assigned: "Chain"
//   a = "Chain"
//   b = "Chain"
//   c = "Chain"
//   ...destructors...
//
// ========================================
// 5. RULE OF THREE SUMMARY
// ========================================
//   ...summary text...
