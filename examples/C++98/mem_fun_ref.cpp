// CodeNebula - C++98 Example: mem_fun_ref (with references/objects)
// Compile: g++ -std=c++98 -Wall -Wextra -o example mem_fun_ref.cpp

#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <string>

class Student {
    std::string name_;
    int grade_;
public:
    Student(const std::string& n, int g) : name_(n), grade_(g) {}
    void print() const {
        std::cout << name_ << ": " << grade_ << std::endl;
    }
    bool passed() const { return grade_ >= 60; }
    int grade() const { return grade_; }
};

int main() {
    // mem_fun_ref works with containers of objects (not pointers)
    std::vector<Student> students;
    students.push_back(Student("Alice", 85));
    students.push_back(Student("Bob", 45));
    students.push_back(Student("Carol", 72));
    students.push_back(Student("Dave", 55));

    // Print all students using mem_fun_ref
    std::cout << "--- All Students ---" << std::endl;
    std::for_each(students.begin(), students.end(),
                  std::mem_fun_ref(&Student::print));

    // Count students who passed
    int pass_count = std::count_if(students.begin(), students.end(),
                                   std::mem_fun_ref(&Student::passed));
    std::cout << "Passed: " << pass_count << std::endl;

    // Count who failed using not1 + mem_fun_ref
    int fail_count = std::count_if(students.begin(), students.end(),
                                   std::not1(std::mem_fun_ref(&Student::passed)));
    std::cout << "Failed: " << fail_count << std::endl;

    return 0;
}

// Expected output:
// --- All Students ---
// Alice: 85
// Bob: 45
// Carol: 72
// Dave: 55
// Passed: 2
// Failed: 2
