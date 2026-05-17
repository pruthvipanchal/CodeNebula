// CodeNebula - C++11 Example: is_standard_layout
// Compile: g++ -std=c++11 -Wall -Wextra -o example is_standard_layout.cpp

// Demonstrates std::is_standard_layout which checks if a type has a
// memory layout compatible with C. Standard layout types can be used
// for C interop and have predictable member offsets.

#include <iostream>
#include <type_traits>

struct StandardLayout {
    int x;
    double y;
    char z;
};

struct NonStandard {
    virtual void foo() {}  // virtual function breaks standard layout
    int x;
};

struct MixedAccess {
public:
    int x;
private:
    int y;  // mixed access specifiers break standard layout
};

struct DerivedSimple : StandardLayout {
    // no additional non-static data members -> still standard layout
};

struct DerivedWithData : StandardLayout {
    int extra;  // data in both base and derived -> non-standard layout
};

int main() {
    std::cout << "=== std::is_standard_layout ===" << std::endl;

    std::cout << "int:              " << std::is_standard_layout<int>::value << std::endl;
    std::cout << "StandardLayout:   " << std::is_standard_layout<StandardLayout>::value << std::endl;
    std::cout << "NonStandard:      " << std::is_standard_layout<NonStandard>::value << std::endl;
    std::cout << "MixedAccess:      " << std::is_standard_layout<MixedAccess>::value << std::endl;
    std::cout << "DerivedSimple:    " << std::is_standard_layout<DerivedSimple>::value << std::endl;
    std::cout << "DerivedWithData:  " << std::is_standard_layout<DerivedWithData>::value << std::endl;

    static_assert(std::is_standard_layout<int>::value, "int is standard layout");
    static_assert(std::is_standard_layout<StandardLayout>::value, "simple struct is SL");
    static_assert(!std::is_standard_layout<NonStandard>::value, "virtual breaks SL");

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::is_standard_layout ===
// int:              1
// StandardLayout:   1
// NonStandard:      0
// MixedAccess:      0
// DerivedSimple:    1
// DerivedWithData:  0
//
// All checks passed!
