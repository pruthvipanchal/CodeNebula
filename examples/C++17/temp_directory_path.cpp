// CodeNebula - C++17 Example: std::filesystem::temp_directory_path
// Compile: g++ -std=c++17 -Wall -Wextra -o example temp_directory_path.cpp -lstdc++fs

// std::filesystem::temp_directory_path() returns the OS-designated temporary
// directory (e.g., /tmp on POSIX, %TEMP% on Windows).

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int main() {
    try {
        // --- Get temp directory ---
        std::cout << "=== temp_directory_path ===" << std::endl;
        fs::path tmp = fs::temp_directory_path();
        std::cout << "Temp directory: " << tmp << std::endl;

        // --- Properties of temp directory ---
        std::cout << "\n=== Properties ===" << std::endl;
        std::cout << "exists:       " << fs::exists(tmp) << std::endl;
        std::cout << "is_directory: " << fs::is_directory(tmp) << std::endl;
        std::cout << "is_absolute:  " << tmp.is_absolute() << std::endl;

        // --- Create a temp file inside it ---
        std::cout << "\n=== Create temp file ===" << std::endl;
        fs::path tmpfile = tmp / "cn_temp_test_12345.txt";
        { std::ofstream(tmpfile) << "temporary data"; }
        std::cout << "Created: " << tmpfile << std::endl;
        std::cout << "File exists: " << fs::exists(tmpfile) << std::endl;
        std::cout << "File size:   " << fs::file_size(tmpfile) << " bytes" << std::endl;

        // --- Create a temp subdirectory ---
        std::cout << "\n=== Create temp subdirectory ===" << std::endl;
        fs::path tmpdir = tmp / "cn_temp_subdir_test";
        fs::create_directory(tmpdir);
        std::cout << "Created dir: " << tmpdir.filename() << std::endl;
        std::cout << "Dir exists:  " << fs::exists(tmpdir) << std::endl;

        // --- Space available in temp filesystem ---
        std::cout << "\n=== Temp filesystem space ===" << std::endl;
        fs::space_info si = fs::space(tmp);
        double free_gb = static_cast<double>(si.free) / (1024.0 * 1024.0 * 1024.0);
        char buf[32];
        std::snprintf(buf, sizeof(buf), "%.2f GB", free_gb);
        std::cout << "Free space: " << buf << std::endl;

        // --- Error code variant ---
        std::cout << "\n=== Error code variant ===" << std::endl;
        std::error_code ec;
        fs::path tmp2 = fs::temp_directory_path(ec);
        std::cout << "Success: " << (!ec) << std::endl;
        std::cout << "Path:    " << tmp2 << std::endl;

        // Cleanup
        fs::remove(tmpfile);
        fs::remove(tmpdir);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output (paths and values vary):
=== temp_directory_path ===
Temp directory: "/tmp"

=== Properties ===
exists:       1
is_directory: 1
is_absolute:  1

=== Create temp file ===
Created: "/tmp/cn_temp_test_12345.txt"
File exists: 1
File size:   14 bytes

=== Create temp subdirectory ===
Created dir: "cn_temp_subdir_test"
Dir exists:  1

=== Temp filesystem space ===
Free space: 50.00 GB

=== Error code variant ===
Success: 1
Path:    "/tmp"
*/
