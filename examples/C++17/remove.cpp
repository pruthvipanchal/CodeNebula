// CodeNebula - C++17 Example: std::filesystem::remove
// Compile: g++ -std=c++17 -Wall -Wextra -o example remove.cpp -lstdc++fs

// std::filesystem::remove deletes a single file or empty directory.
// std::filesystem::remove_all deletes a path and all its contents recursively.

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int main() {
    try {
        fs::path base = fs::temp_directory_path() / "cn_remove_test";
        fs::create_directories(base);

        // --- Remove a file ---
        std::cout << "=== Remove a file ===" << std::endl;
        fs::path file = base / "file.txt";
        { std::ofstream(file) << "data"; }
        std::cout << "Exists before: " << fs::exists(file) << std::endl;
        bool removed = fs::remove(file);
        std::cout << "remove() returned: " << removed << std::endl;
        std::cout << "Exists after:  " << fs::exists(file) << std::endl;

        // --- Remove non-existent file ---
        std::cout << "\n=== Remove non-existent ===" << std::endl;
        removed = fs::remove(base / "nope.txt");
        std::cout << "remove() returned: " << removed << " (false = didn't exist)" << std::endl;

        // --- Remove empty directory ---
        std::cout << "\n=== Remove empty directory ===" << std::endl;
        fs::path empty_dir = base / "empty";
        fs::create_directory(empty_dir);
        removed = fs::remove(empty_dir);
        std::cout << "Removed empty dir: " << removed << std::endl;

        // --- Remove non-empty directory fails ---
        std::cout << "\n=== Remove non-empty directory ===" << std::endl;
        fs::path nonempty = base / "nonempty";
        fs::create_directory(nonempty);
        { std::ofstream(nonempty / "child.txt") << "child"; }
        std::error_code ec;
        fs::remove(nonempty, ec);
        std::cout << "Error: " << ec.message() << std::endl;

        // --- remove_all for recursive deletion ---
        std::cout << "\n=== remove_all ===" << std::endl;
        fs::create_directories(base / "tree" / "sub1");
        fs::create_directories(base / "tree" / "sub2");
        { std::ofstream(base / "tree" / "a.txt") << "a"; }
        { std::ofstream(base / "tree" / "sub1" / "b.txt") << "b"; }
        { std::ofstream(base / "tree" / "sub2" / "c.txt") << "c"; }

        std::uintmax_t count = fs::remove_all(base / "tree");
        std::cout << "Entries removed: " << count << std::endl;
        std::cout << "tree exists: " << fs::exists(base / "tree") << std::endl;

        // --- remove_all on non-existent ---
        std::cout << "\n=== remove_all non-existent ===" << std::endl;
        count = fs::remove_all(base / "ghost");
        std::cout << "Removed: " << count << std::endl;

        // Cleanup remaining
        fs::remove_all(base);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output:
=== Remove a file ===
Exists before: 1
remove() returned: 1
Exists after:  0

=== Remove non-existent ===
remove() returned: 0 (false = didn't exist)

=== Remove empty directory ===
Removed empty dir: 1

=== Remove non-empty directory ===
Error: Directory not empty

=== remove_all ===
Entries removed: 6
tree exists: 0

=== remove_all non-existent ===
Removed: 0
*/
