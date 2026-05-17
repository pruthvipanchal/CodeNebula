// CodeNebula - C++17 Example: std::filesystem::directory_options
// Compile: g++ -std=c++17 -Wall -Wextra -o example directory_options.cpp -lstdc++fs

// std::filesystem::directory_options controls directory iterator behavior:
// whether to follow symlinks and how to handle permission denied errors.

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int main() {
    try {
        fs::path base = fs::temp_directory_path() / "cn_dir_opts";
        fs::create_directories(base / "accessible" / "nested");
        { std::ofstream(base / "accessible" / "file.txt") << "data"; }
        { std::ofstream(base / "accessible" / "nested" / "deep.txt") << "deep"; }

        // --- Default options (none) ---
        std::cout << "=== directory_options::none ===" << std::endl;
        std::cout << "Iterating with default options:" << std::endl;
        for (const auto& entry : fs::recursive_directory_iterator(
                base, fs::directory_options::none)) {
            std::cout << "  " << entry.path().filename().string() << std::endl;
        }

        // --- follow_directory_symlink ---
        std::cout << "\n=== follow_directory_symlink ===" << std::endl;
        std::cout << "This option causes recursive_directory_iterator to" << std::endl;
        std::cout << "follow directory symlinks during recursion." << std::endl;
        // Demonstrate the option (symlink creation may fail in sandboxed envs)
        std::error_code ec;
        fs::create_directory_symlink(base / "accessible", base / "link", ec);
        if (!ec) {
            for (const auto& entry : fs::recursive_directory_iterator(
                    base, fs::directory_options::follow_directory_symlink)) {
                std::cout << "  " << entry.path().filename().string() << std::endl;
            }
        } else {
            std::cout << "  (symlink creation not supported here)" << std::endl;
        }

        // --- skip_permission_denied ---
        std::cout << "\n=== skip_permission_denied ===" << std::endl;
        std::cout << "This option silently skips directories that cause" << std::endl;
        std::cout << "permission denied errors instead of throwing." << std::endl;
        // Iterate safely with skip_permission_denied
        for (const auto& entry : fs::recursive_directory_iterator(
                base, fs::directory_options::skip_permission_denied)) {
            std::cout << "  " << entry.path().filename().string() << std::endl;
        }

        // --- Combining options with bitwise OR ---
        std::cout << "\n=== Combining options ===" << std::endl;
        auto combined = fs::directory_options::follow_directory_symlink
                      | fs::directory_options::skip_permission_denied;
        int count = 0;
        for (const auto& entry : fs::recursive_directory_iterator(base, combined)) {
            ++count;
        }
        std::cout << "Entries found with combined options: " << count << std::endl;

        // --- Error handling without skip_permission_denied ---
        std::cout << "\n=== Error code variant ===" << std::endl;
        auto it = fs::recursive_directory_iterator(base, fs::directory_options::none, ec);
        if (!ec) {
            std::cout << "Iterator created successfully" << std::endl;
        }

        // Cleanup
        fs::remove_all(base);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output (order may vary):
=== directory_options::none ===
Iterating with default options:
  accessible
  file.txt
  nested
  deep.txt

=== follow_directory_symlink ===
This option causes recursive_directory_iterator to
follow directory symlinks during recursion.
  accessible
  file.txt
  nested
  deep.txt
  link
  file.txt
  nested
  deep.txt

=== skip_permission_denied ===
This option silently skips directories that cause
permission denied errors instead of throwing.
  accessible
  file.txt
  nested
  deep.txt

=== Combining options ===
Entries found with combined options: 4

=== Error code variant ===
Iterator created successfully
*/
