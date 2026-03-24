// CodeNebula - C++26 Example: std::flat_set Improvements
// Compile: g++ -std=c++26 -Wall -Wextra -o example flat_set_improvements.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// std::flat_set (C++23) stores unique elements in a sorted contiguous array.
// C++26 adds improved insert_range, heterogeneous erasure, and better
// exception safety guarantees.

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <initializer_list>

// --- C++26 flat_set Improvements ---
//
// #include <flat_set>
//
// std::flat_set<int> fs = {3, 1, 4, 1, 5};  // {1, 3, 4, 5} (unique, sorted)
// fs.insert(2);
//
// // C++26: insert_range from any range
// std::vector<int> more = {7, 3, 9};
// fs.insert_range(more);  // Efficient bulk insert
//
// // C++26: extract underlying container
// auto& underlying = fs.extract();  // Move out the vector

// --- Simulation using sorted vector ---

template<typename T>
class flat_set_sim {
    std::vector<T> data_;
public:
    flat_set_sim() = default;
    flat_set_sim(std::initializer_list<T> init) {
        for (auto& v : init) insert(v);
    }
    bool insert(const T& val) {
        auto it = std::lower_bound(data_.begin(), data_.end(), val);
        if (it != data_.end() && *it == val) return false; // duplicate
        data_.insert(it, val);
        return true;
    }
    void insert_range(const std::vector<T>& range) {
        for (const auto& v : range) insert(v);
    }
    bool contains(const T& val) const {
        return std::binary_search(data_.begin(), data_.end(), val);
    }
    bool erase(const T& val) {
        auto it = std::lower_bound(data_.begin(), data_.end(), val);
        if (it != data_.end() && *it == val) { data_.erase(it); return true; }
        return false;
    }
    std::size_t size() const { return data_.size(); }
    auto begin() const { return data_.begin(); }
    auto end() const { return data_.end(); }
};

int main() {
    std::cout << "=== C++26 std::flat_set Improvements (Simulated) ===" << std::endl;

    flat_set_sim<int> fs = {3, 1, 4, 1, 5, 9, 2, 6};
    std::cout << "Initial set: ";
    for (auto x : fs) std::cout << x << " ";
    std::cout << "(size=" << fs.size() << ")" << std::endl;

    // Insert range (C++26 improvement)
    std::vector<int> more = {7, 3, 10, 5};
    fs.insert_range(more);
    std::cout << "After insert_range: ";
    for (auto x : fs) std::cout << x << " ";
    std::cout << "(size=" << fs.size() << ")" << std::endl;

    // Lookup and erase
    std::cout << "Contains 4: " << std::boolalpha << fs.contains(4) << std::endl;
    std::cout << "Contains 8: " << fs.contains(8) << std::endl;

    fs.erase(4);
    std::cout << "After erase(4): ";
    for (auto x : fs) std::cout << x << " ";
    std::cout << std::endl;

    std::cout << "flat_set: contiguous sorted unique container." << std::endl;
    return 0;
}

// Expected output:
// === C++26 std::flat_set Improvements (Simulated) ===
// Initial set: 1 2 3 4 5 6 9 (size=7)
// After insert_range: 1 2 3 4 5 6 7 9 10 (size=9)
// Contains 4: true
// Contains 8: false
// After erase(4): 1 2 3 5 6 7 9 10
// flat_set: contiguous sorted unique container.
