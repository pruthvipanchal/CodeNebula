// CodeNebula - C++20 Example: Constrained Templates
// Compile: g++ -std=c++20 -Wall -Wextra -o example constrained_templates.cpp

// Demonstrates template<Concept T> syntax for constraining template
// parameters directly in the template parameter list.

#include <iostream>
#include <concepts>
#include <string>
#include <vector>
#include <numeric>

// ------------------------------------------------------------------
// 1. Concept definitions
// ------------------------------------------------------------------
template <typename T>
concept Arithmetic = std::integral<T> || std::floating_point<T>;

template <typename T>
concept Stringlike = std::convertible_to<T, std::string_view>;

template <typename T>
concept Container = requires(T c) {
    typename T::value_type;
    { c.begin() };
    { c.end() };
    { c.size() } -> std::convertible_to<std::size_t>;
};

// ------------------------------------------------------------------
// 2. Constrained function templates: template<Concept T>
// ------------------------------------------------------------------
template <Arithmetic T>
T square(T x) {
    return x * x;
}

template <Arithmetic T>
T average(const std::vector<T>& vals) {
    T sum = std::accumulate(vals.begin(), vals.end(), T{});
    return sum / static_cast<T>(vals.size());
}

template <Stringlike S>
std::string greet(S name) {
    return "Hello, " + std::string(name) + "!";
}

// ------------------------------------------------------------------
// 3. Constrained class template
// ------------------------------------------------------------------
template <Arithmetic T>
class Stats {
    std::vector<T> data_;
public:
    void add(T val) { data_.push_back(val); }

    T min_val() const {
        T m = data_[0];
        for (auto v : data_) if (v < m) m = v;
        return m;
    }

    T max_val() const {
        T m = data_[0];
        for (auto v : data_) if (v > m) m = v;
        return m;
    }

    T sum() const {
        return std::accumulate(data_.begin(), data_.end(), T{});
    }

    void print() const {
        std::cout << "  Stats: min=" << min_val()
                  << " max=" << max_val()
                  << " sum=" << sum() << std::endl;
    }
};

// ------------------------------------------------------------------
// 4. Constrained template with multiple parameters
// ------------------------------------------------------------------
template <Container C, Arithmetic T>
T sum_container_plus(const C& c, T extra) {
    T total = extra;
    for (const auto& elem : c) total += static_cast<T>(elem);
    return total;
}

int main()
{
    std::cout << "=== Constrained Function Templates ===" << std::endl;
    std::cout << "  square(5) = " << square(5) << std::endl;
    std::cout << "  square(2.5) = " << square(2.5) << std::endl;
    // square(std::string("x")); // Compile error: not Arithmetic

    std::vector<double> vals = {10.0, 20.0, 30.0, 40.0};
    std::cout << "  average({10,20,30,40}) = " << average(vals) << std::endl;

    std::cout << "\n=== Stringlike Constraint ===" << std::endl;
    std::cout << "  " << greet("World") << std::endl;
    std::string name = "C++20";
    std::cout << "  " << greet(name) << std::endl;

    std::cout << "\n=== Constrained Class Template ===" << std::endl;
    Stats<int> si;
    si.add(3); si.add(7); si.add(1); si.add(9); si.add(4);
    si.print();

    Stats<double> sd;
    sd.add(1.1); sd.add(2.2); sd.add(3.3);
    sd.print();

    std::cout << "\n=== Multiple Constrained Parameters ===" << std::endl;
    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::cout << "  sum + 100 = " << sum_container_plus(nums, 100) << std::endl;
    std::cout << "  sum + 0.5 = " << sum_container_plus(nums, 0.5) << std::endl;

    return 0;
}

/*
Expected output:

=== Constrained Function Templates ===
  square(5) = 25
  square(2.5) = 6.25
  average({10,20,30,40}) = 25

=== Stringlike Constraint ===
  Hello, World!
  Hello, C++20!

=== Constrained Class Template ===
  Stats: min=1 max=9 sum=24
  Stats: min=1.1 max=3.3 sum=6.6

=== Multiple Constrained Parameters ===
  sum + 100 = 115
  sum + 0.5 = 15.5
*/
