// CodeNebula - C++17 Example: std::filesystem::hard_link_count
// Compile: g++ -std=c++17 -Wall -Wextra -o example hard_link_count.cpp -lstdc++fs

// std::filesystem::hard_link_count() returns the number of hard links to a
// file. Regular files start at 1; directories typically have 2+ (self + parent).

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int main() {
    try {
        fs::path base = fs::temp_directory_path() / "cn_hardlink_test";
        fs::create_directories(base);
        fs::path file = base / "original.txt";
        { std::ofstream(file) << "hard link test data"; }

        // --- Initial hard link count ---
        std::cout << "=== Initial count ===" << std::endl;
        std::cout << "hard_link_count(file): " << fs::hard_link_count(file) << std::endl;

        // --- Create hard links (may fail on some filesystems) ---
        std::cout << "\n=== Create hard links ===" << std::endl;
        std::error_code ec;
        fs::path link1 = base / "link1.txt";
        fs::path link2 = base / "link2.txt";

        fs::create_hard_link(file, link1, ec);
        if (!ec) {
            std::cout << "After 1st hard link: " << fs::hard_link_count(file) << std::endl;

            fs::create_hard_link(file, link2, ec);
            if (!ec) {
                std::cout << "After 2nd hard link: " << fs::hard_link_count(file) << std::endl;
            }

            // All paths point to same file
            std::cout << "\n=== All names same count ===" << std::endl;
            std::cout << "original: " << fs::hard_link_count(file) << std::endl;
            std::cout << "link1:    " << fs::hard_link_count(link1) << std::endl;
            if (fs::exists(link2)) {
                std::cout << "link2:    " << fs::hard_link_count(link2) << std::endl;
            }

            // --- Remove a hard link ---
            std::cout << "\n=== After removing one link ===" << std::endl;
            fs::remove(link1);
            std::cout << "original count: " << fs::hard_link_count(file) << std::endl;
        } else {
            std::cout << "Hard link creation not supported: " << ec.message() << std::endl;
        }

        // --- Directory hard link count ---
        std::cout << "\n=== Directory link count ===" << std::endl;
        std::cout << "base dir: " << fs::hard_link_count(base) << std::endl;
        fs::create_directory(base / "subdir");
        std::cout << "After adding subdir: " << fs::hard_link_count(base) << std::endl;
        std::cout << "(directories gain a link for each subdirectory's '..' entry)" << std::endl;

        // --- Error handling ---
        std::cout << "\n=== Error handling ===" << std::endl;
        auto count = fs::hard_link_count(base / "nonexistent", ec);
        if (ec) {
            std::cout << "Error: " << ec.message() << std::endl;
        } else {
            std::cout << "Count: " << count << std::endl;
        }

        // Cleanup
        fs::remove_all(base);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output (values may differ on Windows):
=== Initial count ===
hard_link_count(file): 1

=== Create hard links ===
After 1st hard link: 2
After 2nd hard link: 3

=== All names same count ===
original: 3
link1:    3
link2:    3

=== After removing one link ===
original count: 2

=== Directory link count ===
base dir: 2
After adding subdir: 3
(directories gain a link for each subdirectory's '..' entry)

=== Error handling ===
Error: No such file or directory
*/
