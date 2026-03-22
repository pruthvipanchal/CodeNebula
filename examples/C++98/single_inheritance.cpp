// CodeNebula - C++98 Example: Single Inheritance
// Compile: g++ -std=c++98 -Wall -Wextra -o example single_inheritance.cpp
//
// This example demonstrates:
// - Deriving a class from a single base class
// - Constructor chaining (base constructed before derived)
// - Destructor order (derived destroyed before base)
// - Member access: inherited public/protected members
// - Method overriding (non-virtual, to show hiding)
// - Using base-class functionality in derived class

#include <iostream>
#include <cstring>
#include <cstdio>

// ============================================================
// Base class: Animal
// ============================================================
class Animal {
private:
    char name[64];
    int  age;

protected:
    // Protected: accessible by derived classes, not by outsiders
    int legs;

public:
    // Constructor
    Animal(const char* n, int a, int l) : age(a), legs(l) {
        std::strncpy(name, n, 63);
        name[63] = '\0';
        std::cout << "  Animal constructor: " << name << std::endl;
    }

    // Destructor
    ~Animal() {
        std::cout << "  Animal destructor: " << name << std::endl;
    }

    // Public accessors
    const char* getName() const { return name; }
    int getAge() const { return age; }

    // A method that derived classes may override (non-virtual here)
    void speak() const {
        std::cout << "  " << name << " says: ..." << std::endl;
    }

    void describe() const {
        std::cout << "  Name: " << name
                  << ", Age: " << age
                  << ", Legs: " << legs << std::endl;
    }
};

// ============================================================
// Derived class: Dog (inherits from Animal)
// ============================================================
class Dog : public Animal {
private:
    char breed[64];

public:
    // Derived constructor calls base constructor in initialiser list
    Dog(const char* n, int a, const char* b)
        : Animal(n, a, 4)   // <-- base constructor called first
    {
        std::strncpy(breed, b, 63);
        breed[63] = '\0';
        std::cout << "  Dog constructor: " << getName()
                  << " (" << breed << ")" << std::endl;
    }

    ~Dog() {
        std::cout << "  Dog destructor: " << getName() << std::endl;
    }

    // Override speak (hides base version -- not virtual dispatch)
    void speak() const {
        std::cout << "  " << getName() << " says: Woof! Woof!" << std::endl;
    }

    void fetch() const {
        std::cout << "  " << getName() << " fetches the ball!" << std::endl;
    }

    void describeBreed() const {
        std::cout << "  Breed: " << breed << std::endl;
        // 'legs' is accessible because it is protected in Animal
        std::cout << "  Legs (from base): " << legs << std::endl;
    }
};

// ============================================================
// Derived class: Snake (inherits from Animal)
// ============================================================
class Snake : public Animal {
private:
    double lengthMeters;

public:
    Snake(const char* n, int a, double len)
        : Animal(n, a, 0), lengthMeters(len)
    {
        std::cout << "  Snake constructor: " << getName() << std::endl;
    }

    ~Snake() {
        std::cout << "  Snake destructor: " << getName() << std::endl;
    }

    void speak() const {
        std::cout << "  " << getName() << " says: Hissss!" << std::endl;
    }

    void describeLength() const {
        std::cout << "  Length: " << lengthMeters << " meters" << std::endl;
    }
};

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "1. CONSTRUCTOR CHAINING" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "  (Base Animal is constructed BEFORE derived Dog)\n" << std::endl;
    {
        Dog rex("Rex", 5, "German Shepherd");
        std::cout << std::endl;
    }
    std::cout << "  (Dog destroyed BEFORE Animal -- reverse order)\n" << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "2. INHERITED MEMBERS" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        Dog buddy("Buddy", 3, "Labrador");
        std::cout << std::endl;

        // Using inherited public method
        buddy.describe();

        // Using derived-specific methods
        buddy.describeBreed();
        buddy.fetch();
        std::cout << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "3. METHOD OVERRIDING (non-virtual)" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        Dog   d("Max", 4, "Poodle");
        Snake s("Kaa", 8, 3.5);
        std::cout << std::endl;

        // Calls Dog::speak() -- hides Animal::speak()
        d.speak();

        // Calls Snake::speak()
        s.speak();

        // Can still call base version explicitly
        std::cout << "\n  Calling Animal::speak() explicitly on Dog:" << std::endl;
        d.Animal::speak();

        std::cout << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "4. USING BASE POINTER (no virtual -- static dispatch)" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        Dog d("Fido", 2, "Beagle");
        std::cout << std::endl;

        Animal* aPtr = &d;  // base pointer to derived object

        // This calls Animal::speak(), NOT Dog::speak()
        // because speak() is not virtual
        aPtr->speak();
        std::cout << "  (Called Animal::speak() -- no virtual dispatch)" << std::endl;

        // Inherited public methods work fine
        aPtr->describe();
        std::cout << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "5. MULTIPLE DERIVED OBJECTS" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        Dog   d("Lucky", 6, "Dalmatian");
        Snake s("Naga", 12, 4.2);
        std::cout << std::endl;

        d.describe();
        d.describeBreed();
        d.speak();

        std::cout << std::endl;

        s.describe();
        s.describeLength();
        s.speak();
        std::cout << std::endl;
    }

    return 0;
}

// Expected output:
// ========================================
// 1. CONSTRUCTOR CHAINING
// ========================================
//   (Base Animal is constructed BEFORE derived Dog)
//
//   Animal constructor: Rex
//   Dog constructor: Rex (German Shepherd)
//
//   Dog destructor: Rex
//   Animal destructor: Rex
//   (Dog destroyed BEFORE Animal -- reverse order)
//
// ========================================
// 2. INHERITED MEMBERS
// ========================================
//   Animal constructor: Buddy
//   Dog constructor: Buddy (Labrador)
//
//   Name: Buddy, Age: 3, Legs: 4
//   Breed: Labrador
//   Legs (from base): 4
//   Buddy fetches the ball!
//
//   Dog destructor: Buddy
//   Animal destructor: Buddy
//
// ========================================
// 3. METHOD OVERRIDING (non-virtual)
// ========================================
//   ...constructor output...
//   Max says: Woof! Woof!
//   Kaa says: Hissss!
//   Calling Animal::speak() explicitly on Dog:
//   Max says: ...
//   ...destructor output...
//
// ========================================
// 4. USING BASE POINTER (no virtual -- static dispatch)
// ========================================
//   ...constructor output...
//   Fido says: ...
//   (Called Animal::speak() -- no virtual dispatch)
//   Name: Fido, Age: 2, Legs: 4
//   ...destructor output...
//
// ========================================
// 5. MULTIPLE DERIVED OBJECTS
// ========================================
//   ...object descriptions...
