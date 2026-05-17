// CodeNebula - C++98 Example: Access Specifiers
// Compile: g++ -std=c++98 -Wall -Wextra -o example access_specifiers.cpp
//
// This example demonstrates:
// - public, private, and protected access specifiers for members
// - How access changes with public, protected, and private inheritance
// - Access rules for derived classes and external code
// - Summary table of all access combinations

#include <iostream>

// ============================================================
// Base class with all three access levels
// ============================================================
class Base {
public:
    int pubVal;

    Base() : pubVal(1), protVal(2), privVal(3) {}

    void showAll() const {
        std::cout << "  public=" << pubVal
                  << ", protected=" << protVal
                  << ", private=" << privVal << std::endl;
    }

protected:
    int protVal;

private:
    int privVal;
};

// ============================================================
// 1. PUBLIC inheritance (most common)
// ============================================================
class PublicDerived : public Base {
public:
    void test() {
        pubVal  = 10;   // OK: public stays public
        protVal = 20;   // OK: protected stays protected (accessible in derived)
        // privVal = 30; // ERROR: private members are never accessible in derived
        std::cout << "  PublicDerived: pubVal=" << pubVal
                  << ", protVal=" << protVal << std::endl;
    }
};

// ============================================================
// 2. PROTECTED inheritance
// ============================================================
class ProtectedDerived : protected Base {
public:
    void test() {
        pubVal  = 10;   // OK: was public, now protected (accessible in derived)
        protVal = 20;   // OK: was protected, stays protected
        // privVal = 30; // ERROR: private is never accessible
        std::cout << "  ProtectedDerived: pubVal=" << pubVal
                  << ", protVal=" << protVal << std::endl;
    }
};

// Class derived from ProtectedDerived -- can still access what's now protected
class GrandchildOfProtected : public ProtectedDerived {
public:
    void test() {
        pubVal  = 100;  // OK: still protected (accessible from further derived)
        protVal = 200;  // OK: still protected
        std::cout << "  GrandchildOfProtected: pubVal=" << pubVal
                  << ", protVal=" << protVal << std::endl;
    }
};

// ============================================================
// 3. PRIVATE inheritance
// ============================================================
class PrivateDerived : private Base {
public:
    void test() {
        pubVal  = 10;   // OK: was public, now private (accessible inside this class)
        protVal = 20;   // OK: was protected, now private
        // privVal = 30; // ERROR: private is never accessible
        std::cout << "  PrivateDerived: pubVal=" << pubVal
                  << ", protVal=" << protVal << std::endl;
    }
};

// Class derived from PrivateDerived -- CANNOT access Base members anymore
class GrandchildOfPrivate : public PrivateDerived {
public:
    void test() {
        // pubVal  = 100;  // ERROR: became private in PrivateDerived
        // protVal = 200;  // ERROR: became private in PrivateDerived
        std::cout << "  GrandchildOfPrivate: cannot access Base members" << std::endl;
    }
};

// ============================================================
// Practical example: Employee hierarchy
// ============================================================
class Employee {
public:
    void getPublicInfo() const {
        std::cout << "  Name: " << name << ", Role: " << role << std::endl;
    }

protected:
    char name[32];
    char role[32];
    double salary;

    void setSalary(double s) { salary = s; }

private:
    char ssn[16];  // Very sensitive -- only Employee itself can access

    void setSSN(const char* s) {
        std::strncpy(ssn, s, 15);
        ssn[15] = '\0';
    }

public:
    Employee(const char* n, const char* r, double s, const char* ssnVal) : salary(s) {
        std::strncpy(name, n, 31); name[31] = '\0';
        std::strncpy(role, r, 31); role[31] = '\0';
        setSSN(ssnVal);
    }
};

class Manager : public Employee {
public:
    Manager(const char* n, double s)
        : Employee(n, "Manager", s, "XXX-XX-XXXX")
    {
    }

