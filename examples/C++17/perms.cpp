// CodeNebula - C++17 Example: std::filesystem::perms
// Compile: g++ -std=c++17 -Wall -Wextra -o example perms.cpp -lstdc++fs

// std::filesystem::perms is a bitmask type representing POSIX permission bits.
// It supports owner/group/others read/write/execute and special bits.

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void show_perms(fs::perms p) {
    auto check = [&](fs::perms bit, char c) {
        return (p & bit) != fs::perms::none ? c : '-';
    };
    std::cout << check(fs::perms::owner_read, 'r')
              << check(fs::perms::owner_write, 'w')
              << check(fs::perms::owner_exec, 'x')
              << check(fs::perms::group_read, 'r')
              << check(fs::perms::group_write, 'w')
              << check(fs::perms::group_exec, 'x')
              << check(fs::perms::others_read, 'r')
              << check(fs::perms::others_write, 'w')
              << check(fs::perms::others_exec, 'x');
    std::cout << " (octal: " << std::oct << static_cast<unsigned>(p) << std::dec << ")";
    std::cout << std::endl;
}

int main() {
    try {
        fs::path tmp = fs::temp_directory_path() / "cn_perms_test.txt";
        { std::ofstream(tmp) << "perms test"; }

        // --- Current permissions ---
        std::cout << "=== Current permissions ===" << std::endl;
        fs::perms p = fs::status(tmp).permissions();
        std::cout << "File: "; show_perms(p);

        // --- Named permission constants ---
        std::cout << "\n=== Permission constants ===" << std::endl;
        std::cout << "owner_all:  "; show_perms(fs::perms::owner_all);
        std::cout << "group_all:  "; show_perms(fs::perms::group_all);
        std::cout << "others_all: "; show_perms(fs::perms::others_all);
        std::cout << "all:        "; show_perms(fs::perms::all);
        std::cout << "none:       "; show_perms(fs::perms::none);

        // --- Bitwise operations ---
        std::cout << "\n=== Bitwise operations ===" << std::endl;
        fs::perms combined = fs::perms::owner_read | fs::perms::owner_write
                           | fs::perms::group_read | fs::perms::others_read;
        std::cout << "rw-r--r--: "; show_perms(combined);

        fs::perms masked = fs::perms::all & ~fs::perms::others_write;
        std::cout << "all & ~others_write: "; show_perms(masked);

        // --- Check individual bits ---
        std::cout << "\n=== Checking bits ===" << std::endl;
        std::cout << "Has owner_read:  " << ((p & fs::perms::owner_read) != fs::perms::none) << std::endl;
        std::cout << "Has owner_exec:  " << ((p & fs::perms::owner_exec) != fs::perms::none) << std::endl;
        std::cout << "Has others_write: " << ((p & fs::perms::others_write) != fs::perms::none) << std::endl;

        // --- Special bits ---
        std::cout << "\n=== Special bits ===" << std::endl;
        std::cout << "set_uid:    "; show_perms(fs::perms::set_uid);
        std::cout << "set_gid:    "; show_perms(fs::perms::set_gid);
        std::cout << "sticky_bit: "; show_perms(fs::perms::sticky_bit);

        // Cleanup
        fs::remove(tmp);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output (permissions may vary):
=== Current permissions ===
File: rw-r--r-- (octal: 644)

=== Permission constants ===
owner_all:  rwx------ (octal: 700)
group_all:  ---rwx--- (octal: 70)
others_all: ------rwx (octal: 7)
all:        rwxrwxrwx (octal: 777)
none:       --------- (octal: 0)

=== Bitwise operations ===
rw-r--r--: rw-r--r-- (octal: 644)
all & ~others_write: rwxrwxr-x (octal: 775)

=== Checking bits ===
Has owner_read:  1
Has owner_exec:  0
Has others_write: 0

=== Special bits ===
set_uid:    --------- (octal: 4000)
set_gid:    --------- (octal: 2000)
sticky_bit: --------- (octal: 1000)
*/
