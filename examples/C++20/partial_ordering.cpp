// CodeNebula - C++20 Example: Partial Ordering
// Compile: g++ -std=c++20 -Wall -Wextra -o example partial_ordering.cpp

// Demonstrates std::partial_ordering for types where some values are
// incomparable, such as floating-point NaN values and set containment.

#include <iostream>
#include <compare>
#include <cmath>
#include <set>

// ------------------------------------------------------------------
// 1. Floating-point comparison naturally yields partial_ordering
// ------------------------------------------------------------------
void compare_doubles(double a, double b) {
    auto result = a <=> b;
    std::cout << "  " << a << " <=> " << b << ": ";
    if (result == std::partial_ordering::less) std::cout << "less";
    else if (result == std::partial_ordering::equivalent) std::cout << "equivalent";
    else if (result == std::partial_ordering::greater) std::cout << "greater";
    else if (result == std::partial_ordering::unordered) std::cout << "unordered";
    std::cout << std::endl;
}

// ------------------------------------------------------------------
// 2. Custom type with partial_ordering: subset comparison
// ------------------------------------------------------------------
struct IntSet {
    std::set<int> data;

    // A is "less" if it is a strict subset of B
    // A is "equivalent" if they have the same elements
    // A is "greater" if B is a strict subset of A
    // Otherwise, they are unordered (neither is a subset)
    std::partial_ordering operator<=>(const IntSet& other) const {
        bool a_sub_b = std::includes(other.data.begin(), other.data.end(),
                                     data.begin(), data.end());
        bool b_sub_a = std::includes(data.begin(), data.end(),
                                     other.data.begin(), other.data.end());

        if (a_sub_b && b_sub_a) return std::partial_ordering::equivalent;
        if (a_sub_b)            return std::partial_ordering::less;
        if (b_sub_a)            return std::partial_ordering::greater;
        return std::partial_ordering::unordered;
    }

    bool operator==(const IntSet& other) const {
        return data == other.data;
    }
};

void print_set(const IntSet& s) {
    std::cout << "{";
    bool first = true;
    for (int v : s.data) {
        if (!first) std::cout << ",";
        std::cout << v;
        first = false;
    }
    std::cout << "}";
}

void compare_sets(const IntSet& a, const IntSet& b) {
    auto result = a <=> b;
    std::cout << "  ";
    print_set(a);
    std::cout << " <=> ";
    print_set(b);
    std::cout << ": ";
    if (result == std::partial_ordering::less) std::cout << "less (subset)";
    else if (result == std::partial_ordering::equivalent) std::cout << "equivalent";
    else if (result == std::partial_ordering::greater) std::cout << "greater (superset)";
    else if (result == std::partial_ordering::unordered) std::cout << "unordered";
    std::cout << std::endl;
}

int main()
{
    std::cout << "=== Float Partial Ordering ===" << std::endl;
    double nan = std::numeric_limits<double>::quiet_NaN();
    compare_doubles(1.0, 2.0);
    compare_doubles(3.0, 3.0);
    compare_doubles(5.0, 1.0);
    compare_doubles(nan, 1.0);
    compare_doubles(1.0, nan);
    compare_doubles(nan, nan);

    std::cout << "\n=== NaN Comparison Booleans ===" << std::endl;
    std::cout << "  NaN < 1.0?  " << (nan < 1.0) << std::endl;
    std::cout << "  NaN > 1.0?  " << (nan > 1.0) << std::endl;
    std::cout << "  NaN == 1.0? " << (nan == 1.0) << std::endl;
    std::cout << "  NaN == NaN? " << (nan == nan) << std::endl;

    std::cout << "\n=== Set Containment (Partial Ordering) ===" << std::endl;
    IntSet a{{1, 2}}, b{{1, 2, 3}}, c{{1, 2}}, d{{2, 3}};
    compare_sets(a, b);   // subset
    compare_sets(b, a);   // superset
    compare_sets(a, c);   // equivalent
    compare_sets(a, d);   // unordered (neither is subset)
    compare_sets(b, d);   // superset

    std::cout << "\n=== partial_ordering Result Values ===" << std::endl;
    std::cout << "  less < 0?        " << (std::partial_ordering::less < 0) << std::endl;
    std::cout << "  equivalent == 0? " << (std::partial_ordering::equivalent == 0) << std::endl;
    std::cout << "  greater > 0?     " << (std::partial_ordering::greater > 0) << std::endl;
    std::cout << "  unordered == 0?  " << (std::partial_ordering::unordered == 0) << std::endl;
    std::cout << "  unordered < 0?   " << (std::partial_ordering::unordered < 0) << std::endl;
    std::cout << "  unordered > 0?   " << (std::partial_ordering::unordered > 0) << std::endl;

    return 0;
}

/*
Expected output:

=== Float Partial Ordering ===
  1 <=> 2: less
  3 <=> 3: equivalent
  5 <=> 1: greater
  nan <=> 1: unordered
  1 <=> nan: unordered
  nan <=> nan: unordered

=== NaN Comparison Booleans ===
  NaN < 1.0?  0
  NaN > 1.0?  0
  NaN == 1.0? 0
  NaN == NaN? 0

=== Set Containment (Partial Ordering) ===
  {1,2} <=> {1,2,3}: less (subset)
  {1,2,3} <=> {1,2}: greater (superset)
  {1,2} <=> {1,2}: equivalent
  {1,2} <=> {2,3}: unordered
  {1,2,3} <=> {2,3}: greater (superset)

=== partial_ordering Result Values ===
  less < 0?        1
  equivalent == 0? 1
  greater > 0?     1
  unordered == 0?  0
  unordered < 0?   0
  unordered > 0?   0
*/
