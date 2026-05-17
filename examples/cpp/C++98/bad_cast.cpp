// CodeNebula - C++98 Example: std::bad_cast
// Compile: g++ -std=c++98 -Wall -Wextra -o example bad_cast.cpp

#include <iostream>
#include <typeinfo>

class Base {
public:
    virtual ~Base() {} // must be polymorphic for dynamic_cast
    virtual void identify() const { std::cout << "I am Base" << std::endl; }
};

class Derived : public Base {
public:
    void identify() const { std::cout << "I am Derived" << std::endl; }
    void special() const { std::cout << "Derived-only method" << std::endl; }
};

class Other : public Base {
public:
    void identify() const { std::cout << "I am Other" << std::endl; }
};

int main() {
    Derived d;
    Base& base_ref = d;

    // Successful dynamic_cast with reference
    try {
        Derived& dref = dynamic_cast<Derived&>(base_ref);
        dref.identify();
        dref.special();
    } catch (const std::bad_cast& e) {
        std::cout << "bad_cast: " << e.what() << std::endl;
    }

    // Failed dynamic_cast with reference throws bad_cast
    try {
        Other& oref = dynamic_cast<Other&>(base_ref);
        oref.identify();
    } catch (const std::bad_cast& e) {
        std::cout << "bad_cast: " << e.what() << std::endl;
    }

    // Pointer version returns NULL instead of throwing
    Base* bptr = &d;
    Other* optr = dynamic_cast<Other*>(bptr);
    if (optr == NULL) {
        std::cout << "Pointer cast returned NULL (no exception)" << std::endl;
    }

    return 0;
}

// Expected output:
// I am Derived
// Derived-only method
// bad_cast: <implementation-defined message>
// Pointer cast returned NULL (no exception)
