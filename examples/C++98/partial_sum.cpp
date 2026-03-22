// CodeNebula - C++98 Example: std::partial_sum
// Compile: g++ -std=c++98 -Wall -Wextra -o example partial_sum.cpp

#include <iostream>
#include <numeric>
#include <functional>
#include <iterator>

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int result[5];

    // Running sum: result[i] = arr[0] + arr[1] + ... + arr[i]
    std::partial_sum(arr, arr + 5, result);

    std::cout << "Original:    ";
    std::copy(arr, arr + 5, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::cout << "Partial sum: ";
    std::copy(result, result + 5, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // Running product using multiplies
    std::partial_sum(arr, arr + 5, result, std::multiplies<int>());

    std::cout << "Partial product: ";
    std::copy(result, result + 5, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // Fibonacci-like: partial_sum on all 1s gives 1,2,3,4,5
    int ones[] = {1, 1, 1, 1, 1};
    std::partial_sum(ones, ones + 5, result);

    std::cout << "Partial sum of 1s: ";
    std::copy(result, result + 5, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Original:    1 2 3 4 5
// Partial sum: 1 3 6 10 15
// Partial product: 1 2 6 24 120
// Partial sum of 1s: 1 2 3 4 5
