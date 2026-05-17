// CodeNebula - C++23 Example: std::ranges::chunk_view
// Compile: g++ -std=c++23 -Wall -Wextra -o example ranges_chunk_view.cpp
// Note: Requires GCC 13+ / Clang 17+

// std::ranges::chunk_view splits a range into non-overlapping chunks of a
// specified size. The last chunk may be smaller if the range size is not
// evenly divisible by the chunk size.

#include <iostream>
#include <ranges>
#include <vector>
#include <string>

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Split into chunks of 3
    std::cout << "=== Chunks of 3 ===" << std::endl;
    for (auto chunk : data | std::views::chunk(3)) {
        std::cout << "  [";
        bool first = true;
        for (auto val : chunk) {
            if (!first) std::cout << ", ";
            std::cout << val;
            first = false;
        }
        std::cout << "]" << std::endl;
    }

    // Split into chunks of 4
    std::cout << "\n=== Chunks of 4 ===" << std::endl;
    for (auto chunk : data | std::views::chunk(4)) {
        std::cout << "  [";
        bool first = true;
        for (auto val : chunk) {
            if (!first) std::cout << ", ";
            std::cout << val;
            first = false;
        }
        std::cout << "]" << std::endl;
    }

    // Practical: process batch items
    std::vector<std::string> tasks = {"A", "B", "C", "D", "E", "F", "G"};
    int batch = 1;
    std::cout << "\n=== Batch processing (batch size 3) ===" << std::endl;
    for (auto chunk : tasks | std::views::chunk(3)) {
        std::cout << "  Batch " << batch++ << ": ";
        for (const auto& task : chunk) {
            std::cout << task << " ";
        }
        std::cout << std::endl;
    }

    // Sum each chunk
    std::cout << "\n=== Sum of each chunk of 5 ===" << std::endl;
    for (auto chunk : data | std::views::chunk(5)) {
        int sum = 0;
        for (auto val : chunk) sum += val;
        std::cout << "  Chunk sum: " << sum << std::endl;
    }

    return 0;
}

// Expected output:
// === Chunks of 3 ===
//   [1, 2, 3]
//   [4, 5, 6]
//   [7, 8, 9]
//   [10]
//
// === Chunks of 4 ===
//   [1, 2, 3, 4]
//   [5, 6, 7, 8]
//   [9, 10]
//
// === Batch processing (batch size 3) ===
//   Batch 1: A B C
//   Batch 2: D E F
//   Batch 3: G
//
// === Sum of each chunk of 5 ===
//   Chunk sum: 15
//   Chunk sum: 40
