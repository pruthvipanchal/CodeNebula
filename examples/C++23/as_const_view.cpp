// CodeNebula - C++23 Example: std::ranges::as_const_view
// Compile: g++ -std=c++23 -Wall -Wextra -o example as_const_view.cpp
// Note: Requires GCC 13+ / Clang 17+

// std::ranges::as_const_view wraps a range so that each element is accessed
// as a const reference. This prevents accidental modification of elements
// during iteration, providing a read-only view of mutable data.

#include <iostream>
#include <ranges>
#include <vector>
#include <string>
#include <type_traits>

// Helper to display items from a read-only view
template <typename View>
void print_readonly(const std::string& label, View&& view) {
    std::cout << label << ": ";
    for (const auto& item : view) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> numbers = {10, 20, 30, 40, 50};

    // as_const prevents modification through the view
    std::cout << "=== Read-only view of mutable vector ===" << std::endl;
    auto const_view = numbers | std::views::as_const;
    print_readonly("  Numbers", const_view);

    // Verify const-ness at compile time
    using ref_type = decltype(*const_view.begin());
    static_assert(std::is_const_v<std::remove_reference_t<ref_type>>,
                  "Elements should be const");
    std::cout << "  Elements are const: true" << std::endl;

    // Original data is still mutable
    numbers[0] = 99;
    std::cout << "\n=== After modifying original ===" << std::endl;
    print_readonly("  Const view reflects change", const_view);

    // Combine with other views
    std::vector<std::string> words = {"hello", "world", "foo", "bar", "baz"};
    std::cout << "\n=== Const view with filter ===" << std::endl;
    auto filtered_const = words
        | std::views::filter([](const std::string& s) { return s.size() == 3; })
        | std::views::as_const;
    for (const auto& w : filtered_const) {
        std::cout << "  " << w << std::endl;
    }

    // Useful in templates to guarantee no modification
    std::cout << "\n=== Const view with transform ===" << std::endl;
    auto sized = numbers
        | std::views::as_const
        | std::views::transform([](int n) { return n * 2; });
    for (auto val : sized) {
        std::cout << "  " << val;
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// === Read-only view of mutable vector ===
//   Numbers: 10 20 30 40 50
//   Elements are const: true
//
// === After modifying original ===
//   Const view reflects change: 99 20 30 40 50
//
// === Const view with filter ===
//   foo
//   bar
//   baz
//
// === Const view with transform ===
//   198  40  60  80  100
