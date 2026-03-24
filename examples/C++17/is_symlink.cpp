// CodeNebula - C++17 Example: std::filesystem::is_symlink
// Compile: g++ -std=c++17 -Wall -Wextra -o example is_symlink.cpp -lstdc++fs

// std::filesystem::is_symlink() checks if a path is a symbolic link.
// Unlike other queries, it uses symlink_status (does not follow symlinks).

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int main() {
    try {
        fs::path base = fs::temp_directory_path() / "cn_is_symlink_test";
        fs::create_directories(base);
        fs::path file = base / "target.txt";
        { std::ofstream(file) << "symlink target"; }

        // --- Regular file is not a symlink ---
        std::cout << "=== Regular file ===" << std::endl;
        std::cout << "is_symlink(target.txt): " << fs::is_symlink(file) << std::endl;

        // --- Directory is not a symlink ---
        std::cout << "\n=== Directory ===" << std::endl;
        std::cout << "is_symlink(base): " << fs::is_symlink(base) << std::endl;

        // --- Create and check symlinks (may fail in sandboxed environments) ---
        std::cout << "\n=== Symbolic links ===" << std::endl;
        fs::path link = base / "link.txt";
        std::error_code ec;
        fs::create_symlink(file, link, ec);
        if (!ec) {
            std::cout << "is_symlink(link):         " << fs::is_symlink(link) << std::endl;
            std::cout << "is_regular_file(link):    " << fs::is_regular_file(link) << std::endl;
            std::cout << "(is_regular_file follows the symlink to the target)" << std::endl;

            // --- symlink_status vs status ---
            std::cout << "\n=== symlink_status vs status ===" << std::endl;
            fs::file_status ss = fs::symlink_status(link);
            fs::file_status rs = fs::status(link);
            std::cout << "symlink_status type: "
                      << (ss.type() == fs::file_type::symlink ? "symlink" : "other") << std::endl;
            std::cout << "status type:         "
                      << (rs.type() == fs::file_type::regular ? "regular" : "other") << std::endl;

            // --- Read through symlink ---
            std::cout << "\n=== Read through symlink ===" << std::endl;
            std::cout << "file_size(link): " << fs::file_size(link) << " bytes" << std::endl;

            // --- Directory symlink ---
            fs::path dir_link = base / "dir_link";
            fs::create_directory_symlink(base, dir_link, ec);
            if (!ec) {
                std::cout << "\n=== Directory symlink ===" << std::endl;
                std::cout << "is_symlink(dir_link):    " << fs::is_symlink(dir_link) << std::endl;
                std::cout << "is_directory(dir_link):  " << fs::is_directory(dir_link) << std::endl;
            }
        } else {
            std::cout << "Symlink creation not supported: " << ec.message() << std::endl;
            std::cout << "(This is normal in sandboxed/online compiler environments)" << std::endl;
        }

        // --- Non-existent path ---
        std::cout << "\n=== Non-existent ===" << std::endl;
        std::cout << "is_symlink(ghost): " << fs::is_symlink(base / "ghost") << std::endl;

        // --- Error code variant ---
        std::cout << "\n=== Error handling ===" << std::endl;
        bool r = fs::is_symlink(file, ec);
        std::cout << "is_symlink: " << r << ", error: " << ec.message() << std::endl;

        // Cleanup
        fs::remove_all(base);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output (when symlinks are supported):
=== Regular file ===
is_symlink(target.txt): 0

=== Directory ===
is_symlink(base): 0

=== Symbolic links ===
is_symlink(link):         1
is_regular_file(link):    1
(is_regular_file follows the symlink to the target)

=== symlink_status vs status ===
symlink_status type: symlink
status type:         regular

=== Read through symlink ===
file_size(link): 14 bytes

=== Directory symlink ===
is_symlink(dir_link):    1
is_directory(dir_link):  1

=== Non-existent ===
is_symlink(ghost): 0

=== Error handling ===
is_symlink: 0, error: Success
*/
