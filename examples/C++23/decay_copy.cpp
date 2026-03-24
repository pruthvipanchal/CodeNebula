// CodeNebula - C++23 Example: auto(x) and auto{x} Decay-Copy
// Compile: g++ -std=c++23 -Wall -Wextra -o example decay_copy.cpp
// Note: Requires GCC 13+ / Clang 16+ / MSVC 19.35+

// C++23 introduces auto(x) and auto{x} as explicit decay-copy expressions.
// They create a prvalue copy with array-to-pointer and function-to-pointer decay.
// Equivalent to: std::decay_t<decltype(x)>(x)

#include <iostream>
#include <type_traits>
#include <vector>
#include <algorithm>
#include <string>

void print_type_info(const char* label, bool is_ptr, bool is_array) {
    std::cout << "  " << label << ": is_pointer=" << is_ptr
              << ", is_array=" << is_array << std::endl;
}

int main() {
    std::cout << "=== auto(x) Decay-Copy ===" << std::endl;

    // Array decays to pointer
    int arr[5] = {1, 2, 3, 4, 5};
    auto decayed = auto(arr);  // int* (array-to-pointer decay)
    std::cout << "Array decay:" << std::endl;
    print_type_info("arr", std::is_pointer_v<decltype(arr)>,
                           std::is_array_v<decltype(arr)>);
    print_type_info("auto(arr)", std::is_pointer_v<decltype(decayed)>,
                                  std::is_array_v<decltype(decayed)>);

    // const ref decays to value copy
    std::cout << "\n=== Stripping references and const ===" << std::endl;
    const std::string& ref = "Hello";
    auto copy = auto(ref);  // std::string (not const std::string&)
    copy += " World";
    std::cout << "  Original ref: " << ref << std::endl;
    std::cout << "  Decayed copy: " << copy << std::endl;
    std::cout << "  is_reference(ref):  " << std::is_reference_v<decltype(ref)> << std::endl;
    std::cout << "  is_reference(copy): " << std::is_reference_v<decltype(copy)> << std::endl;

    // Practical use: passing a decayed copy into an algorithm
    std::cout << "\n=== Practical: sort a decay-copy of a container ===" << std::endl;
    std::vector<int> original = {5, 3, 1, 4, 2};
    // Sort a copy without modifying the original
    auto sorted = auto(original);  // prvalue copy
    std::sort(sorted.begin(), sorted.end());

    std::cout << "  Original: ";
    for (int v : original) std::cout << v << " ";
    std::cout << std::endl;
    std::cout << "  Sorted:   ";
    for (int v : sorted) std::cout << v << " ";
    std::cout << std::endl;

    // auto{x} brace form (same semantics, prevents narrowing)
    std::cout << "\n=== auto{x} brace form ===" << std::endl;
    double d = 3.14;
    auto d_copy = auto{d};
    std::cout << "  auto{3.14} = " << d_copy << std::endl;
    // auto{3.14} would fail if used where narrowing occurs

    return 0;
}

/*
Expected output:
=== auto(x) Decay-Copy ===
Array decay:
  arr: is_pointer=0, is_array=1
  auto(arr): is_pointer=1, is_array=0

=== Stripping references and const ===
  Original ref: Hello
  Decayed copy: Hello World
  is_reference(ref):  1
  is_reference(copy): 0

=== Practical: sort a decay-copy of a container ===
  Original: 5 3 1 4 2
  Sorted:   1 2 3 4 5

=== auto{x} brace form ===
  auto{3.14} = 3.14
*/
