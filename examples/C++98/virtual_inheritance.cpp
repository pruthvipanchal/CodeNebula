// CodeNebula - C++98 Example: Virtual Inheritance
// Compile: g++ -std=c++98 -Wall -Wextra -o example virtual_inheritance.cpp
//
// This example demonstrates:
// - The "Diamond Problem" in multiple inheritance
// - How virtual inheritance solves it (single shared base)
// - Constructor call order with virtual bases
// - Contrast between virtual and non-virtual inheritance

#include <iostream>

// ============================================================
// PART A: THE DIAMOND PROBLEM (without virtual inheritance)
// ============================================================
//
//        PersonNV
//       /        \.
//  StudentNV   EmployeeNV
//       \        /
//      InternNV
//
// Without virtual inheritance, InternNV contains TWO copies of PersonNV.

namespace NonVirtual {

class Person {
protected:
    int id;
public:
    Person(int i) : id(i) {
        std::cout << "  Person(" << id << ") constructed" << std::endl;
    }
    ~Person() {
        std::cout << "  Person(" << id << ") destroyed" << std::endl;
    }
    int getId() const { return id; }
};

class Student : public Person {
protected:
    double gpa;
public:
    Student(int i, double g) : Person(i), gpa(g) {
        std::cout << "  Student constructed (GPA=" << gpa << ")" << std::endl;
    }
};

class Employee : public Person {
protected:
    double salary;
public:
    Employee(int i, double s) : Person(i), salary(s) {
        std::cout << "  Employee constructed (salary=" << salary << ")" << std::endl;
    }
};

class Intern : public Student, public Employee {
public:
    Intern(int studentId, double g, int empId, double s)
        : Student(studentId, g), Employee(empId, s)
    {
        std::cout << "  Intern constructed" << std::endl;
    }

    void show() const {
        // intern.getId()  is AMBIGUOUS -- two copies of Person::id
        // Must qualify:
        std::cout << "  Student ID: " << Student::id
                  << ", Employee ID: " << Employee::id << std::endl;
        std::cout << "  GPA: " << gpa << ", Salary: " << salary << std::endl;
    }
};

} // namespace NonVirtual

// ============================================================
// PART B: SOLVED WITH VIRTUAL INHERITANCE
// ============================================================
//
//         Person
//        /      \.      (virtual)
//   Student    Employee
//        \      /
//        Intern
//
// Only ONE shared Person sub-object exists.

namespace Virtual {

class Person {
protected:
    int id;
public:
    Person(int i) : id(i) {
        std::cout << "  Person(" << id << ") constructed" << std::endl;
    }
    ~Person() {
        std::cout << "  Person(" << id << ") destroyed" << std::endl;
    }
    int getId() const { return id; }
    void setId(int i) { id = i; }
};

// 'virtual' keyword means only ONE Person sub-object is shared
class Student : virtual public Person {
protected:
    double gpa;
public:
    Student(int i, double g) : Person(i), gpa(g) {
        std::cout << "  Student constructed (GPA=" << gpa << ")" << std::endl;
    }
};

class Employee : virtual public Person {
protected:
    double salary;
public:
    Employee(int i, double s) : Person(i), salary(s) {
        std::cout << "  Employee constructed (salary=" << salary << ")" << std::endl;
    }
};

class Intern : public Student, public Employee {
public:
    // IMPORTANT: With virtual inheritance, the MOST-DERIVED class
    // (Intern) must directly initialise the virtual base (Person).
    // The Person() calls in Student and Employee initialisers are
    // IGNORED by the compiler for this hierarchy.
    Intern(int i, double g, double s)
        : Person(i),              // <-- Intern calls Person directly
          Student(i, g),
          Employee(i, s)
    {
        std::cout << "  Intern constructed" << std::endl;
    }

    void show() const {
        // No ambiguity! Only one Person::id exists.
        std::cout << "  ID: " << getId()       // unambiguous now
                  << ", GPA: " << gpa
                  << ", Salary: " << salary << std::endl;
    }
};

} // namespace Virtual

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "1. DIAMOND PROBLEM (no virtual inheritance)" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        std::cout << "  Creating Intern (studentId=101, empId=501):\n" << std::endl;
        NonVirtual::Intern intern(101, 3.8, 501, 25000.0);
        std::cout << std::endl;

        intern.show();

        std::cout << "\n  Notice: Person is constructed TWICE!" << std::endl;
        std::cout << "  intern.getId() would be AMBIGUOUS." << std::endl;
        std::cout << "  Must use Student::id or Employee::id.\n" << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "2. VIRTUAL INHERITANCE (diamond solved)" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        std::cout << "  Creating Intern (id=42):\n" << std::endl;
        Virtual::Intern intern(42, 3.9, 30000.0);
        std::cout << std::endl;

        intern.show();

        std::cout << "\n  Person is constructed only ONCE." << std::endl;
        std::cout << "  getId() is unambiguous.\n" << std::endl;

        // Demonstrate that there is truly one Person
        std::cout << "  Modifying id via setId(99):" << std::endl;
        intern.setId(99);
        intern.show();
        std::cout << "  (Both Student and Employee see the same id)\n" << std::endl;
    }

    std::cout << "========================================" << std::endl;
    std::cout << "3. CONSTRUCTOR ORDER WITH VIRTUAL BASES" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "  With virtual inheritance, construction order is:" << std::endl;
    std::cout << "    1. Virtual base classes (Person) -- called by most-derived" << std::endl;
    std::cout << "    2. Non-virtual bases in declaration order (Student, Employee)" << std::endl;
    std::cout << "    3. The most-derived class (Intern)" << std::endl;
    std::cout << std::endl;
    std::cout << "  Destruction is the exact reverse." << std::endl;

    std::cout << "\n========================================" << std::endl;
    std::cout << "4. DIAGRAM SUMMARY" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "  Without virtual:           With virtual:" << std::endl;
    std::cout << "     Person  Person           Person (one)" << std::endl;
    std::cout << "       |       |              /     \\" << std::endl;
    std::cout << "    Student Employee       Student Employee" << std::endl;
    std::cout << "       \\     /                \\     /" << std::endl;
    std::cout << "       Intern                  Intern" << std::endl;
    std::cout << std::endl;
    std::cout << "  Two Person copies vs one shared Person." << std::endl;

    return 0;
}

// Expected output:
// ========================================
// 1. DIAMOND PROBLEM (no virtual inheritance)
// ========================================
//   Creating Intern (studentId=101, empId=501):
//
//   Person(101) constructed
//   Student constructed (GPA=3.8)
//   Person(501) constructed
//   Employee constructed (salary=25000)
//   Intern constructed
//
//   Student ID: 101, Employee ID: 501
//   GPA: 3.8, Salary: 25000
//
//   Notice: Person is constructed TWICE!
//   ...
//   Person(501) destroyed
//   Person(101) destroyed
//
// ========================================
// 2. VIRTUAL INHERITANCE (diamond solved)
// ========================================
//   Creating Intern (id=42):
//
//   Person(42) constructed           <-- only ONCE
//   Student constructed (GPA=3.9)
//   Employee constructed (salary=30000)
//   Intern constructed
//
//   ID: 42, GPA: 3.9, Salary: 30000
//   ...
//   Modifying id via setId(99):
//   ID: 99, GPA: 3.9, Salary: 30000
//   ...
//   Person(99) destroyed             <-- only ONCE
