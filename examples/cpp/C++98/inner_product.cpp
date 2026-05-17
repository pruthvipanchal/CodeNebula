// CodeNebula - C++98 Example: std::inner_product
// Compile: g++ -std=c++98 -Wall -Wextra -o example inner_product.cpp

#include <iostream>
#include <numeric>
#include <functional>

int main() {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {2, 3, 4, 5, 6};

    // Dot product: sum of a[i]*b[i]
    // 1*2 + 2*3 + 3*4 + 4*5 + 5*6 = 2+6+12+20+30 = 70
    int dot = std::inner_product(a, a + 5, b, 0);
    std::cout << "Dot product: " << dot << std::endl;

    // Custom inner_product: count matching elements
    // Use plus for outer op, equal_to for inner op
    int c[] = {1, 9, 3, 9, 5};
    int matches = std::inner_product(a, a + 5, c, 0,
                                     std::plus<int>(),
                                     std::equal_to<int>());
    std::cout << "Matching elements: " << matches << std::endl;

    // Sum of absolute differences (Manhattan distance)
    // Use plus for outer, custom for inner
    // We'll compute manually since C++98 lacks abs functor
    int sum_diff = 0;
    for (int i = 0; i < 5; ++i) {
        int diff = a[i] - b[i];
        sum_diff += (diff < 0) ? -diff : diff;
    }
    std::cout << "Manhattan distance: " << sum_diff << std::endl;

    return 0;
}

// Expected output:
// Dot product: 70
// Matching elements: 3
// Manhattan distance: 5
