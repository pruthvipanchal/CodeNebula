// CodeNebula - C++17 Example: std::exclusive_scan
// Compile: g++ -std=c++17 -Wall -Wextra -o example exclusive_scan.cpp

// Demonstrates std::exclusive_scan, which computes running totals (prefix sums)
// where each output element EXCLUDES the current input element. The first output
// is always the initial value. This is the complement of inclusive_scan.

#include <iostream>
#include <numeric>
#include <vector>
#include <functional>

void print(const std::string& label, const std::vector<int>& v) {
    std::cout << "  " << label << ": ";
    for (int x : v) std::cout << x << " ";
    std::cout << std::endl;
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic exclusive scan (running sum, excluding current)
    // ------------------------------------------------------------------
    std::cout << "=== basic exclusive scan ===" << std::endl;
    std::vector<int> input = {1, 2, 3, 4, 5};
    std::vector<int> result(input.size());

    // output[i] = init + input[0] + ... + input[i-1]  (excludes input[i])
    std::exclusive_scan(input.begin(), input.end(), result.begin(), 0);

    print("input ", input);
    print("scan  ", result);
    // {0, 0+1, 0+1+2, 0+1+2+3, 0+1+2+3+4} = {0, 1, 3, 6, 10}

    // ------------------------------------------------------------------
    // 2. With non-zero initial value
    // ------------------------------------------------------------------
    std::cout << "\n=== with init=100 ===" << std::endl;
    std::vector<int> data = {10, 20, 30, 40};
    std::vector<int> offset(data.size());

    std::exclusive_scan(data.begin(), data.end(), offset.begin(), 100);

    print("input ", data);
    print("scan  ", offset);
    // {100, 100+10, 100+10+20, 100+10+20+30} = {100, 110, 130, 160}

    // ------------------------------------------------------------------
    // 3. Exclusive scan with multiplication
    // ------------------------------------------------------------------
    std::cout << "\n=== exclusive product scan ===" << std::endl;
    std::vector<int> factors = {2, 3, 4, 5};
    std::vector<int> products(factors.size());

    std::exclusive_scan(factors.begin(), factors.end(), products.begin(),
                        1, std::multiplies<>{});

    print("input  ", factors);
    print("product", products);
    // {1, 1*2, 1*2*3, 1*2*3*4} = {1, 2, 6, 24}

    // ------------------------------------------------------------------
    // 4. Inclusive vs exclusive comparison
    // ------------------------------------------------------------------
    std::cout << "\n=== inclusive vs exclusive ===" << std::endl;
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int> inc(v.size()), exc(v.size());

    std::inclusive_scan(v.begin(), v.end(), inc.begin());
    std::exclusive_scan(v.begin(), v.end(), exc.begin(), 0);

    print("input    ", v);
    print("inclusive", inc);   // {1, 3, 6, 10, 15}
    print("exclusive", exc);   // {0, 1, 3,  6, 10}

    // ------------------------------------------------------------------
    // 5. Practical: byte offsets from sizes
    // ------------------------------------------------------------------
    std::cout << "\n=== byte offsets from sizes ===" << std::endl;
    std::vector<int> sizes = {4, 8, 2, 16, 4};
    std::vector<int> offsets(sizes.size());

    // Each element's offset is the sum of all previous sizes
    std::exclusive_scan(sizes.begin(), sizes.end(), offsets.begin(), 0);

    print("sizes  ", sizes);
    print("offsets", offsets);
    // {0, 4, 12, 14, 30} -- start position of each element

    // ------------------------------------------------------------------
    // 6. In-place exclusive scan
    // ------------------------------------------------------------------
    std::cout << "\n=== in-place scan ===" << std::endl;
    std::vector<int> inplace = {5, 3, 8, 2, 7};
    print("before", inplace);
    std::exclusive_scan(inplace.begin(), inplace.end(), inplace.begin(), 0);
    print("after ", inplace);
    // {0, 5, 8, 16, 18}

    return 0;
}

/*
Expected output:

=== basic exclusive scan ===
  input : 1 2 3 4 5
  scan  : 0 1 3 6 10

=== with init=100 ===
  input : 10 20 30 40
  scan  : 100 110 130 160

=== exclusive product scan ===
  input  : 2 3 4 5
  product: 1 2 6 24

=== inclusive vs exclusive ===
  input    : 1 2 3 4 5
  inclusive: 1 3 6 10 15
  exclusive: 0 1 3 6 10

=== byte offsets from sizes ===
  sizes  : 4 8 2 16 4
  offsets: 0 4 12 14 30

=== in-place scan ===
  before: 5 3 8 2 7
  after : 0 5 8 16 18
*/
