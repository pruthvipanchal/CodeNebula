// CodeNebula - C++17 Example: std::filesystem::space_info
// Compile: g++ -std=c++17 -Wall -Wextra -o example space_info.cpp -lstdc++fs

// std::filesystem::space_info holds capacity, free, and available bytes
// for a filesystem. Returned by std::filesystem::space().

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

std::string bytes_to_readable(std::uintmax_t bytes) {
    const char* units[] = {"B", "KB", "MB", "GB", "TB"};
    int idx = 0;
    double size = static_cast<double>(bytes);
    while (size >= 1024.0 && idx < 4) {
        size /= 1024.0;
        ++idx;
    }
    char buf[64];
    std::snprintf(buf, sizeof(buf), "%.2f %s", size, units[idx]);
    return std::string(buf);
}

int main() {
    try {
        // --- Query space for root/temp path ---
        std::cout << "=== Disk space info ===" << std::endl;
        fs::space_info si = fs::space(fs::temp_directory_path());

        std::cout << "Path queried: " << fs::temp_directory_path() << std::endl;
        std::cout << "Capacity:  " << si.capacity
                  << " (" << bytes_to_readable(si.capacity) << ")" << std::endl;
        std::cout << "Free:      " << si.free
                  << " (" << bytes_to_readable(si.free) << ")" << std::endl;
        std::cout << "Available: " << si.available
                  << " (" << bytes_to_readable(si.available) << ")" << std::endl;

        // --- Examine the struct fields ---
        std::cout << "\n=== Field examination ===" << std::endl;
        std::cout << "capacity >= free: " << (si.capacity >= si.free) << std::endl;
        std::cout << "free >= available: " << (si.free >= si.available) << std::endl;

        // --- Usage percentage ---
        std::cout << "\n=== Usage ===" << std::endl;
        if (si.capacity > 0) {
            double used_pct = 100.0 * (1.0 - static_cast<double>(si.free) / si.capacity);
            std::cout << "Used: " << bytes_to_readable(si.capacity - si.free) << std::endl;
            char pct[16];
            std::snprintf(pct, sizeof(pct), "%.1f%%", used_pct);
            std::cout << "Usage: " << pct << std::endl;
        }

        // --- Compare two paths (may be same filesystem) ---
        std::cout << "\n=== Current directory space ===" << std::endl;
        fs::space_info si2 = fs::space(fs::current_path());
        std::cout << "Current path capacity: " << bytes_to_readable(si2.capacity) << std::endl;
        std::cout << "Same filesystem: " << (si.capacity == si2.capacity ? "likely" : "different") << std::endl;

    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output (values vary by system):
=== Disk space info ===
Path queried: "/tmp"
Capacity:  107374182400 (100.00 GB)
Free:      53687091200 (50.00 GB)
Available: 48318382080 (45.00 GB)

=== Field examination ===
capacity >= free: 1
free >= available: 1

=== Usage ===
Used: 50.00 GB
Usage: 50.0%

=== Current directory space ===
Current path capacity: 100.00 GB
Same filesystem: likely
*/
