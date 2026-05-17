// CodeNebula - C++98 Example: Destructors
// Compile: g++ -std=c++98 -Wall -Wextra -o example destructors.cpp
//
// This example demonstrates:
// - How destructors are called automatically when objects leave scope
// - Resource cleanup (heap memory, simulated file handles)
// - Destruction order: reverse of construction order
// - Destructors in inheritance hierarchies (virtual destructor importance)

#include <iostream>
#include <cstring>

// ============================================================
// 1. Basic destructor with resource cleanup
// ============================================================
class ManagedBuffer {
private:
    char* buffer;
    int   capacity;
    const char* label;

public:
    ManagedBuffer(const char* lbl, int cap)
        : buffer(new char[cap]), capacity(cap), label(lbl)
    {
        std::memset(buffer, 0, capacity);
        std::cout << "  [ManagedBuffer \"" << label
                  << "\"] Constructed (" << capacity << " bytes)" << std::endl;
    }

    ~ManagedBuffer() {
        std::cout << "  [ManagedBuffer \"" << label
                  << "\"] Destructor: freeing " << capacity << " bytes" << std::endl;
        delete[] buffer;
    }

    void write(const char* text) {
        std::strncpy(buffer, text, capacity - 1);
        buffer[capacity - 1] = '\0';
    }

    void print() const {
        std::cout << "  [ManagedBuffer \"" << label << "\"] content: \""
                  << buffer << "\"" << std::endl;
    }
};

// ============================================================
// 2. Destruction order demonstration
// ============================================================
class OrderTracker {
private:
    int id;

public:
    OrderTracker(int i) : id(i) {
        std::cout << "  OrderTracker #" << id << " constructed" << std::endl;
    }

    ~OrderTracker() {
        std::cout << "  OrderTracker #" << id << " DESTROYED" << std::endl;
    }
};

// ============================================================
// 3. Virtual destructor in inheritance
// ============================================================
class Base {
private:
    int* baseData;

public:
    Base() : baseData(new int(42)) {
        std::cout << "  Base constructor (allocated baseData)" << std::endl;
    }

    // Virtual destructor ensures derived destructor is called
    // when deleting through a Base pointer.
    virtual ~Base() {
        std::cout << "  Base destructor (freeing baseData)" << std::endl;
        delete baseData;
    }

    virtual void describe() const {
        std::cout << "  I am Base, baseData = " << *baseData << std::endl;
    }
};

class Derived : public Base {
private:
    int* derivedData;

public:
    Derived() : Base(), derivedData(new int(99)) {
        std::cout << "  Derived constructor (allocated derivedData)" << std::endl;
    }

    ~Derived() {
        std::cout << "  Derived destructor (freeing derivedData)" << std::endl;
        delete derivedData;
    }

    void describe() const {
        std::cout << "  I am Derived, derivedData = " << *derivedData << std::endl;
    }
};

// ============================================================
// 4. Non-virtual destructor problem (for educational contrast)
// ============================================================
class BadBase {
public:
    BadBase()  { std::cout << "  BadBase constructed" << std::endl; }
    // NOTE: destructor is NOT virtual on purpose -- this is the bug
    ~BadBase() { std::cout << "  BadBase destructor" << std::endl; }
};

class BadDerived : public BadBase {
private:
    int* leak;

public:
    BadDerived() : BadBase(), leak(new int(7)) {
        std::cout << "  BadDerived constructed (allocated leak)" << std::endl;
    }

