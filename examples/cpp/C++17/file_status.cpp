// CodeNebula - C++17 Example: std::filesystem::file_status
// Compile: g++ -std=c++17 -Wall -Wextra -o example file_status.cpp -lstdc++fs

// std::filesystem::file_status holds the type and permissions of a file.
// Use status() to query a path, or symlink_status() to not follow symlinks.

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

std::string type_to_string(fs::file_type t) {
    switch (t) {
        case fs::file_type::regular:   return "regular file";
        case fs::file_type::directory: return "directory";
        case fs::file_type::symlink:   return "symlink";
        case fs::file_type::block:     return "block device";
        case fs::file_type::character: return "character device";
        case fs::file_type::fifo:      return "FIFO";
        case fs::file_type::socket:    return "socket";
        case fs::file_type::not_found: return "not found";
        case fs::file_type::unknown:   return "unknown";
        default:                       return "none";
    }
}

int main() {
    try {
        // Setup
        fs::path tmp = fs::temp_directory_path() / "cn_status_test";
        fs::create_directory(tmp);
        fs::path file = tmp / "test.txt";
        { std::ofstream(file) << "status test"; }

        // --- Query file status ---
        std::cout << "=== File status ===" << std::endl;
        fs::file_status fst = fs::status(file);
        std::cout << "Type: " << type_to_string(fst.type()) << std::endl;
        std::cout << "Permissions: " << static_cast<int>(fst.permissions()) << std::endl;

        // --- Query directory status ---
        std::cout << "\n=== Directory status ===" << std::endl;
        fs::file_status dst = fs::status(tmp);
        std::cout << "Type: " << type_to_string(dst.type()) << std::endl;

        // --- Non-existent path ---
        std::cout << "\n=== Non-existent path ===" << std::endl;
        fs::file_status nst = fs::status(tmp / "nonexistent");
        std::cout << "Type: " << type_to_string(nst.type()) << std::endl;

        // --- Using status_known ---
        std::cout << "\n=== status_known ===" << std::endl;
        std::cout << "File status known:  " << fs::status_known(fst) << std::endl;
        std::cout << "Missing status known: " << fs::status_known(nst) << std::endl;

        // --- Construct file_status manually ---
        std::cout << "\n=== Manual construction ===" << std::endl;
        fs::file_status manual(fs::file_type::regular, fs::perms::owner_read);
        std::cout << "Type: " << type_to_string(manual.type()) << std::endl;
        std::cout << "Has owner_read: "
                  << ((manual.permissions() & fs::perms::owner_read) != fs::perms::none)
                  << std::endl;

        // Cleanup
        fs::remove_all(tmp);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output (permission values vary by OS):
=== File status ===
Type: regular file
Permissions: 420

=== Directory status ===
Type: directory

=== Non-existent path ===
Type: not found

=== status_known ===
File status known:  1
Missing status known: 1

=== Manual construction ===
Type: regular file
Has owner_read: 1
*/
