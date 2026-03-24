// CodeNebula - C++17 Example: CTAD with Deduction Guides
// Compile: g++ -std=c++17 -Wall -Wextra -o example ctad.cpp

// Demonstrates user-defined deduction guides for class template argument
// deduction. Deduction guides tell the compiler how to deduce template
// parameters from constructor arguments when implicit deduction is insufficient.

#include <iostream>
#include <string>
#include <vector>
#include <iterator>

// ------------------------------------------------------------------
// 1. Simple wrapper with implicit deduction (no guide needed)
// ------------------------------------------------------------------
template <typename T>
struct Wrapper {
    T value;
    Wrapper(T v) : value(v) {}
};
// Implicit guide: Wrapper(T) -> Wrapper<T> is generated automatically

// ------------------------------------------------------------------
// 2. Custom deduction guide: const char* -> std::string
// ------------------------------------------------------------------
template <typename T>
struct Named {
    std::string label;
    T data;
    Named(const char* l, T d) : label(l), data(d) {}
};
// Without a guide, Named("hello", 42) deduces T from 42 but label is const char*
// This explicit guide ensures the deduction works correctly:
template <typename T>
Named(const char*, T) -> Named<T>;

// ------------------------------------------------------------------
// 3. Deduction guide to pick a different specialization
// ------------------------------------------------------------------
template <typename T>
struct Container {
    std::vector<T> data;

    Container(std::initializer_list<T> init) : data(init) {}

    // Constructor from iterator pair
    template <typename Iter>
    Container(Iter begin, Iter end) : data(begin, end) {}

    void print() const {
        std::cout << "  [";
        for (std::size_t i = 0; i < data.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << data[i];
        }
        std::cout << "]" << std::endl;
    }
};

// Deduction guide for iterator pair: deduce T from iterator's value_type
template <typename Iter>
Container(Iter, Iter) -> Container<typename std::iterator_traits<Iter>::value_type>;

// ------------------------------------------------------------------
// 4. Deduction guide that transforms types
// ------------------------------------------------------------------
template <typename T>
struct SmartValue {
    T val;
    explicit SmartValue(T v) : val(v) {}
};

// Guide: when constructed from const char*, deduce as std::string
SmartValue(const char*) -> SmartValue<std::string>;

int main()
{
    // 1. Implicit deduction
    std::cout << "=== implicit deduction ===" << std::endl;
    Wrapper w1{42};           // Wrapper<int>
    Wrapper w2{3.14};         // Wrapper<double>
    Wrapper w3{std::string("hello")};  // Wrapper<std::string>
    std::cout << "  w1: " << w1.value << std::endl;
    std::cout << "  w2: " << w2.value << std::endl;
    std::cout << "  w3: " << w3.value << std::endl;

    // 2. Custom deduction guide
    std::cout << "\n=== custom deduction guide ===" << std::endl;
    Named n("sensor", 42);    // Named<int> via deduction guide
    std::cout << "  label: " << n.label << ", data: " << n.data << std::endl;

    // 3. Iterator deduction guide
    std::cout << "\n=== iterator deduction guide ===" << std::endl;
    std::vector<double> src{1.1, 2.2, 3.3, 4.4};
    Container c1{src.begin(), src.end()};  // Container<double>
    std::cout << "  from iterators:";
    c1.print();

    Container c2{10, 20, 30};              // Container<int> from init-list
    std::cout << "  from init-list:";
    c2.print();

    // 4. Type-transforming deduction guide
    std::cout << "\n=== type-transforming guide ===" << std::endl;
    SmartValue sv1{42};          // SmartValue<int>
    SmartValue sv2{"hello"};     // SmartValue<std::string> via guide
    std::cout << "  sv1: " << sv1.val << std::endl;
    std::cout << "  sv2: " << sv2.val << std::endl;

    return 0;
}

/*
Expected output:

=== implicit deduction ===
  w1: 42
  w2: 3.14
  w3: hello

=== custom deduction guide ===
  label: sensor, data: 42

=== iterator deduction guide ===
  from iterators:  [1.1, 2.2, 3.3, 4.4]
  from init-list:  [10, 20, 30]

=== type-transforming guide ===
  sv1: 42
  sv2: hello
*/
