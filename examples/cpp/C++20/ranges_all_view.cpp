// CodeNebula - C++20 Example: std::views::all / ref_view / owning_view
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_all_view.cpp

#include <ranges>
#include <vector>
#include <string>
#include <iostream>

// std::views::all converts a range into a view: lvalue -> ref_view,
// rvalue -> owning_view, already a view -> returned unchanged.

void demonstrate_ref_view() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    // views::all on lvalue produces ref_view
    auto view = std::views::all(vec);
    static_assert(std::same_as<decltype(view), std::ranges::ref_view<std::vector<int>>>);

    std::cout << "ref_view: ";
    for (int n : view) std::cout << n << " ";
    std::cout << "\n";

    // Modifying via ref_view modifies original
    *std::ranges::begin(view) = 99;
    std::cout << "vec[0] after modification: " << vec[0] << "\n";
}

void demonstrate_owning_view() {
    // views::all on rvalue produces owning_view
    auto view = std::views::all(std::vector{10, 20, 30});
    static_assert(std::same_as<decltype(view), std::ranges::owning_view<std::vector<int>>>);

    std::cout << "owning_view: ";
    for (int n : view) std::cout << n << " ";
    std::cout << "\n";
}

void demonstrate_identity_for_views() {
    // views::all on a view returns the view itself
    auto iota = std::views::iota(1, 6);
    auto same = std::views::all(iota);
    static_assert(std::same_as<decltype(iota), decltype(same)>);

    std::cout << "Iota view (identity): ";
    for (int n : same) std::cout << n << " ";
    std::cout << "\n";
}

int main() {
    std::cout << "=== ref_view (lvalue) ===\n";
    demonstrate_ref_view();

    std::cout << "\n=== owning_view (rvalue) ===\n";
    demonstrate_owning_view();

    std::cout << "\n=== Identity for views ===\n";
    demonstrate_identity_for_views();

    // Pipe operator implicitly uses views::all
    std::vector<int> data = {5, 10, 15, 20, 25};
    auto pipeline = data | std::views::take(3);
    std::cout << "\nPipeline (implicit all): ";
    for (int n : pipeline) std::cout << n << " ";
    std::cout << "\n";

    // ref_view preserves all properties of the original range
    auto ref = std::views::all(data);
    std::cout << "ref_view size: " << std::ranges::size(ref) << "\n";
    return 0;
}
