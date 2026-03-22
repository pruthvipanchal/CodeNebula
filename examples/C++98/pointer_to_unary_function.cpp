// CodeNebula - C++98 Example: pointer_to_unary_function / ptr_fun (unary)
// Compile: g++ -std=c++98 -Wall -Wextra -o example pointer_to_unary_function.cpp

#include <iostream>
#include <functional>
#include <algorithm>
#include <cstdlib>
#include <cctype>

bool is_upper(char c) {
    return std::isupper(static_cast<unsigned char>(c)) != 0;
}

int absolute(int x) {
    return std::abs(x);
}

int main() {
    // ptr_fun wraps a plain function pointer into a functor
    // This allows it to work with not1, bind1st, bind2nd

    // Count uppercase characters using ptr_fun
    char str[] = "Hello World ABC";
    int len = 15;
    int upper_count = std::count_if(str, str + len,
                                    std::ptr_fun(is_upper));
    std::cout << "Uppercase chars: " << upper_count << std::endl;

    // Use not1 with ptr_fun to count non-uppercase
    int non_upper = std::count_if(str, str + len,
                                  std::not1(std::ptr_fun(is_upper)));
    std::cout << "Non-uppercase chars: " << non_upper << std::endl;

    // Transform with ptr_fun(absolute)
    int arr[] = {-3, 5, -7, 2, -1};
    int result[5];
    std::transform(arr, arr + 5, result, std::ptr_fun(absolute));

    std::cout << "Absolute values: ";
    for (int i = 0; i < 5; ++i) std::cout << result[i] << " ";
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Uppercase chars: 6
// Non-uppercase chars: 9
// Absolute values: 3 5 7 2 1
