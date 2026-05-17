// CodeNebula - C++20 Example: std::derived_from Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example derived_from.cpp

// std::derived_from<Derived, Base> checks whether Derived is publicly
// and unambiguously derived from Base, or is the same type as Base.

#include <concepts>
#include <iostream>
#include <string>

struct Animal {
    virtual std::string speak() const { return "..."; }
    virtual ~Animal() = default;
};

struct Dog : public Animal {
    std::string speak() const override { return "Woof!"; }
};

struct Cat : public Animal {
    std::string speak() const override { return "Meow!"; }
};

struct Robot {};  // Not derived from Animal

// Function constrained to accept only Animal-derived types
template <std::derived_from<Animal> T>
void make_speak(const T& creature) {
    std::cout << "The creature says: " << creature.speak() << "\n";
}

// Factory function returning any Animal subclass
template <typename T>
    requires std::derived_from<T, Animal>
T create_animal() {
    return T{};
}

int main() {
    Dog dog;
    Cat cat;

    // Use constrained function
    make_speak(dog);
    make_speak(cat);
    // make_speak(Robot{});  // Compile error: Robot not derived from Animal

    // Use factory
    auto d = create_animal<Dog>();
    std::cout << "Factory dog says: " << d.speak() << "\n";

    // Compile-time checks
    std::cout << "Dog derived from Animal: "
              << std::derived_from<Dog, Animal> << "\n";
    std::cout << "Animal derived from Animal: "
              << std::derived_from<Animal, Animal> << "\n";
    std::cout << "Robot derived from Animal: "
              << std::derived_from<Robot, Animal> << "\n";
    std::cout << "int derived from Animal: "
              << std::derived_from<int, Animal> << "\n";

    return 0;
}

// Expected output:
// The creature says: Woof!
// The creature says: Meow!
// Factory dog says: Woof!
// Dog derived from Animal: 1
// Animal derived from Animal: 1
// Robot derived from Animal: 0
// int derived from Animal: 0
