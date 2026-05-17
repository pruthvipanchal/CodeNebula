// CodeNebula - C++98 Example: binder1st / bind1st()
// Compile: g++ -std=c++98 -Wall -Wextra -o example binder1st.cpp

#include <iostream>
#include <functional>
#include <algorithm>

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = 8;

    // bind1st(less, 4) creates: 4 < x, i.e., x > 4
    int count = std::count_if(arr, arr + n,
                              std::bind1st(std::less<int>(), 4));
    std::cout << "Elements > 4: " << count << std::endl;

    // bind1st(minus, 10) creates: 10 - x
    int result[8];
    std::transform(arr, arr + n, result,
                   std::bind1st(std::minus<int>(), 10));

    std::cout << "10 - each: ";
    for (int i = 0; i < n; ++i) std::cout << result[i] << " ";
    std::cout << std::endl;

    // bind1st(multiplies, 3) creates: 3 * x
    std::transform(arr, arr + n, result,
                   std::bind1st(std::multiplies<int>(), 3));

    std::cout << "3 * each: ";
    for (int i = 0; i < n; ++i) std::cout << result[i] << " ";
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Elements > 4: 4
// 10 - each: 9 8 7 6 5 4 3 2
// 3 * each: 3 6 9 12 15 18 21 24
