// CodeNebula - C++17 Example: std::filesystem::exists
// Compile: g++ -std=c++17 -Wall -Wextra -o example exists.cpp -lstdc++fs

// std::filesystem::exists() checks whether a path refers to an existing
// file or directory. It follows symlinks by default.

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int main() {
    try {
        fs::path base = fs::temp_directory_path() / "cn_exists_test";
        fs::create_directories(base);

        // --- Check existing file ---
        std::cout << "=== Existing file ===" << std::endl;
        fs::path file = base / "hello.txt";
        { std::ofstream(file) << "hello"; }
        std::cout << "exists(file): " << fs::exists(file) << std::endl;

        // --- Check existing directory ---
        std::cout << "\n=== Existing directory ===" << std::endl;
        std::cout << "exists(base): " << fs::exists(base) << std::endl;
        std::cout << "exists(temp): " << fs::exists(fs::temp_directory_path()) << std::endl;

        // --- Check non-existent path ---
        std::cout << "\n=== Non-existent path ===" << std::endl;
        std::cout << "exists(ghost): " << fs::exists(base / "ghost.txt") << std::endl;
        std::cout << "exists(nodir): " << fs::exists(base / "nodir" / "file") << std::endl;

        // --- Check after removal ---
        std::cout << "\n=== After removal ===" << std::endl;
        std::cout << "Before remove: " << fs::exists(file) << std::endl;
        fs::remove(file);
        std::cout << "After remove:  " << fs::exists(file) << std::endl;

        // --- Using file_status overload ---
        std::cout << "\n=== Using file_status ===" << std::endl;
        fs::file_status st = fs::status(base);
        std::cout << "exists(status(base)): " << fs::exists(st) << std::endl;
        fs::file_status nst = fs::status(base / "nope");
        std::cout << "exists(status(nope)): " << fs::exists(nst) << std::endl;

        // --- Error code variant ---
        std::cout << "\n=== Error code variant ===" << std::endl;
        std::error_code ec;
        bool e = fs::exists(base, ec);
        std::cout << "exists: " << e << ", error: " << ec.message() << std::endl;

        // --- Empty path ---
        std::cout << "\n=== Empty path ===" << std::endl;
        std::cout << "exists(\"\"): " << fs::exists(fs::path{}) << std::endl;

        // Cleanup
        fs::remove_all(base);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output:
=== Existing file ===
exists(file): 1

=== Existing directory ===
exists(base): 1
exists(temp): 1

=== Non-existent path ===
exists(ghost): 0
exists(nodir): 0

=== After removal ===
Before remove: 1
After remove:  0

=== Using file_status ===
exists(status(base)): 1
exists(status(nope)): 0

=== Error code variant ===
exists: 1, error: Success

=== Empty path ===
exists(""): 0
*/
