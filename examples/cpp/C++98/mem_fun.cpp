// CodeNebula - C++98 Example: mem_fun (with pointers)
// Compile: g++ -std=c++98 -Wall -Wextra -o example mem_fun.cpp

#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <string>

class Animal {
    std::string name_;
    int legs_;
public:
    Animal(const std::string& name, int legs) : name_(name), legs_(legs) {}
    void speak() const { std::cout << name_ << " says hello!" << std::endl; }
    int legs() const { return legs_; }
    bool has_four_legs() const { return legs_ == 4; }
};

int main() {
    // mem_fun works with containers of pointers
    std::vector<Animal*> animals;
    Animal cat("Cat", 4);
    Animal bird("Bird", 2);
    Animal dog("Dog", 4);
    Animal spider("Spider", 8);

    animals.push_back(&cat);
    animals.push_back(&bird);
    animals.push_back(&dog);
    animals.push_back(&spider);

    // Call speak() on each animal via mem_fun
    std::cout << "--- All animals speak ---" << std::endl;
    std::for_each(animals.begin(), animals.end(),
                  std::mem_fun(&Animal::speak));

    // Count animals with 4 legs
    int four_legged = std::count_if(animals.begin(), animals.end(),
                                    std::mem_fun(&Animal::has_four_legs));
    std::cout << "Four-legged animals: " << four_legged << std::endl;

    return 0;
}

// Expected output:
// --- All animals speak ---
// Cat says hello!
// Bird says hello!
// Dog says hello!
// Spider says hello!
// Four-legged animals: 2
