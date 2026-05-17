// CodeNebula - C++11 Example: std::forward_as_tuple
// Compile: g++ -std=c++11 -Wall -Wextra -o example forward_as_tuple.cpp

// std::forward_as_tuple creates a tuple of references to its arguments,
// preserving value categories (lvalue/rvalue). Useful for passing
// multiple arguments as a single tuple to functions like emplace.

#include <iostream>
#include <tuple>
#include <string>
#include <map>
#include <utility>

// A function that accepts a tuple of forwarding references
void process(std::tuple<int&&, std::string&&> args) {
    std::cout << "Received: " << std::get<0>(args)
              << ", " << std::get<1>(args) << std::endl;
}

// Demonstrate with a multi-argument factory pattern
struct Person {
    std::string first;
    std::string last;
    int age;
    Person(std::string f, std::string l, int a)
        : first(std::move(f)), last(std::move(l)), age(a) {}
};

// Accept forwarded arguments as a tuple
template<typename Tuple>
void print_tuple_size(Tuple&& t) {
    std::cout << "Tuple size: "
              << std::tuple_size<typename std::remove_reference<Tuple>::type>::value
              << std::endl;
    (void)t;
}

int main() {
    // Basic forward_as_tuple with rvalues
    process(std::forward_as_tuple(42, std::string("hello")));

    // forward_as_tuple with lvalues creates reference tuple
    int x = 10;
    std::string name = "world";
    auto ref_tuple = std::forward_as_tuple(x, name);
    std::get<0>(ref_tuple) = 99;      // modifies x
    std::get<1>(ref_tuple) = "modified";  // modifies name
    std::cout << "x = " << x << ", name = " << name << std::endl;

    // Use with map::emplace for piecewise construction
    std::map<std::string, Person> people;
    people.emplace(
        std::piecewise_construct,
        std::forward_as_tuple("employee1"),
        std::forward_as_tuple("John", "Doe", 30)
    );
    auto& p = people["employee1"];
    std::cout << "Person: " << p.first << " " << p.last
              << ", age " << p.age << std::endl;

    // Mixed lvalue and rvalue references
    int a = 5;
    auto mixed = std::forward_as_tuple(a, 100, std::string("temp"));
    std::cout << "Mixed tuple: " << std::get<0>(mixed) << ", "
              << std::get<1>(mixed) << ", "
              << std::get<2>(mixed) << std::endl;

    // Demonstrate tuple size
    print_tuple_size(std::forward_as_tuple(1, 2.0, "three", 'x'));

    return 0;
}

// Expected output:
// Received: 42, hello
// x = 99, name = modified
// Person: John Doe, age 30
// Mixed tuple: 5, 100, temp
// Tuple size: 4
