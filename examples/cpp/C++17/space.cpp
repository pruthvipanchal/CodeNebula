// CodeNebula - C++17 Example: std::filesystem::space
// Compile: g++ -std=c++17 -Wall -Wextra -o example space.cpp -lstdc++fs

// std::filesystem::space() returns a space_info struct with capacity, free,
// and available bytes for the filesystem containing the given path.

#include <iostream>
#include <filesystem>
#include <cstdio>

namespace fs = std::filesystem;

void print_size(const char* label, std::uintmax_t bytes) {
    double gb = static_cast<double>(bytes) / (1024.0 * 1024.0 * 1024.0);
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%.2f GB", gb);
    std::cout << label << bytes << " bytes (" << buf << ")" << std::endl;
}

int main() {
    try {
        // --- Query temp directory filesystem ---
        std::cout << "=== Space for temp directory ===" << std::endl;
        fs::path tmp = fs::temp_directory_path();
        fs::space_info si = fs::space(tmp);
        std::cout << "Path: " << tmp << std::endl;
        print_size("Capacity:  ", si.capacity);
        print_size("Free:      ", si.free);
        print_size("Available: ", si.available);

        // --- Query current working directory ---
        std::cout << "\n=== Space for current directory ===" << std::endl;
        fs::space_info si2 = fs::space(fs::current_path());
        std::cout << "Path: " << fs::current_path() << std::endl;
        print_size("Capacity:  ", si2.capacity);
        print_size("Free:      ", si2.free);
        print_size("Available: ", si2.available);

        // --- Compute usage statistics ---
        std::cout << "\n=== Usage statistics ===" << std::endl;
        std::uintmax_t used = si.capacity - si.free;
        print_size("Used:      ", used);
        if (si.capacity > 0) {
            double pct = 100.0 * static_cast<double>(used) / si.capacity;
            char buf[16];
            std::snprintf(buf, sizeof(buf), "%.1f%%", pct);
            std::cout << "Usage:     " << buf << std::endl;
        }

        // --- Difference between free and available ---
        std::cout << "\n=== Free vs Available ===" << std::endl;
        std::cout << "free >= available: " << (si.free >= si.available) << std::endl;
        std::cout << "(available excludes space reserved for root/admin)" << std::endl;

        // --- Error code variant ---
        std::cout << "\n=== Error handling ===" << std::endl;
        std::error_code ec;
        fs::space_info si3 = fs::space("/nonexistent_mount_99", ec);
        if (ec) {
            std::cout << "Error querying space: " << ec.message() << std::endl;
        } else {
            std::cout << "Capacity: " << si3.capacity << std::endl;
        }

    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output (values vary by system):
=== Space for temp directory ===
Path: "/tmp"
Capacity:  107374182400 bytes (100.00 GB)
Free:      53687091200 bytes (50.00 GB)
Available: 48318382080 bytes (45.00 GB)

=== Space for current directory ===
Path: "/home/user"
Capacity:  107374182400 bytes (100.00 GB)
Free:      53687091200 bytes (50.00 GB)
Available: 48318382080 bytes (45.00 GB)

=== Usage statistics ===
Used:      53687091200 bytes (50.00 GB)
Usage:     50.0%

=== Free vs Available ===
free >= available: 1
(available excludes space reserved for root/admin)

=== Error handling ===
Error querying space: No such file or directory
*/
