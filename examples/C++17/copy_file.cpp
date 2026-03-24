// CodeNebula - C++17 Example: std::filesystem::copy_file
// Compile: g++ -std=c++17 -Wall -Wextra -o example copy_file.cpp -lstdc++fs

// std::filesystem::copy_file copies a single file. It supports options to
// skip, overwrite, or update existing destinations.

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void show_file(const fs::path& p) {
    std::ifstream ifs(p);
    std::string content;
    std::getline(ifs, content);
    std::cout << p.filename().string() << ": \"" << content
              << "\" (" << fs::file_size(p) << " bytes)" << std::endl;
}

int main() {
    try {
        fs::path base = fs::temp_directory_path() / "cn_copy_file";
        fs::create_directory(base);
        fs::path src = base / "source.txt";
        fs::path dst = base / "copy.txt";

        { std::ofstream(src) << "Hello from source file!"; }

        // --- Basic copy ---
        std::cout << "=== Basic copy_file ===" << std::endl;
        bool copied = fs::copy_file(src, dst);
        std::cout << "Copied: " << copied << std::endl;
        show_file(src);
        show_file(dst);

        // --- Copy fails if destination exists ---
        std::cout << "\n=== Copy to existing (default) ===" << std::endl;
        std::error_code ec;
        fs::copy_file(src, dst, ec);
        std::cout << "Error: " << ec.message() << std::endl;

        // --- Overwrite existing ---
        std::cout << "\n=== overwrite_existing ===" << std::endl;
        { std::ofstream(src) << "Updated source content"; }
        copied = fs::copy_file(src, dst, fs::copy_options::overwrite_existing);
        std::cout << "Overwritten: " << copied << std::endl;
        show_file(dst);

        // --- Skip existing ---
        std::cout << "\n=== skip_existing ===" << std::endl;
        { std::ofstream(src) << "Even newer content"; }
        copied = fs::copy_file(src, dst, fs::copy_options::skip_existing);
        std::cout << "Copied (should be false): " << copied << std::endl;
        show_file(dst);  // Still has old content

        // --- Copy preserves file size ---
        std::cout << "\n=== Size verification ===" << std::endl;
        fs::path big_src = base / "big.dat";
        fs::path big_dst = base / "big_copy.dat";
        { std::ofstream ofs(big_src); for (int i = 0; i < 100; ++i) ofs << "data line\n"; }
        fs::copy_file(big_src, big_dst);
        std::cout << "Source size: " << fs::file_size(big_src) << std::endl;
        std::cout << "Copy size:   " << fs::file_size(big_dst) << std::endl;
        std::cout << "Sizes match: " << (fs::file_size(big_src) == fs::file_size(big_dst)) << std::endl;

        // Cleanup
        fs::remove_all(base);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output:
=== Basic copy_file ===
Copied: 1
source.txt: "Hello from source file!" (23 bytes)
copy.txt: "Hello from source file!" (23 bytes)

=== Copy to existing (default) ===
Error: File exists

=== overwrite_existing ===
Overwritten: 1
copy.txt: "Updated source content" (22 bytes)

=== skip_existing ===
Copied (should be false): 0
copy.txt: "Updated source content" (22 bytes)

=== Size verification ===
Source size: 1000
Copy size:   1000
Sizes match: 1
*/
