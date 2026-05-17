// CodeNebula - C++17 Example: Structured Bindings
// Compile: g++ -std=c++17 -Wall -Wextra -o example structured_bindings.cpp

// Demonstrates structured bindings (auto [a, b] = ...) which allow unpacking
// pairs, tuples, structs, and arrays into named variables in a single declaration.

#include <iostream>
#include <tuple>
#include <map>
#include <string>

struct Point {
    double x;
    double y;
    double z;
};

std::tuple<int, std::string, bool> get_record() {
    return {42, "Alice", true};
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Binding from std::pair
    // ------------------------------------------------------------------
    std::pair<int, std::string> p{1, "hello"};
    auto [id, name] = p;
    std::cout << "=== std::pair ===" << std::endl;
    std::cout << "  id: " << id << ", name: " << name << std::endl;

    // ------------------------------------------------------------------
    // 2. Binding from std::tuple
    // ------------------------------------------------------------------
    auto [num, who, active] = get_record();
    std::cout << "\n=== std::tuple ===" << std::endl;
    std::cout << "  num: " << num << ", who: " << who
              << ", active: " << std::boolalpha << active << std::endl;

    // ------------------------------------------------------------------
    // 3. Binding from a struct (public members, in declaration order)
    // ------------------------------------------------------------------
    Point pt{1.5, 2.7, 3.9};
    auto [px, py, pz] = pt;
    std::cout << "\n=== struct ===" << std::endl;
    std::cout << "  x: " << px << ", y: " << py << ", z: " << pz << std::endl;

    // ------------------------------------------------------------------
    // 4. Binding from a C-style array
    // ------------------------------------------------------------------
    int arr[3] = {10, 20, 30};
    auto [a, b, c] = arr;
    std::cout << "\n=== array ===" << std::endl;
    std::cout << "  a: " << a << ", b: " << b << ", c: " << c << std::endl;

    // ------------------------------------------------------------------
    // 5. Binding by reference (modifications affect the original)
    // ------------------------------------------------------------------
    auto& [rx, ry, rz] = pt;
    rx = 100.0;
    std::cout << "\n=== reference binding ===" << std::endl;
    std::cout << "  pt.x after modification: " << pt.x << std::endl;

    // ------------------------------------------------------------------
    // 6. Using structured bindings in range-for with std::map
    // ------------------------------------------------------------------
    std::map<std::string, int> scores{{"Alice", 95}, {"Bob", 87}, {"Carol", 92}};
    std::cout << "\n=== map iteration ===" << std::endl;
    for (const auto& [student, score] : scores) {
        std::cout << "  " << student << ": " << score << std::endl;
    }

    return 0;
}

/*
Expected output:

=== std::pair ===
  id: 1, name: hello

=== std::tuple ===
  num: 42, who: Alice, active: true

=== struct ===
  x: 1.5, y: 2.7, z: 3.9

=== array ===
  a: 10, b: 20, c: 30

=== reference binding ===
  pt.x after modification: 100

=== map iteration ===
  Alice: 95
  Bob: 87
  Carol: 92
*/
