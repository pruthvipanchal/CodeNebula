// CodeNebula - C++98 Example: for_each
// Compile: g++ -std=c++98 -Wall -Wextra -o example for_each.cpp

// std::for_each applies a function to every element in a range [first, last).
// It returns the function object after processing all elements, which can be
// useful if the function accumulates state.

#include <iostream>
#include <vector>
#include <algorithm>

void print_element(int x) {
    std::cout << x << " ";
}

struct Sum {
    int total;
    Sum() : total(0) {}
    void operator()(int x) { total += x; }
};

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    std::vector<int> v(arr, arr + 5);

    // Apply a free function to print each element
    std::cout << "Elements: ";
    std::for_each(v.begin(), v.end(), print_element);
    std::cout << std::endl;

    // Use a functor to accumulate a sum
    Sum result = std::for_each(v.begin(), v.end(), Sum());
    std::cout << "Sum: " << result.total << std::endl;

    // Apply to a sub-range
    std::cout << "First three: ";
    std::for_each(v.begin(), v.begin() + 3, print_element);
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Elements: 10 20 30 40 50
// Sum: 150
// First three: 10 20 30
