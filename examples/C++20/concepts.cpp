// CodeNebula - C++20 Example: Concepts
// Compile: g++ -std=c++20 -Wall -Wextra -o example concepts.cpp

// Demonstrates defining and using concepts: Numeric, Sortable, Printable,
// and composing concepts with && to constrain template parameters.

#include <iostream>
#include <concepts>
#include <string>
#include <vector>
#include <algorithm>

// ------------------------------------------------------------------
// 1. Define a Numeric concept - requires arithmetic operations
// ------------------------------------------------------------------
template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

// ------------------------------------------------------------------
// 2. Define a Sortable concept - requires < operator and copy
// ------------------------------------------------------------------
template <typename T>
concept Sortable = std::copyable<T> && std::totally_ordered<T>;

// ------------------------------------------------------------------
// 3. Define a Printable concept - requires operator<< with ostream
// ------------------------------------------------------------------
template <typename T>
concept Printable = requires(std::ostream& os, const T& val) {
    { os << val } -> std::convertible_to<std::ostream&>;
};

// ------------------------------------------------------------------
// 4. Constrained functions using concepts
// ------------------------------------------------------------------
template <Numeric T>
T add(T a, T b) {
    return a + b;
}

template <Sortable T>
T find_median(std::vector<T> v) {
    std::sort(v.begin(), v.end());
    return v[v.size() / 2];
}

template <Printable T>
void display(const T& val) {
    std::cout << "  Value: " << val << std::endl;
}

// ------------------------------------------------------------------
// 5. Composed concept: PrintableNumeric
// ------------------------------------------------------------------
template <typename T>
concept PrintableNumeric = Numeric<T> && Printable<T>;

template <PrintableNumeric T>
void show_double(T val) {
    std::cout << "  " << val << " * 2 = " << (val + val) << std::endl;
}

int main()
{
    std::cout << "=== Numeric Concept ===" << std::endl;
    std::cout << "  add(3, 4) = " << add(3, 4) << std::endl;
    std::cout << "  add(1.5, 2.5) = " << add(1.5, 2.5) << std::endl;
    // add(std::string("a"), std::string("b")); // Would not compile

    std::cout << "\n=== Sortable Concept ===" << std::endl;
    std::vector<int> nums = {7, 2, 9, 1, 5};
    std::cout << "  Median of {7,2,9,1,5}: " << find_median(nums) << std::endl;

    std::vector<std::string> words = {"cherry", "apple", "banana"};
    std::cout << "  Median of {cherry,apple,banana}: "
              << find_median(words) << std::endl;

    std::cout << "\n=== Printable Concept ===" << std::endl;
    display(42);
    display(std::string("hello"));
    display(3.14);

    std::cout << "\n=== Composed PrintableNumeric ===" << std::endl;
    show_double(10);
    show_double(2.75);

    std::cout << "\n=== Concept Checks at Compile Time ===" << std::endl;
    std::cout << "  int is Numeric? " << Numeric<int> << std::endl;
    std::cout << "  double is Numeric? " << Numeric<double> << std::endl;
    std::cout << "  string is Numeric? " << Numeric<std::string> << std::endl;
    std::cout << "  string is Sortable? " << Sortable<std::string> << std::endl;
    std::cout << "  string is Printable? " << Printable<std::string> << std::endl;

    return 0;
}

/*
Expected output:

=== Numeric Concept ===
  add(3, 4) = 7
  add(1.5, 2.5) = 4

=== Sortable Concept ===
  Median of {7,2,9,1,5}: 5
  Median of {cherry,apple,banana}: cherry

=== Printable Concept ===
  Value: 42
  Value: hello
  Value: 3.14

=== Composed PrintableNumeric ===
  10 * 2 = 20
  2.75 * 2 = 5.5

=== Concept Checks at Compile Time ===
  int is Numeric? 1
  double is Numeric? 1
  string is Numeric? 0
  string is Sortable? 1
  string is Printable? 1
*/
