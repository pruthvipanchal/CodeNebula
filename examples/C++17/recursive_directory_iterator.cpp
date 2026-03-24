// CodeNebula - C++17 Example: std::filesystem::recursive_directory_iterator
// Compile: g++ -std=c++17 -Wall -Wextra -o example recursive_directory_iterator.cpp -lstdc++fs

// recursive_directory_iterator traverses a directory tree recursively,
// visiting all files and subdirectories at every nesting level.

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int main() {
    try {
        // Setup: create a nested directory structure
        fs::path base = fs::temp_directory_path() / "cn_recur_iter";
        fs::create_directories(base / "src" / "core");
        fs::create_directories(base / "include");
        { std::ofstream(base / "README.md") << "readme"; }
        { std::ofstream(base / "src" / "main.cpp") << "main"; }
        { std::ofstream(base / "src" / "core" / "engine.cpp") << "engine"; }
        { std::ofstream(base / "include" / "header.h") << "header"; }

        // --- Basic recursive iteration ---
        std::cout << "=== Recursive traversal ===" << std::endl;
        for (const auto& entry : fs::recursive_directory_iterator(base)) {
            std::string indent(entry.depth() * 2, ' ');
            std::cout << indent << entry.path().filename().string()
                      << (entry.is_directory() ? "/" : "") << std::endl;
        }

        // --- Depth information ---
        std::cout << "\n=== Depth info ===" << std::endl;
        for (auto it = fs::recursive_directory_iterator(base);
             it != fs::recursive_directory_iterator(); ++it) {
            std::cout << "depth=" << it.depth() << " : "
                      << it->path().filename().string() << std::endl;
        }

        // --- Count files vs directories ---
        std::cout << "\n=== Statistics ===" << std::endl;
        int files = 0, dirs = 0;
        for (const auto& entry : fs::recursive_directory_iterator(base)) {
            if (entry.is_regular_file()) ++files;
            else if (entry.is_directory()) ++dirs;
        }
        std::cout << "Total files: " << files << std::endl;
        std::cout << "Total directories: " << dirs << std::endl;

        // --- Disable recursion on specific directories ---
        std::cout << "\n=== Skip recursion into 'src' ===" << std::endl;
        for (auto it = fs::recursive_directory_iterator(base);
             it != fs::recursive_directory_iterator(); ++it) {
            if (it->is_directory() && it->path().filename() == "src") {
                std::cout << "[skipping] " << it->path().filename().string() << "/" << std::endl;
                it.disable_recursion_pending();
            } else {
                std::cout << it->path().filename().string() << std::endl;
            }
        }

        // Cleanup
        fs::remove_all(base);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}

/*
Expected output (order may vary by OS):
=== Recursive traversal ===
README.md
include/
  header.h
src/
  core/
    engine.cpp
  main.cpp

=== Depth info ===
depth=0 : README.md
depth=0 : include
depth=1 : header.h
depth=0 : src
depth=1 : core
depth=2 : engine.cpp
depth=1 : main.cpp

=== Statistics ===
Total files: 4
Total directories: 3

=== Skip recursion into 'src' ===
README.md
include
header.h
[skipping] src/
*/
