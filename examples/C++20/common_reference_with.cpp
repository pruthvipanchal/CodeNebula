// CodeNebula - C++20 Example: std::common_reference_with Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example common_reference_with.cpp

// std::common_reference_with<T, U> checks that two types share a common
// reference type to which both can be converted. This is fundamental to
// how C++20 ranges and iterators compare mixed types.

#include <concepts>
#include <iostream>
#include <type_traits>

// Accept two parameters that share a common reference type
template <typename T, typename U>
    requires std::common_reference_with<T, U>
void show_common_ref(T a, U b) {
    using Common = std::common_reference_t<T, U>;
    Common ca = a;
    Common cb = b;
    std::cout << "  a as common: " << ca << ", b as common: " << cb << "\n";
}

// Check and report common reference relationship
template <typename T, typename U>
void check_common_ref(const char* t_name, const char* u_name) {
    constexpr bool has_common = std::common_reference_with<T, U>;
    std::cout << t_name << " & " << u_name
              << " have common reference: " << has_common << "\n";
}

int main() {
    // int and double share a common reference (double)
    std::cout << "int and double:\n";
    show_common_ref(42, 3.14);

    // int and long share a common reference (long)
    std::cout << "int and long:\n";
    show_common_ref(10, 20L);

    // int& and const int& share a common reference (const int&)
    std::cout << "float and double:\n";
    show_common_ref(1.5f, 2.5);

    // Check various type pairs
    std::cout << "\nCommon reference checks:\n";
    check_common_ref<int, double>("int", "double");
    check_common_ref<int, long>("int", "long");
    check_common_ref<int&, const int&>("int&", "const int&");
    check_common_ref<float, double>("float", "double");
    check_common_ref<short, int>("short", "int");

    // Show what the common reference type resolves to
    std::cout << "\nCommon reference type sizes:\n";
    std::cout << "int & double -> size: "
              << sizeof(std::common_reference_t<int, double>) << "\n";
    std::cout << "short & long -> size: "
              << sizeof(std::common_reference_t<short, long>) << "\n";

    return 0;
}

// Expected output:
// int and double:
//   a as common: 42, b as common: 3.14
// int and long:
//   a as common: 10, b as common: 20
// float and double:
//   a as common: 1.5, b as common: 2.5
//
// Common reference checks:
// int & double have common reference: 1
// int & long have common reference: 1
// int& & const int& have common reference: 1
// float & double have common reference: 1
// short & int have common reference: 1
//
// Common reference type sizes:
// int & double -> size: 8
// short & long -> size: 8
