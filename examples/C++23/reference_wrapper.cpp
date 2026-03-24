// CodeNebula - C++23 Example: std::reference_wrapper Improvements
// Compile: g++ -std=c++23 -Wall -Wextra -o example reference_wrapper.cpp
// Note: Requires GCC 13+ / Clang 17+

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

// C++23 improves std::reference_wrapper with:
// - operator== and operator<=> for direct comparison
// - Better integration with ranges and algorithms
// - Implicit conversion improvements

struct Student {
    std::string name;
    int grade;

    friend std::ostream& operator<<(std::ostream& os, const Student& s) {
        return os << s.name << " (" << s.grade << ")";
    }
};

int main() {
    std::cout << "=== std::reference_wrapper improvements ===\n\n";

    // Basic reference_wrapper usage with C++23 comparison
    int a = 10, b = 20, c = 30;
    std::vector<std::reference_wrapper<int>> refs = {
        std::ref(c), std::ref(a), std::ref(b)
    };

    std::cout << "--- Sorting references ---\n";
    std::cout << "Before sort: ";
    for (auto& r : refs) std::cout << r.get() << " ";
    std::cout << "\n";

    // C++23: reference_wrapper supports comparison operators
    std::ranges::sort(refs, [](auto& lhs, auto& rhs) {
        return lhs.get() < rhs.get();
    });

    std::cout << "After sort:  ";
    for (auto& r : refs) std::cout << r.get() << " ";
    std::cout << "\n";

    // Modify through references
    refs[0].get() = 100;
    std::cout << "Modified via ref: a=" << a << ", b=" << b << ", c=" << c << "\n\n";

    // Reference wrapper with structs
    std::cout << "--- Student references ---\n";
    std::vector<Student> students = {
        {"Alice", 92}, {"Bob", 85}, {"Charlie", 95}, {"Diana", 88}
    };

    // Create refs to sort without moving Students
    std::vector<std::reference_wrapper<Student>> student_refs(
        students.begin(), students.end());

    // Sort by grade descending
    std::ranges::sort(student_refs, [](const Student& a, const Student& b) {
        return a.grade > b.grade;
    });

    std::cout << "Sorted by grade (desc):\n";
    for (const auto& s : student_refs) {
        std::cout << "  " << s.get() << "\n";
    }

    // Original vector unchanged in order
    std::cout << "\nOriginal order preserved:\n";
    for (const auto& s : students) {
        std::cout << "  " << s << "\n";
    }

    // reference_wrapper with algorithms
    std::cout << "\n--- With algorithms ---\n";
    auto top = std::ranges::max_element(student_refs,
        [](const Student& a, const Student& b) {
            return a.grade < b.grade;
        });
    std::cout << "Top student: " << top->get() << "\n";

    // Using std::cref for const references
    const int x = 42;
    auto cr = std::cref(x);
    std::cout << "\ncref value: " << cr.get() << "\n";

    return 0;
}

// Expected output:
// === std::reference_wrapper improvements ===
//
// --- Sorting references ---
// Before sort: 30 10 20
// After sort:  10 20 30
// Modified via ref: a=100, b=20, c=30
//
// --- Student references ---
// Sorted by grade (desc):
//   Charlie (95)
//   Alice (92)
//   Diana (88)
//   Bob (85)
//
// Original order preserved:
//   Alice (92)
//   Bob (85)
//   Charlie (95)
//   Diana (88)
//
// --- With algorithms ---
// Top student: Charlie (95)
//
// cref value: 42
