// CodeNebula - C++17 Example: std::filesystem::file_size
// Compile: g++ -std=c++17 -Wall -Wextra -o example file_size.cpp -lstdc++fs

// std::filesystem::file_size() returns the size in bytes of a regular file.
// Behavior is implementation-defined for directories and special files.

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

std::string readable_size(std::uintmax_t bytes) {
    const char* units[] = {"B", "KB", "MB"};
    int idx = 0;
    double size = static_cast<double>(bytes);
    while (size >= 1024.0 && idx < 2) { size /= 1024.0; ++idx; }
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%.1f %s", size, units[idx]);
    return buf;
}

int main() {
    try {
        fs::path base = fs::temp_directory_path() / "cn_file_size_test";
        fs::create_directory(base);

        // --- Empty file ---
        std::cout << "=== Empty file ===" << std::endl;
        fs::path empty = base / "empty.txt";
        { std::ofstream(empty); }
        std::cout << "file_size: " << fs::file_size(empty) << " bytes" << std::endl;

        // --- Small file ---
        std::cout << "\n=== Small file ===" << std::endl;
        fs::path small = base / "small.txt";
        { std::ofstream(small) << "Hello, World!"; }
        std::cout << "file_size: " << fs::file_size(small) << " bytes" << std::endl;

        // --- Larger file ---
        std::cout << "\n=== Larger file ===" << std::endl;
        fs::path larger = base / "larger.dat";
        { std::ofstream ofs(larger); for (int i = 0; i < 1000; ++i) ofs << "Line " << i << "\n"; }
        auto sz = fs::file_size(larger);
        std::cout << "file_size: " << sz << " bytes (" << readable_size(sz) << ")" << std::endl;

        // --- Binary file ---
        std::cout << "\n=== Binary file ===" << std::endl;
        fs::path bin = base / "data.bin";
        { std::ofstream ofs(bin, std::ios::binary);
          char buf[256];
          for (int i = 0; i < 256; ++i) buf[i] = static_cast<char>(i);
          ofs.write(buf, 256); }
        std::cout << "file_size: " << fs::file_size(bin) << " bytes" << std::endl;

        // --- Compare file sizes ---
        std::cout << "\n=== Compare sizes ===" << std::endl;
        std::cout << "empty < small:  " << (fs::file_size(empty) < fs::file_size(small)) << std::endl;
        std::cout << "small < larger: " << (fs::file_size(small) < fs::file_size(larger)) << std::endl;

        // --- Error handling ---
        std::cout << "\n=== Error handling ===" << std::endl;
        std::error_code ec;
        auto s = fs::file_size(base / "nonexistent.txt", ec);
        if (ec) {
            std::cout << "Error: " << ec.message() << std::endl;
        }
        // Directory size is implementation-defined
        s = fs::file_size(base, ec);
        std::cout << "Directory size result: "
                  << (ec ? "error" : std::to_string(s)) << std::endl;

        // Cleanup
        fs::remove_all(base);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output:
=== Empty file ===
file_size: 0 bytes

=== Small file ===
file_size: 13 bytes

=== Larger file ===
file_size: 8893 bytes (8.7 KB)

=== Binary file ===
file_size: 256 bytes

=== Compare sizes ===
empty < small:  1
small < larger: 1

=== Error handling ===
Error: No such file or directory
Directory size result: error
*/
