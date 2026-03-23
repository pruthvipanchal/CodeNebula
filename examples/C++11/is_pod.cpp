// CodeNebula - C++11 Example: is_pod
// Compile: g++ -std=c++11 -Wall -Wextra -o example is_pod.cpp

// Demonstrates std::is_pod (Plain Old Data) which checks if a type is
// both trivial and standard-layout. POD types are compatible with C structs.
// Note: std::is_pod is deprecated in C++20; use is_trivial + is_standard_layout.

#include <iostream>
#include <type_traits>
#include <string>

struct PodType {
    int x;
    double y;
    char name[20];
};

struct NonPod {
    std::string name;  // string is neither trivial nor standard-layout
};

struct WithVirtual {
    virtual void foo() {}
    int x;
};

struct WithConstructor {
    WithConstructor() : x(0) {}
    int x;
};

int main() {
    std::cout << "=== std::is_pod ===" << std::endl;

    std::cout << "int:              " << std::is_pod<int>::value << std::endl;
    std::cout << "double:           " << std::is_pod<double>::value << std::endl;
    std::cout << "PodType:          " << std::is_pod<PodType>::value << std::endl;
    std::cout << "int[10]:          " << std::is_pod<int[10]>::value << std::endl;
    std::cout << "NonPod:           " << std::is_pod<NonPod>::value << std::endl;
    std::cout << "WithVirtual:      " << std::is_pod<WithVirtual>::value << std::endl;
    std::cout << "WithConstructor:  " << std::is_pod<WithConstructor>::value << std::endl;

    // POD = trivial + standard_layout
    std::cout << "\nPodType is trivial:          "
              << std::is_trivial<PodType>::value << std::endl;
    std::cout << "PodType is standard_layout:  "
              << std::is_standard_layout<PodType>::value << std::endl;

    static_assert(std::is_pod<int>::value, "int is POD");
    static_assert(std::is_pod<PodType>::value, "PodType is POD");
    static_assert(!std::is_pod<std::string>::value, "string is not POD");

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::is_pod ===
// int:              1
// double:           1
// PodType:          1
// int[10]:          1
// NonPod:           0
// WithVirtual:      0
// WithConstructor:  0
//
// PodType is trivial:          1
// PodType is standard_layout:  1
//
// All checks passed!
