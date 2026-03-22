// CodeNebula - C++98 Example: ostream_iterator
// Compile: g++ -std=c++98 -Wall -Wextra -o example ostream_iterator.cpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
    int arr[] = {1, 2, 3, 4, 5};

    // ostream_iterator writes to an output stream
    std::cout << "With comma delimiter: ";
    std::copy(arr, arr + 5, std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;

    std::cout << "With space delimiter: ";
    std::copy(arr, arr + 5, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // Use with transform to output doubled values
    std::vector<int> v;
    for (int i = 0; i < 5; ++i) v.push_back(arr[i]);

    std::cout << "Doubled values: ";
    std::transform(v.begin(), v.end(),
                   std::ostream_iterator<int>(std::cout, " "),
                   std::bind1st(std::multiplies<int>(), 2));
    std::cout << std::endl;

    return 0;
}

// Expected output:
// With comma delimiter: 1, 2, 3, 4, 5,
// With space delimiter: 1 2 3 4 5
// Doubled values: 2 4 6 8 10
