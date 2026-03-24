// CodeNebula - C++17 Example: std::is_aggregate
// Compile: g++ -std=c++17 -Wall -Wextra -o example is_aggregate.cpp

// Demonstrates std::is_aggregate, a C++17 type trait that detects whether
// a type is an aggregate. Aggregates support brace-initialization without
// a user-provided constructor. This trait is useful for generic code that
// needs to choose between aggregate init and constructor-based init.

#include <iostream>
#include <type_traits>
#include <string>
#include <array>
#include <vector>

// An aggregate: no user-provided constructors, no private members,
// no virtual functions, no base classes (relaxed in C++17)
struct Aggregate {
    int x;
    double y;
    std::string name;
};

// Aggregate with nested aggregate
struct Nested {
    Aggregate inner;
    int z;
};

// NOT aggregate: has user-provided constructor
struct WithConstructor {
    int x;
    WithConstructor(int v) : x(v) {}
};

// NOT aggregate: has private members
class PrivateMembers {
    int x;
public:
    int getX() const { return x; }
};

// NOT aggregate: has virtual function
struct WithVirtual {
    int x;
    virtual void foo() {}
};

// C++17: aggregate with public base class (new in C++17!)
struct Base { int a; };
struct DerivedAggregate : Base {
    int b;
};

// C-style array is an aggregate
using IntArray = int[5];

int main()
{
    // ------------------------------------------------------------------
    // 1. Aggregate types
    // ------------------------------------------------------------------
    std::cout << "=== Aggregate Types ===" << std::endl;
    std::cout << "  Aggregate        : " << std::is_aggregate_v<Aggregate> << std::endl;
    std::cout << "  Nested           : " << std::is_aggregate_v<Nested> << std::endl;
    std::cout << "  DerivedAggregate : " << std::is_aggregate_v<DerivedAggregate> << std::endl;
    std::cout << "  int[5]           : " << std::is_aggregate_v<IntArray> << std::endl;
    std::cout << "  std::array<int,3>: " << std::is_aggregate_v<std::array<int,3>> << std::endl;

    // ------------------------------------------------------------------
    // 2. Non-aggregate types
    // ------------------------------------------------------------------
    std::cout << "\n=== Non-Aggregate Types ===" << std::endl;
    std::cout << "  WithConstructor  : " << std::is_aggregate_v<WithConstructor> << std::endl;
    std::cout << "  PrivateMembers   : " << std::is_aggregate_v<PrivateMembers> << std::endl;
    std::cout << "  WithVirtual      : " << std::is_aggregate_v<WithVirtual> << std::endl;
    std::cout << "  std::string      : " << std::is_aggregate_v<std::string> << std::endl;
    std::cout << "  std::vector<int> : " << std::is_aggregate_v<std::vector<int>> << std::endl;

    // ------------------------------------------------------------------
    // 3. Fundamental types (not aggregates)
    // ------------------------------------------------------------------
    std::cout << "\n=== Fundamental Types ===" << std::endl;
    std::cout << "  int              : " << std::is_aggregate_v<int> << std::endl;
    std::cout << "  double           : " << std::is_aggregate_v<double> << std::endl;

    // ------------------------------------------------------------------
    // 4. Practical: conditional initialization
    // ------------------------------------------------------------------
    std::cout << "\n=== Practical: Aggregate Init ===" << std::endl;

    // C++17 allows aggregate init of DerivedAggregate
    DerivedAggregate da = {{10}, 20};
    std::cout << "  DerivedAggregate{10, 20}: a=" << da.a << " b=" << da.b << std::endl;

    Aggregate agg = {42, 3.14, "test"};
    std::cout << "  Aggregate{42, 3.14, test}: x=" << agg.x
              << " y=" << agg.y << " name=" << agg.name << std::endl;

    return 0;
}

/*
Expected output:

=== Aggregate Types ===
  Aggregate        : 1
  Nested           : 1
  DerivedAggregate : 1
  int[5]           : 1
  std::array<int,3>: 1

=== Non-Aggregate Types ===
  WithConstructor  : 0
  PrivateMembers   : 0
  WithVirtual      : 0
  std::string      : 0
  std::vector<int> : 0

=== Fundamental Types ===
  int              : 0
  double           : 0

=== Practical: Aggregate Init ===
  DerivedAggregate{10, 20}: a=10 b=20
  Aggregate{42, 3.14, test}: x=42 y=3.14 name=test
*/
