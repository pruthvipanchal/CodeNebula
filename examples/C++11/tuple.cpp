// CodeNebula - C++11 Example: std::tuple
// Compile: g++ -std=c++11 -Wall -Wextra -o example tuple.cpp
//
// This example demonstrates:
// - std::tuple creation with make_tuple
// - std::get<> to access elements by index
// - std::tie for unpacking tuple values
// - std::tuple_size and std::tuple_element type traits
// - Tuples as function return values for multiple returns
// - Comparison operators on tuples

#include <iostream>
#include <tuple>
#include <string>
#include <vector>
#include <algorithm>

// ============================================================
// 1. Basic tuple creation and access
// ============================================================
void basicUsage() {
    std::cout << "--- Basic creation and access ---" << std::endl;

    // Direct construction
    std::tuple<int, double, std::string> t1(1, 3.14, "hello");

    // make_tuple deduces types
    auto t2 = std::make_tuple(42, 2.718, std::string("world"));

    std::cout << "  t1: (" << std::get<0>(t1) << ", "
              << std::get<1>(t1) << ", "
              << std::get<2>(t1) << ")" << std::endl;

    std::cout << "  t2: (" << std::get<0>(t2) << ", "
              << std::get<1>(t2) << ", "
              << std::get<2>(t2) << ")" << std::endl;

    // Modify through get
    std::get<0>(t1) = 100;
    std::cout << "  t1 after modify: (" << std::get<0>(t1) << ", ...)" << std::endl;
}

// ============================================================
// 2. std::tie for unpacking
// ============================================================
std::tuple<std::string, int, double> getStudentInfo() {
    return std::make_tuple("Alice", 22, 3.95);
}

void tieUsage() {
    std::cout << "\n--- std::tie for unpacking ---" << std::endl;

    std::string name;
    int age;
    double gpa;

    std::tie(name, age, gpa) = getStudentInfo();
    std::cout << "  Name: " << name << ", Age: " << age
              << ", GPA: " << gpa << std::endl;

    // Ignore certain values with std::ignore
    std::string name2;
    double gpa2;
    std::tie(name2, std::ignore, gpa2) = getStudentInfo();
    std::cout << "  Name: " << name2 << ", GPA: " << gpa2
              << " (age ignored)" << std::endl;
}

// ============================================================
// 3. Multiple return values
// ============================================================
std::tuple<bool, int, std::string> findItem(int id) {
    if (id == 1) return std::make_tuple(true, 1, "Widget");
    if (id == 2) return std::make_tuple(true, 2, "Gadget");
    return std::make_tuple(false, 0, "");
}

// ============================================================
// 4. Tuple comparison (lexicographic)
// ============================================================
void comparisonDemo() {
    std::cout << "\n--- Tuple comparison ---" << std::endl;

    auto a = std::make_tuple(1, "apple");
    auto b = std::make_tuple(1, "banana");
    auto c = std::make_tuple(2, "apple");

    std::cout << "  (1,apple) < (1,banana): " << (a < b) << std::endl;
    std::cout << "  (1,banana) < (2,apple): " << (b < c) << std::endl;
    std::cout << "  (1,apple) == (1,apple): " << (a == a) << std::endl;
}

// ============================================================
// 5. Tuple traits
// ============================================================
void traitsDemo() {
    std::cout << "\n--- Tuple traits ---" << std::endl;

    using MyTuple = std::tuple<int, double, std::string, char>;

    std::cout << "  tuple_size: "
              << std::tuple_size<MyTuple>::value << std::endl;

    // tuple_element gives the type at an index
    // (demonstrated by sizeof here)
    std::cout << "  element 0 size: "
              << sizeof(std::tuple_element<0, MyTuple>::type) << std::endl;
    std::cout << "  element 1 size: "
              << sizeof(std::tuple_element<1, MyTuple>::type) << std::endl;
}

// ============================================================
// 6. Sorting with tuples
// ============================================================
void sortingDemo() {
    std::cout << "\n--- Sorting records via tuples ---" << std::endl;

    std::vector<std::tuple<std::string, int, double>> students = {
        std::make_tuple("Charlie", 20, 3.5),
        std::make_tuple("Alice", 22, 3.9),
        std::make_tuple("Bob", 21, 3.7)
    };

    // Sort by name (element 0) using default tuple comparison
    std::sort(students.begin(), students.end());

    for (const auto& s : students) {
        std::cout << "  " << std::get<0>(s) << ", age "
                  << std::get<1>(s) << ", GPA "
                  << std::get<2>(s) << std::endl;
    }
}

int main() {
    std::cout << "=== std::tuple ===" << std::endl;

    basicUsage();
    tieUsage();

    // Multiple return values
    std::cout << "\n--- Multiple return values ---" << std::endl;
    bool found; int id; std::string name;
    std::tie(found, id, name) = findItem(2);
    if (found) {
        std::cout << "  Found: id=" << id << ", name=" << name << std::endl;
    }
    std::tie(found, id, name) = findItem(99);
    std::cout << "  Item 99 found: " << (found ? "yes" : "no") << std::endl;

    comparisonDemo();
    traitsDemo();
    sortingDemo();

    // tuple_cat: concatenate tuples
    std::cout << "\n--- tuple_cat ---" << std::endl;
    auto part1 = std::make_tuple(1, "hello");
    auto part2 = std::make_tuple(3.14, 'X');
    auto combined = std::tuple_cat(part1, part2);
    std::cout << "  Combined: (" << std::get<0>(combined) << ", "
              << std::get<1>(combined) << ", "
              << std::get<2>(combined) << ", "
              << std::get<3>(combined) << ")" << std::endl;

    return 0;
}

// Expected output:
// === std::tuple ===
// --- Basic creation and access ---
//   t1: (1, 3.14, hello)
//   t2: (42, 2.718, world)
//   t1 after modify: (100, ...)
//
// --- std::tie for unpacking ---
//   Name: Alice, Age: 22, GPA: 3.95
//   Name: Alice, GPA: 3.95 (age ignored)
//
// --- Multiple return values ---
//   Found: id=2, name=Gadget
//   Item 99 found: no
//
// --- Tuple comparison ---
//   (1,apple) < (1,banana): 1
//   (1,banana) < (2,apple): 1
//   (1,apple) == (1,apple): 1
//
// --- Tuple traits ---
//   tuple_size: 4
//   element 0 size: 4
//   element 1 size: 8
//
// --- Sorting records via tuples ---
//   Alice, age 22, GPA 3.9
//   Bob, age 21, GPA 3.7
//   Charlie, age 20, GPA 3.5
//
// --- tuple_cat ---
//   Combined: (1, hello, 3.14, X)
