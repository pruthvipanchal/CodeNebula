// CodeNebula - C++98 Example: std::logical_or
// Compile: g++ -std=c++98 -Wall -Wextra -o example logical_or.cpp

#include <iostream>
#include <functional>
#include <algorithm>

int main() {
    bool a[] = {true, true, false, false};
    bool b[] = {true, false, true, false};
    bool result[4];

    // Element-wise logical OR
    std::transform(a, a + 4, b, result, std::logical_or<bool>());

    std::cout << "a:        ";
    for (int i = 0; i < 4; ++i) std::cout << a[i] << " ";
    std::cout << std::endl;

    std::cout << "b:        ";
    for (int i = 0; i < 4; ++i) std::cout << b[i] << " ";
    std::cout << std::endl;

    std::cout << "a OR b:   ";
    for (int i = 0; i < 4; ++i) std::cout << result[i] << " ";
    std::cout << std::endl;

    // Check if any element is true (fold with logical_or)
    bool arr[] = {false, false, true, false};
    bool any = false;
    for (int i = 0; i < 4; ++i) any = std::logical_or<bool>()(any, arr[i]);
    std::cout << "Any true in {0,0,1,0}: " << (any ? "yes" : "no") << std::endl;

    return 0;
}

// Expected output:
// a:        1 1 0 0
// b:        1 0 1 0
// a OR b:   1 1 1 0
// Any true in {0,0,1,0}: yes
