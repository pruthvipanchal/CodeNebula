// CodeNebula - C++20 Example: Range Utilities (ranges::size/ssize/empty/data/cdata)
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_utils.cpp

#include <ranges>
#include <vector>
#include <array>
#include <string>
#include <list>
#include <span>
#include <iostream>

// std::ranges provides utility CPOs: size(), ssize(), empty(),
// data(), and cdata() for uniform access to range properties.

template <std::ranges::sized_range R>
void print_size_info(const R& r, const char* name) {
    std::cout << name << ": size=" << std::ranges::size(r)
              << ", ssize=" << std::ranges::ssize(r)
              << ", empty=" << std::boolalpha << std::ranges::empty(r) << "\n";
}

template <std::ranges::contiguous_range R>
void print_data_info(const R& r, const char* name) {
    auto ptr = std::ranges::data(r);
    auto cptr = std::ranges::cdata(r);
    std::cout << name << ": data points to first element = "
              << *ptr << ", cdata = " << *cptr << "\n";
}

int main() {
    std::vector<int> vec = {10, 20, 30, 40, 50};
    std::vector<int> empty_vec;
    std::array<double, 3> arr = {1.1, 2.2, 3.3};
    std::string str = "Hello";
    int c_arr[] = {7, 8, 9};

    // Size and empty
    std::cout << "=== Size Info ===\n";
    print_size_info(vec, "vector<int>");
    print_size_info(empty_vec, "empty vector");
    print_size_info(arr, "array<double,3>");
    print_size_info(str, "string");
    print_size_info(c_arr, "int[3]");

    // ssize returns a signed type, useful for avoiding signed/unsigned issues
    auto sz = std::ranges::ssize(vec);
    for (decltype(sz) i = sz - 1; i >= 0; --i) {
        // Safe: no unsigned underflow
    }
    std::cout << "\nssize type is signed: "
              << std::is_signed_v<decltype(sz)> << "\n";

    // Data pointer access for contiguous ranges
    std::cout << "\n=== Data Pointers ===\n";
    print_data_info(vec, "vector<int>");
    print_data_info(arr, "array<double,3>");
    print_data_info(str, "string");
    print_data_info(c_arr, "int[3]");

    // empty() works on all ranges
    std::cout << "\n=== Empty Check ===\n";
    std::cout << "vec empty: " << std::ranges::empty(vec) << "\n";
    std::cout << "empty_vec empty: " << std::ranges::empty(empty_vec) << "\n";

    // Works with views
    auto view = vec | std::views::take(0);
    std::cout << "take(0) empty: " << std::ranges::empty(view) << "\n";
    return 0;
}
