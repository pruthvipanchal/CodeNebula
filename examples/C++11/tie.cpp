// CodeNebula - C++11 Example: std::tie
// Compile: g++ -std=c++11 -Wall -Wextra -o example tie.cpp

// std::tie creates a tuple of lvalue references. It enables unpacking
// tuple/pair values into separate variables and provides a concise way
// to implement comparison operators.

#include <iostream>
#include <tuple>
#include <string>
#include <set>

// Function returning multiple values
std::tuple<int, std::string, double> get_record() {
    return std::make_tuple(42, "Alice", 95.5);
}

// Function returning a pair
std::pair<bool, std::string> validate(int age) {
    if (age < 0) return {false, "Age cannot be negative"};
    if (age > 150) return {false, "Age unrealistic"};
    return {true, "Valid"};
}

// Struct with comparison via tie
struct Employee {
    std::string department;
    std::string name;
    int id;

    bool operator<(const Employee& other) const {
        return std::tie(department, name, id)
             < std::tie(other.department, other.name, other.id);
    }

    bool operator==(const Employee& other) const {
        return std::tie(department, name, id)
            == std::tie(other.department, other.name, other.id);
    }
};

int main() {
    // Unpack a tuple into variables
    int id;
    std::string name;
    double score;
    std::tie(id, name, score) = get_record();
    std::cout << "Record: id=" << id << " name=" << name
              << " score=" << score << std::endl;

    // Unpack a pair
    bool valid;
    std::string message;
    std::tie(valid, message) = validate(25);
    std::cout << "\nValidation: " << (valid ? "OK" : "FAIL")
              << " - " << message << std::endl;

    // Use std::ignore to skip unwanted fields
    std::string name_only;
    std::tie(std::ignore, name_only, std::ignore) = get_record();
    std::cout << "Name only: " << name_only << std::endl;

    // Swap variables using tie
    int a = 10, b = 20;
    std::cout << "\nBefore swap: a=" << a << " b=" << b << std::endl;
    std::tie(a, b) = std::make_tuple(b, a);
    std::cout << "After swap:  a=" << a << " b=" << b << std::endl;

    // Comparison operator via tie (sorted set)
    std::set<Employee> staff = {
        {"Engineering", "Charlie", 3},
        {"Admin", "Alice", 1},
        {"Engineering", "Bob", 2},
        {"Admin", "Dave", 4}
    };

    std::cout << "\nSorted employees:" << std::endl;
    for (const auto& e : staff) {
        std::cout << "  [" << e.department << "] " << e.name
                  << " (#" << e.id << ")" << std::endl;
    }

    // Equality via tie
    Employee e1{"Admin", "Alice", 1};
    Employee e2{"Admin", "Alice", 1};
    Employee e3{"Admin", "Bob", 2};
    std::cout << "\ne1 == e2: " << (e1 == e2 ? "true" : "false") << std::endl;
    std::cout << "e1 == e3: " << (e1 == e3 ? "true" : "false") << std::endl;

    return 0;
}

// Expected output:
// Record: id=42 name=Alice score=95.5
//
// Validation: OK - Valid
// Name only: Alice
//
// Before swap: a=10 b=20
// After swap:  a=20 b=10
//
// Sorted employees:
//   [Admin] Alice (#1)
//   [Admin] Dave (#4)
//   [Engineering] Bob (#2)
//   [Engineering] Charlie (#3)
//
// e1 == e2: true
// e1 == e3: false
