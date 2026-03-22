// CodeNebula - C++98 Example: std::logical_not
// Compile: g++ -std=c++98 -Wall -Wextra -o example logical_not.cpp

#include <iostream>
#include <functional>
#include <algorithm>

int main() {
    bool arr[] = {true, false, true, false, true};
    bool result[5];

    // Negate each boolean value
    std::transform(arr, arr + 5, result, std::logical_not<bool>());

    std::cout << "Original: ";
    for (int i = 0; i < 5; ++i) std::cout << arr[i] << " ";
    std::cout << std::endl;

    std::cout << "Negated:  ";
    for (int i = 0; i < 5; ++i) std::cout << result[i] << " ";
    std::cout << std::endl;

    // Count false values by counting logical_not == true
    int false_count = std::count_if(arr, arr + 5, std::logical_not<bool>());
    std::cout << "False count: " << false_count << std::endl;

    // Count true values using not1(logical_not)
    int true_count = std::count_if(arr, arr + 5,
                                   std::not1(std::logical_not<bool>()));
    std::cout << "True count: " << true_count << std::endl;

    return 0;
}

// Expected output:
// Original: 1 0 1 0 1
// Negated:  0 1 0 1 0
// False count: 2
// True count: 3
