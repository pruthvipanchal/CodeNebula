// CodeNebula - C++98 Example: Pointers to Members
// Compile: g++ -std=c++98 -Wall -Wextra -o example pointers_to_members.cpp

// Demonstrates pointers to class members in C++98: pointer to data member,
// pointer to member function, using .* and ->* operators, arrays of member
// pointers, and practical uses.

#include <iostream>
#include <cstring>

// ------------------------------------------------------------------
// A class to demonstrate member pointers
// ------------------------------------------------------------------
class Student {
public:
    char name[30];
    int  age;
    double gpa;

    Student(const char* n, int a, double g)
        : age(a), gpa(g)
    {
        std::strncpy(name, n, 29);
        name[29] = '\0';
    }

    void introduce() const
    {
        std::cout << "    Hi, I'm " << name << ", age " << age
                  << ", GPA " << gpa << std::endl;
    }

    void study(const char* subject) const
    {
        std::cout << "    " << name << " is studying " << subject << std::endl;
    }

    double getGpa() const { return gpa; }
    int    getAge() const { return age; }
};

// ------------------------------------------------------------------
// Another class for member function pointer variety
// ------------------------------------------------------------------
class Calculator {
public:
    int value;

    Calculator() : value(0) {}
    Calculator(int v) : value(v) {}

    int add(int x) { value += x; return value; }
    int sub(int x) { value -= x; return value; }
    int mul(int x) { value *= x; return value; }

    void reset() { value = 0; }

    void print() const
    {
        std::cout << "    value = " << value << std::endl;
    }
};

