// CodeNebula - C++17 Example: std::inclusive_scan
// Compile: g++ -std=c++17 -Wall -Wextra -o example inclusive_scan.cpp

// Demonstrates std::inclusive_scan, which computes running totals (prefix sums)
// where each output element includes the current input element. Unlike
// std::partial_sum, inclusive_scan allows out-of-order execution, making it
// suitable for parallel execution policies.

#include <iostream>
#include <numeric>
#include <vector>
#include <functional>

void print(const std::string& label, const std::vector<int>& v) {
    std::cout << "  " << label << ": ";
    for (int x : v) std::cout << x << " ";
    std::cout << std::endl;
}

void print_d(const std::string& label, const std::vector<double>& v) {
    std::cout << "  " << label << ": ";
    for (double x : v) std::cout << x << " ";
    std::cout << std::endl;
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic inclusive scan (running sum)
    // ------------------------------------------------------------------
    std::cout << "=== basic inclusive scan (sum) ===" << std::endl;
    std::vector<int> input = {1, 2, 3, 4, 5};
    std::vector<int> result(input.size());

    // output[i] = input[0] + input[1] + ... + input[i]
    std::inclusive_scan(input.begin(), input.end(), result.begin());

    print("input ", input);
    print("scan  ", result);
    // {1, 1+2, 1+2+3, 1+2+3+4, 1+2+3+4+5} = {1, 3, 6, 10, 15}

    // ------------------------------------------------------------------
    // 2. Inclusive scan with custom operation (running product)
    // ------------------------------------------------------------------
    std::cout << "\n=== inclusive scan (product) ===" << std::endl;
    std::vector<int> factors = {1, 2, 3, 4, 5};
    std::vector<int> products(factors.size());

    std::inclusive_scan(factors.begin(), factors.end(), products.begin(),
                        std::multiplies<>{});

    print("input   ", factors);
    print("product ", products);
    // {1, 1*2, 1*2*3, 1*2*3*4, 1*2*3*4*5} = {1, 2, 6, 24, 120}

    // ------------------------------------------------------------------
    // 3. Inclusive scan with initial value
    // ------------------------------------------------------------------
    std::cout << "\n=== inclusive scan with init ===" << std::endl;
    std::vector<int> data = {10, 20, 30};
    std::vector<int> with_init(data.size());

    std::inclusive_scan(data.begin(), data.end(), with_init.begin(),
                        std::plus<>{}, 100);  // init = 100

    print("input    ", data);
    print("scan+100 ", with_init);
    // {100+10, 100+10+20, 100+10+20+30} = {110, 130, 160}

    // ------------------------------------------------------------------
    // 4. Running maximum
    // ------------------------------------------------------------------
    std::cout << "\n=== running maximum ===" << std::endl;
    std::vector<int> vals = {3, 1, 4, 1, 5, 9, 2, 6};
    std::vector<int> maxes(vals.size());

    std::inclusive_scan(vals.begin(), vals.end(), maxes.begin(),
        [](int a, int b) { return a > b ? a : b; });

    print("input  ", vals);
    print("max_so_far", maxes);
    // {3, 3, 4, 4, 5, 9, 9, 9}

    // ------------------------------------------------------------------
    // 5. In-place scan
    // ------------------------------------------------------------------
    std::cout << "\n=== in-place scan ===" << std::endl;
    std::vector<int> inplace = {5, 3, 8, 2, 7};
    print("before", inplace);
    std::inclusive_scan(inplace.begin(), inplace.end(), inplace.begin());
    print("after ", inplace);

    // ------------------------------------------------------------------
    // 6. Practical: cumulative scores
    // ------------------------------------------------------------------
    std::cout << "\n=== cumulative scores ===" << std::endl;
    std::vector<int> scores = {15, 22, 18, 25, 20};
    std::vector<int> cumulative(scores.size());
    std::inclusive_scan(scores.begin(), scores.end(), cumulative.begin());

    print("round scores", scores);
    print("total after ", cumulative);

    return 0;
}

/*
Expected output:

=== basic inclusive scan (sum) ===
  input : 1 2 3 4 5
  scan  : 1 3 6 10 15

=== inclusive scan (product) ===
  input   : 1 2 3 4 5
  product : 1 2 6 24 120

=== inclusive scan with init ===
  input    : 10 20 30
  scan+100 : 110 130 160

=== running maximum ===
  input  : 3 1 4 1 5 9 2 6
  max_so_far: 3 3 4 4 5 9 9 9

=== in-place scan ===
  before: 5 3 8 2 7
  after : 5 8 16 18 25

=== cumulative scores ===
  round scores: 15 22 18 25 20
  total after : 15 37 55 80 100
*/
