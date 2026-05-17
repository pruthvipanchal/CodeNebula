// CodeNebula - C++11 Example: std::type_index
// Compile: g++ -std=c++11 -Wall -Wextra -o example type_index.cpp

// std::type_index is a wrapper around std::type_info that can be used
// as a key in associative containers. Unlike type_info, type_index
// is copyable and supports comparison and hashing.

#include <iostream>
#include <typeindex>
#include <typeinfo>
#include <map>
#include <unordered_map>
#include <string>
#include <memory>

// A simple type registry / factory pattern
class Animal {
public:
    virtual ~Animal() = default;
    virtual std::string speak() const = 0;
};

class Dog : public Animal {
public:
    std::string speak() const override { return "Woof!"; }
};

class Cat : public Animal {
public:
    std::string speak() const override { return "Meow!"; }
};

class Bird : public Animal {
public:
    std::string speak() const override { return "Tweet!"; }
};

int main() {
    // type_index from typeid
    std::type_index ti_int = typeid(int);
    std::type_index ti_double = typeid(double);
    std::type_index ti_string = typeid(std::string);

    std::cout << "type_index names:" << std::endl;
    std::cout << "  int:    " << ti_int.name() << std::endl;
    std::cout << "  double: " << ti_double.name() << std::endl;
    std::cout << "  string: " << ti_string.name() << std::endl;

    // Use as map key -- store type metadata
    std::map<std::type_index, std::string> type_names;
    type_names[typeid(int)] = "integer";
    type_names[typeid(double)] = "double";
    type_names[typeid(std::string)] = "string";
    type_names[typeid(Dog)] = "Dog";
    type_names[typeid(Cat)] = "Cat";

    std::cout << "\nType registry (ordered map):" << std::endl;
    for (const auto& kv : type_names) {
        std::cout << "  " << kv.first.name() << " -> " << kv.second << std::endl;
    }

    // Use in unordered_map (type_index has std::hash specialization)
    std::unordered_map<std::type_index, std::string> sounds;
    sounds[typeid(Dog)] = "Woof";
    sounds[typeid(Cat)] = "Meow";
    sounds[typeid(Bird)] = "Tweet";

    // Lookup by runtime type
    std::unique_ptr<Animal> pet = std::make_unique<Cat>();
    auto it = sounds.find(typeid(*pet));
    if (it != sounds.end()) {
        std::cout << "\nRuntime type lookup: " << it->second << std::endl;
    }

    // Comparison operators
    std::type_index a = typeid(int);
    std::type_index b = typeid(int);
    std::type_index c = typeid(double);
    std::cout << "\nComparisons:" << std::endl;
    std::cout << "  int == int:    " << (a == b ? "true" : "false") << std::endl;
    std::cout << "  int == double: " << (a == c ? "true" : "false") << std::endl;
    std::cout << "  int != double: " << (a != c ? "true" : "false") << std::endl;

    // Hash values
    std::cout << "\nHash values:" << std::endl;
    std::cout << "  hash(int):    " << std::type_index(typeid(int)).hash_code() << std::endl;
    std::cout << "  hash(double): " << std::type_index(typeid(double)).hash_code() << std::endl;

    return 0;
}

// Expected output (mangled names vary by compiler):
// type_index names:
//   int:    i
//   double: d
//   string: NSt7...
//
// Type registry (ordered map):
//   ... -> integer
//   ... -> double
//   ... -> string
//   ... -> Dog
//   ... -> Cat
//
// Runtime type lookup: Meow
//
// Comparisons:
//   int == int:    true
//   int == double: false
//   int != double: true
//
// Hash values:
//   hash(int):    <some hash>
//   hash(double): <some hash>
