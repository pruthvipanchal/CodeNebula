// CodeNebula - C++98 Example: Type Casting
// Compile: g++ -std=c++98 -Wall -Wextra -o example type_casting.cpp

// C++98 provides four named cast operators that replace C-style casts with
// explicit, safer alternatives:
//   static_cast    - Compile-time checked conversions (most common)
//   dynamic_cast   - Runtime-checked downcasts in polymorphic hierarchies
//   const_cast     - Add or remove const/volatile qualifiers
//   reinterpret_cast - Low-level bit reinterpretation (dangerous)

#include <iostream>
#include <string>

// ------------------------------------------------------------------
// Class hierarchy for dynamic_cast demonstration
// ------------------------------------------------------------------
class Animal {
public:
    virtual void speak() const {
        std::cout << "  Animal speaks" << std::endl;
    }
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    void speak() const {
        std::cout << "  Dog: Woof!" << std::endl;
    }
    void fetch() const {
        std::cout << "  Dog fetches the ball!" << std::endl;
    }
};

class Cat : public Animal {
public:
    void speak() const {
        std::cout << "  Cat: Meow!" << std::endl;
    }
    void purr() const {
        std::cout << "  Cat purrs..." << std::endl;
    }
};

// ------------------------------------------------------------------
// Function that takes a const reference (for const_cast demo)
// ------------------------------------------------------------------
void legacyModify(int* p) {
    // Imagine this is a legacy C function that doesn't use const
    // but promises not to modify the value (or we know it's safe)
    std::cout << "  legacyModify reads value: " << *p << std::endl;
}

