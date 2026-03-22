// CodeNebula - C++98 Example: <cstdlib> functions
// Compile: g++ -std=c++98 -Wall -Wextra -o example cstdlib.cpp

#include <iostream>
#include <cstdlib>

int compare_ints(const void* a, const void* b) {
    return (*(const int*)a - *(const int*)b);
}

int main() {
    // rand and srand - pseudo-random numbers
    std::srand(42); // fixed seed for reproducible output
    std::cout << "Random numbers (seed=42): ";
    for (int i = 0; i < 5; ++i) {
        std::cout << (std::rand() % 100) << " ";
    }
    std::cout << std::endl;

    // String to number conversions
    std::cout << "atoi(\"123\") = " << std::atoi("123") << std::endl;
    std::cout << "atof(\"3.14\") = " << std::atof("3.14") << std::endl;
    std::cout << "atol(\"999999\") = " << std::atol("999999") << std::endl;

    // strtol with error checking
    char* end;
    long val = std::strtol("0xFF", &end, 16);
    std::cout << "strtol(\"0xFF\", 16) = " << val << std::endl;

    // abs and div
    std::cout << "abs(-42) = " << std::abs(-42) << std::endl;
    std::div_t d = std::div(17, 5);
    std::cout << "div(17,5): quot=" << d.quot << " rem=" << d.rem << std::endl;

    // qsort
    int arr[] = {5, 2, 8, 1, 9, 3};
    std::qsort(arr, 6, sizeof(int), compare_ints);
    std::cout << "qsorted: ";
    for (int i = 0; i < 6; ++i) std::cout << arr[i] << " ";
    std::cout << std::endl;

    // bsearch on sorted array
    int key = 5;
    int* found = (int*)std::bsearch(&key, arr, 6, sizeof(int), compare_ints);
    std::cout << "bsearch(5): " << (found ? "found" : "not found") << std::endl;

    return 0;
}

// Expected output (rand values are implementation-dependent):
// Random numbers (seed=42): <5 numbers>
// atoi("123") = 123
// atof("3.14") = 3.14
// atol("999999") = 999999
// strtol("0xFF", 16) = 255
// abs(-42) = 42
// div(17,5): quot=3 rem=2
// qsorted: 1 2 3 5 8 9
// bsearch(5): found
