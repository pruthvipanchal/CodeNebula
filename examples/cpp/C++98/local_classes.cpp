// CodeNebula - C++98 Example: Local Classes
// Compile: g++ -std=c++98 -Wall -Wextra -o example local_classes.cpp
//
// This example demonstrates:
// - Defining a class inside a function (local class)
// - Local classes can access the enclosing function's types and static variables
// - Local classes CANNOT access the function's automatic (local) variables
// - Local classes cannot have static data members
// - Local classes cannot be used as template arguments in C++98
// - Practical uses: ad-hoc comparators, strategy objects, helpers

#include <iostream>
#include <cstring>

// ============================================================
// 1. Basic local class
// ============================================================
void basicLocalClass() {
    std::cout << "  Inside basicLocalClass():" << std::endl;

    // This class exists ONLY inside this function
    class Greeter {
    private:
        char message[64];
    public:
        Greeter(const char* msg) {
            std::strncpy(message, msg, 63);
            message[63] = '\0';
        }
        void greet() const {
            std::cout << "    Greeter says: " << message << std::endl;
        }
    };

    Greeter g1("Hello from a local class!");
    Greeter g2("I only exist in this function.");
    g1.greet();
    g2.greet();

    // Greeter cannot be used outside this function
}

// ============================================================
// 2. Local class accessing enclosing scope
// ============================================================
void accessRules() {
    std::cout << "  Inside accessRules():" << std::endl;

    static int staticVar = 42;   // static local -- accessible by local class
    int localVar = 100;          // automatic local -- NOT accessible (void)

    // Suppress unused warning
    (void)localVar;

    enum Color { RED, GREEN, BLUE };  // local enum -- accessible by local class

    class LocalHelper {
    public:
        void show() const {
            // CAN access static variables of the enclosing function
            std::cout << "    staticVar = " << staticVar << std::endl;

            // CAN access local types (enums, typedefs)
            Color c = GREEN;
            std::cout << "    Color GREEN = " << c << std::endl;

            // CANNOT access automatic local variables:
            // std::cout << localVar;  // COMPILE ERROR
        }

        void modify() {
            // Can even modify the static variable
            staticVar += 10;
            std::cout << "    Modified staticVar to " << staticVar << std::endl;
        }
    };

    LocalHelper h;
    h.show();
    h.modify();
    h.show();
}

// ============================================================
// 3. Local class as a strategy / functor
// ============================================================
// Simple sorting function that accepts a comparison interface
class Comparator {
public:
    virtual ~Comparator() {}
    virtual bool lessThan(int a, int b) const = 0;
};

void bubbleSort(int arr[], int n, const Comparator& cmp) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (cmp.lessThan(arr[j + 1], arr[j])) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sortDemo() {
    std::cout << "  Inside sortDemo():" << std::endl;

    int data[] = { 5, 2, 8, 1, 9, 3 };
    int n = 6;

    // Local class: ascending comparator
    class AscCompare : public Comparator {
    public:
        bool lessThan(int a, int b) const {
            return a < b;
        }
    };

    // Local class: descending comparator
    class DescCompare : public Comparator {
    public:
        bool lessThan(int a, int b) const {
            return a > b;
        }
    };

    // Sort ascending
    AscCompare asc;
    bubbleSort(data, n, asc);
    std::cout << "    Ascending:  ";
    for (int i = 0; i < n; ++i) std::cout << data[i] << " ";
    std::cout << std::endl;

    // Sort descending
    DescCompare desc;
    bubbleSort(data, n, desc);
    std::cout << "    Descending: ";
    for (int i = 0; i < n; ++i) std::cout << data[i] << " ";
    std::cout << std::endl;
}

// ============================================================
// 4. Local class with multiple methods
// ============================================================
void calculatorDemo() {
    std::cout << "  Inside calculatorDemo():" << std::endl;

    class Calculator {
    private:
        double memory;
    public:
        Calculator() : memory(0.0) {}

        double add(double a, double b) const { return a + b; }
        double sub(double a, double b) const { return a - b; }
        double mul(double a, double b) const { return a * b; }

        double div(double a, double b) const {
            if (b == 0.0) {
                std::cout << "    ERROR: division by zero" << std::endl;
                return 0.0;
            }
            return a / b;
        }

        void store(double v) { memory = v; }
        double recall() const { return memory; }
    };

    Calculator calc;
    std::cout << "    10 + 3 = " << calc.add(10, 3) << std::endl;
    std::cout << "    10 - 3 = " << calc.sub(10, 3) << std::endl;
    std::cout << "    10 * 3 = " << calc.mul(10, 3) << std::endl;
    std::cout << "    10 / 3 = " << calc.div(10, 3) << std::endl;
    std::cout << "    10 / 0 = ";
    calc.div(10, 0);

    calc.store(42.0);
    std::cout << "    Memory: " << calc.recall() << std::endl;
}