    void giveRaise(double amount) {
        // Can access protected members
        salary += amount;
        std::cout << "  " << name << " got a raise! New salary: $" << salary << std::endl;

        // Cannot access private members
        // std::cout << ssn;    // ERROR: ssn is private in Employee
    }
};

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "1. MEMBER ACCESS WITHIN DERIVED CLASSES" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        PublicDerived    pd;
        ProtectedDerived prd;
        PrivateDerived   pvd;

        pd.test();
        prd.test();
        pvd.test();
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "2. EXTERNAL ACCESS (from main)" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        PublicDerived pd;
        pd.pubVal = 42;    // OK: public inheritance keeps pubVal public
        std::cout << "  PublicDerived.pubVal = " << pd.pubVal << std::endl;
        // pd.protVal = 5; // ERROR: protected is not accessible externally

        ProtectedDerived prd;
        // prd.pubVal = 42; // ERROR: protected inheritance made pubVal protected
        std::cout << "  ProtectedDerived.pubVal  // COMPILE ERROR: now protected" << std::endl;

        PrivateDerived pvd;
        // pvd.pubVal = 42; // ERROR: private inheritance made pubVal private
        std::cout << "  PrivateDerived.pubVal    // COMPILE ERROR: now private" << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "3. GRANDCHILD ACCESS" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        GrandchildOfProtected gp;
        gp.test();   // Can access Base members (they became protected)

        GrandchildOfPrivate gv;
        gv.test();   // Cannot access Base members (they became private)
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "4. PRACTICAL: EMPLOYEE HIERARCHY" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        Manager mgr("Alice", 80000.0);
        mgr.getPublicInfo();        // public method -- OK
        mgr.giveRaise(10000.0);
        // mgr.salary;              // ERROR: protected
        // mgr.ssn;                 // ERROR: private (even if it were protected)
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "5. ACCESS RULES SUMMARY TABLE" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    std::cout << "  Base member  | public inh.  | protected inh. | private inh." << std::endl;
    std::cout << "  -------------|--------------|----------------|-------------" << std::endl;
    std::cout << "  public       | public       | protected      | private" << std::endl;
    std::cout << "  protected    | protected    | protected      | private" << std::endl;
    std::cout << "  private      | inaccessible | inaccessible   | inaccessible" << std::endl;
    std::cout << std::endl;
    std::cout << "  Key points:" << std::endl;
    std::cout << "  - 'private' members are NEVER accessible in derived classes" << std::endl;
    std::cout << "  - Inheritance type sets the MAXIMUM visibility of inherited members" << std::endl;
    std::cout << "  - 'public' inheritance is the most common (models IS-A)" << std::endl;
    std::cout << "  - 'private' inheritance models HAS-A / implemented-in-terms-of" << std::endl;

    return 0;
}

// Expected output:
// ========================================
// 1. MEMBER ACCESS WITHIN DERIVED CLASSES
// ========================================
//   PublicDerived: pubVal=10, protVal=20
//   ProtectedDerived: pubVal=10, protVal=20
//   PrivateDerived: pubVal=10, protVal=20
//
// ========================================
// 2. EXTERNAL ACCESS (from main)
// ========================================
//   PublicDerived.pubVal = 42
//   ProtectedDerived.pubVal  // COMPILE ERROR: now protected
//   PrivateDerived.pubVal    // COMPILE ERROR: now private
//
// ========================================
// 3. GRANDCHILD ACCESS
// ========================================
//   GrandchildOfProtected: pubVal=100, protVal=200
//   GrandchildOfPrivate: cannot access Base members
//
// ========================================
// 4. PRACTICAL: EMPLOYEE HIERARCHY
// ========================================
//   Name: Alice, Role: Manager
//   Alice got a raise! New salary: $90000
//
// ========================================
// 5. ACCESS RULES SUMMARY TABLE
// ========================================
//   ...table...
