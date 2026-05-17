// CodeNebula - C++98 Example: Virtual Functions
// Compile: g++ -std=c++98 -Wall -Wextra -o example virtual_functions.cpp
//
// This example demonstrates:
// - Declaring virtual functions in a base class
// - Overriding in derived classes
// - How virtual dispatch works (vtable concept)
// - Difference between virtual and non-virtual calls
// - Calling the base version from a derived override
// - Cost: virtual functions have a small overhead (vtable pointer)

#include <iostream>
#include <cstring>

// ============================================================
// Base class: Instrument
// ============================================================
class Instrument {
private:
    char name[64];

public:
    Instrument(const char* n) {
        std::strncpy(name, n, 63);
        name[63] = '\0';
    }

    virtual ~Instrument() {}

    const char* getName() const { return name; }

    // --- Virtual functions ---
    virtual void play() const {
        std::cout << "  [Instrument] " << name << " makes a sound" << std::endl;
    }

    virtual void tune() const {
        std::cout << "  [Instrument] Tuning " << name << "..." << std::endl;
    }

    // --- Non-virtual function (static dispatch always) ---
    void description() const {
        std::cout << "  Generic instrument: " << name << std::endl;
    }
};

// ============================================================
// Derived: Piano
// ============================================================
class Piano : public Instrument {
public:
    Piano() : Instrument("Piano") {}

    // Override virtual function
    void play() const {
        std::cout << "  [Piano] Playing elegant piano notes..." << std::endl;
    }

    void tune() const {
        // Can call base version explicitly
        Instrument::tune();
        std::cout << "  [Piano] Adjusting 88 keys..." << std::endl;
    }

    // Hides (not overrides) the non-virtual description()
    void description() const {
        std::cout << "  A grand piano with 88 keys" << std::endl;
    }
};

// ============================================================
// Derived: Guitar
// ============================================================
class Guitar : public Instrument {
private:
    int strings;

public:
    Guitar(int s) : Instrument("Guitar"), strings(s) {}

    void play() const {
        std::cout << "  [Guitar] Strumming " << strings << " strings..." << std::endl;
    }

    void tune() const {
        Instrument::tune();
        std::cout << "  [Guitar] Tuning " << strings << " strings one by one..." << std::endl;
    }

    void description() const {
        std::cout << "  A guitar with " << strings << " strings" << std::endl;
    }
};

// ============================================================
// Derived: Drums
// ============================================================
class Drums : public Instrument {
public:
    Drums() : Instrument("Drums") {}

    void play() const {
        std::cout << "  [Drums] BOOM BAP BOOM BAP!" << std::endl;
    }

    // tune() NOT overridden -- uses Instrument::tune()
};

// ============================================================
// A function demonstrating virtual dispatch
// ============================================================
void perform(const Instrument& inst) {
    std::cout << "  Performing with: " << inst.getName() << std::endl;
    inst.play();         // VIRTUAL dispatch -- calls the derived version
    inst.description();  // NON-VIRTUAL -- always calls Instrument::description()
    std::cout << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "1. VIRTUAL DISPATCH IN ACTION" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        Piano  p;
        Guitar g(6);
        Drums  d;

        // Same function, different behaviour at runtime
        perform(p);
        perform(g);
        perform(d);  // Drums::play() is called; description() is Instrument's
    }

    std::cout << "========================================" << std::endl;
    std::cout << "2. VIRTUAL vs NON-VIRTUAL THROUGH POINTER" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        Piano piano;
        Instrument* ptr = &piano;

        std::cout << "  Through Instrument* pointer:" << std::endl;
        ptr->play();          // Virtual -> Piano::play()
        ptr->description();   // Non-virtual -> Instrument::description()

        std::cout << "\n  Through Piano object directly:" << std::endl;
        piano.play();         // Piano::play()
        piano.description();  // Piano::description() (static dispatch to Piano)
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "3. CALLING BASE VERSION FROM OVERRIDE" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        Piano p;
        Guitar g(12);

        std::cout << "  Piano::tune() calls Instrument::tune() first:" << std::endl;
        p.tune();

        std::cout << "\n  Guitar::tune() calls Instrument::tune() first:" << std::endl;
        g.tune();
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "4. DRUMS: INHERITING BASE VIRTUAL FUNCTION" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        Drums d;
        Instrument* ptr = &d;

        std::cout << "  Drums overrides play():" << std::endl;
        ptr->play();    // Drums::play()

        std::cout << "  Drums does NOT override tune():" << std::endl;
        ptr->tune();    // Instrument::tune() (inherited)
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "5. VTABLE CONCEPT (educational)" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "  When a class has virtual functions, the compiler creates" << std::endl;
    std::cout << "  a 'vtable' -- a table of function pointers for that class." << std::endl;
    std::cout << std::endl;
    std::cout << "  Each object contains a hidden 'vptr' pointing to its" << std::endl;
    std::cout << "  class's vtable. This is how virtual dispatch works:" << std::endl;
    std::cout << std::endl;
    std::cout << "    ptr->play()  -->  vptr->vtable[play_slot]  -->  Piano::play()" << std::endl;
    std::cout << std::endl;
    std::cout << "  Size overhead: one pointer per object (vptr)." << std::endl;
    std::cout << "  Time overhead: one indirection per virtual call." << std::endl;
    std::cout << std::endl;
    {
        std::cout << "  sizeof(Instrument): " << sizeof(Instrument) << " bytes" << std::endl;
        std::cout << "  sizeof(Piano):      " << sizeof(Piano) << " bytes" << std::endl;
        std::cout << "  sizeof(Guitar):     " << sizeof(Guitar) << " bytes" << std::endl;
        std::cout << "  (Sizes include the hidden vptr)" << std::endl;
    }

    return 0;
}

// Expected output (sizes are platform-dependent):
// ========================================
// 1. VIRTUAL DISPATCH IN ACTION
// ========================================
//   Performing with: Piano
//   [Piano] Playing elegant piano notes...
//   Generic instrument: Piano
//
//   Performing with: Guitar
//   [Guitar] Strumming 6 strings...
//   Generic instrument: Guitar
//
//   Performing with: Drums
//   [Drums] BOOM BAP BOOM BAP!
//   Generic instrument: Drums
//
// ========================================
// 2. VIRTUAL vs NON-VIRTUAL THROUGH POINTER
// ========================================
//   Through Instrument* pointer:
//   [Piano] Playing elegant piano notes...
//   Generic instrument: Piano
//
//   Through Piano object directly:
//   [Piano] Playing elegant piano notes...
//   A grand piano with 88 keys
//
// ========================================
// 3. CALLING BASE VERSION FROM OVERRIDE
// ========================================
//   Piano::tune() calls Instrument::tune() first:
//   [Instrument] Tuning Piano...
//   [Piano] Adjusting 88 keys...
//   ...
//
// ========================================
// 4. DRUMS: INHERITING BASE VIRTUAL FUNCTION
// ========================================
//   Drums overrides play():
//   [Drums] BOOM BAP BOOM BAP!
//   Drums does NOT override tune():
//   [Instrument] Tuning Drums...
//
// ========================================
// 5. VTABLE CONCEPT (educational)
// ========================================
//   ...vtable explanation and sizes...
