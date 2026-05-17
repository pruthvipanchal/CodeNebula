// CodeNebula - C++98 Example: std::accumulate
// Compile: g++ -std=c++98 -Wall -Wextra -o example accumulate.cpp

#include <iostream>
#include <numeric>
#include <functional>
#include <vector>
#include <string>

std::string concat(const std::string& a, int b) {
    char buf[20];
    std::sprintf(buf, "%d", b);
    return a + (a.empty() ? "" : ", ") + buf;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};

    // Simple sum
    int sum = std::accumulate(arr, arr + 5, 0);
    std::cout << "Sum: " << sum << std::endl;

    // Product using multiplies
    int product = std::accumulate(arr, arr + 5, 1, std::multiplies<int>());
    std::cout << "Product: " << product << std::endl;

    // Custom fold: build a comma-separated string
    std::vector<int> v(arr, arr + 5);
    std::string result = std::accumulate(v.begin(), v.end(),
                                         std::string(""), concat);
    std::cout << "Joined: " << result << std::endl;

    // Sum of squares using a custom binary operation
    // accumulate(init, op) where op(acc, elem) = acc + elem*elem
    int sum_sq = 0;
    for (int i = 0; i < 5; ++i) sum_sq += arr[i] * arr[i];
    std::cout << "Sum of squares: " << sum_sq << std::endl;

    return 0;
}

// Expected output:
// Sum: 15
// Product: 120
// Joined: 1, 2, 3, 4, 5
// Sum of squares: 55
