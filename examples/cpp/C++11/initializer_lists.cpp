// CodeNebula - C++11 Example: std::initializer_list
// Compile: g++ -std=c++11 -Wall -Wextra -o example initializer_lists.cpp

// Demonstrates std::initializer_list for accepting brace-enclosed lists
// of values. This enables natural initialization syntax for custom containers
// and functions that process variable-length homogeneous data.

#include <iostream>
#include <initializer_list>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

// Real-world scenario: a custom container accepting initializer_list
class IntSet {
    std::vector<int> data_;
public:
    IntSet(std::initializer_list<int> init) : data_(init)
    {
        std::sort(data_.begin(), data_.end());
        auto last = std::unique(data_.begin(), data_.end());
        data_.erase(last, data_.end());
    }

    bool contains(int val) const
    {
        return std::binary_search(data_.begin(), data_.end(), val);
    }

    void print() const
    {
        std::cout << "{";
        for (std::size_t i = 0; i < data_.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << data_[i];
        }
        std::cout << "}";
    }

    std::size_t size() const { return data_.size(); }
};

// Function accepting initializer_list
double average(std::initializer_list<double> values)
{
    if (values.size() == 0) return 0.0;
    double sum = std::accumulate(values.begin(), values.end(), 0.0);
    return sum / values.size();
}

// Overloaded function: initializer_list vs single value
void show(int val)
{
    std::cout << "  show(int): " << val << std::endl;
}

void show(std::initializer_list<int> vals)
{
    std::cout << "  show(init_list): ";
    for (auto v : vals) std::cout << v << " ";
    std::cout << std::endl;
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Standard library with initializer_list
    // ------------------------------------------------------------------
    std::vector<int> nums = {5, 3, 1, 4, 2};
    std::vector<std::string> names = {"Alice", "Bob", "Charlie"};

    std::cout << "=== Standard library ===" << std::endl;
    std::cout << "  nums: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << std::endl;
    std::cout << "  names: ";
    for (const auto& s : names) std::cout << s << " ";
    std::cout << std::endl << std::endl;

    // ------------------------------------------------------------------
    // 2. Custom class with initializer_list constructor
    // ------------------------------------------------------------------
    IntSet evens = {2, 4, 6, 8, 4, 6, 2};   // duplicates removed

    std::cout << "=== Custom IntSet ===" << std::endl;
    std::cout << "  evens: ";
    evens.print();
    std::cout << std::endl;
    std::cout << "  size: " << evens.size() << " (duplicates removed)" << std::endl;
    std::cout << "  contains(4): " << (evens.contains(4) ? "yes" : "no") << std::endl;
    std::cout << "  contains(5): " << (evens.contains(5) ? "yes" : "no") << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Functions accepting initializer_list
    // ------------------------------------------------------------------
    double avg = average({10.0, 20.0, 30.0, 40.0});

    std::cout << "=== Function with initializer_list ===" << std::endl;
    std::cout << "  average({10,20,30,40}): " << avg << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Iterating over initializer_list properties
    // ------------------------------------------------------------------
    auto il = {1, 2, 3, 4, 5};

    std::cout << "=== Initializer_list properties ===" << std::endl;
    std::cout << "  size: " << il.size() << std::endl;
    std::cout << "  elements: ";
    for (auto it = il.begin(); it != il.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl << std::endl;

    // ------------------------------------------------------------------
    // 5. Overload resolution with initializer_list
    // ------------------------------------------------------------------
    std::cout << "=== Overload resolution ===" << std::endl;
    show(42);           // calls show(int)
    show({1, 2, 3});    // calls show(initializer_list<int>)

    return 0;
}

/*
Expected output:

=== Standard library ===
  nums: 5 3 1 4 2
  names: Alice Bob Charlie

=== Custom IntSet ===
  evens: {2, 4, 6, 8}
  size: 4 (duplicates removed)
  contains(4): yes
  contains(5): no

=== Function with initializer_list ===
  average({10,20,30,40}): 25

=== Initializer_list properties ===
  size: 5
  elements: 1 2 3 4 5

=== Overload resolution ===
  show(int): 42
  show(init_list): 1 2 3
*/
