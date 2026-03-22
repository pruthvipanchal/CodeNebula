// CodeNebula - C++98 Example: std::adjacent_difference
// Compile: g++ -std=c++98 -Wall -Wextra -o example adjacent_difference.cpp

#include <iostream>
#include <numeric>
#include <functional>
#include <iterator>

int main() {
    int arr[] = {1, 3, 6, 10, 15};
    int result[5];

    // Compute differences: result[0]=arr[0], result[i]=arr[i]-arr[i-1]
    std::adjacent_difference(arr, arr + 5, result);

    std::cout << "Original:    ";
    std::copy(arr, arr + 5, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::cout << "Differences: ";
    std::copy(result, result + 5, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // Custom operation: adjacent ratios
    double data[] = {1.0, 2.0, 6.0, 24.0, 120.0};
    double ratios[5];
    std::adjacent_difference(data, data + 5, ratios, std::divides<double>());

    // Note: first element is copied as-is, rest are data[i]/data[i-1]
    std::cout << "Ratios: ";
    for (int i = 0; i < 5; ++i) std::cout << ratios[i] << " ";
    std::cout << std::endl;

    // adjacent_difference is the inverse of partial_sum
    int sums[] = {1, 3, 6, 10, 15};
    std::adjacent_difference(sums, sums + 5, result);
    std::cout << "Inverse of partial_sum: ";
    std::copy(result, result + 5, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Original:    1 3 6 10 15
// Differences: 1 2 3 4 5
// Ratios: 1 2 3 4 5
// Inverse of partial_sum: 1 2 3 4 5
