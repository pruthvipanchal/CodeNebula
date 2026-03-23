// CodeNebula - C++11 Example: std::mem_fn
// Compile: g++ -std=c++11 -Wall -Wextra -o example mem_fn.cpp

// std::mem_fn creates a callable wrapper from a pointer to member
// function or data member. Unlike std::bind, it doesn't fix any
// arguments -- the object is passed at call time.

#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>

struct Employee {
    std::string name;
    int salary;

    void greet() const {
        std::cout << "Hi, I'm " << name << std::endl;
    }

    int bonus(int percent) const {
        return salary * percent / 100;
    }

    bool earns_more_than(int threshold) const {
        return salary > threshold;
    }
};

int main() {
    // Basic mem_fn with member function
    auto greet = std::mem_fn(&Employee::greet);
    Employee alice{"Alice", 80000};
    greet(alice);  // pass object as first argument

    // mem_fn with member function taking arguments
    auto bonus = std::mem_fn(&Employee::bonus);
    std::cout << "Alice 10% bonus: " << bonus(alice, 10) << std::endl;

    // Works with pointers too
    Employee* ptr = &alice;
    greet(ptr);
    std::cout << "Bonus via pointer: " << bonus(ptr, 15) << std::endl;

    // Works with smart pointers
    auto bob = std::make_shared<Employee>(Employee{"Bob", 95000});
    greet(bob);
    std::cout << "Bob 20% bonus: " << bonus(bob, 20) << std::endl;

    // Use mem_fn with algorithms
    std::vector<Employee> team = {
        {"Carol", 70000}, {"Dave", 90000}, {"Eve", 60000}
    };

    std::cout << "\nTeam greetings:" << std::endl;
    std::for_each(team.begin(), team.end(), std::mem_fn(&Employee::greet));

    // mem_fn with data members (accesses the member directly)
    auto get_name = std::mem_fn(&Employee::name);
    auto get_salary = std::mem_fn(&Employee::salary);
    std::cout << "\nTeam salaries:" << std::endl;
    for (const auto& e : team) {
        std::cout << "  " << get_name(e) << ": $" << get_salary(e) << std::endl;
    }

    // Use mem_fn in count_if
    auto earns_more = std::mem_fn(&Employee::earns_more_than);
    long count = std::count_if(team.begin(), team.end(),
        [&earns_more](const Employee& e) { return earns_more(e, 65000); });
    std::cout << "\nEmployees earning > $65000: " << count << std::endl;

    return 0;
}

// Expected output:
// Hi, I'm Alice
// Alice 10% bonus: 8000
// Hi, I'm Alice
// Bonus via pointer: 12000
// Hi, I'm Bob
// Bob 20% bonus: 19000
//
// Team greetings:
// Hi, I'm Carol
// Hi, I'm Dave
// Hi, I'm Eve
//
// Team salaries:
//   Carol: $70000
//   Dave: $90000
//   Eve: $60000
//
// Employees earning > $65000: 2
