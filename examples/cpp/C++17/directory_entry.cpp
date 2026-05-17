// CodeNebula - C++17 Example: std::filesystem::directory_entry
// Compile: g++ -std=c++17 -Wall -Wextra -o example directory_entry.cpp -lstdc++fs

// std::filesystem::directory_entry holds information about a directory entry
// including path, file type, size, and last write time. It caches status info.

#include <iostream>
#include <filesystem>
#include <fstream>
#include <chrono>

namespace fs = std::filesystem;

int main() {
    try {
        // Create a temp file to inspect
        fs::path tmp = fs::temp_directory_path() / "cn_dir_entry_test.txt";
        { std::ofstream ofs(tmp); ofs << "Hello, directory_entry!"; }

        // --- Construct a directory_entry ---
        std::cout << "=== directory_entry basics ===" << std::endl;
        fs::directory_entry entry(tmp);
        std::cout << "path:     " << entry.path() << std::endl;
        std::cout << "exists:   " << entry.exists() << std::endl;

        // --- File type queries ---
        std::cout << "\n=== Type queries ===" << std::endl;
        std::cout << "is_regular_file: " << entry.is_regular_file() << std::endl;
        std::cout << "is_directory:    " << entry.is_directory() << std::endl;
        std::cout << "is_symlink:      " << entry.is_symlink() << std::endl;

        // --- Size and time ---
        std::cout << "\n=== Size and time ===" << std::endl;
        std::cout << "file_size: " << entry.file_size() << " bytes" << std::endl;
        auto ftime = entry.last_write_time();
        auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
            ftime - fs::file_time_type::clock::now() + std::chrono::system_clock::now());
        auto time_t_val = std::chrono::system_clock::to_time_t(sctp);
        std::cout << "last_write_time: " << std::ctime(&time_t_val);

        // --- Status ---
        std::cout << "\n=== Status ===" << std::endl;
        fs::file_status st = entry.status();
        std::cout << "type is regular_file: "
                  << (st.type() == fs::file_type::regular) << std::endl;

        // --- Refresh after external change ---
        std::cout << "\n=== Refresh ===" << std::endl;
        { std::ofstream ofs(tmp); ofs << "Updated content with more data"; }
        entry.refresh();
        std::cout << "After refresh, file_size: " << entry.file_size() << " bytes" << std::endl;

        // --- Directory entry for a directory ---
        std::cout << "\n=== Directory entry ===" << std::endl;
        fs::directory_entry dir_entry(fs::temp_directory_path());
        std::cout << "temp dir exists:       " << dir_entry.exists() << std::endl;
        std::cout << "temp dir is_directory:  " << dir_entry.is_directory() << std::endl;

        // Cleanup
        fs::remove(tmp);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output (paths and times vary):
=== directory_entry basics ===
path:     "/tmp/cn_dir_entry_test.txt"
exists:   1

=== Type queries ===
is_regular_file: 1
is_directory:    0
is_symlink:      0

=== Size and time ===
file_size: 23 bytes
last_write_time: <current date/time>

=== Status ===
type is regular_file: 1

=== Refresh ===
After refresh, file_size: 30 bytes

=== Directory entry ===
temp dir exists:       1
temp dir is_directory:  1
*/
