// CodeNebula - C++23 Example: std::ranges::zip_transform_view
// Compile: g++ -std=c++23 -Wall -Wextra -o example ranges_zip_transform_view.cpp
// Note: Requires GCC 13+ / Clang 17+

// std::ranges::zip_transform_view zips multiple ranges together and applies
// a transformation function to each tuple of elements. It combines the
// functionality of zip_view and transform_view in a single operation.

#include <iostream>
#include <ranges>
#include <vector>
#include <string>

int main() {
    std::vector<double> prices = {10.0, 25.0, 15.0, 30.0};
    std::vector<int> quantities = {3, 1, 5, 2};

    // Compute total cost per item using zip_transform
    std::cout << "=== Item totals (price * quantity) ===" << std::endl;
    auto totals = std::views::zip_transform(
        [](double price, int qty) { return price * qty; },
        prices, quantities
    );
    for (auto total : totals) {
        std::cout << "  Total: $" << total << std::endl;
    }

    // Combine three ranges with a formatting function
    std::vector<std::string> items = {"Widget", "Gadget", "Gizmo", "Doodad"};
    std::cout << "\n=== Formatted receipts ===" << std::endl;
    auto receipts = std::views::zip_transform(
        [](const std::string& item, double price, int qty) {
            return item + ": " + std::to_string(qty) + " x $"
                   + std::to_string(price).substr(0, std::to_string(price).find('.') + 3);
        },
        items, prices, quantities
    );
    for (const auto& receipt : receipts) {
        std::cout << "  " << receipt << std::endl;
    }

    // Mathematical operations: element-wise addition
    std::vector<int> a = {1, 2, 3, 4, 5};
    std::vector<int> b = {10, 20, 30, 40, 50};
    std::cout << "\n=== Element-wise sum ===" << std::endl;
    for (auto sum : std::views::zip_transform(std::plus{}, a, b)) {
        std::cout << "  " << sum;
    }
    std::cout << std::endl;

    // Weighted average calculation
    std::vector<double> values = {90.0, 80.0, 70.0};
    std::vector<double> weights = {0.5, 0.3, 0.2};
    std::cout << "\n=== Weighted contributions ===" << std::endl;
    for (auto wv : std::views::zip_transform(std::multiplies{}, values, weights)) {
        std::cout << "  " << wv << std::endl;
    }

    return 0;
}

// Expected output:
// === Item totals (price * quantity) ===
//   Total: $30
//   Total: $25
//   Total: $75
//   Total: $60
//
// === Formatted receipts ===
//   Widget: 3 x $10.00
//   Gadget: 1 x $25.00
//   Gizmo: 5 x $15.00
//   Doodad: 2 x $30.00
//
// === Element-wise sum ===
//   11  22  33  44  55
//
// === Weighted contributions ===
//   45
//   24
//   14
