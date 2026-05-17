// CodeNebula - C++20 Example: Strong Ordering
// Compile: g++ -std=c++20 -Wall -Wextra -o example strong_ordering.cpp

// Demonstrates std::strong_ordering: result values (less, equal, greater,
// equivalent), and how it differs from other ordering categories.

#include <iostream>
#include <compare>
#include <string>
#include <vector>
#include <algorithm>

// ------------------------------------------------------------------
// 1. strong_ordering: equal values are truly indistinguishable
// ------------------------------------------------------------------
struct StudentID {
    int id;
    std::string name;

    // Compare only by id - two students with same id are "equal"
    std::strong_ordering operator<=>(const StudentID& other) const {
        return id <=> other.id;
    }

    bool operator==(const StudentID& other) const {
        return id == other.id;
    }
};

// ------------------------------------------------------------------
// 2. Default strong_ordering for simple aggregates
// ------------------------------------------------------------------
struct RGB {
    int r, g, b;
    auto operator<=>(const RGB&) const = default;
};

// ------------------------------------------------------------------
// 3. Examining strong_ordering result values
// ------------------------------------------------------------------
void describe_ordering(std::strong_ordering ord, const char* expr) {
    std::cout << "  " << expr << " is ";
    if (ord == std::strong_ordering::less)
        std::cout << "less";
    else if (ord == std::strong_ordering::equal)
        std::cout << "equal";
    else if (ord == std::strong_ordering::equivalent)
        std::cout << "equivalent";
    else if (ord == std::strong_ordering::greater)
        std::cout << "greater";
    std::cout << std::endl;
}

// ------------------------------------------------------------------
// 4. strong_ordering from built-in integer comparison
// ------------------------------------------------------------------
void compare_ints(int a, int b) {
    auto result = a <=> b;
    std::cout << "  " << a << " <=> " << b << ": ";
    if (result < 0) std::cout << "less";
    else if (result == 0) std::cout << "equal";
    else std::cout << "greater";
    std::cout << std::endl;
}

int main()
{
    std::cout << "=== strong_ordering Result Values ===" << std::endl;
    describe_ordering(1 <=> 2, "1 <=> 2");
    describe_ordering(5 <=> 5, "5 <=> 5");
    describe_ordering(9 <=> 3, "9 <=> 3");

    std::cout << "\n=== equal vs equivalent ===" << std::endl;
    // For strong_ordering, equal and equivalent are the same value
    std::cout << "  equal == equivalent? "
              << (std::strong_ordering::equal == std::strong_ordering::equivalent)
              << std::endl;

    std::cout << "\n=== Integer Comparisons ===" << std::endl;
    compare_ints(10, 20);
    compare_ints(42, 42);
    compare_ints(99, 1);

    std::cout << "\n=== StudentID Ordering ===" << std::endl;
    std::vector<StudentID> students = {
        {3, "Charlie"}, {1, "Alice"}, {2, "Bob"}, {1, "Duplicate"}
    };
    std::sort(students.begin(), students.end());
    for (const auto& s : students) {
        std::cout << "  ID=" << s.id << " Name=" << s.name << std::endl;
    }

    std::cout << "\n  ID 1 == ID 1 (different names)? "
              << (students[0] == students[1]) << std::endl;

    std::cout << "\n=== RGB Ordering ===" << std::endl;
    RGB red{255, 0, 0}, green{0, 255, 0}, red2{255, 0, 0};
    std::cout << "  red == red2? " << (red == red2) << std::endl;
    std::cout << "  red < green? " << (red < green) << std::endl;
    describe_ordering(red <=> green, "red <=> green");

    std::cout << "\n=== Conversion to Other Orderings ===" << std::endl;
    std::strong_ordering so = 5 <=> 3;
    std::weak_ordering wo = so;       // implicit conversion ok
    std::partial_ordering po = so;    // implicit conversion ok
    std::cout << "  strong->weak (> 0)? " << (wo > 0) << std::endl;
    std::cout << "  strong->partial (> 0)? " << (po > 0) << std::endl;

    return 0;
}

/*
Expected output:

=== strong_ordering Result Values ===
  1 <=> 2 is less
  5 <=> 5 is equal
  9 <=> 3 is greater

=== equal vs equivalent ===
  equal == equivalent? 1

=== Integer Comparisons ===
  10 <=> 20: less
  42 <=> 42: equal
  99 <=> 1: greater

=== StudentID Ordering ===
  ID=1 Name=Alice
  ID=1 Name=Duplicate
  ID=2 Name=Bob
  ID=3 Name=Charlie

  ID 1 == ID 1 (different names)? 1

=== RGB Ordering ===
  red == red2? 1
  red < green? 0
  red <=> green is greater

=== Conversion to Other Orderings ===
  strong->weak (> 0)? 1
  strong->partial (> 0)? 1
*/