    ~BadDerived() {
        std::cout << "  BadDerived destructor (freeing leak)" << std::endl;
        delete leak;
    }
};

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "1. BASIC DESTRUCTOR & RESOURCE CLEANUP" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        ManagedBuffer buf("demo", 64);
        buf.write("Hello, C++98!");
        buf.print();
        std::cout << "  -- leaving scope --" << std::endl;
    }
    std::cout << "  (buffer has been freed)\n" << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "2. DESTRUCTION ORDER (reverse of construction)" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        OrderTracker a(1);
        OrderTracker b(2);
        OrderTracker c(3);
        std::cout << "  -- leaving scope --" << std::endl;
    }
    std::cout << "  (destroyed 3, 2, 1 -- reverse order)\n" << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "3. VIRTUAL DESTRUCTOR (correct cleanup)" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        std::cout << "  Creating Derived via Base pointer:" << std::endl;
        Base* ptr = new Derived();
        ptr->describe();
        std::cout << "  Deleting via Base pointer:" << std::endl;
        delete ptr;  // Calls ~Derived() then ~Base() thanks to virtual
    }
    std::cout << "  (Both Derived and Base destructors ran)\n" << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "4. NON-VIRTUAL DESTRUCTOR (memory leak!)" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        std::cout << "  Creating BadDerived via BadBase pointer:" << std::endl;
        BadBase* ptr = new BadDerived();
        std::cout << "  Deleting via BadBase pointer:" << std::endl;
        delete ptr;  // Only ~BadBase() runs! ~BadDerived() is SKIPPED -> leak
    }
    std::cout << "  (Only BadBase destructor ran -- BadDerived leaked!)" << std::endl;
    std::cout << "  LESSON: Always make base-class destructors virtual" << std::endl;
    std::cout << "  if the class will be used polymorphically.\n" << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "5. MEMBER OBJECTS DESTRUCTION ORDER" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        std::cout << "  Creating two ManagedBuffers in a scope:" << std::endl;
        ManagedBuffer first("first", 32);
        ManagedBuffer second("second", 16);
        first.write("I was created first");
        second.write("I was created second");
        first.print();
        second.print();
        std::cout << "  -- leaving scope --" << std::endl;
    }
    std::cout << "  (\"second\" destroyed before \"first\")" << std::endl;

    return 0;
}

// Expected output (addresses will vary):
// ========================================
// 1. BASIC DESTRUCTOR & RESOURCE CLEANUP
// ========================================
//   [ManagedBuffer "demo"] Constructed (64 bytes)
//   [ManagedBuffer "demo"] content: "Hello, C++98!"
//   -- leaving scope --
//   [ManagedBuffer "demo"] Destructor: freeing 64 bytes
//   (buffer has been freed)
//
// ========================================
// 2. DESTRUCTION ORDER (reverse of construction)
// ========================================
//   OrderTracker #1 constructed
//   OrderTracker #2 constructed
//   OrderTracker #3 constructed
//   -- leaving scope --
//   OrderTracker #3 DESTROYED
//   OrderTracker #2 DESTROYED
//   OrderTracker #1 DESTROYED
//   (destroyed 3, 2, 1 -- reverse order)
//
// ========================================
// 3. VIRTUAL DESTRUCTOR (correct cleanup)
// ========================================
//   Creating Derived via Base pointer:
//   Base constructor (allocated baseData)
//   Derived constructor (allocated derivedData)
//   I am Derived, derivedData = 99
//   Deleting via Base pointer:
//   Derived destructor (freeing derivedData)
//   Base destructor (freeing baseData)
//   (Both Derived and Base destructors ran)
//
// ========================================
// 4. NON-VIRTUAL DESTRUCTOR (memory leak!)
// ========================================
//   Creating BadDerived via BadBase pointer:
//   BadBase constructed
//   BadDerived constructed (allocated leak)
//   Deleting via BadBase pointer:
//   BadBase destructor
//   (Only BadBase destructor ran -- BadDerived leaked!)
//   LESSON: Always make base-class destructors virtual
//   if the class will be used polymorphically.
//
// ========================================
// 5. MEMBER OBJECTS DESTRUCTION ORDER
// ========================================
//   Creating two ManagedBuffers in a scope:
//   [ManagedBuffer "first"] Constructed (32 bytes)
//   [ManagedBuffer "second"] Constructed (16 bytes)
//   [ManagedBuffer "first"] content: "I was created first"
//   [ManagedBuffer "second"] content: "I was created second"
//   -- leaving scope --
//   [ManagedBuffer "second"] Destructor: freeing 16 bytes
//   [ManagedBuffer "first"] Destructor: freeing 32 bytes
//   ("second" destroyed before "first")
