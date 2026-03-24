// CodeNebula - C++17 Example: std::transform_reduce
// Compile: g++ -std=c++17 -Wall -Wextra -o example transform_reduce.cpp

// Demonstrates std::transform_reduce, which fuses a transformation step with
// a reduction step. It applies a unary or binary transform to elements, then
// reduces the results. This is more efficient than separate transform + reduce
// calls and is parallelizable.

#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <functional>
#include <cmath>

int main()
{
    // ------------------------------------------------------------------
    // 1. Dot product (binary transform_reduce): multiply pairs, then sum
    // ------------------------------------------------------------------
    std::cout << "=== dot product (binary form) ===" << std::endl;
    std::vector<double> a = {1.0, 2.0, 3.0, 4.0};
    std::vector<double> b = {5.0, 6.0, 7.0, 8.0};

    // init + reduce(transform(a[i], b[i]))
    // = 0 + (1*5) + (2*6) + (3*7) + (4*8) = 70
    double dot = std::transform_reduce(
        a.begin(), a.end(), b.begin(),
        0.0  // init
    );  // default: multiply pairs, then sum
    std::cout << "  a = {1,2,3,4}, b = {5,6,7,8}" << std::endl;
    std::cout << "  dot product = " << dot << std::endl;

    // ------------------------------------------------------------------
    // 2. Sum of squares (unary transform_reduce)
    // ------------------------------------------------------------------
    std::cout << "\n=== sum of squares (unary form) ===" << std::endl;
    std::vector<int> v = {1, 2, 3, 4, 5};

    int sum_sq = std::transform_reduce(
        v.begin(), v.end(),
        0,                      // init
        std::plus<>{},          // reduce operation
        [](int x) { return x * x; }  // transform
    );
    std::cout << "  v = {1,2,3,4,5}" << std::endl;
    std::cout << "  sum of squares = " << sum_sq << std::endl;

    // ------------------------------------------------------------------
    // 3. Euclidean distance
    // ------------------------------------------------------------------
    std::cout << "\n=== euclidean distance ===" << std::endl;
    std::vector<double> p1 = {1.0, 2.0, 3.0};
    std::vector<double> p2 = {4.0, 6.0, 3.0};

    double dist_sq = std::transform_reduce(
        p1.begin(), p1.end(), p2.begin(),
        0.0,                    // init
        std::plus<>{},          // reduce: sum
        [](double x, double y) { return (x - y) * (x - y); }  // transform
    );
    std::cout << "  p1 = {1,2,3}, p2 = {4,6,3}" << std::endl;
    std::cout << "  distance = " << std::sqrt(dist_sq) << std::endl;

    // ------------------------------------------------------------------
    // 4. Count elements matching a predicate
    // ------------------------------------------------------------------
    std::cout << "\n=== count matching ===" << std::endl;
    std::vector<int> scores = {85, 92, 67, 91, 78, 95, 88};

    int passing = std::transform_reduce(
        scores.begin(), scores.end(),
        0,
        std::plus<>{},
        [](int s) { return s >= 80 ? 1 : 0; }
    );
    std::cout << "  scores: ";
    for (int s : scores) std::cout << s << " ";
    std::cout << std::endl;
    std::cout << "  passing (>=80): " << passing << std::endl;

    // ------------------------------------------------------------------
    // 5. Total string length
    // ------------------------------------------------------------------
    std::cout << "\n=== total string length ===" << std::endl;
    std::vector<std::string> words = {"hello", "world", "foo", "bar"};

    std::size_t total_len = std::transform_reduce(
        words.begin(), words.end(),
        std::size_t{0},
        std::plus<>{},
        [](const std::string& s) { return s.size(); }
    );
    std::cout << "  words: hello, world, foo, bar" << std::endl;
    std::cout << "  total length = " << total_len << std::endl;

    // ------------------------------------------------------------------
    // 6. Weighted sum
    // ------------------------------------------------------------------
    std::cout << "\n=== weighted sum ===" << std::endl;
    std::vector<double> values  = {10.0, 20.0, 30.0};
    std::vector<double> weights = {0.2,  0.3,  0.5};

    double weighted = std::transform_reduce(
        values.begin(), values.end(), weights.begin(),
        0.0  // default: multiply pairs, then sum
    );
    std::cout << "  values:  10, 20, 30" << std::endl;
    std::cout << "  weights: 0.2, 0.3, 0.5" << std::endl;
    std::cout << "  weighted sum = " << weighted << std::endl;

    return 0;
}

/*
Expected output:

=== dot product (binary form) ===
  a = {1,2,3,4}, b = {5,6,7,8}
  dot product = 70

=== sum of squares (unary form) ===
  v = {1,2,3,4,5}
  sum of squares = 55

=== euclidean distance ===
  p1 = {1,2,3}, p2 = {4,6,3}
  distance = 5

=== count matching ===
  scores: 85 92 67 91 78 95 88
  passing (>=80): 5

=== total string length ===
  words: hello, world, foo, bar
  total length = 16

=== weighted sum ===
  values:  10, 20, 30
  weights: 0.2, 0.3, 0.5
  weighted sum = 23
*/
