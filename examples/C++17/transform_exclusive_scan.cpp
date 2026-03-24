// CodeNebula - C++17 Example: std::transform_exclusive_scan
// Compile: g++ -std=c++17 -Wall -Wextra -o example transform_exclusive_scan.cpp

// std::transform_exclusive_scan applies a unary transform to each element,
// then computes an exclusive prefix scan (each output excludes the current
// transformed element). It fuses transform + exclusive_scan in one pass.

#include <iostream>
#include <numeric>
#include <vector>
#include <functional>
#include <string>

int main() {
    // --- Basic: square then exclusive scan ---
    std::cout << "=== Square + exclusive scan ===" << std::endl;
    std::vector<int> input = {1, 2, 3, 4, 5};
    std::vector<int> result(input.size());

    std::transform_exclusive_scan(
        input.begin(), input.end(), result.begin(),
        0,                                      // initial value
        std::plus<>{},                           // binary op (accumulate)
        [](int x) { return x * x; }             // unary transform
    );

    std::cout << "Input:     ";
    for (int v : input) std::cout << v << " ";
    std::cout << std::endl;
    std::cout << "Squared:   ";
    for (int v : input) std::cout << (v * v) << " ";
    std::cout << std::endl;
    std::cout << "Exc. scan: ";
    for (int v : result) std::cout << v << " ";
    std::cout << std::endl;
    // result[i] = init + sum of x*x for j < i
    // [0, 1, 5, 14, 30]

    // --- Double then exclusive scan with multiply ---
    std::cout << "\n=== Double + multiply exclusive scan ===" << std::endl;
    std::vector<int> vals = {1, 2, 3, 4};
    std::vector<int> prod(vals.size());

    std::transform_exclusive_scan(
        vals.begin(), vals.end(), prod.begin(),
        1,                                       // identity for multiplication
        std::multiplies<>{},                     // binary op
        [](int x) { return x * 2; }             // double each element
    );

    std::cout << "Input:     ";
    for (int v : vals) std::cout << v << " ";
    std::cout << std::endl;
    std::cout << "Exc. scan: ";
    for (int v : prod) std::cout << v << " ";
    std::cout << std::endl;
    // doubled: 2, 4, 6, 8
    // exclusive product scan: [1, 2, 8, 48]

    // --- String length prefix sums ---
    std::cout << "\n=== String lengths exclusive scan ===" << std::endl;
    std::vector<std::string> words = {"hi", "hello", "world", "!"};
    std::vector<int> offsets(words.size());

    std::transform_exclusive_scan(
        words.begin(), words.end(), offsets.begin(),
        0,
        std::plus<>{},
        [](const std::string& s) { return static_cast<int>(s.size()); }
    );

    std::cout << "Words:   ";
    for (const auto& w : words) std::cout << "\"" << w << "\" ";
    std::cout << std::endl;
    std::cout << "Offsets: ";
    for (int v : offsets) std::cout << v << " ";
    std::cout << std::endl;
    // offsets: [0, 2, 7, 12] (start position of each word)

    // --- With initial value ---
    std::cout << "\n=== With initial value 100 ===" << std::endl;
    std::vector<int> data = {1, 2, 3};
    std::vector<int> out(data.size());

    std::transform_exclusive_scan(
        data.begin(), data.end(), out.begin(),
        100, std::plus<>{}, [](int x) { return x; }
    );

    std::cout << "Result: ";
    for (int v : out) std::cout << v << " ";
    std::cout << std::endl;
    // [100, 101, 103]

    return 0;
}

/*
Expected output:
=== Square + exclusive scan ===
Input:     1 2 3 4 5
Squared:   1 4 9 16 25
Exc. scan: 0 1 5 14 30

=== Double + multiply exclusive scan ===
Input:     1 2 3 4
Exc. scan: 1 2 8 48

=== String lengths exclusive scan ===
Words:   "hi" "hello" "world" "!"
Offsets: 0 2 7 12

=== With initial value 100 ===
Result: 100 101 103
*/
