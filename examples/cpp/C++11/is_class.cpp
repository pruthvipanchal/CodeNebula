// CodeNebula - C++11 Example: is_class
// Compile: g++ -std=c++11 -Wall -Wextra -o example is_class.cpp

// Demonstrates std::is_class to check if a type is a class or struct.
// Note: unions are NOT classes; enums are NOT classes.

#include <iostream>
#include <type_traits>
#include <string>
#include <vector>

struct MyStruct { int x; };
class MyClass { int x; };
union MyUnion { int i; float f; };
enum MyEnum { A, B };
enum class MyEnumClass { X, Y };

int main() {
    std::cout << "=== std::is_class ===" << std::endl;

    std::cout << "MyStruct:        " << std::is_class<MyStruct>::value << std::endl;
    std::cout << "MyClass:         " << std::is_class<MyClass>::value << std::endl;
    std::cout << "std::string:     " << std::is_class<std::string>::value << std::endl;
    std::cout << "std::vector<int>:" << std::is_class<std::vector<int>>::value << std::endl;
    std::cout << "MyUnion:         " << std::is_class<MyUnion>::value << std::endl;
    std::cout << "MyEnum:          " << std::is_class<MyEnum>::value << std::endl;
    std::cout << "MyEnumClass:     " << std::is_class<MyEnumClass>::value << std::endl;
    std::cout << "int:             " << std::is_class<int>::value << std::endl;
    std::cout << "int*:            " << std::is_class<int*>::value << std::endl;

    static_assert(std::is_class<MyStruct>::value, "struct is a class");
    static_assert(std::is_class<MyClass>::value, "class is a class");
    static_assert(!std::is_class<MyUnion>::value, "union is not a class");
    static_assert(!std::is_class<int>::value, "int is not a class");
    static_assert(!std::is_class<MyEnum>::value, "enum is not a class");

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::is_class ===
// MyStruct:        1
// MyClass:         1
// std::string:     1
// std::vector<int>:1
// MyUnion:         0
// MyEnum:          0
// MyEnumClass:     0
// int:             0
// int*:            0
//
// All checks passed!
