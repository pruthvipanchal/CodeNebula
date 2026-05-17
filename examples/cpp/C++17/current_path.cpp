// CodeNebula - C++17 Example: std::filesystem::current_path
// Compile: g++ -std=c++17 -Wall -Wextra -o example current_path.cpp -lstdc++fs

// std::filesystem::current_path() gets or sets the process working directory.
// Setting the current path affects all relative path operations afterward.

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    try {
        // --- Get current working directory ---
        std::cout << "=== Get current_path ===" << std::endl;
        fs::path original = fs::current_path();
        std::cout << "Current directory: " << original << std::endl;

        // --- Path properties ---
        std::cout << "\n=== Path properties ===" << std::endl;
        std::cout << "is_absolute: " << original.is_absolute() << std::endl;
        std::cout << "parent:      " << original.parent_path() << std::endl;
        std::cout << "filename:    " << original.filename() << std::endl;

        // --- Change to temp directory ---
        std::cout << "\n=== Change current_path ===" << std::endl;
        fs::path tmp = fs::temp_directory_path();
        fs::current_path(tmp);
        std::cout << "Changed to: " << fs::current_path() << std::endl;

        // --- Relative paths now resolve from new cwd ---
        std::cout << "\n=== Relative path resolution ===" << std::endl;
        fs::path rel("subdir");
        std::cout << "Relative 'subdir' from cwd: " << (fs::current_path() / rel) << std::endl;

        // --- Restore original directory ---
        std::cout << "\n=== Restore original ===" << std::endl;
        fs::current_path(original);
        std::cout << "Restored to: " << fs::current_path() << std::endl;

        // --- Error code variant ---
        std::cout << "\n=== Error handling ===" << std::endl;
        std::error_code ec;
        fs::current_path("/nonexistent_dir_xyz", ec);
        if (ec) {
            std::cout << "Error: " << ec.message() << std::endl;
        }
        std::cout << "Still at: " << fs::current_path() << std::endl;

        // --- Canonical current path ---
        std::cout << "\n=== Canonical path ===" << std::endl;
        fs::path canonical = fs::canonical(fs::current_path());
        std::cout << "Canonical: " << canonical << std::endl;

    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output (paths vary by system):
=== Get current_path ===
Current directory: "/home/user/project"

=== Path properties ===
is_absolute: 1
parent:      "/home/user"
filename:    "project"

=== Change current_path ===
Changed to: "/tmp"

=== Relative path resolution ===
Relative 'subdir' from cwd: "/tmp/subdir"

=== Restore original ===
Restored to: "/home/user/project"

=== Error handling ===
Error: No such file or directory
Still at: "/home/user/project"

=== Canonical path ===
Canonical: "/home/user/project"
*/
