// CodeNebula - C++17 Example: std::filesystem::last_write_time
// Compile: g++ -std=c++17 -Wall -Wextra -o example last_write_time.cpp -lstdc++fs

// std::filesystem::last_write_time gets or sets a file's last modification
// time. Returns a file_time_type based on the filesystem clock.

#include <iostream>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <ctime>

namespace fs = std::filesystem;

void print_ftime(const char* label, fs::file_time_type ftime) {
    // Convert file_time_type to system_clock for display
    auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
        ftime - fs::file_time_type::clock::now() + std::chrono::system_clock::now());
    std::time_t tt = std::chrono::system_clock::to_time_t(sctp);
    std::cout << label << std::ctime(&tt);  // ctime adds newline
}

int main() {
    try {
        fs::path base = fs::temp_directory_path() / "cn_lwt_test";
        fs::create_directory(base);
        fs::path file = base / "test.txt";
        { std::ofstream(file) << "last_write_time test"; }

        // --- Get last write time ---
        std::cout << "=== Get last_write_time ===" << std::endl;
        fs::file_time_type ftime = fs::last_write_time(file);
        print_ftime("File modified: ", ftime);

        // --- Compare two files ---
        std::cout << "=== Compare modification times ===" << std::endl;
        fs::path file2 = base / "newer.txt";
        { std::ofstream(file2) << "I am newer"; }
        fs::file_time_type ftime2 = fs::last_write_time(file2);
        std::cout << "file2 >= file1: " << (ftime2 >= ftime) << std::endl;

        // --- Set last write time ---
        std::cout << "\n=== Set last_write_time ===" << std::endl;
        auto old_time = ftime - std::chrono::hours(24);
        fs::last_write_time(file, old_time);
        fs::file_time_type updated = fs::last_write_time(file);
        print_ftime("After setting 24h earlier: ", updated);

        // --- Verify the time changed ---
        std::cout << "=== Verify change ===" << std::endl;
        auto diff = ftime - updated;
        auto hours = std::chrono::duration_cast<std::chrono::hours>(diff).count();
        std::cout << "Difference: ~" << hours << " hours" << std::endl;

        // --- Error handling ---
        std::cout << "\n=== Error handling ===" << std::endl;
        std::error_code ec;
        fs::last_write_time(base / "nonexistent.txt", ec);
        std::cout << "Nonexistent: " << ec.message() << std::endl;

        // --- Time arithmetic ---
        std::cout << "\n=== Time arithmetic ===" << std::endl;
        auto now = fs::file_time_type::clock::now();
        auto age = now - fs::last_write_time(file);
        auto age_hours = std::chrono::duration_cast<std::chrono::hours>(age).count();
        std::cout << "File age: ~" << age_hours << " hours" << std::endl;

        // Cleanup
        fs::remove_all(base);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output (times vary):
=== Get last_write_time ===
File modified: Mon Mar 24 12:00:00 2026

=== Compare modification times ===
file2 >= file1: 1

=== Set last_write_time ===
After setting 24h earlier: Sun Mar 23 12:00:00 2026

=== Verify change ===
Difference: ~24 hours

=== Error handling ===
Nonexistent: No such file or directory

=== Time arithmetic ===
File age: ~24 hours
*/
