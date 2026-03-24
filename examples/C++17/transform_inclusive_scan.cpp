// CodeNebula - C++17 Example: std::transform_inclusive_scan
// Compile: g++ -std=c++17 -Wall -Wextra -o example transform_inclusive_scan.cpp

// Demonstrates std::transform_inclusive_scan, which fuses a unary transform
// with an inclusive prefix scan. Each element is first transformed, then
// accumulated with previous results. More efficient than separate
// transform + inclusive_scan calls.

#include <iostream>
#include <numeric>
#include <vector>
#include <functional>
#include <string>
#include <cmath>

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
    // 1. Running sum of squares
    // ------------------------------------------------------------------
    std::cout << "=== running sum of squares ===" << std::endl;
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int> result(v.size());

    // For each i: result[i] = v[0]^2 + v[1]^2 + ... + v[i]^2
    std::transform_inclusive_scan(
        v.begin(), v.end(), result.begin(),
        std::plus<>{},                  // reduce: sum
        [](int x) { return x * x; }    // transform: square
    );

    print("input  ", v);
    print("sq_scan", result);
    // {1, 1+4, 1+4+9, 1+4+9+16, 1+4+9+16+25} = {1, 5, 14, 30, 55}

    // ------------------------------------------------------------------
    // 2. Running sum of absolute values
    // ------------------------------------------------------------------
    std::cout << "\n=== running sum of absolute values ===" << std::endl;
    std::vector<int> mixed = {3, -1, 4, -1, 5, -9};
    std::vector<int> abs_scan(mixed.size());

    std::transform_inclusive_scan(
        mixed.begin(), mixed.end(), abs_scan.begin(),
        std::plus<>{},
        [](int x) { return std::abs(x); }
    );

    print("input   ", mixed);
    print("abs_scan", abs_scan);
    // {3, 3+1, 3+1+4, 3+1+4+1, 3+1+4+1+5, 3+1+4+1+5+9} = {3, 4, 8, 9, 14, 23}

    // ------------------------------------------------------------------
    // 3. With initial value
    // ------------------------------------------------------------------
    std::cout << "\n=== with initial value ===" << std::endl;
    std::vector<int> data = {1, 2, 3};
    std::vector<int> with_init(data.size());

    std::transform_inclusive_scan(
        data.begin(), data.end(), with_init.begin(),
        std::plus<>{},
        [](int x) { return x * 10; },  // transform: multiply by 10
        100                              // initial value
    );

    print("input    ", data);
    print("scan+100 ", with_init);
    // {100+10, 100+10+20, 100+10+20+30} = {110, 130, 160}

    // ------------------------------------------------------------------
    // 4. Cumulative doubled values
    // ------------------------------------------------------------------
    std::cout << "\n=== cumulative doubled values ===" << std::endl;
    std::vector<int> nums = {5, 3, 8, 2, 7};
    std::vector<int> doubled_scan(nums.size());

    std::transform_inclusive_scan(
        nums.begin(), nums.end(), doubled_scan.begin(),
        std::plus<>{},
        [](int x) { return x * 2; }
    );

    print("input  ", nums);
    print("2x_scan", doubled_scan);
    // {10, 10+6, 10+6+16, 10+6+16+4, 10+6+16+4+14} = {10, 16, 32, 36, 50}

    // ------------------------------------------------------------------
    // 5. Running product of incremented values
    // ------------------------------------------------------------------
    std::cout << "\n=== running product of (x+1) ===" << std::endl;
    std::vector<int> base = {1, 2, 3, 4};
    std::vector<int> prod_scan(base.size());

    std::transform_inclusive_scan(
        base.begin(), base.end(), prod_scan.begin(),
        std::multiplies<>{},
        [](int x) { return x + 1; }
    );

    print("input    ", base);
    print("prod(x+1)", prod_scan);
    // {2, 2*3, 2*3*4, 2*3*4*5} = {2, 6, 24, 120}

    // ------------------------------------------------------------------
    // 6. Practical: running total of discounted prices
    // ------------------------------------------------------------------
    std::cout << "\n=== running total (10% discount) ===" << std::endl;
    std::vector<double> prices = {100.0, 50.0, 75.0, 200.0};
    std::vector<double> running(prices.size());

    std::transform_inclusive_scan(
        prices.begin(), prices.end(), running.begin(),
        std::plus<>{},
        [](double p) { return p * 0.9; }  // 10% discount
    );

    print_d("prices ", prices);
    print_d("running", running);
    // {90, 90+45, 90+45+67.5, 90+45+67.5+180} = {90, 135, 202.5, 382.5}

    return 0;
}

/*
Expected output:

=== running sum of squares ===
  input  : 1 2 3 4 5
  sq_scan: 1 5 14 30 55

=== running sum of absolute values ===
  input   : 3 -1 4 -1 5 -9
  abs_scan: 3 4 8 9 14 23

=== with initial value ===
  input    : 1 2 3
  scan+100 : 110 130 160

=== cumulative doubled values ===
  input  : 5 3 8 2 7
  2x_scan: 10 16 32 36 50

=== running product of (x+1) ===
  input    : 1 2 3 4
  prod(x+1): 2 6 24 120

=== running total (10% discount) ===
  prices : 100 50 75 200
  running: 90 135 202.5 382.5
*/
