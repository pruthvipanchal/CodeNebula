// CodeNebula - C++17 Example: std::filesystem::rename
// Compile: g++ -std=c++17 -Wall -Wextra -o example rename.cpp -lstdc++fs

// std::filesystem::rename moves or renames a file or directory. If the
// destination exists: for files it replaces; for directories behavior is OS-defined.

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void list_dir(const fs::path& dir) {
    for (const auto& entry : fs::directory_iterator(dir)) {
        std::cout << "  " << entry.path().filename().string() << std::endl;
    }
}

int main() {
    try {
        fs::path base = fs::temp_directory_path() / "cn_rename_test";
        fs::create_directories(base);

        // --- Rename a file ---
        std::cout << "=== Rename a file ===" << std::endl;
        fs::path old_file = base / "old_name.txt";
        fs::path new_file = base / "new_name.txt";
        { std::ofstream(old_file) << "rename test content"; }
        std::cout << "Before:" << std::endl;
        list_dir(base);

        fs::rename(old_file, new_file);
        std::cout << "After rename:" << std::endl;
        list_dir(base);
        std::cout << "Old exists: " << fs::exists(old_file) << std::endl;
        std::cout << "New exists: " << fs::exists(new_file) << std::endl;

        // --- Rename (move) to a subdirectory ---
        std::cout << "\n=== Move file to subdirectory ===" << std::endl;
        fs::path subdir = base / "dest";
        fs::create_directory(subdir);
        fs::path moved = subdir / "moved.txt";
        fs::rename(new_file, moved);
        std::cout << "File moved to: " << moved.filename() << std::endl;
        std::cout << "Exists in dest: " << fs::exists(moved) << std::endl;

        // --- Rename a directory ---
        std::cout << "\n=== Rename a directory ===" << std::endl;
        fs::path old_dir = base / "old_dir";
        fs::path new_dir = base / "new_dir";
        fs::create_directory(old_dir);
        { std::ofstream(old_dir / "inside.txt") << "inside"; }
        fs::rename(old_dir, new_dir);
        std::cout << "old_dir exists: " << fs::exists(old_dir) << std::endl;
        std::cout << "new_dir exists: " << fs::exists(new_dir) << std::endl;
        std::cout << "Contents of new_dir:" << std::endl;
        list_dir(new_dir);

        // --- Rename replaces existing file ---
        std::cout << "\n=== Replace existing file ===" << std::endl;
        fs::path a = base / "a.txt";
        fs::path b = base / "b.txt";
        { std::ofstream(a) << "content A"; }
        { std::ofstream(b) << "content B"; }
        fs::rename(a, b);  // b is replaced with a's content
        std::cout << "a exists: " << fs::exists(a) << std::endl;
        std::cout << "b exists: " << fs::exists(b) << std::endl;
        std::ifstream ifs(b);
        std::string content;
        std::getline(ifs, content);
        std::cout << "b content: \"" << content << "\"" << std::endl;

        // --- Error code variant ---
        std::cout << "\n=== Error handling ===" << std::endl;
        std::error_code ec;
        fs::rename(base / "nonexistent", base / "target", ec);
        std::cout << "Rename nonexistent: " << ec.message() << std::endl;

        // Cleanup
        fs::remove_all(base);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output:
=== Rename a file ===
Before:
  old_name.txt
After rename:
  new_name.txt
Old exists: 0
New exists: 1

=== Move file to subdirectory ===
File moved to: moved.txt
Exists in dest: 1

=== Rename a directory ===
old_dir exists: 0
new_dir exists: 1
Contents of new_dir:
  inside.txt

=== Replace existing file ===
a exists: 0
b exists: 1
b content: "content A"

=== Error handling ===
Rename nonexistent: No such file or directory
*/
