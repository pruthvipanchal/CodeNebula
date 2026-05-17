// CodeNebula - C++11 Example: is_base_of
// Compile: g++ -std=c++11 -Wall -Wextra -o example is_base_of.cpp

// Demonstrates std::is_base_of to check inheritance relationships.
// is_base_of<Base, Derived>::value is true if Base is a base class of Derived.

#include <iostream>
#include <type_traits>

class Animal {};
class Dog : public Animal {};
class GoldenRetriever : public Dog {};
class Cat : public Animal {};
class Unrelated {};

int main() {
    std::cout << "=== std::is_base_of ===" << std::endl;

    std::cout << "Animal -> Dog:             "
              << std::is_base_of<Animal, Dog>::value << std::endl;
    std::cout << "Animal -> GoldenRetriever: "
              << std::is_base_of<Animal, GoldenRetriever>::value << std::endl;
    std::cout << "Dog -> GoldenRetriever:    "
              << std::is_base_of<Dog, GoldenRetriever>::value << std::endl;
    std::cout << "Animal -> Cat:             "
              << std::is_base_of<Animal, Cat>::value << std::endl;
    std::cout << "Dog -> Cat:                "
              << std::is_base_of<Dog, Cat>::value << std::endl;
    std::cout << "Animal -> Unrelated:       "
              << std::is_base_of<Animal, Unrelated>::value << std::endl;

    // A class is a base of itself
    std::cout << "Animal -> Animal:          "
              << std::is_base_of<Animal, Animal>::value << std::endl;

    static_assert(std::is_base_of<Animal, Dog>::value, "Animal is base of Dog");
    static_assert(!std::is_base_of<Dog, Cat>::value, "Dog is not base of Cat");
    static_assert(std::is_base_of<Animal, Animal>::value, "A class is base of itself");

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::is_base_of ===
// Animal -> Dog:             1
// Animal -> GoldenRetriever: 1
// Dog -> GoldenRetriever:    1
// Animal -> Cat:             1
// Dog -> Cat:                0
// Animal -> Unrelated:       0
// Animal -> Animal:          1
//
// All checks passed!
