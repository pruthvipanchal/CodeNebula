// CodeNebula - C++98 Example: Pure Virtual Functions
// Compile: g++ -std=c++98 -Wall -Wextra -o example pure_virtual_functions.cpp
//
// This example demonstrates:
// - Declaring pure virtual functions with = 0
// - Classes with pure virtual functions become abstract (cannot be instantiated)
// - Derived classes MUST override all pure virtuals to be instantiable
// - Using abstract classes as interfaces
// - A pure virtual function CAN have a body (optional default implementation)

#include <iostream>
#include <cstring>

// ============================================================
// 1. Abstract base class: Serializable (interface-like)
// ============================================================
class Serializable {
public:
    virtual ~Serializable() {}

    // Pure virtual: every Serializable object must implement these
    virtual void serialize() const = 0;
    virtual void deserialize(const char* data) = 0;
};

// ============================================================
// 2. Abstract base class: Logger
//    Has a pure virtual with a body (default implementation)
// ============================================================
class Logger {
public:
    virtual ~Logger() {}

    // Pure virtual WITH a body -- derived classes must still override,
    // but can call Logger::log() as a default implementation.
    virtual void log(const char* message) const = 0;

    void logInfo(const char* msg) const {
        std::cout << "  [INFO] ";
        log(msg);  // virtual dispatch
    }
};

// Providing a body for the pure virtual function
// (defined outside the class, as required by the standard)
void Logger::log(const char* message) const {
    std::cout << "[DefaultLogger] " << message << std::endl;
}

// ============================================================
// 3. Abstract base class: Animal (some pure, some concrete)
// ============================================================
class Animal {
protected:
    char name[64];

public:
    Animal(const char* n) {
        std::strncpy(name, n, 63);
        name[63] = '\0';
    }
    virtual ~Animal() {}

    // Pure virtual -- MUST be overridden
    virtual void speak() const = 0;
    virtual void move() const = 0;

    // Concrete (non-pure) -- can be inherited as-is
    void identify() const {
        std::cout << "  I am " << name << std::endl;
    }
};

// ============================================================
// Concrete derived classes
// ============================================================
class Dog : public Animal {
public:
    Dog(const char* n) : Animal(n) {}

    void speak() const {
        std::cout << "  " << name << " says: Woof!" << std::endl;
    }

    void move() const {
        std::cout << "  " << name << " runs on four legs" << std::endl;
    }
};

class Bird : public Animal {
public:
    Bird(const char* n) : Animal(n) {}

    void speak() const {
        std::cout << "  " << name << " says: Tweet!" << std::endl;
    }

    void move() const {
        std::cout << "  " << name << " flies through the air" << std::endl;
    }
};

// PartialAnimal: only overrides speak(), NOT move() -- still abstract!
class PartialAnimal : public Animal {
public:
    PartialAnimal(const char* n) : Animal(n) {}

    void speak() const {
        std::cout << "  " << name << " says: ???" << std::endl;
    }

    // move() is NOT overridden -- PartialAnimal is still abstract
};

// CompleteAnimal: derives from PartialAnimal and provides move()
class CompleteAnimal : public PartialAnimal {
public:
    CompleteAnimal(const char* n) : PartialAnimal(n) {}

    void move() const {
        std::cout << "  " << name << " walks slowly" << std::endl;
    }
};

// ============================================================
// Concrete: ConsoleLogger (implements Logger)
// ============================================================
class ConsoleLogger : public Logger {
public:
    void log(const char* message) const {
        std::cout << "[Console] " << message << std::endl;
    }
};

// FileLogger: uses the base class's default implementation
class FileLogger : public Logger {
public:
    void log(const char* message) const {
        // Use the default implementation from Logger
        std::cout << "  (FileLogger calling Logger::log) ";
        Logger::log(message);
    }
};

// ============================================================
// Concrete: Config (implements Serializable)
// ============================================================
class Config : public Serializable {
private:
    int volume;
    int brightness;

public:
    Config(int v, int b) : volume(v), brightness(b) {}

    void serialize() const {
        std::cout << "  Serialized: vol=" << volume
                  << ",bright=" << brightness << std::endl;
    }

