// CodeNebula - C++98 Example: std::logical_and
// Compile: g++ -std=c++98 -Wall -Wextra -o example logical_and.cpp

#include <iostream>
#include <functional>
#include <algorithm>

int main() {
    bool a[] = {true, true, false, true, false};
    bool b[] = {true, false, false, true, true};
    bool result[5];

    // Element-wise logical AND
    std::transform(a, a + 5, b, result, std::logical_and<bool>());

    std::cout << "a:         ";
    for (int i = 0; i < 5; ++i) std::cout << a[i] << " ";
    std::cout << std::endl;

    std::cout << "b:         ";
    for (int i = 0; i < 5; ++i) std::cout << b[i] << " ";
    std::cout << std::endl;

    std::cout << "a AND b:   ";
    for (int i = 0; i < 5; ++i) std::cout << result[i] << " ";
    std::cout << std::endl;

    // Check if all elements are true (fold with logical_and)
    bool all_a = true;
    for (int i = 0; i < 5; ++i) all_a = std::logical_and<bool>()(all_a, a[i]);
    std::cout << "All true in a: " << (all_a ? "yes" : "no") << std::endl;

    return 0;
}

// Expected output:
// a:         1 1 0 1 0
// b:         1 0 0 1 1
// a AND b:   1 0 0 1 0
// All true in a: no