int main()
{
    // ------------------------------------------------------------------
    // 1. Pointer to data member
    // ------------------------------------------------------------------
    std::cout << "=== Pointer to Data Member ===" << std::endl;

    // Declare a pointer to an int member of Student
    int Student::*pAge = &Student::age;

    // Declare a pointer to a double member of Student
    double Student::*pGpa = &Student::gpa;

    Student alice("Alice", 20, 3.8);

    // Use .* operator with an object
    std::cout << "  alice.*pAge = " << alice.*pAge << std::endl;
    std::cout << "  alice.*pGpa = " << alice.*pGpa << std::endl;

    // Modify through member pointer
    alice.*pAge = 21;
    alice.*pGpa = 3.9;
    std::cout << "  After modification:" << std::endl;
    std::cout << "  alice.*pAge = " << alice.*pAge << std::endl;
    std::cout << "  alice.*pGpa = " << alice.*pGpa << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Pointer to data member with ->* (pointer to object)
    // ------------------------------------------------------------------
    std::cout << "=== Using ->* Operator ===" << std::endl;

    Student* pStudent = &alice;

    // Use ->* operator with a pointer to object
    std::cout << "  pStudent->*pAge = " << pStudent->*pAge << std::endl;
    std::cout << "  pStudent->*pGpa = " << pStudent->*pGpa << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Pointer to member function (no parameters, const)
    // ------------------------------------------------------------------
    std::cout << "=== Pointer to Member Function ===" << std::endl;

    // Declare a pointer to a const member function: void (Student::*)() const
    void (Student::*pIntroduce)() const = &Student::introduce;

    Student bob("Bob", 22, 3.5);

    // Call using .* with an object
    std::cout << "  alice.introduce() via pointer:" << std::endl;
    (alice.*pIntroduce)();

    std::cout << "  bob.introduce() via pointer:" << std::endl;
    (bob.*pIntroduce)();

    // Call using ->* with a pointer to object
    Student* pBob = &bob;
    std::cout << "  pBob->introduce() via pointer:" << std::endl;
    (pBob->*pIntroduce)();
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Pointer to member function with parameters
    // ------------------------------------------------------------------
    std::cout << "=== Member Function Pointer with Parameters ===" << std::endl;

    void (Student::*pStudy)(const char*) const = &Student::study;

    (alice.*pStudy)("Mathematics");
    (bob.*pStudy)("Physics");
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Switching between member pointers (data members)
    // ------------------------------------------------------------------
    std::cout << "=== Switching Data Member Pointers ===" << std::endl;

    Student students[] = {
        Student("Alice", 20, 3.8),
        Student("Bob", 22, 3.5),
        Student("Carol", 19, 3.9)
    };

    // Print a specific field for all students using a member pointer
    std::cout << "  Ages: ";
    int Student::*field = &Student::age;
    for (int i = 0; i < 3; ++i) {
        std::cout << students[i].*field << " ";
    }
    std::cout << std::endl;

    std::cout << "  GPAs: ";
    double Student::*dfield = &Student::gpa;
    for (int i = 0; i < 3; ++i) {
        std::cout << students[i].*dfield << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 6. Array of member function pointers (Calculator)
    // ------------------------------------------------------------------
    std::cout << "=== Array of Member Function Pointers ===" << std::endl;

    // Pointer to member function: int (Calculator::*)(int)
    typedef int (Calculator::*CalcOp)(int);

    CalcOp ops[] = { &Calculator::add, &Calculator::sub, &Calculator::mul };
    const char* opNames[] = { "add", "sub", "mul" };

    Calculator calc(10);
    std::cout << "  Starting value: ";
    calc.print();

    for (int i = 0; i < 3; ++i) {
        int result = (calc.*ops[i])(5);
        std::cout << "  After " << opNames[i] << "(5): result = " << result;
        std::cout << ", ";
        calc.print();
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 7. Pointer to member function returning value
    // ------------------------------------------------------------------
    std::cout << "=== Member Function Returning Value ===" << std::endl;

    double (Student::*getter)() const;

    // Point to getGpa
    getter = &Student::getGpa;
    std::cout << "  GPAs via pointer to getGpa():" << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "    " << students[i].name << ": "
                  << (students[i].*getter)() << std::endl;
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 8. Practical: generic "print field" function using member pointer
    // ------------------------------------------------------------------
    std::cout << "=== Generic Field Printer ===" << std::endl;

    // Print a table of student data using member pointers
    std::cout << "  Name          Age   GPA" << std::endl;
    std::cout << "  --------------------------" << std::endl;

    int Student::*agePtr = &Student::age;
    double Student::*gpaPtr = &Student::gpa;

    for (int i = 0; i < 3; ++i) {
        std::cout << "  ";
        // Print name (fixed width, manual padding)
        int nameLen = static_cast<int>(std::strlen(students[i].name));
        std::cout << students[i].name;
        for (int j = nameLen; j < 14; ++j) std::cout << ' ';

        std::cout << students[i].*agePtr << "    "
                  << students[i].*gpaPtr << std::endl;
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 9. sizeof member pointers
    // ------------------------------------------------------------------
    std::cout << "=== sizeof Member Pointers ===" << std::endl;
    std::cout << "  sizeof(int Student::*)                : "
              << sizeof(int Student::*) << std::endl;
    std::cout << "  sizeof(void (Student::*)() const)     : "
              << sizeof(void (Student::*)()) << std::endl;
    std::cout << "  sizeof(int (Calculator::*)(int))      : "
              << sizeof(int (Calculator::*)(int)) << std::endl;
    std::cout << "  sizeof(int*)  (regular pointer)       : "
              << sizeof(int*) << std::endl;
    std::cout << "  (Member pointers may be larger than regular pointers)" << std::endl;

    return 0;
}

/*
Expected output:

=== Pointer to Data Member ===
  alice.*pAge = 20
  alice.*pGpa = 3.8
  After modification:
  alice.*pAge = 21
  alice.*pGpa = 3.9

=== Using ->* Operator ===
  pStudent->*pAge = 21
  pStudent->*pGpa = 3.9

=== Pointer to Member Function ===
  alice.introduce() via pointer:
    Hi, I'm Alice, age 21, GPA 3.9
  bob.introduce() via pointer:
    Hi, I'm Bob, age 22, GPA 3.5
  pBob->introduce() via pointer:
    Hi, I'm Bob, age 22, GPA 3.5

=== Member Function Pointer with Parameters ===
    Alice is studying Mathematics
    Bob is studying Physics

=== Switching Data Member Pointers ===
  Ages: 20 22 19
  GPAs: 3.8 3.5 3.9

=== Array of Member Function Pointers ===
  Starting value:     value = 10
  After add(5): result = 15,     value = 15
  After sub(5): result = 10,     value = 10
  After mul(5): result = 50,     value = 50

=== Member Function Returning Value ===
  GPAs via pointer to getGpa():
    Alice: 3.8
    Bob: 3.5
    Carol: 3.9

=== Generic Field Printer ===
  Name          Age   GPA
  --------------------------
  Alice         20    3.8
  Bob           22    3.5
  Carol         19    3.9

=== sizeof Member Pointers ===
  sizeof(int Student::*)                : 4 (or 8)
  sizeof(void (Student::*)() const)     : 8 (or 16)
  sizeof(int (Calculator::*)(int))      : 8 (or 16)
  sizeof(int*)  (regular pointer)       : 4 (or 8)
  (Member pointers may be larger than regular pointers)
*/
