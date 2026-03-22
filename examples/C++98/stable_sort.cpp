// CodeNebula - C++98 Example: stable_sort
// Compile: g++ -std=c++98 -Wall -Wextra -o example stable_sort.cpp

// std::stable_sort sorts elements while preserving the relative
// order of equivalent elements. This matters when sorting by a
// key that does not uniquely identify each element.

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Student {
    std::string name;
    int grade;
    Student(const std::string& n, int g) : name(n), grade(g) {}
};

bool by_grade(const Student& a, const Student& b) {
    return a.grade < b.grade;
}

void print_students(const std::vector<Student>& v, const char* label) {
    std::cout << label << ":" << std::endl;
    for (std::vector<Student>::const_iterator it = v.begin();
         it != v.end(); ++it) {
        std::cout << "  " << it->name << " (grade " << it->grade << ")"
                  << std::endl;
    }
}

int main() {
    std::vector<Student> students;
    students.push_back(Student("Alice", 90));
    students.push_back(Student("Bob", 85));
    students.push_back(Student("Carol", 90));
    students.push_back(Student("Dave", 85));
    students.push_back(Student("Eve", 95));

    print_students(students, "Original order");

    // stable_sort preserves original order for equal grades
    // Alice stays before Carol (both 90), Bob stays before Dave (both 85)
    std::stable_sort(students.begin(), students.end(), by_grade);
    print_students(students, "After stable_sort by grade");

    return 0;
}

// Expected output:
// Original order:
//   Alice (grade 90)
//   Bob (grade 85)
//   Carol (grade 90)
//   Dave (grade 85)
//   Eve (grade 95)
// After stable_sort by grade:
//   Bob (grade 85)
//   Dave (grade 85)
//   Alice (grade 90)
//   Carol (grade 90)
//   Eve (grade 95)
