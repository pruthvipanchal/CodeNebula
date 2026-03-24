// CodeNebula - C++17 Example: std::filesystem::resize_file
// Compile: g++ -std=c++17 -Wall -Wextra -o example resize_file.cpp -lstdc++fs

// std::filesystem::resize_file changes a file's size. Truncation discards
// data beyond the new size; extension fills with zero bytes.

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

void show_file(const fs::path& p) {
    std::cout << "  Size: " << fs::file_size(p) << " bytes" << std::endl;
    std::ifstream ifs(p, std::ios::binary);
    std::string content((std::istreambuf_iterator<char>(ifs)),
                         std::istreambuf_iterator<char>());
    std::cout << "  Content: \"";
    for (char c : content) {
        if (c >= 32 && c < 127) std::cout << c;
        else std::cout << "\\0";
    }
    std::cout << "\"" << std::endl;
}

int main() {
    try {
        fs::path base = fs::temp_directory_path() / "cn_resize_test";
        fs::create_directory(base);
        fs::path file = base / "data.txt";

        // Create a file with known content
        { std::ofstream(file) << "Hello, World!"; }  // 13 bytes

        std::cout << "=== Original file ===" << std::endl;
        show_file(file);

        // --- Truncate the file ---
        std::cout << "\n=== Truncate to 5 bytes ===" << std::endl;
        fs::resize_file(file, 5);
        show_file(file);

        // --- Extend the file (zero-filled) ---
        std::cout << "\n=== Extend to 10 bytes ===" << std::endl;
        fs::resize_file(file, 10);
        show_file(file);

        // --- Resize to zero ---
        std::cout << "\n=== Resize to 0 ===" << std::endl;
        fs::resize_file(file, 0);
        show_file(file);
        std::cout << "  File still exists: " << fs::exists(file) << std::endl;

        // --- Error handling ---
        std::cout << "\n=== Error handling ===" << std::endl;
        std::error_code ec;
        fs::resize_file(base / "nonexistent.txt", 100, ec);
        std::cout << "Resize nonexistent: " << ec.message() << std::endl;

        // --- Practical use: pre-allocate file space ---
        std::cout << "\n=== Pre-allocate space ===" << std::endl;
        fs::path preallocated = base / "preallocated.bin";
        { std::ofstream(preallocated); }  // create empty
        fs::resize_file(preallocated, 1024);
        std::cout << "Pre-allocated size: " << fs::file_size(preallocated) << " bytes" << std::endl;

        // Cleanup
        fs::remove_all(base);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output:
=== Original file ===
  Size: 13 bytes
  Content: "Hello, World!"

=== Truncate to 5 bytes ===
  Size: 5 bytes
  Content: "Hello"

=== Extend to 10 bytes ===
  Size: 10 bytes
  Content: "Hello\0\0\0\0\0"

=== Resize to 0 ===
  Size: 0 bytes
  Content: ""
  File still exists: 1

=== Error handling ===
Resize nonexistent: No such file or directory

=== Pre-allocate space ===
Pre-allocated size: 1024 bytes
*/
