// CodeNebula - C++11 Example: final Keyword
// Compile: g++ -std=c++11 -Wall -Wextra -o example final_specifier.cpp

// Demonstrates the 'final' specifier for classes and virtual methods.
// 'final' on a class prevents inheritance; on a method, prevents further
// overriding. This enforces design intent and can enable compiler optimizations.

#include <iostream>
#include <string>
#include <memory>

// ------------------------------------------------------------------
// 1. final on virtual methods
// ------------------------------------------------------------------
class Animal {
public:
    virtual std::string speak() const = 0;
    virtual std::string type() const { return "Animal"; }
    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    // Override and mark final: no further overriding allowed
    std::string speak() const override final
    {
        return "Woof!";
    }

    std::string type() const override
    {
        return "Dog";
    }
};

class GoldenRetriever : public Dog {
public:
    // speak() cannot be overridden here (it's final in Dog)
    // std::string speak() const override { return "Bark!"; }  // ERROR!

    // type() can still be overridden (not final)
    std::string type() const override
    {
        return "Golden Retriever";
    }
};

// ------------------------------------------------------------------
// 2. final on classes (prevents inheritance)
// ------------------------------------------------------------------
class Singleton final {
    static Singleton* instance_;
    int value_;

    Singleton(int v) : value_(v) {}

public:
    static Singleton& instance(int v = 0)
    {
        if (!instance_) {
            instance_ = new Singleton(v);
        }
        return *instance_;
    }

    int value() const { return value_; }
    void setValue(int v) { value_ = v; }
};

Singleton* Singleton::instance_ = nullptr;

// class DerivedSingleton : public Singleton {};  // ERROR: Singleton is final

// ------------------------------------------------------------------
// 3. final in a class hierarchy
// ------------------------------------------------------------------
class Base {
public:
    virtual void process() const
    {
        std::cout << "  Base::process" << std::endl;
    }
    virtual void validate() const
    {
        std::cout << "  Base::validate" << std::endl;
    }
    virtual ~Base() = default;
};

class Middle : public Base {
public:
    void process() const override final  // sealed: no further override
    {
        std::cout << "  Middle::process (final)" << std::endl;
    }

    void validate() const override       // still overridable
    {
        std::cout << "  Middle::validate" << std::endl;
    }
};

class Leaf : public Middle {
public:
    // process() is final in Middle, cannot override
    // void process() const override {}   // ERROR!

    void validate() const override
    {
        std::cout << "  Leaf::validate" << std::endl;
    }
};

int main()
{
    // ------------------------------------------------------------------
    // final methods in animal hierarchy
    // ------------------------------------------------------------------
    std::cout << "=== Final methods ===" << std::endl;
    std::unique_ptr<Animal> dog(new Dog());
    std::unique_ptr<Animal> golden(new GoldenRetriever());

    std::cout << "  Dog:    " << dog->type() << " says " << dog->speak() << std::endl;
    std::cout << "  Golden: " << golden->type() << " says " << golden->speak() << std::endl;
    std::cout << "  (speak() is final in Dog -> Golden can't change it)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // final class (Singleton)
    // ------------------------------------------------------------------
    std::cout << "=== Final class ===" << std::endl;
    Singleton& s = Singleton::instance(42);
    std::cout << "  Singleton value: " << s.value() << std::endl;
    std::cout << "  (class Singleton final -> cannot be subclassed)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Hierarchy with selective final
    // ------------------------------------------------------------------
    std::cout << "=== Selective final in hierarchy ===" << std::endl;
    Leaf leaf;
    Base* ptr = &leaf;
    ptr->process();      // Middle::process (final, not overridden in Leaf)
    ptr->validate();     // Leaf::validate (overridden normally)
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Summary
    // ------------------------------------------------------------------
    std::cout << "=== Summary ===" << std::endl;
    std::cout << "  'final' on method: prevents subclass from overriding" << std::endl;
    std::cout << "  'final' on class:  prevents any subclass entirely" << std::endl;
    std::cout << "  Benefit: enforces design + enables devirtualization" << std::endl;

    delete &Singleton::instance();
    return 0;
}

/*
Expected output:

=== Final methods ===
  Dog:    Dog says Woof!
  Golden: Golden Retriever says Woof!
  (speak() is final in Dog -> Golden can't change it)

=== Final class ===
  Singleton value: 42
  (class Singleton final -> cannot be subclassed)

=== Selective final in hierarchy ===
  Middle::process (final)
  Leaf::validate

=== Summary ===
  'final' on method: prevents subclass from overriding
  'final' on class:  prevents any subclass entirely
  Benefit: enforces design + enables devirtualization
*/
