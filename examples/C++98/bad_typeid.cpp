// CodeNebula - C++98 Example: std::bad_typeid
// Compile: g++ -std=c++98 -Wall -Wextra -o example bad_typeid.cpp

#include <iostream>
#include <typeinfo>

class Base {
public:
    virtual ~Base() {} // polymorphic
};

class Derived : public Base {};

int main() {
    // Normal typeid usage
    Derived d;
    Base* bptr = &d;
    std::cout << "typeid(*bptr): " << typeid(*bptr).name() << std::endl;

    // typeid on a dereferenced null pointer to a polymorphic type
    // throws std::bad_typeid
    Base* null_ptr = NULL;
    try {
        // Dereferencing null pointer in typeid for polymorphic type
        std::cout << "typeid(*null): " << typeid(*null_ptr).name() << std::endl;
    } catch (const std::bad_typeid& e) {
        std::cout << "bad_typeid caught: " << e.what() << std::endl;
    }

    // typeid on a non-dereferenced pointer does NOT throw
    // (it gives the type of the pointer itself)
    std::cout << "typeid(null_ptr): " << typeid(null_ptr).name() << std::endl;

    // typeid comparison
    Base b;
    std::cout << "Same type: " << (typeid(*bptr) == typeid(d)) << std::endl;
    std::cout << "Different: " << (typeid(b) == typeid(d)) << std::endl;

    return 0;
}

// Expected output (type names are implementation-defined):
// typeid(*bptr): <mangled name for Derived>
// bad_typeid caught: <implementation-defined message>
// typeid(null_ptr): <mangled name for Base*>
// Same type: 1
// Different: 0
