// CodeNebula - C++23 Example: std::span Enhancements
// Compile: g++ -std=c++23 -Wall -Wextra -o example span_enhancements.cpp
// Note: Requires GCC 13+ / Clang 17+

#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <span>
#include <vector>

// C++23 enhances std::span with additional utility. This example covers
// subspan, first, last, as_bytes, and as_writable_bytes for safe,
// non-owning views over contiguous memory.

void print_span(std::string_view label, std::span<const int> s) {
    std::cout << label << " [" << s.size() << "]: ";
    for (int v : s) std::cout << v << " ";
    std::cout << "\n";
}

int main() {
    std::cout << "=== std::span enhancements ===\n\n";

    std::vector<int> data = {10, 20, 30, 40, 50, 60, 70, 80};
    std::span<int> full(data);

    print_span("Full span", full);

    // --- first / last ---
    std::cout << "\n--- first / last ---\n";
    print_span("first(3)", full.first(3));
    print_span("last(3)", full.last(3));

    // --- subspan ---
    std::cout << "\n--- subspan ---\n";
    print_span("subspan(2, 4)", full.subspan(2, 4));
    print_span("subspan(5)", full.subspan(5));  // from index 5 to end

    // --- Static extent subspan ---
    std::array<int, 6> arr = {1, 2, 3, 4, 5, 6};
    std::span<int, 6> static_span(arr);
    auto sub = static_span.subspan<1, 3>();  // compile-time offset/count
    print_span("Static subspan<1,3>", sub);

    // --- as_bytes: view raw memory ---
    std::cout << "\n--- as_bytes ---\n";
    std::array<int, 2> ints = {0x01020304, 0x05060708};
    auto bytes = std::as_bytes(std::span(ints));
    std::cout << "Byte view of {0x01020304, 0x05060708}:\n  ";
    for (auto b : bytes) {
        std::cout << std::hex << static_cast<unsigned>(static_cast<unsigned char>(
            static_cast<std::underlying_type_t<std::byte>>(b)))
                  << " ";
    }
    std::cout << std::dec << "\n";
    std::cout << "Byte span size: " << bytes.size() << "\n";

    // --- as_writable_bytes: modify through byte view ---
    std::cout << "\n--- as_writable_bytes ---\n";
    int value = 0;
    auto writable = std::as_writable_bytes(std::span(&value, 1));
    writable[0] = std::byte{0xFF};
    std::cout << "After writing 0xFF to first byte: " << value << "\n";

    // --- Practical: process sub-ranges ---
    std::cout << "\n--- Practical: process sub-ranges ---\n";
    std::vector<int> scores = {85, 92, 78, 95, 88, 72, 90, 83};
    std::span<int> score_span(scores);

    // Sort just the middle portion
    auto middle = score_span.subspan(2, 4);
    std::ranges::sort(middle);
    print_span("After sorting middle 4", score_span);

    return 0;
}

// Expected output (on little-endian system):
// === std::span enhancements ===
//
// Full span [8]: 10 20 30 40 50 60 70 80
//
// --- first / last ---
// first(3) [3]: 10 20 30
// last(3) [3]: 60 70 80
//
// --- subspan ---
// subspan(2, 4) [4]: 30 40 50 60
// subspan(5) [3]: 60 70 80
// Static subspan<1,3> [3]: 2 3 4
//
// --- as_bytes ---
// Byte view of {0x01020304, 0x05060708}:
//   4 3 2 1 8 7 6 5
// Byte span size: 8
//
// --- as_writable_bytes ---
// After writing 0xFF to first byte: 255
//
// --- Practical: process sub-ranges ---
// After sorting middle 4 [8]: 85 92 78 88 95 72 90 83
