// CodeNebula - C++17 Example: std::filesystem::is_regular_file
// Compile: g++ -std=c++17 -Wall -Wextra -o example is_regular_file.cpp -lstdc++fs

// std::filesystem::is_regular_file() checks if a path refers to a regular file
// (not a directory, symlink, device, etc.). It follows symlinks.

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int main() {
    try {
        fs::path base = fs::temp_directory_path() / "cn_is_reg_test";
        fs::create_directories(base / "subdir");
        fs::path file = base / "data.txt";
        fs::path empty_file = base / "empty.txt";
        { std::ofstream(file) << "regular file content"; }
        { std::ofstream(empty_file); }  // empty file is still regular

        // --- Check regular files ---
        std::cout << "=== Regular file checks ===" << std::endl;
        std::cout << "is_regular_file(data.txt):  " << fs::is_regular_file(file) << std::endl;
        std::cout << "is_regular_file(empty.txt): " << fs::is_regular_file(empty_file) << std::endl;

        // --- Check non-regular entries ---
        std::cout << "\n=== Non-regular checks ===" << std::endl;
        std::cout << "is_regular_file(subdir): " << fs::is_regular_file(base / "subdir") << std::endl;
        std::cout << "is_regular_file(base):   " << fs::is_regular_file(base) << std::endl;

        // --- Check non-existent ---
        std::cout << "\n=== Non-existent ===" << std::endl;
        std::cout << "is_regular_file(ghost): " << fs::is_regular_file(base / "ghost.txt") << std::endl;

        // --- Using file_status ---
        std::cout << "\n=== Using file_status ===" << std::endl;
        fs::file_status fst = fs::status(file);
        fs::file_status dst = fs::status(base / "subdir");
        std::cout << "is_regular_file(file status): " << fs::is_regular_file(fst) << std::endl;
        std::cout << "is_regular_file(dir status):  " << fs::is_regular_file(dst) << std::endl;

        // --- Practical: count regular files ---
        std::cout << "\n=== Count regular files ===" << std::endl;
        { std::ofstream(base / "a.cpp") << "code"; }
        { std::ofstream(base / "b.h") << "header"; }
        int count = 0;
        for (const auto& entry : fs::directory_iterator(base)) {
            if (entry.is_regular_file()) {
                ++count;
                std::cout << "  " << entry.path().filename().string()
                          << " (" << entry.file_size() << " bytes)" << std::endl;
            }
        }
        std::cout << "Total regular files: " << count << std::endl;

        // --- Error code variant ---
        std::cout << "\n=== Error handling ===" << std::endl;
        std::error_code ec;
        bool result = fs::is_regular_file(file, ec);
        std::cout << "is_regular_file: " << result << ", error: " << ec.message() << std::endl;

        // Cleanup
        fs::remove_all(base);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output (order may vary):
=== Regular file checks ===
is_regular_file(data.txt):  1
is_regular_file(empty.txt): 1

=== Non-regular checks ===
is_regular_file(subdir): 0
is_regular_file(base):   0

=== Non-existent ===
is_regular_file(ghost): 0

=== Using file_status ===
is_regular_file(file status): 1
is_regular_file(dir status):  0

=== Count regular files ===
  a.cpp (4 bytes)
  b.h (6 bytes)
  data.txt (20 bytes)
  empty.txt (0 bytes)
Total regular files: 4

=== Error handling ===
is_regular_file: 1, error: Success
*/
