// CodeNebula - C++11 Example: Emplace Operations for Containers
// Compile: g++ -std=c++11 -Wall -Wextra -o example emplace_operations.cpp

// emplace_back and emplace construct elements in-place, avoiding unnecessary
// copies or moves. They forward arguments directly to the element's constructor,
// which is more efficient than push_back or insert with a temporary object.

#include <iostream>
#include <vector>
#include <map>
#include <string>

struct Person {
    std::string name;
    int age;

    Person(const std::string& n, int a) : name(n), age(a) {
        std::cout << "  Constructed: " << name << std::endl;
    }
    Person(const Person& other) : name(other.name), age(other.age) {
        std::cout << "  Copied: " << name << std::endl;
    }
    Person(Person&& other) noexcept : name(std::move(other.name)), age(other.age) {
        std::cout << "  Moved: " << name << std::endl;
    }
};

int main() {
    std::vector<Person> people;
    people.reserve(3);  // prevent reallocation

    // push_back requires creating a temporary, then moving it
    std::cout << "push_back:" << std::endl;
    people.push_back(Person("Alice", 30));

    // emplace_back constructs directly in the container
    std::cout << "emplace_back:" << std::endl;
    people.emplace_back("Bob", 25);

    // emplace for maps - construct key-value pair in-place
    std::cout << "\nMap emplace:" << std::endl;
    std::map<int, Person> directory;
    directory.emplace(1, Person("Charlie", 35));

    // emplace with piecewise_construct for maps
    std::cout << "Piecewise emplace:" << std::endl;
    directory.emplace(std::piecewise_construct,
                      std::forward_as_tuple(2),
                      std::forward_as_tuple("Dave", 28));

    // Print results
    std::cout << "\nPeople in vector:" << std::endl;
    for (const auto& p : people) {
        std::cout << "  " << p.name << " (age " << p.age << ")" << std::endl;
    }

    std::cout << "People in map:" << std::endl;
    for (const auto& pair : directory) {
        std::cout << "  #" << pair.first << ": " << pair.second.name
                  << " (age " << pair.second.age << ")" << std::endl;
    }

    return 0;
}

// Expected output (may vary slightly by compiler):
// push_back:
//   Constructed: Alice
//   Moved: Alice
// emplace_back:
//   Constructed: Bob
//
// Map emplace:
//   Constructed: Charlie
//   Moved: Charlie
// Piecewise emplace:
//   Constructed: Dave
//
// People in vector:
//   Alice (age 30)
//   Bob (age 25)
// People in map:
//   #1: Charlie (age 35)
//   #2: Dave (age 28)