int main() {
    std::cout << "=== C++98 Type Casting ===" << std::endl;

    // =================================================================
    // 1. static_cast - compile-time conversions
    // =================================================================
    std::cout << "\n--- 1. static_cast ---" << std::endl;

    // a) Numeric type conversions
    int i = 65;
    double d = static_cast<double>(i);
    std::cout << "int 65 -> double: " << d << std::endl;
    // Expected: 65

    double pi = 3.14159;
    int truncated = static_cast<int>(pi);
    std::cout << "double 3.14159 -> int: " << truncated << std::endl;
    // Expected: 3

    // b) int to char (ASCII)
    char ch = static_cast<char>(i);
    std::cout << "int 65 -> char: '" << ch << "'" << std::endl;
    // Expected: 'A'

    // c) Enum to int and back
    enum Color { RED, GREEN, BLUE };
    Color c = GREEN;
    int colorVal = static_cast<int>(c);
    std::cout << "GREEN -> int: " << colorVal << std::endl;
    // Expected: 1

    Color backToColor = static_cast<Color>(2);
    std::cout << "int 2 -> Color: " << backToColor << std::endl;
    // Expected: 2 (BLUE)

    // d) Upcast (derived to base) - always safe
    Dog dog;
    Animal* animalPtr = static_cast<Animal*>(&dog);
    animalPtr->speak();
    // Expected: Dog: Woof!

    // e) Downcast with static_cast (unchecked - use only when sure)
    Dog* dogPtr = static_cast<Dog*>(animalPtr);
    dogPtr->fetch();
    // Expected: Dog fetches the ball!

    // f) void* conversions
    int val = 777;
    void* vp = static_cast<void*>(&val);
    int* ip = static_cast<int*>(vp);
    std::cout << "void* round-trip: " << *ip << std::endl;
    // Expected: 777

    // =================================================================
    // 2. dynamic_cast - runtime-checked polymorphic casts
    // =================================================================
    std::cout << "\n--- 2. dynamic_cast ---" << std::endl;

    // Create animals
    Animal* animals[3];
    animals[0] = new Dog();
    animals[1] = new Cat();
    animals[2] = new Dog();

    for (int idx = 0; idx < 3; ++idx) {
        std::cout << "animals[" << idx << "]: ";

        // Try to cast to Dog*
        Dog* dptr = dynamic_cast<Dog*>(animals[idx]);
        if (dptr != 0) {
            std::cout << "is a Dog -> ";
            dptr->fetch();
        }

        // Try to cast to Cat*
        Cat* cptr = dynamic_cast<Cat*>(animals[idx]);
        if (cptr != 0) {
            std::cout << "is a Cat -> ";
            cptr->purr();
        }
    }
    // Expected:
    // animals[0]: is a Dog ->   Dog fetches the ball!
    // animals[1]: is a Cat ->   Cat purrs...
    // animals[2]: is a Dog ->   Dog fetches the ball!

    // dynamic_cast with references (throws std::bad_cast on failure)
    std::cout << "\ndynamic_cast with references:" << std::endl;
    try {
        Animal& ref = *animals[0];
        Dog& dogRef = dynamic_cast<Dog&>(ref);
        dogRef.speak();
        // Expected: Dog: Woof!
    }
    catch (const std::bad_cast& e) {
        std::cout << "bad_cast: " << e.what() << std::endl;
    }

    // Cleanup
    for (int idx = 0; idx < 3; ++idx) {
        delete animals[idx];
    }

    // =================================================================
    // 3. const_cast - add/remove const
    // =================================================================
    std::cout << "\n--- 3. const_cast ---" << std::endl;

    // a) Remove const to pass to a legacy function
    const int constVal = 42;
    int* mutablePtr = const_cast<int*>(&constVal);
    legacyModify(mutablePtr);
    // Expected: legacyModify reads value: 42
    // WARNING: Actually modifying constVal through mutablePtr is undefined behavior!

    // b) A practical use: non-const overload calling const overload
    // (common pattern to avoid code duplication)
    const std::string greeting = "Hello";
    std::string& mutableRef = const_cast<std::string&>(greeting);
    std::cout << "const_cast string: " << mutableRef << std::endl;
    // Expected: Hello

    // c) Adding const (always safe)
    int mutableVal = 100;
    const int* constPtr = const_cast<const int*>(&mutableVal);
    std::cout << "Added const: " << *constPtr << std::endl;
    // Expected: 100

    // =================================================================
    // 4. reinterpret_cast - low-level bit reinterpretation
    // =================================================================
    std::cout << "\n--- 4. reinterpret_cast ---" << std::endl;

    // a) Pointer to integer and back
    int original = 12345;
    int* origPtr = &original;

    // Store pointer value as an integer
    long ptrAsLong = reinterpret_cast<long>(origPtr);
    std::cout << "Pointer as long: " << ptrAsLong << std::endl;

    // Convert back to pointer
    int* recoveredPtr = reinterpret_cast<int*>(ptrAsLong);
    std::cout << "Recovered value: " << *recoveredPtr << std::endl;
    // Expected: 12345

    // b) View bytes of an integer
    int number = 0x41424344;  // ASCII: 'A' 'B' 'C' 'D'
    char* bytes = reinterpret_cast<char*>(&number);
    std::cout << "Bytes of 0x41424344: ";
    for (int b = 0; b < static_cast<int>(sizeof(int)); ++b) {
        std::cout << "0x" << std::hex
                  << (static_cast<int>(bytes[b]) & 0xFF) << " ";
    }
    std::cout << std::dec << std::endl;
    // Output depends on endianness

    // c) Function pointer cast (rare, platform-specific)
    typedef void (*FuncPtr)();
    FuncPtr fp = reinterpret_cast<FuncPtr>(origPtr);
    // We would never call fp - this just shows the cast compiles
    std::cout << "Function pointer cast compiled (not called)." << std::endl;

    // =================================================================
    // 5. Comparison with C-style cast
    // =================================================================
    std::cout << "\n--- 5. C-style vs C++ casts ---" << std::endl;

    double x = 9.99;

    // C-style cast (works but unclear intent)
    int c_style = (int)x;
    std::cout << "C-style (int)9.99 = " << c_style << std::endl;

    // C++ named cast (clear intent, searchable, compiler-checked)
    int cpp_style = static_cast<int>(x);
    std::cout << "static_cast<int>(9.99) = " << cpp_style << std::endl;
    // Both produce: 9

    std::cout << "\nPrefer named casts: they make intent clear and are searchable." << std::endl;

    return 0;
}

/*
Expected Output:
=== C++98 Type Casting ===

--- 1. static_cast ---
int 65 -> double: 65
double 3.14159 -> int: 3
int 65 -> char: 'A'
GREEN -> int: 1
int 2 -> Color: 2
  Dog: Woof!
  Dog fetches the ball!
void* round-trip: 777

--- 2. dynamic_cast ---
animals[0]: is a Dog ->   Dog fetches the ball!
animals[1]: is a Cat ->   Cat purrs...
animals[2]: is a Dog ->   Dog fetches the ball!

dynamic_cast with references:
  Dog: Woof!

--- 3. const_cast ---
  legacyModify reads value: 42
const_cast string: Hello
Added const: 100

--- 4. reinterpret_cast ---
Pointer as long: <address>
Recovered value: 12345
Bytes of 0x41424344: <depends on endianness>
Function pointer cast compiled (not called).

--- 5. C-style vs C++ casts ---
C-style (int)9.99 = 9
static_cast<int>(9.99) = 9

Prefer named casts: they make intent clear and are searchable.
*/
