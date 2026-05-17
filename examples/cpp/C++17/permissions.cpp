// CodeNebula - C++17 Example: std::filesystem::permissions
// Compile: g++ -std=c++17 -Wall -Wextra -o example permissions.cpp -lstdc++fs

// std::filesystem::permissions() modifies file permission bits. It supports
// add, remove, and replace operations via perm_options flags.

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void show_perms(const fs::path& p) {
    fs::perms prm = fs::status(p).permissions();
    auto check = [&](fs::perms bit, char c) {
        return (prm & bit) != fs::perms::none ? c : '-';
    };
    std::cout << check(fs::perms::owner_read, 'r')
              << check(fs::perms::owner_write, 'w')
              << check(fs::perms::owner_exec, 'x')
              << check(fs::perms::group_read, 'r')
              << check(fs::perms::group_write, 'w')
              << check(fs::perms::group_exec, 'x')
              << check(fs::perms::others_read, 'r')
              << check(fs::perms::others_write, 'w')
              << check(fs::perms::others_exec, 'x')
              << std::endl;
}

int main() {
    try {
        fs::path base = fs::temp_directory_path() / "cn_perms_mod";
        fs::create_directory(base);
        fs::path file = base / "test.txt";
        { std::ofstream(file) << "permissions test"; }

        // --- Show initial permissions ---
        std::cout << "=== Initial permissions ===" << std::endl;
        std::cout << "File: "; show_perms(file);

        // --- Replace all permissions ---
        std::cout << "\n=== Replace (set to rwxr-xr-x) ===" << std::endl;
        fs::permissions(file,
            fs::perms::owner_all | fs::perms::group_read | fs::perms::group_exec
            | fs::perms::others_read | fs::perms::others_exec,
            fs::perm_options::replace);
        std::cout << "File: "; show_perms(file);

        // --- Add a permission ---
        std::cout << "\n=== Add group_write ===" << std::endl;
        fs::permissions(file, fs::perms::group_write, fs::perm_options::add);
        std::cout << "File: "; show_perms(file);

        // --- Remove a permission ---
        std::cout << "\n=== Remove others_read and others_exec ===" << std::endl;
        fs::permissions(file,
            fs::perms::others_read | fs::perms::others_exec,
            fs::perm_options::remove);
        std::cout << "File: "; show_perms(file);

        // --- Make read-only ---
        std::cout << "\n=== Make read-only ===" << std::endl;
        fs::permissions(file,
            fs::perms::owner_read | fs::perms::group_read,
            fs::perm_options::replace);
        std::cout << "File: "; show_perms(file);

        // --- Restore write for cleanup ---
        std::cout << "\n=== Restore write permission ===" << std::endl;
        fs::permissions(file, fs::perms::owner_write, fs::perm_options::add);
        std::cout << "File: "; show_perms(file);

        // --- Error code variant ---
        std::cout << "\n=== Error handling ===" << std::endl;
        std::error_code ec;
        fs::permissions(base / "nonexistent", fs::perms::owner_read,
                       fs::perm_options::replace, ec);
        std::cout << "Nonexistent: " << ec.message() << std::endl;

        // Cleanup
        fs::remove_all(base);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output (on POSIX systems):
=== Initial permissions ===
File: rw-r--r--

=== Replace (set to rwxr-xr-x) ===
File: rwxr-xr-x

=== Add group_write ===
File: rwxrwxr-x

=== Remove others_read and others_exec ===
File: rwxrwx---

=== Make read-only ===
File: r--r-----

=== Restore write permission ===
File: rw-r-----

=== Error handling ===
Nonexistent: No such file or directory
*/
