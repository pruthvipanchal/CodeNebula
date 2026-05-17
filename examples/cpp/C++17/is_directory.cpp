// CodeNebula - C++17 Example: std::filesystem::is_directory
// Compile: g++ -std=c++17 -Wall -Wextra -o example is_directory.cpp -lstdc++fs

// std::filesystem::is_directory() checks if a path refers to a directory.
// It follows symlinks. Use symlink_status to check without following.

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int main() {
    try {
        fs::path base = fs::temp_directory_path() / "cn_is_dir_test";
        fs::create_directories(base / "subdir");
        fs::path file = base / "file.txt";
        { std::ofstream(file) << "data"; }

        // --- Check directories ---
        std::cout << "=== Directory checks ===" << std::endl;
        std::cout << "is_directory(base):   " << fs::is_directory(base) << std::endl;
        std::cout << "is_directory(subdir): " << fs::is_directory(base / "subdir") << std::endl;
        std::cout << "is_directory(temp):   " << fs::is_directory(fs::temp_directory_path()) << std::endl;

        // --- Check files ---
        std::cout << "\n=== File checks ===" << std::endl;
        std::cout << "is_directory(file): " << fs::is_directory(file) << std::endl;

        // --- Check non-existent ---
        std::cout << "\n=== Non-existent ===" << std::endl;
        std::cout << "is_directory(ghost): " << fs::is_directory(base / "ghost") << std::endl;

        // --- Using file_status ---
        std::cout << "\n=== Using file_status ===" << std::endl;
        fs::file_status dir_st = fs::status(base);
        fs::file_status file_st = fs::status(file);
        std::cout << "is_directory(dir status):  " << fs::is_directory(dir_st) << std::endl;
        std::cout << "is_directory(file status): " << fs::is_directory(file_st) << std::endl;

        // --- Practical: filter directories from listing ---
        std::cout << "\n=== Filter directories ===" << std::endl;
        { std::ofstream(base / "a.txt") << "a"; }
        fs::create_directory(base / "dir2");
        for (const auto& entry : fs::directory_iterator(base)) {
            if (fs::is_directory(entry.status())) {
                std::cout << "  [DIR]  " << entry.path().filename().string() << std::endl;
            } else {
                std::cout << "  [FILE] " << entry.path().filename().string() << std::endl;
            }
        }

        // --- Error code variant ---
        std::cout << "\n=== Error handling ===" << std::endl;
        std::error_code ec;
        bool result = fs::is_directory(base, ec);
        std::cout << "is_directory: " << result << ", error: " << ec.message() << std::endl;

        // Cleanup
        fs::remove_all(base);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output (order of listing may vary):
=== Directory checks ===
is_directory(base):   1
is_directory(subdir): 1
is_directory(temp):   1

=== File checks ===
is_directory(file): 0

=== Non-existent ===
is_directory(ghost): 0

=== Using file_status ===
is_directory(dir status):  1
is_directory(file status): 0

=== Filter directories ===
  [FILE] a.txt
  [DIR]  dir2
  [FILE] file.txt
  [DIR]  subdir

=== Error handling ===
is_directory: 1, error: Success
*/