// ============================================================
// 5. Local class restrictions demonstration
// ============================================================
void restrictionsDemo() {
    std::cout << "  Inside restrictionsDemo():" << std::endl;

    class Local {
    public:
        // static int count;  // ERROR: local classes cannot have static data members
        int value;

        Local(int v) : value(v) {}

        // Can have static MEMBER FUNCTIONS (some compilers)
        // but cannot have static DATA members

        void show() const {
            std::cout << "    Local value = " << value << std::endl;
        }
    };

    Local a(10);
    Local b(20);
    a.show();
    b.show();

    std::cout << "    Restrictions:" << std::endl;
    std::cout << "    - No static data members" << std::endl;
    std::cout << "    - Cannot access enclosing function's local variables" << std::endl;
    std::cout << "    - CAN access static local variables and types" << std::endl;
    std::cout << "    - Cannot be used as template arguments (C++98)" << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "1. BASIC LOCAL CLASS" << std::endl;
    std::cout << "========================================" << std::endl;
    basicLocalClass();

    // Greeter g("test");  // ERROR: Greeter is not visible here

    std::cout << "\n========================================" << std::endl;
    std::cout << "2. ACCESS RULES (static vars, types)" << std::endl;
    std::cout << "========================================" << std::endl;
    accessRules();

    std::cout << "\n========================================" << std::endl;
    std::cout << "3. LOCAL CLASS AS STRATEGY (sorting)" << std::endl;
    std::cout << "========================================" << std::endl;
    sortDemo();

    std::cout << "\n========================================" << std::endl;
    std::cout << "4. LOCAL CLASS WITH MULTIPLE METHODS" << std::endl;
    std::cout << "========================================" << std::endl;
    calculatorDemo();

    std::cout << "\n========================================" << std::endl;
    std::cout << "5. LOCAL CLASS RESTRICTIONS" << std::endl;
    std::cout << "========================================" << std::endl;
    restrictionsDemo();

    std::cout << "\n========================================" << std::endl;
    std::cout << "6. LOCAL vs NESTED CLASSES" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "  Nested class:" << std::endl;
    std::cout << "    - Defined inside another CLASS" << std::endl;
    std::cout << "    - Can be public, private, or protected" << std::endl;
    std::cout << "    - Accessible via Outer::Inner (if public)" << std::endl;
    std::cout << "    - Can have static members" << std::endl;
    std::cout << std::endl;
    std::cout << "  Local class:" << std::endl;
    std::cout << "    - Defined inside a FUNCTION" << std::endl;
    std::cout << "    - Visible only within that function" << std::endl;
    std::cout << "    - Cannot have static data members" << std::endl;
    std::cout << "    - Cannot access enclosing function's local variables" << std::endl;
    std::cout << "    - Great for one-off helpers, comparators, strategies" << std::endl;

    return 0;
}

// Expected output:
// ========================================
// 1. BASIC LOCAL CLASS
// ========================================
//   Inside basicLocalClass():
//     Greeter says: Hello from a local class!
//     Greeter says: I only exist in this function.
//
// ========================================
// 2. ACCESS RULES (static vars, types)
// ========================================
//   Inside accessRules():
//     staticVar = 42
//     Color GREEN = 1
//     Modified staticVar to 52
//     staticVar = 52
//     Color GREEN = 1
//
// ========================================
// 3. LOCAL CLASS AS STRATEGY (sorting)
// ========================================
//   Inside sortDemo():
//     Ascending:  1 2 3 5 8 9
//     Descending: 9 8 5 3 2 1
//
// ========================================
// 4. LOCAL CLASS WITH MULTIPLE METHODS
// ========================================
//   Inside calculatorDemo():
//     10 + 3 = 13
//     10 - 3 = 7
//     10 * 3 = 30
//     10 / 3 = 3.33333
//     10 / 0 =     ERROR: division by zero
//     Memory: 42
//
// ========================================
// 5. LOCAL CLASS RESTRICTIONS
// ========================================
//   Inside restrictionsDemo():
//     Local value = 10
//     Local value = 20
//     Restrictions:
//     ...
//
// ========================================
// 6. LOCAL vs NESTED CLASSES
// ========================================
//   ...comparison...
