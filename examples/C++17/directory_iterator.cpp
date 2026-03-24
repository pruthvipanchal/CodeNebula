// CodeNebula - C++17 Example: std::filesystem::directory_iterator
// Compile: g++ -std=c++17 -Wall -Wextra -o example directory_iterator.cpp -lstdc++fs

// std::filesystem::directory_iterator iterates over entries in a single
// directory (non-recursively). It supports range-based for loops.

#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;

int main() {
    try {
        // Setup: create a temp directory with some files
        fs::path base = fs::temp_directory_path() / "cn_dir_iter_test";
        fs::create_directories(base / "subdir");
        { std::ofstream(base / "alpha.txt") << "A"; }
        { std::ofstream(base / "beta.txt") << "B"; }
        { std::ofstream(base / "gamma.cpp") << "C"; }

        // --- Basic iteration ---
        std::cout << "=== Directory contents ===" << std::endl;
        for (const auto& entry : fs::directory_iterator(base)) {
            std::cout << "  " << entry.path().filename()
                      << (entry.is_directory() ? " [dir]" : " [file]") << std::endl;
        }

        // --- Collect and sort entries ---
        std::cout << "\n=== Sorted entries ===" << std::endl;
        std::vector<fs::directory_entry> entries;
        for (const auto& entry : fs::directory_iterator(base)) {
            entries.push_back(entry);
        }
        std::sort(entries.begin(), entries.end(),
            [](const fs::directory_entry& a, const fs::directory_entry& b) {
                return a.path().filename() < b.path().filename();
            });
        for (const auto& e : entries) {
            std::cout << "  " << e.path().filename() << std::endl;
        }

        // --- Count entries ---
        std::cout << "\n=== Entry count ===" << std::endl;
        auto it = fs::directory_iterator(base);
        auto count = std::distance(fs::begin(it), fs::end(it));
        std::cout << "Number of entries: " << count << std::endl;

        // --- Empty directory ---
        std::cout << "\n=== Empty directory ===" << std::endl;
        fs::path empty_dir = base / "empty";
        fs::create_directory(empty_dir);
        bool is_empty = (fs::directory_iterator(empty_dir) == fs::directory_iterator{});
        std::cout << "Empty dir is empty: " << is_empty << std::endl;

        // Cleanup
        fs::remove_all(base);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output (order may vary before sorting):
=== Directory contents ===
  alpha.txt [file]
  beta.txt [file]
  gamma.cpp [file]
  subdir [dir]

=== Sorted entries ===
  alpha.txt
  beta.txt
  gamma.cpp
  subdir

=== Entry count ===
Number of entries: 4

=== Empty directory ===
Empty dir is empty: 1
*/
