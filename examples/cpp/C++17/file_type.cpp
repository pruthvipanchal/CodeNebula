// CodeNebula - C++17 Example: std::filesystem::file_type
// Compile: g++ -std=c++17 -Wall -Wextra -o example file_type.cpp -lstdc++fs

// std::filesystem::file_type is an enum classifying entries as regular files,
// directories, symlinks, block/character devices, FIFOs, sockets, etc.

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void classify(const fs::path& p) {
    std::error_code ec;
    fs::file_status st = fs::status(p, ec);
    std::cout << p.filename().string() << " -> ";
    if (ec) {
        std::cout << "error: " << ec.message() << std::endl;
        return;
    }
    switch (st.type()) {
        case fs::file_type::none:      std::cout << "none"; break;
        case fs::file_type::not_found: std::cout << "not_found"; break;
        case fs::file_type::regular:   std::cout << "regular"; break;
        case fs::file_type::directory: std::cout << "directory"; break;
        case fs::file_type::symlink:   std::cout << "symlink"; break;
        case fs::file_type::block:     std::cout << "block"; break;
        case fs::file_type::character: std::cout << "character"; break;
        case fs::file_type::fifo:      std::cout << "fifo"; break;
        case fs::file_type::socket:    std::cout << "socket"; break;
        case fs::file_type::unknown:   std::cout << "unknown"; break;
    }
    std::cout << std::endl;
}

int main() {
    try {
        fs::path base = fs::temp_directory_path() / "cn_file_type_test";
        fs::create_directories(base / "subdir");
        { std::ofstream(base / "file.txt") << "data"; }

        // --- Classify created entries ---
        std::cout << "=== Classifying entries ===" << std::endl;
        classify(base / "file.txt");
        classify(base / "subdir");
        classify(base / "nonexistent");

        // --- Using convenience functions ---
        std::cout << "\n=== Convenience type checks ===" << std::endl;
        std::cout << "is_regular_file: " << fs::is_regular_file(base / "file.txt") << std::endl;
        std::cout << "is_directory:    " << fs::is_directory(base / "subdir") << std::endl;
        std::cout << "is_symlink:      " << fs::is_symlink(base / "file.txt") << std::endl;
        std::cout << "is_block_file:   " << fs::is_block_file(base / "file.txt") << std::endl;
        std::cout << "is_char_file:    " << fs::is_character_file(base / "file.txt") << std::endl;
        std::cout << "is_fifo:         " << fs::is_fifo(base / "file.txt") << std::endl;
        std::cout << "is_socket:       " << fs::is_socket(base / "file.txt") << std::endl;
        std::cout << "is_other:        " << fs::is_other(base / "file.txt") << std::endl;

        // --- Check temp directory itself ---
        std::cout << "\n=== Temp directory type ===" << std::endl;
        classify(fs::temp_directory_path());

        // --- Check if a status indicates emptiness ---
        std::cout << "\n=== is_empty ===" << std::endl;
        std::cout << "subdir is empty: " << fs::is_empty(base / "subdir") << std::endl;
        std::cout << "file is empty:   " << fs::is_empty(base / "file.txt") << std::endl;

        // Cleanup
        fs::remove_all(base);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output:
=== Classifying entries ===
file.txt -> regular
subdir -> directory
nonexistent -> not_found

=== Convenience type checks ===
is_regular_file: 1
is_directory:    1
is_symlink:      0
is_block_file:   0
is_char_file:    0
is_fifo:         0
is_socket:       0
is_other:        0

=== Temp directory type ===
tmp -> directory

=== is_empty ===
subdir is empty: 1
file is empty:   0
*/
