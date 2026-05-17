// CodeNebula - C++11 Example: Initializer List Constructors for Containers
// Compile: g++ -std=c++11 -Wall -Wextra -o example initializer_list_support.cpp

// C++11 containers support std::initializer_list constructors, allowing
// brace-enclosed initialization. You can also write custom classes that
// accept initializer_list parameters for flexible initialization.

#include <iostream>
#include <initializer_list>
#include <vector>
#include <map>
#include <set>
#include <string>

// Custom class that accepts initializer_list
class NumberBag {
    std::vector<int> data_;
public:
    NumberBag(std::initializer_list<int> init) : data_(init) {
        std::cout << "Constructed with " << init.size() << " elements" << std::endl;
    }

    void assign(std::initializer_list<int> init) {
        data_.assign(init);
    }

    void print(const std::string& label) const {
        std::cout << label << ": ";
        for (const auto& n : data_) {
            std::cout << n << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    // Vector initialized with brace syntax
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::cout << "Vector: ";
    for (const auto& v : vec) std::cout << v << " ";
    std::cout << std::endl;

    // Set initialized with braces
    std::set<std::string> colors = {"red", "green", "blue"};
    std::cout << "Set: ";
    for (const auto& c : colors) std::cout << c << " ";
    std::cout << std::endl;

    // Map initialized with nested braces
    std::map<std::string, int> scores = {{"Alice", 95}, {"Bob", 87}};
    std::cout << "Map:" << std::endl;
    for (const auto& pair : scores) {
        std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }

    // Custom class with initializer_list
    NumberBag bag = {10, 20, 30, 40};
    bag.print("Bag");

    // Reassign with new initializer list
    bag.assign({100, 200});
    bag.print("Reassigned");

    // Assign to vector with initializer list
    vec = {99, 88, 77};
    std::cout << "Reassigned vector: ";
    for (const auto& v : vec) std::cout << v << " ";
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Vector: 1 2 3 4 5
// Set: blue green red
// Map:
//   Alice: 95
//   Bob: 87
// Constructed with 4 elements
// Bag: 10 20 30 40
// Reassigned: 100 200
// Reassigned vector: 99 88 77
