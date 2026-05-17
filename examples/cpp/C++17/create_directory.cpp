// CodeNebula - C++17 Example: std::filesystem::create_directory
// Compile: g++ -std=c++17 -Wall -Wextra -o example create_directory.cpp -lstdc++fs

// create_directory creates a single directory; create_directories creates
// nested directories (like mkdir -p). Both return whether a directory was created.

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    try {
        fs::path base = fs::temp_directory_path() / "cn_create_dir";

        // --- Create a single directory ---
        std::cout << "=== create_directory ===" << std::endl;
        bool created = fs::create_directory(base);
        std::cout << "Created '" << base.filename() << "': " << created << std::endl;

        // Creating again returns false (already exists)
        created = fs::create_directory(base);
        std::cout << "Created again: " << created << " (already exists)" << std::endl;

        // --- Create nested directories ---
        std::cout << "\n=== create_directories ===" << std::endl;
        fs::path nested = base / "a" / "b" / "c";
        created = fs::create_directories(nested);
        std::cout << "Created 'a/b/c': " << created << std::endl;
        std::cout << "Exists: " << fs::exists(nested) << std::endl;

        // --- Verify the hierarchy ---
        std::cout << "\n=== Verify hierarchy ===" << std::endl;
        std::cout << "a exists:     " << fs::exists(base / "a") << std::endl;
        std::cout << "a/b exists:   " << fs::exists(base / "a" / "b") << std::endl;
        std::cout << "a/b/c exists: " << fs::exists(nested) << std::endl;

        // --- create_directory with error_code ---
        std::cout << "\n=== Error code variant ===" << std::endl;
        std::error_code ec;
        fs::create_directory(base / "safe_dir", ec);
        std::cout << "Created with ec: " << (!ec ? "success" : ec.message()) << std::endl;

        // --- create_directory with attributes from existing dir ---
        std::cout << "\n=== Copy attributes ===" << std::endl;
        fs::path attr_dir = base / "with_attrs";
        created = fs::create_directory(attr_dir, base);
        std::cout << "Created with attributes from parent: " << created << std::endl;

        // --- Show what was created ---
        std::cout << "\n=== Contents of base ===" << std::endl;
        for (const auto& entry : fs::directory_iterator(base)) {
            std::cout << "  " << entry.path().filename().string()
                      << (entry.is_directory() ? "/" : "") << std::endl;
        }

        // Cleanup
        fs::remove_all(base);
        std::cout << "\nCleaned up: " << !fs::exists(base) << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output:
=== create_directory ===
Created 'cn_create_dir': 1
Created again: 0 (already exists)

=== create_directories ===
Created 'a/b/c': 1
Exists: 1

=== Verify hierarchy ===
a exists:     1
a/b exists:   1
a/b/c exists: 1

=== Error code variant ===
Created with ec: success

=== Copy attributes ===
Created with attributes from parent: 1

=== Contents of base ===
  a/
  safe_dir/
  with_attrs/

Cleaned up: 1
*/