    void deserialize(const char* data) {
        std::cout << "  Deserializing from: \"" << data << "\"" << std::endl;
        // Simplified parsing for demonstration
        volume = 50;
        brightness = 75;
        std::cout << "  Result: vol=" << volume
                  << ", bright=" << brightness << std::endl;
    }
};

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "1. CANNOT INSTANTIATE ABSTRACT CLASS" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        // Animal a("test");       // ERROR: cannot instantiate abstract class
        // Logger l;               // ERROR: same
        // PartialAnimal p("p");   // ERROR: move() is still pure virtual

        std::cout << "  Animal a(\"test\");       // COMPILE ERROR" << std::endl;
        std::cout << "  Logger l;               // COMPILE ERROR" << std::endl;
        std::cout << "  PartialAnimal p(\"p\");   // COMPILE ERROR (move() still pure)" << std::endl;
        std::cout << std::endl;
        std::cout << "  CompleteAnimal c(\"c\");  // OK -- all pure virtuals overridden" << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "2. POLYMORPHISM WITH PURE VIRTUAL FUNCTIONS" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        Dog   d("Rex");
        Bird  b("Tweety");

        // Array of base pointers
        const int COUNT = 2;
        Animal* animals[COUNT];
        animals[0] = &d;
        animals[1] = &b;

        for (int i = 0; i < COUNT; ++i) {
            animals[i]->identify();
            animals[i]->speak();      // pure virtual -- dispatches to derived
            animals[i]->move();       // pure virtual -- dispatches to derived
            std::cout << std::endl;
        }
    }

    std::cout << "========================================" << std::endl;
    std::cout << "3. GRADUAL OVERRIDE (PartialAnimal chain)" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        CompleteAnimal ca("Turtle");
        ca.identify();
        ca.speak();   // from PartialAnimal
        ca.move();    // from CompleteAnimal
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "4. PURE VIRTUAL WITH DEFAULT BODY" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        ConsoleLogger cl;
        FileLogger    fl;

        std::cout << "  ConsoleLogger:" << std::endl;
        cl.logInfo("Application started");

        std::cout << "\n  FileLogger (uses Logger::log default):" << std::endl;
        fl.logInfo("Writing to file");
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "5. INTERFACE PATTERN (Serializable)" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        Config cfg(80, 60);
        Serializable* s = &cfg;   // base pointer

        s->serialize();
        s->deserialize("vol=50,bright=75");
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "6. SUMMARY" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "  - Pure virtual: virtual void f() = 0;" << std::endl;
    std::cout << "  - Makes the class abstract (cannot instantiate)" << std::endl;
    std::cout << "  - Derived MUST override ALL pure virtuals to be concrete" << std::endl;
    std::cout << "  - A pure virtual CAN have a body (optional default)" << std::endl;
    std::cout << "  - Partial override chains: still abstract until all are overridden" << std::endl;

    return 0;
}

// Expected output:
// ========================================
// 1. CANNOT INSTANTIATE ABSTRACT CLASS
// ========================================
//   Animal a("test");       // COMPILE ERROR
//   Logger l;               // COMPILE ERROR
//   PartialAnimal p("p");   // COMPILE ERROR (move() still pure)
//
//   CompleteAnimal c("c");  // OK -- all pure virtuals overridden
//
// ========================================
// 2. POLYMORPHISM WITH PURE VIRTUAL FUNCTIONS
// ========================================
//   I am Rex
//   Rex says: Woof!
//   Rex runs on four legs
//
//   I am Tweety
//   Tweety says: Tweet!
//   Tweety flies through the air
//
// ========================================
// 3. GRADUAL OVERRIDE (PartialAnimal chain)
// ========================================
//   I am Turtle
//   Turtle says: ???
//   Turtle walks slowly
//
// ========================================
// 4. PURE VIRTUAL WITH DEFAULT BODY
// ========================================
//   ConsoleLogger:
//   [INFO] [Console] Application started
//
//   FileLogger (uses Logger::log default):
//   [INFO]   (FileLogger calling Logger::log) [DefaultLogger] Writing to file
//
// ========================================
// 5. INTERFACE PATTERN (Serializable)
// ========================================
//   Serialized: vol=80,bright=60
//   Deserializing from: "vol=50,bright=75"
//   Result: vol=50, bright=75
//
// ========================================
// 6. SUMMARY
// ========================================
//   ...summary text...
