// CodeNebula - C++20 Example: std::ranges::borrowed_range Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_borrowed_range.cpp

#include <ranges>
#include <vector>
#include <string>
#include <span>
#include <algorithm>
#include <iostream>

// std::ranges::borrowed_range indicates that iterators from a range
// remain valid even after the range object is destroyed. This prevents
// dangling iterator bugs at compile time.

// Safe function: returns iterator only from borrowed ranges
template <std::ranges::borrowed_range R>
auto safe_find(R&& r, const std::ranges::range_value_t<R>& val) {
    return std::ranges::find(r, val);
}

int main() {
    // Views and spans are borrowed ranges
    static_assert(std::ranges::borrowed_range<std::span<int>>);
    static_assert(std::ranges::borrowed_range<std::string_view>);

    // Owning containers are NOT borrowed (iterators dangle if container dies)
    static_assert(!std::ranges::borrowed_range<std::vector<int>>);
    static_assert(!std::ranges::borrowed_range<std::string>);

    // Safe: finding in an lvalue container
    std::vector<int> vec = {10, 20, 30, 40, 50};
    auto it = std::ranges::find(vec, 30);
    if (it != vec.end()) {
        std::cout << "Found: " << *it << "\n";
    }

    // ranges::find on rvalue non-borrowed range returns ranges::dangling
    auto result = std::ranges::find(std::vector{1, 2, 3}, 2);
    static_assert(std::same_as<decltype(result), std::ranges::dangling>);
    std::cout << "Rvalue vector find returns dangling (compile-time safety)\n";

    // span is borrowed - safe to return iterators from rvalue
    int arr[] = {5, 10, 15, 20};
    auto sp_result = std::ranges::find(std::span(arr), 15);
    std::cout << "Found in span: " << *sp_result << "\n";

    // string_view is borrowed
    auto sv_result = std::ranges::find(std::string_view("hello"), 'l');
    std::cout << "Found in string_view: " << *sv_result << "\n";

    // iota_view is borrowed
    auto iota = std::views::iota(1, 10);
    static_assert(std::ranges::borrowed_range<decltype(iota)>);
    auto iota_it = safe_find(iota, 7);
    std::cout << "Found in iota: " << *iota_it << "\n";

    // Subrange is borrowed
    auto sub = std::ranges::subrange(vec.begin() + 1, vec.begin() + 4);
    static_assert(std::ranges::borrowed_range<decltype(sub)>);
    std::cout << "Subrange: ";
    for (int n : sub) std::cout << n << " ";
    std::cout << "\n";

    return 0;
}
